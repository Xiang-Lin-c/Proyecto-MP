#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "Posicio.h"
#include "Tauler.h"
#include <iostream>
using namespace std;

const int MAX_PASSOS = 12;
const int MAX_CAPTURES = 12; 

class Moviment
{
private:
    Posicio trajecte[MAX_PASSOS];       
    int nPassos;                        
    Posicio fitxesCapturades[MAX_CAPTURES]; 
    int nCaptures;                      
    bool captura;                       
    TipusFitxa tipusFitxa;              

public:
    
    Moviment() : nPassos(0), nCaptures(0), captura(false) {};
    Moviment(const Posicio& inici, TipusFitxa tipus);

    
    void afegirPosicio(const Posicio& pos); 
    void eliminarUltimaPosicio();
    void netejar();        
    void afegirFitxaCapturada(const Posicio& pos); 
    
    Posicio inici() const; 
    Posicio fi() const;
   
    int getNumPassos() const {return nPassos; };
    int getNumCaptures() const { return nCaptures; };
    bool esCaptura() const { return captura; };

    
    bool esValid(const Tauler& tauler) const;
    bool posicioValida(const Posicio& pos, const Tauler& tauler) const;

    
    Moviment auxMoviment() const;

    bool operator==(const Moviment& altre) const;
};

#endif
