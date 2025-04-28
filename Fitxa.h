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

    // Métodos para gestionar movimientos válidos
    void generarMovimentsValids(const Tauler& tauler); // Genera movimientos válidos según el tipo de ficha
    void netejaMovimentsValids();                     // Limpia los movimientos válidos
    void afegeixMovimentValid(const Moviment& moviment); // Añade un movimiento válido
    int getNumMoviments() const;                      // Devuelve el número de movimientos válidos
    Moviment getMovimentValid(int index) const;       // Obtiene un movimiento válido por índice

    // Métodos adicionales
    void convertirADama();                            // Convierte la ficha en dama
    bool esBuida() const;                             // Verifica si la ficha está vacía
    bool esDama() const;                              // Verifica si la ficha es una dama

private:
    TipusFitxa m_tipus;                               // Tipo de ficha (normal, dama, vacía)
    ColorFitxa m_color;                               // Color de la ficha (negro, blanco, vacío)
    Posicio m_posicio;                                // Posición actual de la ficha
    Moviment m_movimentsValids[MAX_MOVIMENTS];        // Movimientos válidos de la ficha
    int m_numMoviments;                               // Número de movimientos válidos
};

#endif
