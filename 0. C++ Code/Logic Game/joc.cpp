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
	//TODO 1: Interactuar amb la crida per dibuixar gr�fics (sprites).
	// 	      Dibuixar a pantalla el fons i el gr�fic amb el tauler buit.
	//------------------------------------------------------------------

	//TODO 1.1 Afegir l'include de GraphicManager --> #include "GraphicManager.h"
	//TODO 1.2 Fer la crida de dibuixar un sprite --> GraphicManager::getInstance()->drawSprite(image, posX, posY);
	//	    Per comen�ar podem cridar el drawSprite amb els params --> 
	//          (GRAFIC_FONS,0,0) i 
	//          (GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER)

 


	//TODO 1.3: Dibuixar a pantalla el gr�fic amb el tauler i una fitxa blanca a la posici� (fila, columna ) del tauler


	//TODO 2: Interactuar amb el ratol�.
	//------------------------------------------------------------------
	//TODO 2.1: Dibuixar la fitxa blanca al tauler nom�s si estem pressionant el bot� del ratol�



    //TODO 2.2: Dibuixar la fitxa blanca al tauler nom�s si estem pressionant el bot� del ratol� i el ratol�
    // est� dins del l�mits del tauler

 

    //TODO 2.3: Dibuixar la fitxa blanca al tauler nom�s si estem pressionant el bot� del ratol� i el ratol�
    // est� dins del l�mits del tauler. Dibuixa la fitxa a la casella on est� el ratol�



    //TODO 2.4: Dibuixar la fitxa blanca a la casella on cliquem al ratol�. La fitxa s'ha de mantenir dibuixada
    // a la casella quan deixem de clicar amb el ratol�. Quan cliquem a una altra casella, la fitxa canvia de posici�
    // a la nova casella

        
        
    // TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Mostrar la posici� actual del ratol� a sota del tauler



	return false;
}
void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL)
    {
        m_cuaMoviments.guardaEnFitxer(m_nomFitxerMoviments);
    }
}



