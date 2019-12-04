#include "Controller.h"
int main() {
	Controller* c;
	int* opcion = new int;
	string direccion;
	cout << "Path inicial:\n" << "1. C:\\" << endl << "2. D:\\" << endl << "3. Escribir otra ruta" << endl;
	cin >> *opcion;
	if (*opcion == 1) {
		c = new Controller("C:\\");
	}
	else if (*opcion == 2) {
		c = new Controller("D:\\");
	}
	else if (*opcion == 3) {
		cout << "Escribe la ruta: "; cin.ignore(); getline(cin, direccion);
		c = new Controller(direccion); 
	}
	delete opcion;
	c->createTrees();
	c->menu();
	delete c;
	return 0;
}