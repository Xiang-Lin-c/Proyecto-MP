#include "tauler.hpp"

Tauler::Tauler() {
	for (int i = 0; i < N_FILES; i++) {
		for (int j = 0; j < N_COLUMNES; j++) {
			m_tauler[i][j].setTipus(TIPUS_EMPTY);
			m_tauler[i][j].setPosicio(Posicio(i, j));
		}
	}
}

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
			else if (tipusFitxa == 'X') {
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

void Tauler::processaMovimentCaptura(const Fitxa& fitxa, int m_fila, int m_columna) {
	int fila = fitxa.getPosicio().getFila();
	int columna = fitxa.getPosicio().getColumna();
	Posicio pos;



	if (fitxa.getTipus() == TIPUS_NORMAL) {
		if (fitxa.getColor() == COLOR_NEGRE) {
			// Movimiento hacia abajo izquierda
			if (esPosicioValida(Posicio(fila + 1, columna - 1)) &&
				m_tauler[fila + 1][columna - 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila + 2, columna - 2)) &&
					m_tauler[fila + 2][columna - 2].esBuida()) {
					pos = Posicio(fila + 2, columna - 2);
					m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
					m_tauler[m_fila][m_columna].ModificaUltimMovimentCaptura(Posicio(fila + 1, columna - 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna);
				}
			}
			// Movimiento hacia abajo derecha
			if (esPosicioValida(Posicio(fila + 1, columna + 1)) &&
				m_tauler[fila + 1][columna + 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila + 2, columna + 2)) &&
					m_tauler[fila + 2][columna + 2].esBuida()) {
					pos = Posicio(fila + 2, columna + 2);
					m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
					m_tauler[m_fila][m_columna].ModificaUltimMovimentCaptura(Posicio(fila + 1, columna + 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna);
				}
			}
		}
		else {
			// Movimiento hacia arriba izquierda
			if (esPosicioValida(Posicio(fila - 1, columna - 1)) &&
				m_tauler[fila - 1][columna - 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila - 2, columna - 2)) &&
					m_tauler[fila - 2][columna - 2].esBuida()) {
					pos = Posicio(fila - 2, columna - 2);
					m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
					m_tauler[m_fila][m_columna].ModificaUltimMovimentCaptura(Posicio(fila - 1, columna - 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna);
				}
			}
			// Movimiento hacia arriba derecha
			if (esPosicioValida(Posicio(fila - 1, columna + 1)) &&
				m_tauler[fila - 1][columna + 1].getColor() != fitxa.getColor()) {
				if (esPosicioValida(Posicio(fila - 2, columna + 2)) &&
					m_tauler[fila - 2][columna + 2].esBuida()) {
					pos = Posicio(fila - 2, columna + 2);
					m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
					m_tauler[m_fila][m_columna].ModificaUltimMovimentCaptura(Posicio(fila - 1, columna + 1));
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna);
				}
			}
		}
	}
}

void Tauler::desplazarDama(Fitxa fitxa, int m_fila, int m_columna, int direccion) {
	Posicio pos;
	int fila = fitxa.getPosicio().getFila();
	int columna = fitxa.getPosicio().getColumna();
	switch (direccion) {
	case 1: // arriba izquierda
		if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].esBuida()) {
			pos = Posicio(fila + 1, columna - 1);
			m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
			desplazarDama(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna, direccion);
		}
		break;
	case 2: // arriba derecha
		if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].esBuida()) {
			pos = Posicio(fila + 1, columna + 1);
			m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
			desplazarDama(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna, direccion);
		}
		break;
	case 3: // abajo izquierda
		if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].esBuida()) {
			pos = Posicio(fila - 1, columna - 1);
			m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
			desplazarDama(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna, direccion);
		}
		break;
	case 4: // abajo derecha
		if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna - 1].esBuida()) {
			pos = Posicio(fila - 1, columna + 1);
			m_tauler[m_fila][m_columna].ModificaUltimMoviment(pos);
			desplazarDama(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), m_fila, m_columna, direccion);
		}
		break;
	}
}


void Tauler::actualitzaMovimentsFitxa(Fitxa& fitxa) {
	const int fila = fitxa.getPosicio().getFila();
	const int columna = fitxa.getPosicio().getColumna();
	Posicio pos;
	if (fitxa.getTipus() == TIPUS_NORMAL) {
		if (fitxa.getColor() == COLOR_NEGRE) {
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
					mov.afegirFitxaCapturada(Posicio(fila + 1, columna - 1));
					fitxa.afegeixMovimentValid(mov);
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
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
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
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
					mov.afegirFitxaCapturada(Posicio(fila - 1, columna - 1));
					fitxa.afegeixMovimentValid(mov);

					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
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
					mov.afegirFitxaCapturada(Posicio(fila - 1, columna + 1));
					fitxa.afegeixMovimentValid(mov);
					processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
				}
			}
		}
	}
	else if (fitxa.getTipus() == TIPUS_DAMA) {
		int direccion;                                         //indicador de direccion de movimiento(1: arriba izquierda, 2: arriba y derecha, 3: abajo izquierda, 4: abajo derecha)
		if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].esBuida()) {
			direccion = 1;
			pos = Posicio(fila + 1, columna - 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
			desplazarDama(fitxa, fila, columna, direccion);
		}

		if (esPosicioValida(Posicio(fila + 1, columna - 1)) && m_tauler[fila + 1][columna - 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila + 2, columna - 2)) && m_tauler[fila + 2][columna - 2].esBuida()) {
				pos = Posicio(fila + 2, columna - 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				mov.afegirFitxaCapturada(Posicio(fila + 1, columna - 1));
				fitxa.afegeixMovimentValid(mov);
				if (m_tauler[fila + 1][columna - 1].getTipus() == TIPUS_DAMA) {
					fitxa.afegirCapturaDama();
				}
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
			}

		}

		if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].esBuida()) {
			direccion = 2;
			pos = Posicio(fila + 1, columna + 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
			desplazarDama(fitxa, fila, columna, direccion);
		}
		if (esPosicioValida(Posicio(fila + 1, columna + 1)) && m_tauler[fila + 1][columna + 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila + 2, columna + 2)) && m_tauler[fila + 2][columna + 2].esBuida()) {
				pos = Posicio(fila + 2, columna + 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				mov.afegirFitxaCapturada(Posicio(fila + 1, columna + 1));
				fitxa.afegeixMovimentValid(mov);
				if (m_tauler[fila + 1][columna + 1].getTipus() == TIPUS_DAMA) {
					fitxa.afegirCapturaDama();
				}
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
			}
		}

		if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].esBuida()) {
			direccion = 3;
			pos = Posicio(fila - 1, columna - 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
			desplazarDama(fitxa, fila, columna, direccion);
		}
		if (esPosicioValida(Posicio(fila - 1, columna - 1)) && m_tauler[fila - 1][columna - 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila - 2, columna - 2)) && m_tauler[fila - 2][columna - 2].esBuida()) {
				pos = Posicio(fila - 2, columna - 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				mov.afegirFitxaCapturada(Posicio(fila - 1, columna - 1));
				fitxa.afegeixMovimentValid(mov);
				if (m_tauler[fila - 1][columna - 1].getTipus() == TIPUS_DAMA) {
					fitxa.afegirCapturaDama();
				}
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
			}
		}

		if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].esBuida()) {
			direccion = 4;
			pos = Posicio(fila - 1, columna + 1);
			Moviment mov;
			mov.afegirPosicio(pos);
			fitxa.afegeixMovimentValid(mov);
			desplazarDama(fitxa, fila, columna, direccion);
		}
		if (esPosicioValida(Posicio(fila - 1, columna + 1)) && m_tauler[fila - 1][columna + 1].getColor() != fitxa.getColor()) {
			if (esPosicioValida(Posicio(fila - 2, columna + 2)) && m_tauler[fila - 2][columna + 2].esBuida()) {
				pos = Posicio(fila - 2, columna + 2);
				Moviment mov;
				mov.afegirPosicio(pos);
				mov.afegirFitxaCapturada(Posicio(fila + 1, columna - 1));
				fitxa.afegeixMovimentValid(mov);
				if (m_tauler[fila - 1][columna + 1].getTipus() == TIPUS_DAMA) {
					fitxa.afegirCapturaDama();
				}
				processaMovimentCaptura(Fitxa(fitxa.getTipus(), fitxa.getColor(), pos), fila, columna);
			}
		}

	}
}

void Tauler::actualitzaMovimentsValids() {
	for (int i = 0; i < N_FILES; i++) {
		for (int j = 0; j < N_COLUMNES; j++) {
			actualitzaMovimentsFitxa(m_tauler[i][j]);

		}
	}
}

void Tauler::getPosicionsPossibles(Posicio origen, int& nPosicions, Posicio posicionsPossibles[]) {
	actualitzaMovimentsValids();
	nPosicions = 0;

	if (!esPosicioValida(origen)) return;

	Fitxa fitxa = m_tauler[origen.getFila()][origen.getColumna()];
	int nMoviments = fitxa.getNumMoviments();

	for (int i = 0; i < nMoviments; ++i) {
		const Moviment& moviment = fitxa.getMovimentValid(i);
		int nPassos = moviment.getNumPassos();

		for (int j = 0; j < nPassos; ++j) {
			Posicio pos = moviment.getPosicio(j);
			bool trobat = false;

			for (int z = 0; z < nPosicions; ++z) {
				if (pos == posicionsPossibles[z]) {
					trobat = true;
				}
			}

			if (!trobat) {
				posicionsPossibles[nPosicions] = pos;
				++nPosicions;
			}
		}
	}
}




void Tauler::eliminarFitxa(Posicio pos) {
	int fila = pos.getFila();
	int columna = pos.getColumna();
	m_tauler[fila][columna].netejaMovimentsValids();
	m_tauler[fila][columna].setTipus(TIPUS_EMPTY);
	m_tauler[fila][columna].setPosicio(pos);
}

void Tauler::inicialitzaFitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio) {
	int fila = posicio.getFila();
	int columna = posicio.getColumna();
	m_tauler[fila][columna].setTipus(tipus);
	m_tauler[fila][columna].setColor(color);
	m_tauler[fila][columna].setPosicio(posicio);
	m_tauler[fila][columna].netejaMovimentsValids();
}

bool Tauler::mouFitxa(Posicio origen, Posicio desti) {
	actualitzaMovimentsValids();


	if (!esPosicioValida(origen) || !esPosicioValida(desti) || origen == desti) {
		return false;
	}
	Fitxa& fitxaOrigen = m_tauler[origen.getFila()][origen.getColumna()];
	if (fitxaOrigen.esBuida()) {
		return false;
	}


	int filaOrigen = origen.getFila();
	int colOrigen = origen.getColumna();
	int filaDesti = desti.getFila();
	int colDesti = desti.getColumna();


	int maxCapt = 0;
	int maxDamaCapt = 0;
	int nCapturas = 0;


	if (fitxaOrigen.getTipus() == TIPUS_DAMA) {
		int diffFila = filaDesti - filaOrigen;
		int diffCol = colDesti - colOrigen;


		if (diffFila == diffCol || diffFila == -diffCol) {

			int dirFila;
			if (diffFila > 0) {
				dirFila = 1;
			}
			else {
				dirFila = -1;
			}

			int dirCol;
			if (diffCol > 0) {
				dirCol = 1;
			}
			else {
				dirCol = -1;
			}

			int f = filaOrigen + dirFila;
			int c = colOrigen + dirCol;
			bool soloVacios = true;
			int  numEnemigos = 0;
			Posicio posCapt;

			while (f != filaDesti && c != colDesti) {
				Fitxa& fz = m_tauler[f][c];
				if (!fz.esBuida()) {
					if (fz.getColor() == fitxaOrigen.getColor() || numEnemigos == 1) {
						soloVacios = false;
					}
					else {
						numEnemigos = 1;
						posCapt = Posicio(f, c);
					}
				}
				f += dirFila;
				c += dirCol;
			}

			if (soloVacios && numEnemigos == 0) {
				m_tauler[filaDesti][colDesti] = fitxaOrigen;
				eliminarFitxa(origen);
				return true;
			}
			if (soloVacios && numEnemigos == 1) {
				eliminarFitxa(posCapt);
				m_tauler[filaDesti][colDesti] = fitxaOrigen;
				eliminarFitxa(origen);
				return true;
			}

		}
	}

	int indexMov = -1;
	int indexPaso = -1;
	bool encontrado = false;

	for (int i = 0; i < fitxaOrigen.getNumMoviments(); i++) {
		const Moviment& mv = fitxaOrigen.getMovimentValid(i);
		if (mv.getNumCaptures() > maxCapt) {
			maxCapt = mv.getNumCaptures();
		}
		if (mv.getNumDamaCapturada() > maxDamaCapt) {
			maxDamaCapt = mv.getNumDamaCapturada();
		}
		for (int j = 0; j < mv.getNumPassos(); j++) {
			if (mv.getPosicio(j) == desti) {
				indexMov = i;
				indexPaso = j;
				encontrado = true;
			}
		}
	}
	if (!encontrado) {
		return false;
	}

	const Moviment& movSel = fitxaOrigen.getMovimentValid(indexMov);
	nCapturas = movSel.getEstatCaptures(indexPaso);

	if ((maxCapt > 0 && movSel.getNumCaptures() < maxCapt) ||
		(maxDamaCapt > 0 && movSel.getNumDamaCapturada() < maxDamaCapt)) {
		return false;
	}

	for (int k = 0; k < nCapturas; k++) {
		eliminarFitxa(movSel.getFitxaCapturada(k));
	}


	m_tauler[filaDesti][colDesti] = fitxaOrigen;
	eliminarFitxa(origen);


	Fitxa& dest = m_tauler[filaDesti][colDesti];
	if (dest.getTipus() == TIPUS_NORMAL) {
		if (dest.getColor() == COLOR_NEGRE && filaDesti == N_FILES - 1) {
			dest.convertirDama();
		}
		else if (dest.getColor() == COLOR_BLANC && filaDesti == 0) {
			dest.convertirDama();
		}
	}


	if (nCapturas < maxCapt) {
		eliminarFitxa(Posicio(filaDesti, colDesti));
	}

	return true;
}













string Tauler::toString() const {
	string resultat;
	TipusFitxa tipus;
	ColorFitxa color;

	for (int i = 0; i < N_FILES; i++) {
		resultat = resultat + (char)('0' + (8 - i)) + ": ";  // imprimeix '8'..'1'

		for (int j = 0; j < N_COLUMNES; j++) {
			tipus = m_tauler[i][j].getTipus();
			color = m_tauler[i][j].getColor();

			if (tipus == TIPUS_EMPTY)
				resultat = resultat + "_ ";
			else if (tipus == TIPUS_NORMAL) {
				if (color == COLOR_BLANC)
					resultat = resultat + "O ";
				else
					resultat = resultat + "X ";
			}
			else { // TIPUS_DAMA
				if (color == COLOR_BLANC)
					resultat = resultat + "D ";
				else
					resultat = resultat + "R ";
			}
		}

		resultat = resultat + "\n";
	}

	resultat = resultat + "   a b c d e f g h\n";
	return resultat;
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

