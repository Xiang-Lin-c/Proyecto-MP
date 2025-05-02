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
    int EstatCaptures[MAX_PASSOS];
    int nDamaCapturada;
    bool m_captura;

public:

    Moviment() : nPassos(0), nCaptures(0), m_captura(false), nDamaCapturada(0) {};

    void afegirPosicio(Posicio& pos);
    void eliminarUltimaPosicio();
    void netejar();
    void afegirFitxaCapturada(Posicio pos);
    void afegirDamaCapturada();

    Posicio inici() const;
    Posicio fi() const;

    int getNumPassos() const;
    int getNumCaptures() const;
    int getNumDamaCapturada() const;
    int getEstatCaptures(int index) const;
    Posicio getFitxaCapturada(int index) const;
    bool esCaptura() const;
    Posicio getPosicio(int index) const;

    void eliminarFitxaCapturada(const Posicio& pos);

    Moviment auxMoviment() const;

};

#endif
