#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "Posicio.h"
#include "Tauler.h"
#include <iostream>
using namespace std;

const int MAX_PASSOS = 12;
const int MAX_CAPTURES = 12; // Máximo número de fichas capturadas en un movimiento

class Moviment
{
private:
    Posicio trajecte[MAX_PASSOS];       // Secuencia de posiciones del movimiento
    int nPassos;                        // Número de posiciones en el movimiento
    Posicio fitxesCapturades[MAX_CAPTURES]; // Posiciones de las fichas capturadas
    int nCaptures;                      // Número de fichas capturadas
    bool captura;                       // Indica si el movimiento implica capturas
    TipusFitxa tipusFitxa;              // Tipo de ficha asociada al movimiento (normal o dama)

public:
    // Constructores
    Moviment();
    Moviment(const Posicio& inici, TipusFitxa tipus);
    // Métodos para gestionar el movimiento
    void afegirPosicio(const Posicio& pos);          // Añade una posición al movimiento
    void eliminarUltimaPosicio();                   // Elimina la última posición del movimiento
    void netejar();                                 // Limpia el movimiento (reinicia el estado)
    void afegirFitxaCapturada(const Posicio& pos);  // Añade una ficha capturada al movimiento

    // Métodos para obtener información del movimiento
    Posicio inici() const;                          // Devuelve la posición inicial del movimiento
    Posicio fi() const;       
    // Devuelve la posición final del movimiento
    int getNumPassos() const;                       // Devuelve el número de pasos en el movimiento
    int getNumCaptures() const;                     // Devuelve el número de fichas capturadas
    bool esCaptura() const;                         // Indica si el movimiento es una captura

    // Métodos de validación
    bool esValid(const Tauler& tauler) const;       // Comprueba si el movimiento es válido
    bool posicioValida(const Posicio& pos, const Tauler& tauler) const; // Comprueba si una posición es válida

    // Métodos adicionales
    Moviment auxMoviment() const;                   // Duplica el movimiento actual
    

    // Operadores
    bool operator==(const Moviment& altre) const;   // Compara dos movimientos
};

#endif
