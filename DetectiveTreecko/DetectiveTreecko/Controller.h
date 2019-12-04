#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS
#include <experimental/filesystem>
#include <filesystem>
#include "AVLTree.h"
#include "Fichero.h"
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std::experimental::filesystem;
using namespace std::chrono_literals;
class Controller {
	AVLTree<Fichero*, string, nullptr> *ficherosPorNombre;
	AVLTree<Fichero*, string, nullptr> *ficherosPorExtension;
	AVLTree<Fichero*, double, 0> *ficherosPorTamanio;
	AVLTree<Fichero*, string, nullptr> *ficherosPorFecha;
	AVLTree<Fichero*, string, nullptr> *ficherosPorNombreal;
	AVLTree<Fichero*, string, nullptr> *ficherosPorExtensional;
	string pathInicial;
	string Fecha(string aux, string aux2, string aux3) {
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
		else if (aux2 == "Dec")  aux2 = "12";

		if (aux3 == " 1") aux3 = "01";
		else if (aux3 == " 2")  aux3 = "02";
		else if (aux3 == " 3")  aux3 = "03";
		else if (aux3 == " 4")  aux3 = "04";
		else if (aux3 == " 5")  aux3 = "05";
		else if (aux3 == " 6")  aux3 = "06";
		else if (aux3 == " 7")  aux3 = "07";
		else if (aux3 == " 8")  aux3 = "08";
		else if (aux3 == " 9")  aux3 = "09";

		string devolver = aux + '\\' + aux2 + '\\' + aux3;
		return devolver;
	}
	void MostrarCantidad(vector<Fichero*>* aux, function<void(Fichero*)> prnt) {
		cout << "Cantidad de Ficheros encontrados: " << aux->size() << endl;
		vector<Fichero*> r1 = *aux;
		int64_t n = r1.size();
		for (int64_t i = 0; i < n; i++) {
			prnt(r1[i]); 
		}
	}
	
public:
	Controller(string pathInicial) { this->pathInicial = pathInicial; }
	void readDirectory(string path) {
		for (const auto& entry : directory_iterator(path)) {
			if (is_directory(entry.path())) {
				readDirectory(entry.path().string()); 
			}
			else {
				Fichero *f = new Fichero();
				f->SetPath(entry.path().string());
				f->SetNombre(entry.path().filename().string());
				f->SetExtension(entry.path().extension().string());
				f->SetSize(file_size(entry.path())*0.001);
				f->SetNombreal(entry.path().filename().string());
				f->SetExtensional(entry.path().extension().string());
	
				f->SetExtension(f->GetExtension().erase(0,1));

				size_t lenght1 = f->GetNombreal().length();
				string nombrealaux = f->GetNombreal();
				size_t pointpos = nombrealaux.find(".");
				if (pointpos != -1) {
					nombrealaux.erase(pointpos, lenght1-1);
				}
				f->SetNombreal(nombrealaux);

				string toswap1 = f->GetNombreal();
				reverse(toswap1.begin(), toswap1.end());
				f->SetNombreal(toswap1);

				string toswap2 = f->GetExtensional();
				reverse(toswap2.begin(), toswap2.end());
				f->SetExtensional(toswap2);

				auto ftime = last_write_time(entry.path());
				time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
				f->SetFecha(asctime(localtime(&cftime)));
				string aux = f->GetFecha().substr(20, 4);
				string aux2 = f->GetFecha().substr(4, 3);
				string aux3 = f->GetFecha().substr(8, 2);

				f->SetFecha(Fecha(aux, aux2, aux3));
				
				ficherosPorExtension->Add(f);
				ficherosPorTamanio->Add(f);
				ficherosPorFecha->Add(f);
				ficherosPorNombre->Add(f);
				ficherosPorNombreal->Add(f);
				ficherosPorExtensional->Add(f);
			}
		}
	}
	void createTrees() {
		auto comparableByname = [](Fichero* f) { return f->GetNombre(); };
		ficherosPorNombre = new AVLTree<Fichero*, string, nullptr>(comparableByname);

		auto comparableByExt = [](Fichero* f) { return f->GetExtension(); };
		ficherosPorExtension = new AVLTree<Fichero*, string, nullptr>(comparableByExt);

		auto comparableByTam = [](Fichero* f) { return f->GetSize(); };
		ficherosPorTamanio = new AVLTree<Fichero*, double, 0>(comparableByTam);

		auto comparableByFecha = [](Fichero* f) { return f->GetFecha(); };
		ficherosPorFecha = new AVLTree<Fichero*, string, nullptr>(comparableByFecha);

		auto comparableBynameal = [](Fichero* f) {return f->GetNombreal(); };
		ficherosPorNombreal = new AVLTree<Fichero*, string, nullptr>(comparableBynameal);

		auto comparableByExtal = [](Fichero* f) {return f->GetExtensional(); };
		ficherosPorExtensional = new AVLTree<Fichero*, string, nullptr>(comparableByExtal);

		readDirectory(pathInicial);
	}
	void menu() {
		auto prnt = [](Fichero* f) { cout << f->GetNombre() << " - " << f->GetSize() << "KB - " << f->GetFecha() <<"\n"; };
		auto startWith = [](Fichero* f, string startWith) { return f->GetNombre().find(startWith) == 0; };
		auto startWith2 = [](Fichero* f, string startWith2) { return f->GetExtension().find(startWith2) == 0; };
		auto finitationWith = [](Fichero* f, string startWith) { return f->GetNombreal().find(startWith) == 0; };
		auto finitationWith2 = [](Fichero* f, string startWith2) { return f->GetExtensional().find(startWith2) == 0; };
		auto FunMay = [](Fichero* f, double eux) { return f->GetSize() > eux; };
		auto FunMen = [](Fichero* f, double eux) { return f->GetSize() < eux; };
		auto FunIgu = [](Fichero* f, double eux) { return f->GetSize() == eux; };
				
		auto FunIguDia = [](Fichero* f, string eux) { return f->GetFecha().substr(8,9) == eux; };
		auto FunIguMes = [](Fichero* f, string eux) { return f->GetFecha().substr(5,2) == eux; };
		auto FunIguAño = [](Fichero* f, string eux) { return f->GetFecha().substr(0,4) == eux; };
		
		auto contain = [](Fichero* f, string s) { return f->GetNombre().find(s) != -1; };
		auto contain2 = [](Fichero* f, string s) { return f->GetExtension().find(s) != -1; };

		int option = -1;
		while (option != 0) {
			cout << "F.I.F.I Explorer" << endl;
			cout << "1. Buscar por Nombre\n" << "2. Buscar por tamanio\n" << "3. Buscar por extension\n" << "4. Buscar por fecha\n" << "5. Ordenar\n";
			cin >> option;
			string searchVal;
			string searchVal2;
			string theday;
			string themonth;
			string theyear;
			switch (option) {
			case 1:
				int buscarOpcion;
				cout << "1. Inicia con:\n" << "2. Termina con:\n" << "3. Contiene :\n"; cin >> buscarOpcion;
				cout << "Ingrese la valor a buscar \n"; cin >> searchVal;
				if (buscarOpcion == 1) {
					vector<Fichero*>* result = ficherosPorNombre->findStarWith(searchVal, startWith);
					MostrarCantidad(result, prnt);
				}
				else if (buscarOpcion == 2) {
					reverse(searchVal.begin(), searchVal.end());
					vector<Fichero*>* result = ficherosPorNombreal->findStarWith(searchVal, finitationWith);
					MostrarCantidad(result, prnt);
				}
				else if (buscarOpcion == 3) {
					vector<Fichero*>* result = ficherosPorNombre->findContain(searchVal, contain);
					MostrarCantidad(result, prnt);
				}
				break;
			case 2:
				int buscarOp, eux;
				cout << "1. Mayor que:\n" << "2. Menor que:\n" << "3. Igual que:\n";
				cin >> buscarOp;
				cout << "Ingrese la valor a buscar \n";
				cin >> eux;
				if (buscarOp == 1) {
					vector<Fichero*>* result = ficherosPorTamanio->Comp(eux, FunMay);
					MostrarCantidad(result, prnt);
				}
				else if(buscarOp == 2) {
					vector<Fichero*>* result = ficherosPorTamanio->Comp(eux, FunMen);
					MostrarCantidad(result, prnt);
				}
				else if (buscarOp == 3) {
					vector<Fichero*> *result = ficherosPorTamanio->Comp(eux, FunIgu);
					MostrarCantidad(result, prnt);
				}
				break;
			case 3:
				int buscarOpcion2;
				cout << "1. Inicia con:\n" << "2. Termina con:\n" << "3. Contiene :\n"; cin >> buscarOpcion2;
				cout << "Ingrese la valor a buscar \n"; cin >> searchVal2;
				if (buscarOpcion2 == 1) {
					vector<Fichero*>* result = ficherosPorExtension->findStarWith(searchVal2, startWith2);
					MostrarCantidad(result, prnt);
				}
				else if (buscarOpcion2 == 2) {
					reverse(searchVal2.begin(), searchVal2.end());
					vector<Fichero*>* result = ficherosPorExtensional->findStarWith(searchVal2, finitationWith2);
					MostrarCantidad(result, prnt);
				}
				else if (buscarOpcion2 == 3) {
					vector<Fichero*>* result = ficherosPorExtension->findContain(searchVal2, contain2);
					MostrarCantidad(result, prnt);
				}
				break;
			case 4:
				int elegir;
				cout << "1. Dia:\n" << "2. Mes:\n" << "3. Anio:\n"; cin >> elegir;
				if (elegir == 1) {
					cout << "Ingresa el dia en numero de dos digitos: "; cin >> theday;
					vector<Fichero*> *result = ficherosPorFecha->Comp2(theday, FunIguDia);
					MostrarCantidad(result, prnt);
				}
				else if (elegir == 2) {
					cout << "Ingresa el mes en numero de dos digitos: "; cin >> themonth;
					vector<Fichero*> *result = ficherosPorFecha->Comp2(themonth, FunIguMes);
					MostrarCantidad(result, prnt);
				}
				else if (elegir == 3) {
					cout << "Ingresa el anio: "; cin >> theyear;
					vector<Fichero*> *result = ficherosPorFecha->Comp2(theyear, FunIguAño);
					MostrarCantidad(result, prnt);
				}
				break;
			case 5:
				int opc, opc2;
				cout << "Ordenar por:\n" << "1. Nombre\n" << "2. Tamanio\n" << "3. Extension\n" << "4. Fecha\n"; cin >> opc;
				cout << "1. Ascendente\n" << "2. Descendente\n"; cin >> opc2;
				if (opc == 1) {
					if (opc2 == 1) {
						ficherosPorNombre->inorder(prnt);
					}
					else {
						ficherosPorNombre->reversedInorder(prnt);
					}
				}
				else if (opc == 2) {
					if (opc2 == 1) {
						ficherosPorTamanio->inorder(prnt);
					}
					else {
						ficherosPorTamanio->reversedInorder(prnt);
					}
				}
				else if (opc == 3) {
					if (opc2 == 1) {
						ficherosPorExtension->inorder(prnt);
					}
					else {
						ficherosPorExtension->reversedInorder(prnt);
					}
				}
				else if (opc == 4) {
					if (opc2 == 1) {
						ficherosPorFecha->inorder(prnt);
					}
					else {
						ficherosPorFecha->reversedInorder(prnt);
					}
				}
				break;
			default:
				break;
			}
			system("pause");
			system("CLS");
		}		
	}
};