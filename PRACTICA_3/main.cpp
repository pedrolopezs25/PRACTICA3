#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string leerArchivo(string nombreArchivo) {
    ifstream archivo;
    string texto = "";
    char caracter;

    archivo.open(nombreArchivo);

    if (!archivo) {
        throw "Error en la lectura del archivo";
    }

    while (archivo.get(caracter)) {
        texto = texto + caracter;
    }

    archivo.close();

    return texto;
}

int main() {
    string nombreArchivo;
    string texto;

    cout << "Ingrese el nombre del archivo de prueba:" << endl;
    getline(cin, nombreArchivo);

    try {
        texto = leerArchivo(nombreArchivo);

        cout << endl;
        cout << "---- Texto leido del archivo ----" << endl;
        cout << texto << endl;
    }
    catch (const char* mensaje) {
        cerr << mensaje << endl;
    }

    return 0;
}