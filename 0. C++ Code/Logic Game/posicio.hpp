
#ifndef POSICIO_H
#define POSICIO_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

const int N_FILES = 8;
const int N_COLUMNES = 8;

using namespace std;

class Posicio
{

public:

    Posicio() : m_fila(-1), m_columna(-1), m_captura(false) {};
    Posicio(const string& pos);
    Posicio(int fila, int columna) : m_fila(fila), m_columna(columna), m_captura(false) {};

    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }
    void setFila(int fila) { m_fila = fila; }
    void setColumna(int columna) { m_columna = columna; }
    void fromString(const string& pos);
    string toString() const;
    bool operator==(const Posicio& posicio) const;
    void setCaptura() { m_captura = true; }
    bool getCaptura() const { return m_captura; }
private:
    int m_fila;
    int m_columna;
    bool m_captura;
};


ostream& operator<<(ostream& out, const Posicio& posicio);

#endif