#pragma once
#include <string>
using namespace std;
class Fichero {
	string nombre;
	string path;
	string extension;
	string fecha;
	long size;
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
	void SetSize(long size) { this->size = size; }
	long GetSize() { return size; }
	void SetNombreal(string nombreal) { this->nombreal = nombreal; }
	string GetNombreal() { return nombreal; }
	void SetExtensional(string extensional) { this->extensional = extensional; }
	string GetExtensional() { return extensional; }
	
};