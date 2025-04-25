#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "Posicio.h"
#include "Tauler.h"
#include <iostream>
using namespace std;

const int MAX_PASSOS = 12;
const int MAX_MOVIMENTS = 32;

class Moviment
{
private:
    Posicio trajecte[MAX_PASSOS];
    int nMoviments;
    bool salt;
    bool captura;



public:
    Moviment();
    Moviment(const Posicio& inici);

    bool posicioValida(const Posicio& pos, const Tauler& tauler) const;
    void afegirPosicio(const Posicio& pos);
    void eliminarUltimaPosicio();
    void netejar();

    bool esValid() const;

    Posicio inici() const;
    Posicio fi() const;

    int calcularPunts(const Tauler& tauler) const;
    bool operator==(const Moviment& altre) const;

    void generarMoviments(const Posicio& inici, const Tauler& tauler, Moviment resultat[], int& quantitat) const; //Important
    void imprimirTauler() const;
};

#endif