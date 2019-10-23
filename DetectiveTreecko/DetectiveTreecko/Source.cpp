#include <iostream>
#include <filesystem> // investigar. tiene funciones que permite iterar carpetas y archivos, extraer el tamanio de un archivo, etc

using namespace std;
using namespace std::experimental::filesystem; // libreria propuestra por c++, aun experimental

int main() {
	string path = "c:\\"; // la ruta que queremos escanear
	for (const auto & entry : directory_iterator(path)) {
		cout << entry.path() << endl;
	}

	system("pause");
	return 0;
}