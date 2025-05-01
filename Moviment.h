#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.hpp"
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
	int nDamaCapturada;                 // Número de damas capturadas
    bool m_captura;                       // Indica si el movimiento implica capturas

public:
    
	Moviment() : nPassos(0), nCaptures(0), m_captura(false) {};

    
    void afegirPosicio(const Posicio& pos); 
    void eliminarUltimaPosicio();
    void netejar();        
    void afegirFitxaCapturada( Posicio& pos); 
	void afegirDamaCapturada(); // Añadir dama capturada
    
    Posicio inici() const;
    Posicio fi() const;       
  
    int getNumPassos() const;
    int getNumCaptures() const;
    bool esCaptura() const;
	Posicio getPosicio(int index) const;
    

    int getNumPassos() const;
    int getNumCaptures() const;
	int getNumDamaCapturada() const; 
    int getEstatCaptures(int index) const;
	Posicio getFitxaCapturada(int index) const;       // Devuelve la posición de una ficha capturada
    bool esCaptura() const;                         // Indica si el movimiento es una captura
	Posicio getPosicio(int index) const;             // Devuelve una posición específica del movimiento


    void eliminarFitxaCapturada(const Posicio& pos);

    Moviment auxMoviment() const;

};

#endif
