#include "Controller.h"
// Por ahora lo que tenemos es la clase AVLTree, el arbol balanceado que hizo el inigualable Canaval
// la clase fichero que contiene los atributos por los cuales se pueden ordenar los archivos
// la clase controller para construir los arboles
int main() {
	Controller* c = new Controller("D:\\SEMINARIO");
	c->createTrees();
	c->menu();
	delete c;
	return 0;
}