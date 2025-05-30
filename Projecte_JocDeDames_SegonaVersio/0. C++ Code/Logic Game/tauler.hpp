
#ifndef TAULER_H
#define TAULER_H
#include "Fitxa.h"
#include <string>
#include <iostream>
#include <fstream>

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
    Fitxa m_tauler[N_FILES][N_COLUMNES]; 
    void inicialitzaFitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio);
    bool esPosicioValida(const Posicio& pos) const;
    void actualitzaMovimentsFitxa(Fitxa& fitxa);
    void desplazarDama(Fitxa fitxa, int fila, int columna, int direccion);
    void processaMovimentCaptura(const Fitxa& fitxa, int fila, int columna);

};
#endif