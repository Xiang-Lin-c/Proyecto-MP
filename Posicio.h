#pragma once
#include <string>

using namespace std;

class Posicio
{

private:
    int m_fila;
    int m_columna;
public:

    Posicio() : m_fila(0), m_columna(0) {}
    Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}

    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }
    void setFila(int fila) { m_fila = fila; }
    void setColumna(int columna) { m_columna = columna; }


    bool operator==(const Posicio& posicio) const;
};