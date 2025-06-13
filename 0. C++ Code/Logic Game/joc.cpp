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
, origenSeleccionat(false), destiSeleccionat(false), m_numPosicionsPosibles(0) {
}

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

//Aquesta funció retorna la posició seleccionada per l'usuari a partir de les coordenades del ratolí.
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
    return Posicio(-1, -1); 
}

// Aquesta funció dibuixa la fitxa a la posició corresponent al tauler.
 // Utilitza el GraphicManager per dibuixar les sprites de les fitxes.
 // La posició de la fitxa es calcula a partir de la seva posició en el tauler.
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

// Aquesta funció marca les posicions possibles per moure una fitxa.
 // Utilitza el GraphicManager per dibuixar un sprite que indica que la posició és vàlida.
 // Les posicions possibles es passen com a paràmetre i es dibuixen al tauler.
 // Si la posició és vàlida (no és -1, -1), es dibuixa el sprite de posició vàlida.
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

// Aquesta funció guarda les posicions possibles per moure una fitxa.
 // Aquesta informació s'utilitza per marcar les posicions vàlides al tauler.
 // El paràmetre numPosicions indica el nombre de posicions a guardar.

void Joc::guardarPosicionsPosibles(Posicio posicions[], int numPosicions) {
    m_numPosicionsPosibles = numPosicions;
    for (int i = 0; i < numPosicions; i++) {
        m_posicionsPosibles[i] = posicions[i];
    }
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    switch (m_mode)
    {
    case MODE_JOC_NORMAL:
        return actualitzaModeNormal(mousePosX, mousePosY, mouseStatus);
        break;
    case MODE_JOC_REPLAY:
        return actualitzaModeReplay(mousePosX, mousePosY, mouseStatus);
        break;
    default:
        return false;
        break;
    }
}

// Aquesta funció actualitza el mode normal del joc.
 // Dibuixa el tauler, les fitxes i les posicions possibles per moure.
 // També gestiona la selecció de fitxes i moviments.
 // Retorna true si la partida ha acabat, false en cas contrari.
bool Joc::actualitzaModeNormal(int mousePosX, int mousePosY, bool mouseStatus)
{
    m_tauler.actualitzaMovimentsValids();
    GraphicManager* gManager = GraphicManager::getInstance();
    gManager->drawSprite(GRAFIC_FONS, 0, 0);
    gManager->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
    if (m_jugadorTorn == 1)
        colorJugador = "Blanc";
    else
        colorJugador = "Negre";


    string modeText = "Mode: NORMAL";
    string color;
    if (m_jugadorTorn == 1)
    {
        color = "Blanques";
    }
    else
    {
        color = "Negres";
    }
    string tornText = "Torn del jugador: " + color;
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 150;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, modeText);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 40, 0.8, tornText);
    std::string msg = "PosX: " + std::to_string(mousePosX) + ", PosY: " + std::to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 80, 0.8, msg);


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

            if (!fitxaClicada.esBuida() &&
                ((m_jugadorTorn == 1 && fitxaClicada.getColor() == COLOR_BLANC) ||
                    (m_jugadorTorn == 2 && fitxaClicada.getColor() == COLOR_NEGRE)))
            {
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
        Moviment moviment;
        moviment.afegirPosicio(origen);
        moviment.afegirPosicio(desti);
        m_cuaMoviments.afegeix(moviment);
        origenSeleccionat = false;
        destiSeleccionat = false;
        m_numPosicionsPosibles = 0;
        if (m_jugadorTorn == 1)
            m_jugadorTorn = 2;
        else
            m_jugadorTorn = 1;
        comprovaFinalPartida();

    }

    if (m_finalPartida)
    {
        return true;
    }

    return false;
}

// Aquesta funció actualitza el mode replay del joc.
 // Dibuixa el tauler, les fitxes i les posicions possibles per moure.
 // També gestiona els moviments de les fitxes en mode replay.
 // Retorna true si la partida ha acabat, false en cas contrari.
bool Joc::actualitzaModeReplay(int mousePosX, int mousePosY, bool mouseStatus)
{
    m_tauler.actualitzaMovimentsValids();
    GraphicManager* gManager = GraphicManager::getInstance();
    gManager->drawSprite(GRAFIC_FONS, 0, 0);
    gManager->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    if (m_jugadorTorn == 1)
        colorJugador = "Blanc";
    else
        colorJugador = "Negre";

    string modeText = "Mode: REPLAY";
    string color;
    if (m_jugadorTorn == 1)
    {
        color = "Blanques";
    }
    else
    {
        color = "Negres";
    }
    string tornText = "Torn del jugador: " + color;
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 150;
    gManager->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, modeText);
    gManager->drawFont(FONT_WHITE_30, posTextX, posTextY + 40, 0.8, tornText);
    string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    gManager->drawFont(FONT_WHITE_30, posTextX, posTextY + 80, 0.8, msg);

    for (int i = 0; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) {
            DibuixaFitxa(m_tauler.getFitxa(i, j));
        }
    }

    static bool mouseAnterior = false;
    bool mouseClick = mouseStatus && !mouseAnterior;
    mouseAnterior = mouseStatus;

    if (mouseClick && !m_finalPartida) {
        Posicio clicada = getPosicioSeleccionada(mousePosX, mousePosY, true);
        if (clicada.getFila() != -1) {
            if (!m_cuaMoviments.esBuida()) {
                Moviment mov;
                if (m_cuaMoviments.primerMoviment(mov))
                {
                    if (mov.getNumPassos() >= 2) {
                        m_tauler.mouFitxa(mov.getPosicio(0), mov.getPosicio(1));
                    }
                    if (m_jugadorTorn == 1)
                        m_jugadorTorn = 2;
                    else
                        m_jugadorTorn = 1;
                    comprovaFinalPartida();
                }
            }
        }
    }

    if (m_cuaMoviments.esBuida() && !m_finalPartida) {
        string msgMov = "No queden mes moviments!";
        gManager->drawFont(FONT_RED_30, posTextX, posTextY + 120, 0.8, msgMov);
    }

    if (m_finalPartida) {
        string guanyadorText = "Guanyador: Jugador " + to_string(m_guanyador);
        gManager->drawFont(FONT_GREEN_30, posTextX, posTextY + 120, 0.8, guanyadorText);
        return true;
    }

    return false;
}

// Aquesta funció comprova si la partida ha acabat.
 // Si les fitxes blanques són 0, el guanyador és el jugador 2 (negre).
 // Si les fitxes negres són 0, el guanyador és el jugador 1 (blanc).
void Joc::comprovaFinalPartida() {
    Tauler& tauler = m_tauler;
    int fitxesBlanques = tauler.getNumFitxes(COLOR_BLANC);
    int fitxesNegres = tauler.getNumFitxes(COLOR_NEGRE);

    if (fitxesBlanques == 0) {
        m_finalPartida = true;
        m_guanyador = 2;
    }
    else if (fitxesNegres == 0) {
        m_finalPartida = true;
        m_guanyador = 1;
    }
}

void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL)
    {
        m_cuaMoviments.guardaEnFitxer(m_nomFitxerMoviments);
    }
}

// Aquesta funció mostra el guanyador de la partida.
// Dibuixa el tauler, les fitxes i les posicions possibles per moure.
// També mostra el guanyador i un missatge per sortir del joc.
// Utilitza el GraphicManager per dibuixar els sprites i textos.
void Joc::MostrarGuanyador(int mousePosX, int mousePosY, bool mouseStatus) {

    m_tauler.actualitzaMovimentsValids();
    GraphicManager* gManager = GraphicManager::getInstance();

    gManager->drawSprite(GRAFIC_FONS, 0, 0);
    gManager->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);


    string modeText = "Mode: NORMAL";
    string color;
    if (m_jugadorTorn == 2)
    {
        color = "Blanques";
    }
    else
    {
        color = "Negres";
    }
    string tornText = "Torn del jugador: " + color;
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 150;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, modeText);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 40, 0.8, tornText);
    string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 80, 0.8, msg);


    for (int i = 0; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) {
            DibuixaFitxa(m_tauler.getFitxa(i, j));
        }
    }

    string guanyador;

	if (m_guanyador == 1)
		guanyador = "Blanques";
	else
		guanyador = "Negres";

    string guanyadorText = "Guanyador: Jugador " + color;
    GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posTextX, posTextY + 120, 0.8, guanyadorText);
    string msgFinal = "Premi ESC per sortir del joc";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY + 150, 0.8, msgFinal);


}


