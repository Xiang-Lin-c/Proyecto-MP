#pragma once
#include <string>
#include <iostream>

using namespace std;

class Posicio
{

public:

    Posicio() : m_fila(0), m_columna(0) {}
    Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}

    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }
    void setFila(int fila) { m_fila = fila; }
    void setColumna(int columna) { m_columna = columna; }
    string toString() const;
    void fromString(const string& pos);
    bool operator==(const Posicio& posicio) const;
    void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, Posicio& posicio);
    void escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio);
    ifstream& operator>>(ifstream& fitxer, Posicio& posicio);
    ofstream& operator<<(ofstream& fitxer, const Posicio& posicio);
private:
    int m_fila;
    int m_columna;



};
