#ifndef FITXA_H
#define FITXA_H

#include "posicio.hpp"
#include "Moviment.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
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
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio) : m_tipus(tipus), m_color(color), m_posicio(posicio) {
    }

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Posicio getPosicio() const;

    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(Posicio posicio);


    void netejaMovimentsValids();
    void afegeixMovimentValid(Moviment& moviment);
    int getNumMoviments() const;
    bool esPosicioVisitada(const Posicio& pos) const;
    int getnumDamesCapturades(int index) const;
    void afegirCaptura(Posicio pos);
    void afegirCapturaDama();
    void afegirPosicionsPossibles(const Posicio& pos);

    Moviment getMovimentValid(int index) const;
    bool esMovimentValid(const Posicio& posicio) const;
    void convertirDama();
    bool esBuida() const;
    bool esDama() const;
    Moviment getMovimentActual() const;
private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Posicio m_posicio;
    vector <Posicio> m_possicionsPosibles;
    vector<Moviment> m_movimentsValids;
};

#endif