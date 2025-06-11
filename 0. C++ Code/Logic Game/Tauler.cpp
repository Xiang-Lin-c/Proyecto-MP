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
				if (posActual.getCaptura())
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
				if (posActual.getCaptura())
					PosValides = getPosicionsValidesCaptura(fitxa, posActual);

			}
			if (movimentActual.getNumPassos() != 0) {
				CalcularFitxesCapturades(movimentActual, fitxa);
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
				CalcularFitxesCapturades(movimentActual, fitxa);
				fitxa.afegeixMovimentValid(movimentActual);
			}

		} while (!movimentsPendents.empty());
	}
}
void Tauler::CalcularFitxesCapturades(Moviment& MovimentActual, const Fitxa& fitxa) {
	Posicio pActual = fitxa.getPosicio();
	Posicio pos;
	for (int i = 0; i < MovimentActual.getNumPassos(); i++) {
		if (MovimentActual.getPosicio(i).getCaptura()) {
			pos = MovimentActual.getPosicio(i);
			Posicio direccio = getDireccioCaptura(pActual, pos);
			int fila = pActual.getFila() + direccio.getFila();
			int columna = pActual.getColumna() + direccio.getColumna();
			Posicio posCapturada(fila, columna);
			MovimentActual.afegirFitxaCapturada(posCapturada);
		}

		pActual = MovimentActual.getPosicio(i);
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

	m_tauler[fila][columna].setTipus(TIPUS_EMPTY);
	m_tauler[fila][columna].setColor(COLOR_BUIT);

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
Posicio Tauler::getDireccioCaptura(const Posicio& Inici, const Posicio& Final) {
	Posicio direccio;
	int fila, columna;

	fila = Final.getFila() - Inici.getFila();
	columna = Final.getColumna() - Inici.getColumna();

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

int Tauler::getIndexMoviment(const Fitxa& fitxa, const Posicio& desti) const {

	for (int i = 0; i < fitxa.getNumMoviments(); i++) {

		for (int j = 0; j < fitxa.getMovimentValid(i).getNumPassos(); j++) {
			if (fitxa.getMovimentValid(i).getPosicio(j) == desti) {
				return i;
			}
		}
	}

	return -1;
}

Posicio Tauler::recercaFitxaAmbCaptura(const Fitxa& fitxa, bool& fitxaCaptura) const {
	for (int i = 0; i < N_FILES; i++) {
		for (int j = 0; j < N_COLUMNES; j++) {
			if (m_tauler[i][j].getColor() == fitxa.getColor()) {
				Fitxa fitxaActual = m_tauler[i][j];
				for (int i = 0; i < fitxaActual.getNumMoviments(); i++) {
					if (fitxaActual.getMovimentValid(i).esCaptura()) {
						fitxaCaptura = true;
						return fitxaActual.getPosicio();
					}

				}
			}
		}
	}

	return Posicio();
}

bool Tauler::recercaMovimentAmbCaptura(const Fitxa& fitxa) const {
	for (int i = 0; i < fitxa.getNumMoviments(); i++) {
		if (fitxa.getMovimentValid(i).esCaptura()) {
			return true;
		}

	}
	return false;
}


bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {
	actualitzaMovimentsValids();
	int numCaptures, numMaxCaptures, indexMoviment, indexPosicio;
	int FilaOrigen, FilaDesti, ColumnaOrigen, ColumnaDesti;
	bool esUltimaPosicio, esCaptura, fitxaAmbCaptura = false, movimentAmbCaptura = false;
	Fitxa fitxa = m_tauler[origen.getFila()][origen.getColumna()];
	Posicio fitxaBufar;
	if (!esPosicioValida(origen) || !esPosicioValida(desti)) {
		return false;
	}

	if (origen == desti)
		return false;

	FilaOrigen = origen.getFila();
	ColumnaOrigen = origen.getColumna();
	FilaDesti = desti.getFila();
	ColumnaDesti = desti.getColumna();
	indexMoviment = getIndexMoviment(m_tauler[FilaOrigen][ColumnaOrigen], desti);

	if (indexMoviment == -1) {
		return false;
	}
	else {
		Moviment moviment = m_tauler[FilaOrigen][ColumnaOrigen].getMovimentValid(indexMoviment);
		if (moviment.getUltimaPosicio() == desti)
			esUltimaPosicio = true;
		else {
			esUltimaPosicio = false;
			indexPosicio = moviment.getIndexPosicio(desti);
		}

		if (esUltimaPosicio) {
			numCaptures = moviment.getNumCaptures();
			if (moviment.esCaptura()) {

				for (int i = 0; i < numCaptures; i++) {
					eliminarFitxa(moviment.getFitxaCapturada(i));
				}

			}
			else {
				movimentAmbCaptura = recercaMovimentAmbCaptura(fitxa);
				if (movimentAmbCaptura) {
					eliminarFitxa(origen);
					return false;
				}
				fitxaBufar = recercaFitxaAmbCaptura(fitxa, fitxaAmbCaptura);

				if (fitxaAmbCaptura)
					eliminarFitxa(fitxaBufar);

			}
			m_tauler[FilaDesti][ColumnaDesti].setColor(fitxa.getColor());
			m_tauler[FilaDesti][ColumnaDesti].setTipus(fitxa.getTipus());
			m_tauler[FilaDesti][ColumnaDesti].setPosicio(desti);
			eliminarFitxa(origen);
			if (m_tauler[FilaDesti][ColumnaDesti].getColor() == COLOR_BLANC && FilaDesti == 0) {
				m_tauler[FilaDesti][ColumnaDesti].convertirDama();
			}
			else if (m_tauler[FilaDesti][ColumnaDesti].getColor() == COLOR_NEGRE && FilaDesti == N_FILES - 1) {
				m_tauler[FilaDesti][ColumnaDesti].convertirDama();
			}

			return true;

		}
		else
		{
			numCaptures = moviment.getEstatCaptures(indexPosicio);
			numMaxCaptures = moviment.getNumCaptures();

			if (numCaptures > 0) {
				for (int i = 0; i < numCaptures; i++) {
					eliminarFitxa(moviment.getFitxaCapturada(i));
				}
				eliminarFitxa(origen);
				return true;
			}
			else
			{
				movimentAmbCaptura = recercaMovimentAmbCaptura(fitxa);
				if (movimentAmbCaptura) {
					eliminarFitxa(origen);
					return false;
				}
				m_tauler[FilaDesti][ColumnaDesti].setColor(fitxa.getColor());
				m_tauler[FilaDesti][ColumnaDesti].setTipus(fitxa.getTipus());
				m_tauler[FilaDesti][ColumnaDesti].setPosicio(desti);
				eliminarFitxa(origen);
				if (m_tauler[FilaDesti][ColumnaDesti].getColor() == COLOR_BLANC && FilaDesti == 0) {
					m_tauler[FilaDesti][ColumnaDesti].convertirDama();
				}
				else if (m_tauler[FilaDesti][ColumnaDesti].getColor() == COLOR_NEGRE && FilaDesti == N_FILES - 1) {
					m_tauler[FilaDesti][ColumnaDesti].convertirDama();
				}

				return true;
			}

		}
	}


	return true;
}


Fitxa Tauler::getFitxa(int fila, int columna) const {
	return m_tauler[fila][columna];
}
