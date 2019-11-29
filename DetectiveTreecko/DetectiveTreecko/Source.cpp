#include "Controller.h"
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
	c = new Controller("C:\\Program Files (x86)");
	c->createTrees();
	c->menu();
	delete c;
	return 0;
}
