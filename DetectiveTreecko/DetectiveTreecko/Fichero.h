#pragma once
#include <string>
using namespace std;
class Fichero {
public:
	// lo puse public por ahora por evitar tener que crear setters y getters para los siguientes atributos
	string nombre;
	string path;
	string extension;
	long size;
};