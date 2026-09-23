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

string comprimirRLE(string texto) {
    string comprimido = "";

    if (texto.length() == 0) {
        return comprimido;
    }

    int contador = 1;

    for (int i = 0; i < texto.length(); i++) {
        if (i < texto.length() - 1 && texto[i] == texto[i + 1]) {
            contador++;
        }
        else {
            comprimido = comprimido + to_string(contador);
            comprimido = comprimido + "|";
            comprimido = comprimido + texto[i];
            comprimido = comprimido + "|";

            contador = 1;
        }
    }
        return comprimido;
}
string descomprimirRLE(string comprimido) {
    string descomprimido = "";

    int i = 0;

    while (i < comprimido.length()) {
        string numero = "";

        // Lee todos los dígitos de la cantidad
        while (comprimido[i] != '|') {
            numero = numero + comprimido[i];
            i++;
        }

        int cantidad = stoi(numero);

        // Salta el primer separador |
        i++;

        // Lee el carácter que se debe repetir
        char caracter = comprimido[i];

        // Salta el carácter
        i++;

        // Salta el segundo separador |
        i++;

        // Agrega el carácter la cantidad indicada
        for (int j = 0; j < cantidad; j++) {
            descomprimido = descomprimido + caracter;
        }
    }

    return descomprimido;
}

int main() {
    string nombreArchivo;
    string textoOriginal;
    string textoComprimido;
    string textoDescomprimido;

    cout << "Ingrese el nombre del archivo de prueba:" << endl;
    getline(cin, nombreArchivo);

    try {
        textoOriginal = leerArchivo(nombreArchivo);

        cout << endl;
        cout << "---- Texto original ----" << endl;
        cout << textoOriginal << endl;

        textoComprimido = comprimirRLE(textoOriginal);

        cout << endl;
        cout << "---- Texto comprimido ----" << endl;
        cout << textoComprimido << endl;

        textoDescomprimido = descomprimirRLE(textoComprimido);

        cout << endl;
        cout << "---- Texto descomprimido ----" << endl;
        cout << textoDescomprimido << endl;

        cout << endl;

        if (textoOriginal == textoDescomprimido) {
            cout << "Verificacion correcta: el texto recuperado es igual al original."
                 << endl;
        }
        else {
            cout << "Error: el texto recuperado no coincide con el original."
                 << endl;
        }
    }
    catch (const char* mensaje) {
        cerr << mensaje << endl;
    }

    return 0;
}