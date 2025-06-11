//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"

Joc::Joc() : m_tauler(), m_cuaMoviments(), m_mode(MODE_JOC_NONE), m_jugadorTorn(1), m_finalPartida(false), m_guanyador(0), m_fitxaSeleccionada(false), m_posicioSeleccionada(), m_movimentsValids(), m_mouseAnterior(false)
, origenSeleccionat(false), destiSeleccionat(false), m_numPosicionsPosibles(0) {}

void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
    m_mode = mode;
    m_nomFitxerMoviments = nomFitxerMoviments;
	origenSeleccionat = false;
	destiSeleccionat = false;
	m_numPosicionsPosibles = 0;
    m_tauler.inicialitza(nomFitxerTauler);

    m_jugadorTorn = 1;
    m_finalPartida = false;
    m_guanyador = 0;
    m_fitxaSeleccionada = false;
    m_movimentsValids.clear();

    if (mode == MODE_JOC_NORMAL)
    {
        m_cuaMoviments.buidaCua();
    }
    else if (mode == MODE_JOC_REPLAY)
    {
        m_cuaMoviments.carregaDeFitxer(nomFitxerMoviments);
    }
}


Posicio Joc::getPosicioSeleccionada(int mousePosX, int mousePosY, bool mouseStatus) const {
    if ((mouseStatus) && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
        (mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
        (mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
        (mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
    {
		int filaRato = (mousePosY - POS_Y_TAULER - CASELLA_INICIAL_Y) / ALCADA_CASELLA;
		int columnaRato = (mousePosX - POS_X_TAULER - CASELLA_INICIAL_X) / AMPLADA_CASELLA;

		if (filaRato >= 0 && filaRato < NUM_FILES_TAULER && columnaRato >= 0 && columnaRato < NUM_COLS_TAULER)
		{
			return Posicio(filaRato, columnaRato);
		}
	}
	return Posicio(-1, -1); // Retorna una posició invàlida si el ratolí no està sobre el tauler
}


void Joc::DibuixaFitxa(const Fitxa& fitxa) {
	GraphicManager* gManager = GraphicManager::getInstance();
	int posX = POS_X_TAULER + CASELLA_INICIAL_X + fitxa.getPosicio().getColumna() * AMPLADA_CASELLA;
    int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + fitxa.getPosicio().getFila() * ALCADA_CASELLA;

    if (fitxa.getColor() == COLOR_BLANC) {
        if (fitxa.getTipus() == TIPUS_NORMAL)
            gManager->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
		else if (fitxa.getTipus() == TIPUS_DAMA) {
			gManager->drawSprite(GRAFIC_DAMA_BLANCA, posX, posY);
		}
    }
    else
        if (fitxa.getColor() == COLOR_NEGRE) {
            if (fitxa.getTipus() == TIPUS_NORMAL)
                gManager->drawSprite(GRAFIC_FITXA_NEGRA, posX, posY);
            else if (fitxa.getTipus() == TIPUS_DAMA) {
                gManager->drawSprite(GRAFIC_DAMA_NEGRA, posX, posY);
            }
        }

}

void Joc::MarcarPosicionsPosibles(const Posicio PosicionsPosibles[]) {
    GraphicManager* gManager = GraphicManager::getInstance();
    for (int i = 0; i < m_numPosicionsPosibles; i++) {
        if (PosicionsPosibles[i].getFila() != -1 && PosicionsPosibles[i].getColumna() != -1) {
            int posX = POS_X_TAULER + CASELLA_INICIAL_X + PosicionsPosibles[i].getColumna() * AMPLADA_CASELLA;
            int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + PosicionsPosibles[i].getFila() * ALCADA_CASELLA;
            gManager->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
        }
    }
}

void Joc::guardarPosicionsPosibles(Posicio posicions[], int numPosicions) {
	m_numPosicionsPosibles = numPosicions;
	for (int i = 0; i < numPosicions; i++) {
		m_posicionsPosibles[i] = posicions[i];
	}
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    m_tauler.actualitzaMovimentsValids();
    GraphicManager* gManager = GraphicManager::getInstance();
    gManager->drawSprite(GRAFIC_FONS, 0, 0);
    gManager->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    for (int i = 0; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) {
            DibuixaFitxa(m_tauler.getFitxa(i, j));
        }
    }

    MarcarPosicionsPosibles(m_posicionsPosibles);

    static bool mouseAnterior = false;
    bool mouseClick = mouseStatus && !mouseAnterior;
    mouseAnterior = mouseStatus;

    if (mouseClick) {
        Posicio clicada = getPosicioSeleccionada(mousePosX, mousePosY, true);
        if (clicada.getFila() != -1) {
            Fitxa fitxaClicada = m_tauler.getFitxa(clicada.getFila(), clicada.getColumna());

            if (!fitxaClicada.esBuida()) {
                origen = clicada;
                origenSeleccionat = true;
                destiSeleccionat = false;
                m_tauler.getPosicionsPossibles(origen, m_numPosicionsPosibles, m_posicionsPosibles);
            }
            else if (origenSeleccionat) {
                for (int i = 0; i < m_numPosicionsPosibles; i++) {
                    if (clicada == m_posicionsPosibles[i]) {
                        desti = clicada;
                        destiSeleccionat = true;
                        break;
                    }
                }
            }
        }
    }

    if (origenSeleccionat && destiSeleccionat) {
        m_tauler.mouFitxa(origen, desti);
        origenSeleccionat = false;
        destiSeleccionat = false;
        m_numPosicionsPosibles = 0;
    }

    return true;
}




void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL)
    {
        m_cuaMoviments.guardaEnFitxer(m_nomFitxerMoviments);
    }
}



