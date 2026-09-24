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

struct Entry {
    int prefix;
    char c;
};

int findEntry(Entry* dict, int size, int prefix, char c) {
    for (int i = 1; i < size; i++) {
        if (dict[i].prefix == prefix && dict[i].c == c) {
            return i;
        }
    }

    return -1;
}

void compressLZ78(const char* input) {
    Entry* dict = new Entry[1000];
    int dictSize = 1;

    int currentPrefix = 0;

    cout << "Salida (indice, caracter):" << endl;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1) {
            currentPrefix = index;
        }
        else {
            cout << "(" << currentPrefix << ", " << c << ")" << endl;

            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = c;

            dictSize++;
            currentPrefix = 0;
        }
    }

    // Si al terminar queda una frase encontrada pero no impresa.
    if (currentPrefix != 0) {
        cout << "(" << currentPrefix << ", FIN)" << endl;
    }

    delete[] dict;
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

    char texto[] = "ABAABABA";

    cout << "Texto original: " << texto << endl;
    cout << endl;

    compressLZ78(texto);

    return 0;
}