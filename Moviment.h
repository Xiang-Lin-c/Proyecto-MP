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
    Posicio trajecte[MAX_PASSOS];       // Secuencia de posiciones del movimiento
    int nPassos;                        // Número de posiciones en el movimiento
    Posicio fitxesCapturades[MAX_CAPTURES]; // Posiciones de las fichas capturadas
    int nCaptures;                      // Número de fichas capturadas
    bool m_captura;                       // Indica si el movimiento implica capturas
    TipusFitxa tipusFitxa;              // Tipo de ficha asociada al movimiento (normal o dama)

public:
    
	Moviment() : nPassos(0), nCaptures(0), captura(false), tipusFitxa(TIPUS_EMPTY) {};
    Moviment(const Posicio& inici, TipusFitxa tipus);

    
    void afegirPosicio(const Posicio& pos); 
    void eliminarUltimaPosicio();
    void netejar();        
    void afegirFitxaCapturada(const Posicio& pos); 
    
    Posicio inici() const;                          // Devuelve la posición inicial del movimiento
    Posicio fi() const;       
    // Devuelve la posición final del movimiento
    int getNumPassos() const;                       // Devuelve el número de pasos en el movimiento
    int getNumCaptures() const;                     // Devuelve el número de fichas capturadas
    bool esCaptura() const;                         // Indica si el movimiento es una captura
	Posicio getPosicio(int index) const;             // Devuelve una posición específica del movimiento
    
    bool esValid(const Tauler& tauler) const;       // Comprueba si el movimiento es válido
    bool posicioValida(const Posicio& pos, const Tauler& tauler) const; // Comprueba si una posición es válida

    
    bool esValid(const Tauler& tauler) const;
    bool posicioValida(const Posicio& pos, const Tauler& tauler) const;

    
    Moviment auxMoviment() const;

    bool operator==(const Moviment& altre) const;
};

#endif
