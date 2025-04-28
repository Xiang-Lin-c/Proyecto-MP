#ifndef TAULER_H
#define TAULER_H
#include "Fitxa.h"
#include "Posicio.h"
#include "Moviment.h"
#include <string.h>
#include <iostream>

const int N_FILES = 8;
const int N_COLUMNES = 8;
const int MAX_POSICIONS = 20;

class Tauler {

public:
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(Posicio origen, int& nPosicions, Posicio posicionsPossibles[]);
    bool mouFitxa(Posicio origen, Posicio desti);
    string toString() const;
    void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
    void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];
	void inicialitzaFitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio);
    bool esMovimentValid(Posicio origen, Posicio desti);
    void actualitzaMovimentsFitxa(Fitxa fitxa);
    void processaMovimentSimple(Posicio origen, Posicio desti);
    void processaMovimentCaptura(Posicio origen, Posicio desti);

};
