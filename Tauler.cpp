#include "Tauler.h"

void Tauler::inicialitzaFitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& pos) {
    int fila = pos.getFila();
    int col = pos.getColumna();

    if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES) {
        tauler[fila][col] = Fitxa(tipus, color, pos);
    }
}

bool Tauler::esPosicioValida(const Posicio& pos) const {
    return pos.getFila() >= 0 && pos.getFila() < N_FILES &&
        pos.getColumna() >= 0 && pos.getColumna() < N_COLUMNES;
}
