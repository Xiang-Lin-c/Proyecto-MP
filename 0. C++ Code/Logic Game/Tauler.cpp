#include "tauler.hpp"

Tauler::Tauler() {
	m_tauler.resize(N_FILES, vector<Fitxa>(N_COLUMNES));
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

queue<Posicio> Tauler::getPosicionsValides(Fitxa& fitxa, Posicio pos) {
	queue<Posicio> posicionsValides;
	vector<Posicio> direcciones = getDirecciones(fitxa);
	for (const Posicio& dir : direcciones) {
		int fila = pos.getFila() + dir.getFila();
		int columna = pos.getColumna() + dir.getColumna();
		Posicio PosAdjacent(fila, columna);
		if (esPosicioValida(PosAdjacent) && esCasellaBuida(PosAdjacent)) {
			if (!fitxa.esPosicioVisitada(PosAdjacent)) {
				fitxa.afegirPosicionsPossibles(PosAdjacent);
				posicionsValides.push(PosAdjacent);
			}

		}

		if (esPosicioValida(PosAdjacent) && esFichaContraria(fitxa, PosAdjacent)) {
			fila += dir.getFila();
			columna += dir.getColumna();
			Posicio posCapturada(fila, columna);
			if (esPosicioValida(posCapturada) && esCasellaBuida(posCapturada)) {
				if (!fitxa.esPosicioVisitada(posCapturada)) {
					posCapturada.setCaptura();
					fitxa.afegirPosicionsPossibles(posCapturada);
					posicionsValides.push(posCapturada);
				}
			}
		}
	}

	return posicionsValides;
}

queue<Posicio> Tauler::getPosicionsValidesCaptura(Fitxa& fitxa, Posicio pos) {
	queue<Posicio> posicionsValides;
	vector<Posicio> direcciones = getDirecciones(fitxa);
	for (const Posicio& dir : direcciones) {
		int fila = pos.getFila() + dir.getFila();
		int columna = pos.getColumna() + dir.getColumna();
		Posicio PosAdjacent(fila, columna);


		if (esPosicioValida(PosAdjacent) && esFichaContraria(fitxa, PosAdjacent)) {
			fila += dir.getFila();
			columna += dir.getColumna();
			Posicio posCapturada(fila, columna);
			if (esPosicioValida(posCapturada) && esCasellaBuida(posCapturada)) {
				if (!fitxa.esPosicioVisitada(posCapturada)) {
					posCapturada.setCaptura();
					fitxa.afegirPosicionsPossibles(posCapturada);
					posicionsValides.push(posCapturada);
				}
			}
		}
	}

	return posicionsValides;
}


queue<Posicio> Tauler::desplazarDama(Fitxa& fitxa, const Posicio& pos, const Posicio& direccio) {
	queue<Posicio> posicionsValides;
	int fila = pos.getFila() + direccio.getFila();
	int columna = pos.getColumna() + direccio.getColumna();
	Posicio PosAdjacent(fila, columna);

	if (esPosicioValida(PosAdjacent) && esCasellaBuida(PosAdjacent)) {
		if (!fitxa.esPosicioVisitada(PosAdjacent)) {
			fitxa.afegirPosicionsPossibles(PosAdjacent);
			posicionsValides.push(PosAdjacent);
		}

	}

	if (esPosicioValida(PosAdjacent) && esFichaContraria(fitxa, PosAdjacent)) {
		fila += direccio.getFila();
		columna += direccio.getColumna();
		Posicio posCapturada(fila, columna);
		if (esPosicioValida(posCapturada) && esCasellaBuida(posCapturada)) {
			if (!fitxa.esPosicioVisitada(posCapturada)) {
				posCapturada.setCaptura();
				fitxa.afegirPosicionsPossibles(posCapturada);
				posicionsValides.push(posCapturada);
			}
		}

	}

	return posicionsValides;
}

void Tauler::CalcularMovimentsValids(Fitxa& fitxa) {
	fitxa.netejaMovimentsValids();
	queue<Moviment> movimentsPendents;
	queue<Posicio> PosValides;
	Moviment movimentActual;
	Moviment movimentPendent;
	movimentsPendents.push(movimentActual);
	Posicio posActual;

	if (fitxa.getTipus() == TIPUS_NORMAL) {
		do {
			movimentActual = movimentsPendents.front();
			movimentsPendents.pop();
			if (movimentActual.getNumPassos() > 0) {
				posActual = movimentActual.getUltimaPosicio();
				PosValides = getPosicionsValidesCaptura(fitxa, posActual);
			}
			else {
				posActual = fitxa.getPosicio();
				PosValides = getPosicionsValides(fitxa, posActual);

			}

			while (!PosValides.empty()) {
				Moviment Actual = movimentActual;
				posActual = PosValides.front();
				movimentActual.afegirPosicio(posActual);
				PosValides.pop();
				while (!PosValides.empty()) {
					Posicio pos = PosValides.front();
					movimentPendent = Actual;
					movimentPendent.afegirPosicio(pos);
					movimentsPendents.push(movimentPendent);
					PosValides.pop();
				}
				PosValides = getPosicionsValidesCaptura(fitxa, posActual);

			}
			if (movimentActual.getNumPassos() != 0) {
				fitxa.afegeixMovimentValid(movimentActual);
			}

		} while (!movimentsPendents.empty());
	}
	else if (fitxa.getTipus() == TIPUS_DAMA) {
		do {
			movimentActual = movimentsPendents.front();
			movimentsPendents.pop();
			if (movimentActual.getNumPassos() > 0) {
				posActual = movimentActual.getUltimaPosicio();

				if (!posActual.getCaptura()) {
					Posicio direccio = getDireccioDama(fitxa, posActual);
					PosValides = desplazarDama(fitxa, posActual, direccio);
				}
				else {
					PosValides = getPosicionsValidesCaptura(fitxa, posActual);
				}
			}
			else {
				posActual = fitxa.getPosicio();
				PosValides = getPosicionsValides(fitxa, posActual);

			}

			while (!PosValides.empty()) {
				Moviment Actual = movimentActual;
				posActual = PosValides.front();
				movimentActual.afegirPosicio(posActual);
				PosValides.pop();
				while (!PosValides.empty()) {
					Posicio pos = PosValides.front();
					movimentPendent = Actual;
					fitxa.afegirPosicionsPossibles(posActual);
					movimentPendent.afegirPosicio(pos);
					movimentsPendents.push(movimentPendent);

					PosValides.pop();
				}
				if (!posActual.getCaptura()) {
					Posicio direccio = getDireccioDama(fitxa, posActual);
					PosValides = desplazarDama(fitxa, posActual, direccio);
				}
				else
					PosValides = getPosicionsValidesCaptura(fitxa, posActual);
			}
			if (movimentActual.getNumPassos() != 0) {
				fitxa.afegeixMovimentValid(movimentActual);
			}

		} while (!movimentsPendents.empty());
	}
}


void Tauler::actualitzaMovimentsValids() {
	for (int i = 0; i < N_FILES; i++) {
		for (int j = 0; j < N_COLUMNES; j++) {
			CalcularMovimentsValids(m_tauler[i][j]);
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

bool Tauler::esCasellaBuida(const Posicio& pos) const {
	return esPosicioValida(pos) && m_tauler[pos.getFila()][pos.getColumna()].esBuida();
}

bool Tauler::esFichaContraria(const Fitxa& ficha, const Posicio& pos) const {
	if (!esPosicioValida(pos)) return false;
	const Fitxa& otra = m_tauler[pos.getFila()][pos.getColumna()];
	return !otra.esBuida() && otra.getColor() != ficha.getColor();
}

vector<Posicio> Tauler::getDirecciones(const Fitxa& fitxa) const {
	vector<Posicio> direcciones;

	if (fitxa.esDama()) {
		direcciones.push_back(Posicio(-1, -1)); // Arriba izquierda
		direcciones.push_back(Posicio(-1, 1));  // Arriba derecha
		direcciones.push_back(Posicio(1, -1));  // Abajo izquierda
		direcciones.push_back(Posicio(1, 1));   // Abajo derecha
	}
	else {
		if (fitxa.getColor() == COLOR_BLANC) {
			direcciones.push_back(Posicio(-1, -1)); // Arriba izquierda
			direcciones.push_back(Posicio(-1, 1));  // Arriba derecha
		}
		else if (fitxa.getColor() == COLOR_NEGRE) {
			direcciones.push_back(Posicio(1, -1));  // Abajo izquierda
			direcciones.push_back(Posicio(1, 1));   // Abajo derecha
		}
	}

	return direcciones;
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

Posicio Tauler::getDireccioDama(const Fitxa fitxa, const Posicio& pos) const {
	Posicio direccio;
	int fila, columna;

	fila = pos.getFila() - fitxa.getPosicio().getFila();
	columna = pos.getColumna() - fitxa.getPosicio().getColumna();

	if (fila > 0 && columna > 0)
	{
		direccio = Posicio(1, 1); // Abajo derecha
	}
	else if (fila > 0 && columna < 0)
	{
		direccio = Posicio(1, -1); // Abajo izquierda
	}
	else if (fila < 0 && columna > 0)
	{
		direccio = Posicio(-1, 1); // Arriba derecha
	}
	else if (fila < 0 && columna < 0)
	{
		direccio = Posicio(-1, -1); // Arriba izquierda
	}

	return direccio;
}




bool Tauler::mouFitxa(Posicio origen, Posicio desti) {
	actualitzaMovimentsValids();

	if (!esPosicioValida(origen) || !esPosicioValida(desti) || origen == desti)
		return false;

	Fitxa& fitxaOrigen = m_tauler[origen.getFila()][origen.getColumna()];
	if (fitxaOrigen.esBuida())
		return false;

	int filaOrigen = origen.getFila();
	int colOrigen = origen.getColumna();
	int filaDesti = desti.getFila();
	int colDesti = desti.getColumna();

	// Cas especial: moviment de dama sense captura o amb captura simple
	if (fitxaOrigen.getTipus() == TIPUS_DAMA) {
		int diffFila = filaDesti - filaOrigen;
		int diffCol = colDesti - colOrigen;

		if (abs(diffFila) == abs(diffCol)) {
			int dirFila = (diffFila > 0) ? 1 : -1;
			int dirCol = (diffCol > 0) ? 1 : -1;

			int f = filaOrigen + dirFila;
			int c = colOrigen + dirCol;
			int numEnemics = 0;
			Posicio posCapt;

			while (f != filaDesti && c != colDesti) {
				Fitxa& fz = m_tauler[f][c];
				if (!fz.esBuida()) {
					if (fz.getColor() == fitxaOrigen.getColor() || numEnemics == 1)
						return false;
					numEnemics = 1;
					posCapt = Posicio(f, c);
				}
				f += dirFila;
				c += dirCol;
			}

			if (numEnemics == 1)
				eliminarFitxa(posCapt);

			m_tauler[filaDesti][colDesti] = fitxaOrigen;
			eliminarFitxa(origen);
			return true;
		}
	}

	// Buscar moviment vàlid
	int indexMov = -1, indexPaso = -1, maxCapt = 0, maxDamaCapt = 0;
	for (int i = 0; i < fitxaOrigen.getNumMoviments(); i++) {
		const Moviment& mv = fitxaOrigen.getMovimentValid(i);
		maxCapt = std::max(maxCapt, mv.getNumCaptures());
		maxDamaCapt = std::max(maxDamaCapt, mv.getNumDamaCapturada());

		for (int j = 0; j < mv.getNumPassos(); j++) {
			if (mv.getPosicio(j) == desti) {
				indexMov = i;
				indexPaso = j;
			}
		}
	}

	if (indexMov == -1)
		return false;

	const Moviment& movSel = fitxaOrigen.getMovimentValid(indexMov);
	int nCapturas = movSel.getEstatCaptures(indexPaso);

	if ((maxCapt > 0 && movSel.getNumCaptures() < maxCapt) ||
		(maxDamaCapt > 0 && movSel.getNumDamaCapturada() < maxDamaCapt))
		return false;

	for (int k = 0; k < nCapturas; k++)
		eliminarFitxa(movSel.getFitxaCapturada(k));

	m_tauler[filaDesti][colDesti] = fitxaOrigen;
	eliminarFitxa(origen);

	Fitxa& dest = m_tauler[filaDesti][colDesti];
	if (dest.getTipus() == TIPUS_NORMAL) {
		if ((dest.getColor() == COLOR_NEGRE && filaDesti == N_FILES - 1) ||
			(dest.getColor() == COLOR_BLANC && filaDesti == 0)) {
			dest.convertirDama();
		}
	}

	if (nCapturas < maxCapt)
		eliminarFitxa(Posicio(filaDesti, colDesti));

	return true;
}