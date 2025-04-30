#include "Tauler.h"
void Tauler::inicialitza(const string& nomFitxer) {
	ifstream fitxer(nomFitxer);
	if (fitxer.is_open()) {
		char tipusFitxa;
		ColorFitxa color;
		TipusFitxa tipus;
		Posicio posicio;
		string pos;
		while (fitxer >> tipusFitxa >> pos) {
			posicio.fromString(pos);
			if (tipusFitxa == 'O') {
				color = COLOR_BLANC; 
				tipus = TIPUS_NORMAL;
			}
			else if (tipusFitxa == 'X'){
				color = COLOR_NEGRE;
				tipus = TIPUS_NORMAL;
			}
			else if (tipusFitxa == 'D') {
				color = COLOR_BLANC;
				tipus = TIPUS_DAMA;
			}
			else
			{
				color = COLOR_NEGRE;
				tipus = TIPUS_DAMA;
			}
			inicialitzaFitxa(tipus, color, posicio);
		}
		fitxer.close();
	}
}

void Tauler::processaMovimentCaptura(Fitxa fitxa) {
	int fila = fitxa.getPosicio().getFila();
	int columna = fitxa.getPosicio().getColumna();
	Posicio pos;
	if (fitxa.getTipus() == TIPUS_NORMAL) {
		if (fitxa.getColor() == COLOR_BLANC) {
			if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila + 2, columna - 2)) && m_tauler[fila + 2][columna - 2].esBuida()) {
					pos = Posicio(fila + 2, columna - 2);
					fitxa.ModificaUltimMoviment(pos);
					fitxa.afegirCaptura(Posicio(fila + 1, columna - 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
			if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila + 2, columna + 2)) && m_tauler[fila + 2][columna + 2].esBuida()) {
					pos = Posicio(fila + 2, columna + 2);
					fitxa.ModificaUltimMoviment(pos);		
					fitxa.afegirCaptura(Posicio(fila + 1, columna + 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
		}
		else {
			if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila - 2, columna - 2)) && m_tauler[fila - 2][columna - 2].esBuida()) {
					pos = Posicio(fila - 2, columna - 2);
					fitxa.ModificaUltimMoviment(pos);	
					fitxa.afegirCaptura(Posicio(fila - 1, columna - 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
			if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila - 2, columna + 2)) && m_tauler[fila - 2][columna + 2].esBuida()) {
					pos = Posicio(fila - 2, columna + 2);
					fitxa.ModificaUltimMoviment(pos);	
					fitxa.afegirCaptura(Posicio(fila - 1, columna + 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
		}
	}
	else if (fitxa.getTipus() == TIPUS_DAMA) {
		if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila + 2, columna - 2)) && m_tauler[fila + 2][columna - 2].esBuida()) {
				pos = Posicio(fila + 2, columna - 2);
				fitxa.ModificaUltimMoviment(pos);	
				fitxa.afegirCaptura(Posicio(fila + 1, columna - 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}

		if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila + 2, columna + 2)) && m_tauler[fila + 2][columna + 2].esBuida()) {
				pos = Posicio(fila + 2, columna + 2);
				fitxa.ModificaUltimMoviment(pos);	
				fitxa.afegirCaptura(Posicio(fila + 1, columna + 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}

		if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila - 2, columna - 2)) && m_tauler[fila - 2][columna - 2].esBuida()) {
				pos = Posicio(fila - 2, columna - 2);
				fitxa.ModificaUltimMoviment(pos);	
				fitxa.afegirCaptura(Posicio(fila - 1, columna - 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}

		if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila - 2, columna + 2)) && m_tauler[fila - 2][columna + 2].esBuida()) {
				pos = Posicio(fila - 2, columna + 2);
				fitxa.ModificaUltimMoviment(pos);	
				fitxa.afegirCaptura(Posicio(fila - 1, columna + 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}
	}
}


void Tauler::actualitzaMovimentsFitxa(Fitxa& fitxa) {
	int fila = fitxa.getPosicio().getFila();
	int columna = fitxa.getPosicio().getColumna();
	Posicio pos;
	if (fitxa.getTipus() == TIPUS_NORMAL) {
		if (fitxa.getColor() == COLOR_BLANC) {
			if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].esBuida()) {
				pos = Posicio(fila + 1, columna - 1);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
			}
			else if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila + 2, columna - 2)) && m_tauler[fila + 2][columna - 2].esBuida()) {
					pos = Posicio(fila + 2, columna - 2);
					Moviment mov;
					mov.afegirPosicio(pos);
					fitxa.afegeixMovimentValid(mov);
					fitxa.afegirCaptura(Posicio(fila + 1, columna - 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
			if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].esBuida()) {
				pos = Posicio(fila + 1, columna + 1);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
			}
			else if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila + 2, columna + 2)) && m_tauler[fila + 2][columna + 2].esBuida()) {
					pos = Posicio(fila + 2, columna + 2);
					Moviment mov;
					mov.afegirPosicio(pos);
					fitxa.afegeixMovimentValid(mov);
					fitxa.afegirCaptura(Posicio(fila + 1, columna + 1));	
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
		}
		else {
			if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].esBuida()) {
				pos = Posicio(fila - 1, columna - 1);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
			}
			else if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila - 2, columna - 2)) && m_tauler[fila - 2][columna - 2].esBuida()) {
					pos = Posicio(fila - 2, columna - 2);
					Moviment mov;
					mov.afegirPosicio(pos);
					fitxa.afegeixMovimentValid(mov);
					fitxa.afegirCaptura(Posicio(fila - 1, columna - 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
			if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].esBuida()) {
				pos = Posicio(fila - 1, columna + 1);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
			}
			else if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila - 2, columna + 2)) && m_tauler[fila - 2][columna + 2].esBuida()) {
					pos = Posicio(fila - 2, columna + 2);
					Moviment mov;
					mov.afegirPosicio(pos);
					fitxa.afegeixMovimentValid(mov);
					fitxa.afegirCaptura(Posicio(fila - 1, columna + 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
				}
			}
		}
	}
	else if (fitxa.getTipus() == TIPUS_DAMA) {
		if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].esBuida()) {
			pos = Posicio(fila + 1, columna - 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
		}
		else if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila + 2, columna - 2)) && m_tauler[fila + 2][columna - 2].esBuida()) {
				pos = Posicio(fila + 2, columna - 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
				fitxa.afegirCaptura(Posicio(fila + 1, columna - 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}

		if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].esBuida()) {
			pos = Posicio(fila + 1, columna + 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
		}
		else if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila + 2, columna + 2)) && m_tauler[fila + 2][columna + 2].esBuida()) {
				pos = Posicio(fila + 2, columna + 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
				fitxa.afegirCaptura(Posicio(fila + 1, columna + 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}

		if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].esBuida()) {
			pos = Posicio(fila - 1, columna - 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
		}
		else if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila - 2, columna - 2)) && m_tauler[fila - 2][columna - 2].esBuida()) {
				pos = Posicio(fila - 2, columna - 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
				fitxa.afegirCaptura(Posicio(fila - 1, columna - 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}

		if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].esBuida()) {
			pos = Posicio(fila - 1, columna + 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
		}
		else if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila - 2, columna + 2)) && m_tauler[fila - 2][columna + 2].esBuida()) {
				pos = Posicio(fila - 2, columna + 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				fitxa.afegeixMovimentValid(mov);
				fitxa.afegirCaptura(Posicio(fila - 1, columna + 1));
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos));
			}
		}
	}
}

void Tauler::actualitzaMovimentsValids() {
    for (int i = 0; i < N_FILES; i++) {
        for (int j = 0; j < N_COLUMNES; j++) {
            if (!m_tauler[i][j].esBuida()) {
				m_tauler[i][j].netejaMovimentsValids();
                actualitzaMovimentsFitxa(m_tauler[i][j]);
            }
        }
    }
}

void Tauler::getPosicionsPossibles(Posicio origen, int& nPosicions, Posicio posicionsPossibles[]) {
	actualitzaMovimentsValids();
	int fila = origen.getFila();
	int columna = origen.getColumna();
	Fitxa fitxa = m_tauler[fila][columna];
	int nMoviments = fitxa.getNumMoviments();
	int nPassos;
	Posicio pos;
	bool trobat = false;
	nPosicions = 0;
	for (int i = 0; i < nMoviments; i++) {
		nPassos = fitxa.getMovimentValid(i).getNumPassos();
		for (int j = 0; j < nPassos; j++) {
			trobat = false;
			pos = fitxa.getMovimentValid(i).getPosicio(j);
			for (int z = 0; z < nPosicions; z++) {
				if (pos == posicionsPossibles[z]) {
					trobat = true;
					break;
				}
			}
			if (trobat == false) {
				posicionsPossibles[nPosicions] = pos;
				nPosicions++;
			}
		}
	}
}

bool Tauler::mouFitxa(Posicio origen, Posicio desti) {

}


string Tauler::toString() const {
	ofstream fitxa;
	TipusFitxa tipus;
	ColorFitxa color;

	for (int i = N_FILES - 1; i >= 0; i--) {
		for (int j = 0; j < N_COLUMNES; j++) {
			tipus = m_tauler[i][j].getTipus();
			color = m_tauler[i][j].getColor();
			if (tipus == TIPUS_EMPTY)
				fitxa << "_";
			else if (tipus == TIPUS_NORMAL) {
				if (color == COLOR_BLANC)
					fitxa << "O";
				else
					fitxa << "X";
			}
			else {
				if (color == COLOR_BLANC)
					fitxa << "D";
				else
					fitxa << "R";
			}
		}
		fitxa << endl;
	}
	fitxa.close();
}

bool Tauler::esPosicioValida(const Posicio& pos) const {
	if (pos.getFila() >= 0 && pos.getFila() < N_FILES && pos.getColumna() >= 0 && pos.getColumna() < N_COLUMNES) {
		return true;
	}
	return false;
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


void Tauler::inicialitzaFitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio) {
	int fila = posicio.getFila();
	int col = posicio.getColumna();

	if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES) {
		m_tauler[fila][col] = Fitxa(tipus, color, posicio);

	}
}


