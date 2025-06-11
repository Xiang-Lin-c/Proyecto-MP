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

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) 
{
	//TODO 1: Interactuar amb la crida per dibuixar gràfics (sprites).
	// 	      Dibuixar a pantalla el fons i el gràfic amb el tauler buit.
	//------------------------------------------------------------------
    GraphicManager* gManager = GraphicManager::getInstance();
    gManager->drawSprite(GRAFIC_FONS, 0, 0);
    gManager->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    int fila = 2;      // Ejemplo: fila 2 (0-7)
    int columna = 0;   // Ejemplo: columna 3 (0-7)

    // 4. Calcular la posición (x, y) de la ficha en píxeles
    float posX = POS_X_TAULER + CASELLA_INICIAL_X + columna * AMPLADA_CASELLA;
    float posY = POS_Y_TAULER + CASELLA_INICIAL_Y + fila * ALCADA_CASELLA;

    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);

    if ((mouseStatus) && (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
        (mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
        (mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
        (mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
    {
        int posX = POS_X_TAULER + CASELLA_INICIAL_X + ((columna) * AMPLADA_CASELLA);
        int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + ((fila) * ALCADA_CASELLA);
        GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
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



