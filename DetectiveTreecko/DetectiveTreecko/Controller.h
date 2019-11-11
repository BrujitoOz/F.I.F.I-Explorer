#pragma once
#include "AVLTree.h"
#include "Fichero.h"
#include <vector>
#include <iostream>
#include <filesystem> // investigar. tiene funciones que permite iterar carpetas y archivos, extraer el tamanio de un archivo, etc
using namespace std;
using namespace std::experimental::filesystem; // libreria propuestra por c++, aun experimental
class Controller { // creamos los arboles por nombre, extension y tamanio
	AVLTree<Fichero*, string, nullptr> *ficherosPorNombre;
	AVLTree<Fichero*, string, nullptr> *ficherosPorExtension;
	AVLTree<Fichero*, long, 0> *ficherosPorTamanio;
	string pathInicial; // este es el C\\ que le pasan por parametro desde el source
public:
	Controller(string pathInicial) { this->pathInicial = pathInicial; }
	void readDirectory(string path) {
		for (const auto& entry : directory_iterator(path)) {
			if (is_directory(entry.path())) {
				readDirectory(entry.path().string()); // se llama recursivamente para leer todos los archivos, incluidos los que esten dentro de otra carpeta
			}
			else {
				Fichero *f = new Fichero();
				f->path = entry.path().string();
				f->nombre = entry.path().filename().string();
				f->extension = entry.path().extension().string();
				f->size = file_size(entry.path());
				ficherosPorNombre->add(f);
				ficherosPorExtension->add(f);
				ficherosPorTamanio->add(f);
				//cout << entry.path() << endl;
			}
		}
	}
	void createTrees() {
		auto comparableByname = [](Fichero* f) { return f->nombre; };
		ficherosPorNombre = new AVLTree<Fichero*, string, nullptr>(comparableByname);

		auto comparableByExt = [](Fichero* f) { return f->extension; };
		ficherosPorExtension = new AVLTree<Fichero*, string, nullptr>(comparableByExt);

		auto comparableByTam = [](Fichero* f) { return f->size; };
		ficherosPorTamanio = new AVLTree<Fichero*, long, nullptr>(comparableByTam);

		readDirectory(pathInicial);
	}
	void menu() {
		auto prnt = [](Fichero* f) { cout << f->nombre << " - " << f->size << "\n"; };
		auto startWith = [](Fichero* f, string startWith) { return f->nombre.find(startWith) == 0; };
		int option;
		while (option != 0) {
			cout << "1. Ordenar Ascendente por Nombre\n" << "2. Ordenar Descendente por Nombres\n" << "3. Buscar por Nombre\n";
			cin >> option;
			string searchVal;
			switch (option) {
			case 1:
				ficherosPorNombre->inorder(prnt);
				break;
			case 2:
				ficherosPorNombre->reversedInorder(prnt);
				break;
			case 3:
				int buscarOpcion;
				cout << "1. Inicia con:\n" << "2. Termina con:\n" << "3. Igual a:\n";
				cin >> buscarOpcion;
				cout << "Ingrese la valor a buscar \n";
				cin >> searchVal;
				if (buscarOpcion == 3) {
					Fichero *f = ficherosPorNombre->find(searchVal);
					cout << "El Fichero se encuentra en :" << endl;
					cout << f->path << endl;
				}
				else if (buscarOpcion == 1) {
					vector<Fichero*> *result = ficherosPorNombre->findStarWith(searchVal, startWith);
					cout << "Cantidad de Ficheros encontrados:" << result->size() << endl;
					vector<Fichero*> r1 = *result;
					for (int i = 0; i < r1.size(); i++) {
						prnt(r1[i]);
					}		
				}
			default:
				break;
			}
			system("pause");
		}
		//ficherosPorExtension->inorder(prnt);
		cout << "--------------------==\n";
	}
};