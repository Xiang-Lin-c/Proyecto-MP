#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"
#include "CuaMoviments.h"

using namespace std;


class Joc 
{

public:
    Joc() {};
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void finalitza();
    
    
private:
    Tauler m_tauler;
    CuaMoviments m_cua;
};

#endif 
