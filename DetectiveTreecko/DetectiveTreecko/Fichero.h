#pragma once
#include <string>
#include <cstdint>
#include <stdint.h>
typedef long long int li;
using namespace std;
class Fichero {
	string nombre;
	string path;
	string extension;
	string fecha;
	double size;
	string nombreal;
	string extensional; 
public:
	void SetNombre(string nombre) { this->nombre = nombre; }
	string GetNombre() { return nombre; }
	void SetPath(string path) { this->path = path; }
	string GetPath() { return path; }
	void SetExtension(string extension) { this->extension = extension; }
	string GetExtension() { return extension; }
	void SetFecha(string fecha) { this->fecha = fecha; }
	string GetFecha() { return fecha; }
	void SetSize(double size) { this->size = size; }
	double GetSize() { return size; }
	void SetNombreal(string nombreal) { this->nombreal = nombreal; }
	string GetNombreal() { return nombreal; }
	void SetExtensional(string extensional) { this->extensional = extensional; }
	string GetExtensional() { return extensional; }
};