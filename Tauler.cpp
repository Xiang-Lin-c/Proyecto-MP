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

void Tauler::llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) {
	ifstream fitxer(nomFitxer);
	for (int i = 0; i < N_FILES; i++) {
		for (int j = 0; j < N_COLUMNES; j++) {
			tauler[i][j] = ' ';
		}
	}

	if (fitxer.is_open()) {
		char simbol;
		string posicio;
		while (fitxer >> simbol >> posicio) {
			char Cfila = posicio[1];
			char Ccolumna = posicio[0];
			int fila = N_FILES - (Cfila - '1') - 1;
			int columna = Ccolumna - 'a';
			tauler[fila][columna] = simbol;
		}
		fitxer.close();

	}
}
void Tauler::escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) {
	ofstream fitxer(nomFitxer);
	if (fitxer.is_open()) {
		for (int i = 0; i < N_FILES; i++) {
			for (int j = 0; j < N_COLUMNES; j++) {
				if (tauler[i][j] != ' ') {
					char fila = '1' + (N_FILES - i - 1);
					char columna = 'a' + j;
					fitxer << tauler[i][j] << " " << columna << fila << endl;
				}
			}
		}
		fitxer.close();
	}

}