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
    int nPassos;                        // N�mero de posiciones en el movimiento
    Posicio fitxesCapturades[MAX_CAPTURES]; // Posiciones de las fichas capturadas
    int nCaptures;                      // N�mero de fichas capturadas
    bool captura;                       // Indica si el movimiento implica capturas
    TipusFitxa tipusFitxa;              // Tipo de ficha asociada al movimiento (normal o dama)

public:
    
    Moviment();
    Moviment(const Posicio& inici, TipusFitxa tipus);

    
    void afegirPosicio(const Posicio& pos);          // A�ade una posici�n al movimiento
    void eliminarUltimaPosicio();                   // Elimina la �ltima posici�n del movimiento
    void netejar();                                 // Limpia el movimiento (reinicia el estado)
    void afegirFitxaCapturada(const Posicio& pos);  // A�ade una ficha capturada al movimiento

    
    Posicio inici() const;                          // Devuelve la posici�n inicial del movimiento
    Posicio fi() const;       
    // Devuelve la posici�n final del movimiento
    int getNumPassos() const;                       // Devuelve el n�mero de pasos en el movimiento
    int getNumCaptures() const;                     // Devuelve el n�mero de fichas capturadas
    bool esCaptura() const;                         // Indica si el movimiento es una captura

    
    bool esValid(const Tauler& tauler) const;       // Comprueba si el movimiento es v�lido
    bool posicioValida(const Posicio& pos, const Tauler& tauler) const; // Comprueba si una posici�n es v�lida

    
    Moviment auxMoviment() const;                   // Duplica el movimiento actual
    

   
    bool operator==(const Moviment& altre) const;   // Compara dos movimientos
};

#endif
