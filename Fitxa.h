#ifndef FITXA_H
#define FITXA_H

#include "Posicio.h"
#include "Moviment.h"
#include <iostream>
#include <string>
using namespace std;

const int MAX_MOVIMENTS = 20;

typedef enum TipusFitxa
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
};

typedef enum ColorFitxa
{
    COLOR_NEGRE,
    COLOR_BLANC,
};

class Fitxa
{
public:
    Fitxa() : m_tipus(TIPUS_EMPTY) {};
    Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio);

    // Getters
    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Posicio getPosicio() const;

    // Setters
    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(Posicio posicio);

    // M�todos para gestionar movimientos v�lidos
    void generarMovimentsValids(const Tauler& tauler); // Genera movimientos v�lidos seg�n el tipo de ficha
    void netejaMovimentsValids();                     // Limpia los movimientos v�lidos
    void afegeixMovimentValid(const Moviment& moviment); // A�ade un movimiento v�lido
    int getNumMoviments() const;                      // Devuelve el n�mero de movimientos v�lidos
    Moviment getMovimentValid(int index) const;       // Obtiene un movimiento v�lido por �ndice

    // M�todos adicionales
    void convertirADama();                            // Convierte la ficha en dama
    bool esBuida() const;                             // Verifica si la ficha est� vac�a
    bool esDama() const;                              // Verifica si la ficha es una dama

private:
    TipusFitxa m_tipus;                               // Tipo de ficha (normal, dama, vac�a)
    ColorFitxa m_color;                               // Color de la ficha (negro, blanco, vac�o)
    Posicio m_posicio;                                // Posici�n actual de la ficha
    Moviment m_movimentsValids[MAX_MOVIMENTS];        // Movimientos v�lidos de la ficha
    int m_numMoviments;                               // N�mero de movimientos v�lidos
};

#endif
