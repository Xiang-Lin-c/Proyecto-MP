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

Joc::Joc() : m_tauler(), m_cuaMoviments(), m_mode(MODE_JOC_NONE), m_jugadorTorn(1), m_finalPartida(false), m_guanyador(0), m_fitxaSeleccionada(false), m_posicioSeleccionada(), m_movimentsValids(), m_mouseEstatAnterior(false) {}

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
    m_mouseEstatAnterior = false;

    if (mode == MODE_JOC_NORMAL)
    {
        m_cuaMoviments.buidaCua();
    }
    else if (mode == MODE_JOC_REPLAY)
    {
        m_cuaMoviments.carregaDeFitxer(nomFitxerMoviments);
    }
}
void Joc::dibuixaFitxesTauler() 
{
    for (int fila = 0; fila < NUM_FILES_TAULER; ++fila) {
        for (int col = 0; col < NUM_COLS_TAULER; ++col) {
            const Fitxa& fitxa = m_tauler.getFitxa(fila, col);
            if (!fitxa.esBuida()) {
                IMAGE_NAME grafico;
                if (fitxa.getColor() == COLOR_BLANC) {
                    grafico = fitxa.esDama() ? GRAFIC_DAMA_BLANCA : GRAFIC_FITXA_BLANCA;
                }
                else if (fitxa.getColor() == COLOR_NEGRE) {
                    grafico = fitxa.esDama() ? GRAFIC_DAMA_NEGRA : GRAFIC_FITXA_NEGRA;
                }
                else {
                    continue;
                }
                int posX = POS_X_TAULER + CASELLA_INICIAL_X + col * AMPLADA_CASELLA;
                int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + fila * ALCADA_CASELLA;
                GraphicManager::getInstance()->drawSprite(grafico, posX, posY);
            }
        }
    }
}
void Joc::comprovaFinalPartida() {
    int fitxesBlanques = m_tauler.getNumFitxes(COLOR_BLANC);
    int fitxesNegres = m_tauler.getNumFitxes(COLOR_NEGRE);

    if (fitxesBlanques == 0) {
        m_finalPartida = true;
        m_guanyador = 2;
    }
    else if (fitxesNegres == 0) {
        m_finalPartida = true;
        m_guanyador = 1;
    }
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    switch (m_mode)
    {
    case MODE_JOC_NORMAL:
        return actualitzaModeNormal(mousePosX, mousePosY, mouseStatus);
    case MODE_JOC_REPLAY:
        return actualitzaModeReplay(mousePosX, mousePosY, mouseStatus);
    default:
        dibuixaFitxesTauler();
        return false;
    }
}

bool Joc::actualitzaModeNormal(int mousePosX, int mousePosY, bool mouseStatus)
{
    // 1. Dibujar fondo y tablero
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    // 2. Dibujar todas las fichas en el tablero
    dibuixaFitxesTauler();

    // 3. Mostrar el modo y el jugador actual
    std::string modeText = "Mode: NORMAL";
    std::string tornText = "Torn del jugador: " + std::to_string(m_jugadorTorn);
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 60;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, modeText);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 40, 0.8, tornText);

    // 4. Mostrar la posición del ratón
    std::string msg = "PosX: " + std::to_string(mousePosX) + ", PosY: " + std::to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 80, 0.8, msg);

    // 5. Si la partida ha terminado, mostrar el ganador y devolver true
    if (m_finalPartida)
    {
        std::string guanyadorText = "Guanyador: Jugador " + std::to_string(m_guanyador);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posTextX, posTextY + 120, 0.8, guanyadorText);
        return true;
    }

    // 6. Si hay una ficha seleccionada, mostrar los movimientos válidos
    if (m_fitxaSeleccionada)
    {
        for (const Moviment& mov : m_movimentsValids)
        {
            Posicio desti = mov.fi();
            int col = desti.getColumna();
            int fila = desti.getFila();
            int posX = POS_X_TAULER + CASELLA_INICIAL_X + col * AMPLADA_CASELLA;
            int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + fila * ALCADA_CASELLA;
            GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
        }
    }

    // 7. Detectar flanco de subida del ratón (clic nuevo)
    bool clickNou = mouseStatus && !m_mouseEstatAnterior;

    // 8. Si se hace clic dentro del tablero
    if (clickNou &&
        mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X) &&
        mousePosY >= (POS_Y_TAULER + CASELLA_INICIAL_Y) &&
        mousePosX < (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER) &&
        mousePosY < (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER))
    {
        // Calcular la casilla clicada
        int col = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
        int fila = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;

        Posicio posClic(fila, col);

        // Si no hay ficha seleccionada, intentamos seleccionar una ficha del jugador actual
        if (!m_fitxaSeleccionada)
        {
            const Fitxa& fitxa = m_tauler.getFitxa(fila, col);
            if (!fitxa.esBuida() &&
                ((m_jugadorTorn == 1 && fitxa.getColor() == COLOR_BLANC) ||
                    (m_jugadorTorn == 2 && fitxa.getColor() == COLOR_NEGRE)))
            {
                m_fitxaSeleccionada = true;
                m_posicioSeleccionada = posClic;
                m_movimentsValids.clear();

                // Obtener movimientos válidos para la ficha seleccionada
                int nPosicions = 0;
                Posicio posicionsPossibles[20];
                m_tauler.getPosicionsPossibles(posClic, nPosicions, posicionsPossibles);

                for (int i = 0; i < nPosicions; ++i)
                {
                    Moviment mov;
                    mov.afegirPosicio(m_posicioSeleccionada);
                    mov.afegirPosicio(posicionsPossibles[i]);
                    m_movimentsValids.push_back(mov);
                }
            }
        }
        else
        {
            // Si hay ficha seleccionada, comprobar si el clic es en una posición válida
            bool esMovimentValid = false;
            Moviment movimentSeleccionat;
            for (const Moviment& mov : m_movimentsValids)
            {
                if (mov.fi() == posClic)
                {
                    esMovimentValid = true;
                    movimentSeleccionat = mov;
                    break;
                }
            }

            if (esMovimentValid)
            {
                // Ejecutar el movimiento
                m_tauler.mouFitxa(movimentSeleccionat.inici(), movimentSeleccionat.fi());

                // Guardar el movimiento en la cola
                m_cuaMoviments.afegeix(movimentSeleccionat);

                // Comprobar si la partida ha terminado
                comprovaFinalPartida();

                // Cambiar el turno si la partida no ha terminado
                if (!m_finalPartida)
                    m_jugadorTorn = (m_jugadorTorn == 1) ? 2 : 1;

                // Deseleccionar ficha y limpiar movimientos válidos
                m_fitxaSeleccionada = false;
                m_movimentsValids.clear();
            }
            else
            {
                // Si el clic no es en una posición válida, deselecciona la ficha
                m_fitxaSeleccionada = false;
                m_movimentsValids.clear();
            }
        }
    }

    // Actualizar el estado anterior del ratón
    m_mouseEstatAnterior = mouseStatus;

    return false;
}

bool Joc::actualitzaModeReplay(int mousePosX, int mousePosY, bool mouseStatus)
{
    // 1. Dibujar fondo y tablero
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    // 2. Dibujar todas las fichas en el tablero
    dibuixaFitxesTauler();

    // 3. Mostrar el modo y el jugador actual
    std::string modeText = "Mode: REPLAY";
    std::string tornText = "Torn del jugador: " + std::to_string(m_jugadorTorn);
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 60;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, modeText);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 40, 0.8, tornText);

    // 4. Mostrar la posición del ratón
    std::string msg = "PosX: " + std::to_string(mousePosX) + ", PosY: " + std::to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 80, 0.8, msg);

    // 5. Si la partida ha terminado, mostrar el ganador y devolver true
    if (m_finalPartida)
    {
        std::string guanyadorText = "Guanyador: Jugador " + std::to_string(m_guanyador);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, posTextX, posTextY + 120, 0.8, guanyadorText);
        return true;
    }

    // 6. Si se hace clic dentro del tablero y hay movimientos en la cola, ejecutar el siguiente movimiento
    // Solo ejecuta el movimiento si el botón acaba de ser pulsado (flanco de subida)
    if (mouseStatus && !m_mouseEstatAnterior &&
        mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X) &&
        mousePosY >= (POS_Y_TAULER + CASELLA_INICIAL_Y) &&
        mousePosX < (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER) &&
        mousePosY < (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER))
    {
        if (!m_cuaMoviments.esBuida())
        {
            Moviment mov;
            if (m_cuaMoviments.primerMoviment(mov))
            {
                // Ejecutar el movimiento en el tablero
                m_tauler.mouFitxa(mov.inici(), mov.fi());

                // Comprobar si la partida ha terminado
                comprovaFinalPartida();

                // Cambiar el turno si la partida no ha terminado
                if (!m_finalPartida)
                    m_jugadorTorn = (m_jugadorTorn == 1) ? 2 : 1;
            }
        }
        else
        {
            // No quedan movimientos en la cola y la partida no ha terminado
            std::string noMovs = "No es poden fer mes moviments!";
            GraphicManager::getInstance()->drawFont(FONT_RED_30, posTextX, posTextY + 160, 0.8, noMovs);
        }
    }

    // 7. Si no se hace clic o se hace fuera del tablero, solo se visualiza el estado actual

    // Al final de la función, actualiza el estado anterior
    m_mouseEstatAnterior = mouseStatus;

    return false;
}

void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL)
    {
        m_cuaMoviments.guardaEnFitxer(m_nomFitxerMoviments);
    }
}



