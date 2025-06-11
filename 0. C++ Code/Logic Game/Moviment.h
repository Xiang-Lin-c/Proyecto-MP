#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.hpp"
#include <iostream>
#include <vector>

using namespace std;

const int MAX_PASSOS = 12;
const int MAX_CAPTURES = 12;

class Moviment
{
private:

    vector<Posicio> trajecte;
    vector<Posicio> fitxesCapturades;
    vector<int>EstatCaptures;
    int nPassos;
    int nCaptures;
    int m_maxCaptures;
    int m_maxPassos;
    int nDamaCapturada;
    bool m_captura;
    Posicio direccio;

public:

    Moviment() : nPassos(0), nCaptures(0), m_captura(false), nDamaCapturada(0), m_maxCaptures(MAX_CAPTURES), m_maxPassos(MAX_PASSOS) { direccio = Posicio(0, 0); }
    void afegirPosicio(Posicio& pos);
    void eliminarUltimaPosicio();
    void netejar();
    void afegirDamaCapturada();

    Posicio inici() const;
    Posicio fi() const;

    int getNumPassos() const;
    int getNumCaptures() const;
    int getNumDamaCapturada() const;
    int getIndexPosicio(const Posicio& pos) const;
    int getEstatCaptures(int index) const;
    Posicio getFitxaCapturada(int index) const;
    void afegirFitxaCapturada(const Posicio& pos);
    void setnCaptures();
    bool esCaptura() const;
    Posicio getPosicio(int index) const;
    Posicio getUltimaPosicio() const;
    bool esPosicioVisitada(const Posicio& pos) const;
    void eliminarFitxaCapturada(const Posicio& pos);

    Moviment auxMoviment() const;

};

#endif
