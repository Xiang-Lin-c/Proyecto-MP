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

Joc::Joc() : m_tauler(), m_cuaMoviments(), m_mode(MODE_JOC_NONE), m_jugadorTorn(1), m_finalPartida(false), m_guanyador(0), m_fitxaSeleccionada(false), m_posicioSeleccionada(), m_movimentsValids() {}

void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
    m_mode = mode;
    m_nomFitxerMoviments = nomFitxerMoviments;

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
    for (int i = 0; i < MAX_MOVIMENTS; i++) {
        if (PosicionsPosibles[i].getFila() != -1 && PosicionsPosibles[i].getColumna() != -1&& PosicionsPosibles[i].getFila() != 0 && PosicionsPosibles[i].getColumna() != 0) {
            int posX = POS_X_TAULER + CASELLA_INICIAL_X + PosicionsPosibles[i].getColumna() * AMPLADA_CASELLA;
            int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + PosicionsPosibles[i].getFila() * ALCADA_CASELLA;
            gManager->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
        }
    }
}


bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) 
{
	//TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites).
	// 	      Dibuixar a pantalla el fons i el gràfic amb el tauler buit.
	//------------------------------------------------------------------
    m_tauler.actualitzaMovimentsValids();
    GraphicManager* gManager = GraphicManager::getInstance();
    gManager->drawSprite(GRAFIC_FONS, 0, 0);
    gManager->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
    for (int i = 0; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) {
			DibuixaFitxa(m_tauler.getFitxa(i,j));
        }
    }
    Posicio origen, desti;
	int filaOrigen, columnaOrigen, filaDesti, columnaDesti;
	bool origenSeleccionat = false, destiSeleccionat = false;

	origen = getPosicioSeleccionada(mousePosX, mousePosY, mouseStatus);
    if (origen.getFila() != -1 && origen.getColumna() != -1) {
        filaOrigen = origen.getFila();
        columnaOrigen = origen.getColumna();
        origenSeleccionat = true;
    }
    else
        origenSeleccionat = false;

    if (origenSeleccionat) {
        Posicio posicionsPosibles[MAX_MOVIMENTS];
        int numPosicions;
        m_tauler.getPosicionsPossibles(origen, numPosicions, posicionsPosibles);
		MarcarPosicionsPosibles(posicionsPosibles);
		desti = getPosicioSeleccionada(mousePosX, mousePosY, mouseStatus);
        for (int i = 0; i < numPosicions; i++) {
            if (desti == posicionsPosibles[i]) {
				destiSeleccionat = true;
                break;
            }
            else
				destiSeleccionat = false;
        }
    }




	//TODO 1.3: Dibuixar a pantalla el gràfic amb el tauler i una fitxa blanca a la posició (fila, columna ) del tauler


	//TODO 2: Interactuar amb el ratolí.
	//------------------------------------------------------------------
	//TODO 2.1: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí



    //TODO 2.2: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
    // està dins del límits del tauler

 

    //TODO 2.3: Dibuixar la fitxa blanca al tauler només si estem pressionant el botó del ratolí i el ratolí
    // està dins del límits del tauler. Dibuixa la fitxa a la casella on està el ratolí



    //TODO 2.4: Dibuixar la fitxa blanca a la casella on cliquem al ratolí. La fitxa s'ha de mantenir dibuixada
    // a la casella quan deixem de clicar amb el ratolí. Quan cliquem a una altra casella, la fitxa canvia de posició
    // a la nova casella

        
        
    // TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Mostrar la posició actual del ratolí a sota del tauler



	return false;
}
void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL)
    {
        m_cuaMoviments.guardaEnFitxer(m_nomFitxerMoviments);
    }
}



