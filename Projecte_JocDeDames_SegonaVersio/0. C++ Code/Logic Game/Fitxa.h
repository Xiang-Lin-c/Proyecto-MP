
#ifndef FITXA_H
#define FITXA_H

#include "posicio.hpp"
#include "Moviment.h"
#include <iostream>
#include <string>
using namespace std;

const int MAX_MOVIMENTS = 20;

enum TipusFitxa
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
};

enum ColorFitxa
{
    COLOR_NEGRE,
    COLOR_BLANC,
    COLOR_BUIT
};

class Fitxa
{
public:
    Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_BUIT) {};
    Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio) : m_tipus(tipus), m_color(color), m_posicio(posicio), m_numMoviments(0) {
    }

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Posicio getPosicio() const;

    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(Posicio posicio);


    void netejaMovimentsValids();
    void afegeixMovimentValid(Moviment& moviment);
    void ModificaUltimMoviment(Posicio& posicio);
    int getNumMoviments() const;

    int getnumDamesCapturades(int index) const;
    void afegirCaptura(Posicio pos);
    void ModificaUltimMovimentCaptura(Posicio posicio);
    void ModificaUltimMovimentCapturaDama(Posicio posicio);
    void afegirCapturaDama();
    Moviment getMovimentValid(int index) const;

    void convertirDama();
    bool esBuida() const;
    bool esDama() const;

private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Posicio m_posicio;
    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_numMoviments;
};

#endif