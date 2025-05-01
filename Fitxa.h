#ifndef FITXA_H
#define FITXA_H

#include "Posicio.h"
#include "Moviment.h"
#include "Tauler.h" 
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

    
    void generarMovimentsValids(const Tauler& tauler);
    void netejaMovimentsValids();
    void afegeixMovimentValid(const Moviment& moviment); 
	void ModificaUltimMoviment(const Posicio& posicio);
	void eliminarFitxaCapturada(const Posicio& pos);
    int getNumMoviments() const;
	int getnumDamesCapturades(int index) const; // Retorna el nombre de dames capturades
    void afegirCaptura(const Posicio& pos);
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
