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



void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments) {
    if (mode == MODE_JOC_NORMAL) {
       m_tauler.inicialitza(nomFitxerTauler);
       m_tauler.actualitzaMovimentsValids();

    }
    else
        if (mode == MODE_JOC_REPLAY) {

        }
}


bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{


    return false;
}




