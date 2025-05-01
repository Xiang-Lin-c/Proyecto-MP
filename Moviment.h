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
    bool m_captura; 
    TipusFitxa tipusFitxa;
    Posicio trajecte[MAX_PASSOS]; 
    int nPassos;  
    Posicio fitxesCapturades[MAX_CAPTURES]; 
    int nCaptures;    
    int EstatCaptures[MAX_PASSOS];
	int nDamaCapturada;     
    bool m_captura;
    TipusFitxa tipusFitxa;    

public:
    
	Moviment() : nPassos(0), nCaptures(0), m_captura(false), tipusFitxa(TIPUS_EMPTY) {};
    Moviment(const Posicio& inici, TipusFitxa tipus);

    
    void afegirPosicio(const Posicio& pos); 
    void eliminarUltimaPosicio();
    void netejar();        
    void afegirFitxaCapturada(const Posicio& pos); 
	void afegirDamaCapturada(); 
    
    Posicio inici() const;
    Posicio fi() const;       
  
    int getNumPassos() const;
    int getNumCaptures() const;
    bool esCaptura() const;
	Posicio getPosicio(int index) const;
    
    bool esValid(const Tauler& tauler) const;
    bool posicioValida(const Posicio& pos, const Tauler& tauler) const;
    int getNumPassos() const;
    int getNumCaptures() const;
	int getNumDamaCapturada() const; 
    int getEstatCaptures(int index) const;
	Posicio getFitxaCapturada(int index) const; 
    bool esCaptura() const; 
	Posicio getPosicio(int index) const; 
    
    bool esValid(const Tauler& tauler) const;  
    bool posicioValida(const Posicio& pos, const Tauler& tauler) const; 

    void eliminarFitxaCapturada(const Posicio& pos);

    Moviment auxMoviment() const;

    bool operator==(const Moviment& altre) const;
};

#endif
