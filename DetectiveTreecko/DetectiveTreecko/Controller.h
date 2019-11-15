#pragma once
#include <filesystem> // investigar. tiene funciones que permite iterar carpetas y archivos, extraer el tamanio de un archivo, etc
#include "AVLTree.h"
#include "Fichero.h"
#include <chrono>
#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;
using namespace std::experimental::filesystem; // libreria propuestra por c++, aun experimental
using namespace std::chrono_literals;
class Controller { // creamos los arboles por nombre, extension y tamanio
	AVLTree<Fichero*, string, nullptr> *ficherosPorNombre;
	AVLTree<Fichero*, string, nullptr> *ficherosPorExtension;
	AVLTree<Fichero*, long, 0> *ficherosPorTamanio;
	AVLTree<Fichero*, string, nullptr> *ficherosPorFecha;
	string pathInicial; // este es el C\\ que le pasan por parametro desde el source
public:

	string Fecha(string aux, string aux2, string aux3)
	{ 
	
			if (aux2 == "Jan") aux2 = "01";
			else if (aux2 == "Feb")  aux2 = "02";
			else if (aux2 == "Mar")  aux2 = "03";
			else if (aux2 == "Apr")  aux2 = "04";
			else if (aux2 == "May")  aux2 = "05";
			else if (aux2 == "Jun")  aux2 = "06";
			else if (aux2 == "Jul")  aux2 = "07";
			else if (aux2 == "Aug")  aux2 = "08";
			else if (aux2 == "Sep")  aux2 = "09";
			else if (aux2 == "Oct")  aux2 = "10";
			else if (aux2 == "Nov")  aux2 = "11";
			else if (aux2 == "Dic")  aux2 = "12";

			if (aux3 == " 1") aux3 = "01";
			else if (aux3 == " 2")  aux3 = "02";
			else if (aux3 == " 3")  aux3 = "03";
			else if (aux3 == " 4")  aux3 = "04";
			else if (aux3 == " 5")  aux3 = "05";
			else if (aux3 == " 6")  aux3 = "06";
			else if (aux3 == " 7")  aux3 = "07";
			else if (aux3 == " 8")  aux3 = "08";
			else if (aux3 == " 9")  aux3 = "09";


		string devolver = aux + '\\' + aux2 +'\\' + aux3;
		return devolver;
	}

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

				auto ftime = last_write_time(entry.path());
				time_t cftime = decltype(ftime)::clock::to_time_t(ftime);

				f->fecha = asctime(localtime(&cftime));



				string aux = f->fecha.substr(20, 4);
				string aux2 = f->fecha.substr(4, 3);
				string aux3 = f->fecha.substr(8, 2);

				f->fecha = Fecha(aux, aux2, aux3);
				
				ficherosPorNombre->add(f);
				ficherosPorExtension->add(f);
				ficherosPorTamanio->add(f);
				ficherosPorFecha->add(f);
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

		auto comparableByFecha = [](Fichero* f) { return f->fecha; };
		ficherosPorFecha = new AVLTree<Fichero*, string, nullptr>(comparableByFecha);

		readDirectory(pathInicial);
	}
	void menu() {
		auto prnt = [](Fichero* f) { cout << f->nombre << " - " << f->size << " - " << f->fecha << "\n"; };
		auto startWith = [](Fichero* f, string startWith) { return f->nombre.find(startWith) == 0; };
		int option = -1;
		while (option != 0) {
			cout << "1. Ordenar Ascendente por Nombre\n" << "2. Ordenar Descendente por Nombres\n" << "3. Buscar por Nombre\n";
			cin >> option;
			string searchVal;
			switch (option) {
			case 1:
				ficherosPorFecha->inorder(prnt);
				break;
			case 2:
				ficherosPorFecha->reversedInorder(prnt);
				break;
			case 3:
				int buscarOpcion;
				cout << "1. Inicia con:\n" << "2. Termina con:\n" << "3. Igual a:\n" << "4. Mayor a\n" << "5. Menor a\n";
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
				else if (buscarOpcion == 4) {
					cout << "Ingrese al valor a commparar: " << endl;
					long eux;
					cin >> eux;
					Fichero *f = ficherosPorTamanio->find(eux);
				// y devoler todos los hijos derechos de este fichero 
				}
			default:
				break;
			}
			system("pause");
			system("CLS");
		}
		cout << "--------------------==\n";
	}
};