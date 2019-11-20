#include "Controller.h"
// Por ahora lo que tenemos es la clase AVLTree, el arbol balanceado que hizo el inigualable Canaval
// la clase fichero que contiene los atributos por los cuales se pueden ordenar los archivos
// la clase controller para construir los arboles
int main() {
	Controller* c;
	/*int* opcion = new int;
	string escribeesta;
	cout << "Path inicial:\n " << "1. C:\\" << endl << "2. D:\\" << endl << "3. Tipear la ruta";
	cin >> *opcion;
	if (*opcion == 1) {
		c = new Controller("C:\\");
	}
	else if (*opcion == 2) {
		c = new Controller("D:\\");
	}
	else if (*opcion == 2) {
		cout << "Escribe la ruta: "; cin >> escribeesta;
		c = new Controller(escribeesta);
	}
	delete opcion;*/
	c = new Controller("C:\\test");
	c->createTrees();
	c->menu();
	delete c;
	return 0;
}