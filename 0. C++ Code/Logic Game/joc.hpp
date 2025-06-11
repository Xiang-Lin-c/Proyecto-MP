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

private:
    Tauler m_tauler;                        // Tablero de juego
    CuaMoviments m_cuaMoviments;            // Cola de movimientos realizados
    ModeJoc m_mode;                         // Modo de juego (normal o reproducción)
    int m_jugadorTorn;                      // Jugador con el turno actual (1 o 2)
    bool m_finalPartida;                    // Indica si la partida ha terminado
    bool m_mouseAnterior;
    int m_guanyador;                        // Jugador ganador (0 si no hay ganador aún)
    bool m_fitxaSeleccionada;                // Indica si hay una ficha seleccionada
	bool origenSeleccionat; // Indica si se ha seleccionado un origen para el movimiento
	bool destiSeleccionat;           
    Posicio m_posicioSeleccionada;          // Posición de la ficha seleccionada
    Posicio m_posicionsPosibles[MAX_MOVIMENTS];
    Posicio origen;
    Posicio desti;
    int m_numPosicionsPosibles;
    vector<Moviment> m_movimentsValids;     // Movimientos válidos para la ficha seleccionada
    string m_nomFitxerMoviments;       // Nombre del archivo de movimientos
    void DibuixaFitxa(const Fitxa& fitxa);
    void MarcarPosicionsPosibles(const Posicio PosicionsPosibles[]);
    Posicio getPosicioSeleccionada(int mousePosX, int mousePosY, bool mouseStatus) const;
    void guardarPosicionsPosibles(Posicio posicions[], int numPosicions);


};

#endif
