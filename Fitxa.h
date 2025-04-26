#ifndef FITXA_H
#define FITXA_H

#include "posicio.h"
#include "moviment.h"
#include <iostream>
#include <string>
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
    COLOR_EMPTY
};

class Fitxa {

public:
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio);
    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Moviment getMovimentValid(int index);
    int getNumMoviments();
    Posicio getPosicio() const;
    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(Posicio posicio);
    void afegeixMovimentValid(Moviment moviment);
    void netejaMovimentsValids();
    void convertirADama();
    bool esBuida() const;
private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_numMoviments;
    Posicio m_posicio;

};
#endif