
#ifndef TAULER_H
#define TAULER_H
#include "Fitxa.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class Tauler {

public:
    Tauler();
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(Posicio origen, int& nPosicions, Posicio posicionsPossibles[]);
    bool mouFitxa(Posicio origen, Posicio desti);
    string toString() const;
    void eliminarFitxa(Posicio pos);
    void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
    void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

private:
    vector<vector<Fitxa>> m_tauler;
    void inicialitzaFitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio);
    void CalcularMovimentsValids(Fitxa& fitxa);
    queue<Posicio> getPosicionsValides(Fitxa& fitxa, Posicio pos);
    queue<Posicio> getPosicionsValidesCaptura(Fitxa& fitxa, Posicio pos);
    queue<Posicio> desplazarDama(Fitxa& fitxa, const Posicio& pos, const Posicio& direccio);
    bool esPosicioValida(const Posicio& pos) const;
    bool esCasellaBuida(const Posicio& pos) const;
    bool esFichaContraria(const Fitxa& ficha, const Posicio& pos) const;
    vector<Posicio> getDirecciones(const Fitxa& fitxa) const;
    Posicio getDireccioDama(const Fitxa, const Posicio& pos) const;




};
#endif