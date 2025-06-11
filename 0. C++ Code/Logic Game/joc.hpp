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
    int m_guanyador;                        // Jugador ganador (0 si no hay ganador aún)
    bool m_fitxaSeleccionada;                // Indica si hay una ficha seleccionada
    Posicio m_posicioSeleccionada;          // Posición de la ficha seleccionada
    vector<Moviment> m_movimentsValids;     // Movimientos válidos para la ficha seleccionada
    string m_nomFitxerMoviments;       // Nombre del archivo de movimientos
    void DibuixaFitxa(const Fitxa& fitxa);
    Posicio getPosicioSeleccionada(int mousePosX, int mousePosY, bool mouseStatus) const;


};

#endif
