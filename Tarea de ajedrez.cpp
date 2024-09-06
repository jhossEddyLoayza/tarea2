#include <iostream>
using namespace std;

const short FILAS = 5;
const short COLUMNAS = 5;

class Pieza {
private:
    short fila;
    short columna;

public:
    Pieza() : fila(1), columna(1) {}
    Pieza(short f, short c) : fila(f), columna(c) {}

    short getFila() const { return fila; }
    short getColumna() const { return columna; }

    void setFila(short f) { fila = f; }
    void setColumna(short c) { columna = c; }

    void verInfo() const {
        cout << "Fila: " << getFila() << ", Columna: " << getColumna() << endl;
    }

    bool esCeldaValida(short f, short c) const {
        return f >= 1 && f <= FILAS && c >= 1 && c <= COLUMNAS;
    }
};
class Peon : public Pieza {
private:
    short direccion;

public:
    Peon(short f, short c, short dir) : Pieza(f, c), direccion(dir) {}

    void avanzar() {
        short nuevaFila = getFila() + direccion;
        if (esCeldaValida(nuevaFila, getColumna())) {
            setFila(nuevaFila);
        }
        else {
            cout << "No se puede avanzar a esa posición." << endl;
        }
    }

    bool puedoIrA(short f, short c) const {
        return abs(f - getFila()) == 1 && abs(c - getColumna()) == 1;
    }
};

class Torre : public Pieza {
private:
    short numeroCuadros;

public:
    Torre(short f, short c, short numCuadros) : Pieza(f, c), numeroCuadros(numCuadros) {}

    void avanzar(short f, short c) {
        if (esCeldaValida(f, c) && (abs(f - getFila()) <= numeroCuadros || abs(c - getColumna()) <= numeroCuadros)) {
            setFila(f);
            setColumna(c);
        }
        else {
            cout << "No se puede avanzar a esa posición." << endl;
        }
    }
};

void imprimirTablero(const Peon & peon, const Torre& torre) {
    for (short i = 1; i <= FILAS; ++i) {
        for (short j = 1; j <= COLUMNAS; ++j) {
            cout << "+---";
        }
        cout << "+" << endl;

        for (short j = 1; j <= COLUMNAS; ++j) {
            if (i == peon.getFila() && j == peon.getColumna()) {
                cout << "| P ";
            }
            else if (i == torre.getFila() && j == torre.getColumna()) {
                cout << "| T ";
            }
            else {
                cout << "|   ";
            }
        }
        cout << "|" << endl;
    }

    for (short j = 1; j <= COLUMNAS; ++j) {
        cout << "+---";
    }
    cout << "+" << endl;
}

int main() {

    short filaPeon = 2, columnaPeon = 3;
    short filaTorre = 1, columnaTorre = 4;
    short destinoFilaTorre, destinoColumnaTorre;
    short moverTorre, moverPeon;

    Peon peon(filaPeon, columnaPeon, 1);
    Torre torre(filaTorre, columnaTorre, 1);

    cout << "Estado inicial del tablero:" << endl;
    imprimirTablero(peon, torre);

    while (peon.getFila() < FILAS) {
        cout << "Desea mover la torre? (si = 1, no = 0): ";
        cin >> moverTorre;

        if (moverTorre == 1) {
            cout << "Ingrese la posición de destino para la torre (fila y columna): ";
            cin >> destinoFilaTorre >> destinoColumnaTorre;
            torre.avanzar(destinoFilaTorre, destinoColumnaTorre);
        }

        cout << "Desea mover el peón? (si = 1, no = 0): ";
        cin >> moverPeon;

        if (moverPeon == 1) {
            peon.avanzar();
        }

        cout << "Estado actual del tablero:" << endl;
        imprimirTablero(peon, torre);
    }

    return 0;
}