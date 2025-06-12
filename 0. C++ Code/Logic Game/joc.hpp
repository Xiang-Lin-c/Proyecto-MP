#ifndef JOC_H
#define JOC_H

#include <vector>
#include "info_joc.hpp"
#include "Tauler.hpp"
#include "CuaMoviments.h"


using namespace std;

class Joc
{
public:
    Joc();

    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);

    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);

    void finalitza();
    bool getFinalPartida() const { return m_finalPartida; }
    void MostrarGuanyador(int mousePosX, int mousePosY, bool mouseStatus);
private:
    Tauler m_tauler;
    CuaMoviments m_cuaMoviments; 
    ModeJoc m_mode;
    int m_jugadorTorn;
    string colorJugador;
    bool m_finalPartida; 
    bool m_mouseAnterior;
    int m_guanyador;  
    bool m_fitxaSeleccionada;
    bool origenSeleccionat;
    bool destiSeleccionat;
    Posicio m_posicioSeleccionada; 
    Posicio m_posicionsPosibles[MAX_MOVIMENTS];
    Posicio origen;
    Posicio desti;
    int m_numPosicionsPosibles;
    vector<Moviment> m_movimentsValids;
    string m_nomFitxerMoviments;
    void DibuixaFitxa(const Fitxa& fitxa);
    void MarcarPosicionsPosibles(const Posicio PosicionsPosibles[]);
    Posicio getPosicioSeleccionada(int mousePosX, int mousePosY, bool mouseStatus) const;
    void guardarPosicionsPosibles(Posicio posicions[], int numPosicions);
    bool actualitzaModeNormal(int mousePosX, int mousePosY, bool mouseStatus);
    bool actualitzaModeReplay(int mousePosX, int mousePosY, bool mouseStatus);
    void comprovaFinalPartida();



};

#endif
