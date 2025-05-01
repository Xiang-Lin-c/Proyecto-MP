#ifndef FITXA_H
#define FITXA_H

#include "posicio.hpp"
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

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    Posicio getPosicio() const;

    void setTipus(TipusFitxa tipus);
    void setColor(ColorFitxa color);
    void setPosicio(Posicio posicio);

    
    void netejaMovimentsValids();
    void afegeixMovimentValid( Moviment& moviment); 
	void ModificaUltimMoviment( Posicio& posicio);
    int getNumMoviments() const;

	int getnumDamesCapturades(int index) const; 
    void afegirCaptura(Posicio& pos);
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
