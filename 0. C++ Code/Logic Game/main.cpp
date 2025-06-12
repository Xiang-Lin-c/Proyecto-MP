//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./joc.hpp"
#include "./info_joc.hpp"


int main(int argc, const char* argv[])
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    pantalla.show();

    Joc joc;
    string nomFitxerTauler = "data/Games/tauler_inicial.txt";
    string nomFitxerMoviments = "data/Games/moviments.txt";

    int opcio = 0;
    do {
        cout << "Tria el mode de joc:" << endl;
        cout << "1.Mode Normal" << endl;
        cout << "2.Mode Replay" << endl;
        cout << "Mode 1 o 2: ";
        cin >> opcio;
    } while (opcio != 1 && opcio != 2);

    ModeJoc modeSeleccionat = (opcio == 1) ? MODE_JOC_NORMAL : MODE_JOC_REPLAY;
    joc.inicialitza(modeSeleccionat, nomFitxerTauler, nomFitxerMoviments);

    do
    {
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        bool final = joc.actualitza(mousePosX, mousePosY, mouseStatus);

        pantalla.update();
        if (final) {
            joc.finalitza();
            break;
        }
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));

    if (joc.getFinalPartida()) {
        do
        {
            pantalla.processEvents();

            bool mouseStatus = Mouse_getBtnLeft();
            int mousePosX = Mouse_getX();
            int mousePosY = Mouse_getY();

            joc.MostrarGuanyador(mousePosX, mousePosY, mouseStatus);

            pantalla.update();

        } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
    }

    SDL_Quit();
    return 0;
}

