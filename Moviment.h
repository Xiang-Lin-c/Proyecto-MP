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
    Posicio trajecte[MAX_PASSOS];       // Secuencia de posiciones del movimiento
    int nPassos;                        // N�mero de posiciones en el movimiento
    Posicio fitxesCapturades[MAX_CAPTURES]; // Posiciones de las fichas capturadas
    int nCaptures;                      // N�mero de fichas capturadas
    int EstatCaptures[MAX_PASSOS];
	int nDamaCapturada;                 // N�mero de damas capturadas
    bool m_captura;                       // Indica si el movimiento implica capturas

public:
    
	Moviment() : nPassos(0), nCaptures(0), m_captura(false) {};

    
    void afegirPosicio(const Posicio& pos); 
    void eliminarUltimaPosicio();
    void netejar();        
    void afegirFitxaCapturada( Posicio& pos); 
	void afegirDamaCapturada(); // A�adir dama capturada
    
    Posicio inici() const;                          // Devuelve la posici�n inicial del movimiento
    Posicio fi() const;       
    // Devuelve la posici�n final del movimiento
    int getNumPassos() const;                       // Devuelve el n�mero de pasos en el movimiento
    int getNumCaptures() const;                     // Devuelve el n�mero de fichas capturadas
	int getNumDamaCapturada() const;                // Devuelve el n�mero de damas capturadas
    int getEstatCaptures(int index) const;
	Posicio getFitxaCapturada(int index) const;       // Devuelve la posici�n de una ficha capturada
    bool esCaptura() const;                         // Indica si el movimiento es una captura
	Posicio getPosicio(int index) const;             // Devuelve una posici�n espec�fica del movimiento


    
    Moviment auxMoviment() const;

    bool operator==(const Moviment& altre) const;
};

#endif
