#include "posicio.h"

bool Posicio::operator==(const Posicio& posicio) const
{
	bool iguals = false;

	if (m_fila == posicio.m_fila && m_columna == posicio.m_columna)
	{
		iguals = true;
	}
	return iguals;
}

Posicio::Posicio(const string& pos) {
	m_fila = (N_FILES - 1) - (pos[1] - '1');
	m_columna = pos[0] - 'a';
}


void Posicio::fromString(const string& pos) {
	m_fila = (N_FILES - 1) - (pos[1] - '1');
	m_columna = pos[0] - 'a';
}

ifstream& Posicio::operator>>(ifstream& fitxer, Posicio& posicio) {
	string x;
	fitxer >> x;
	posicio.fromString(x);
	return fitxer;

}
ofstream& Posicio::operator<<(ofstream& fitxer, const Posicio& posicio) {
	string x;
	x = posicio.toString();
	fitxer << x;
	return fitxer;
}

void Posicio::llegeixFitxa(const string& nomFitxer, char& tipusFitxa, Posicio& posicio) {
	ifstream fitxer(nomFitxer);
	fitxer >> tipusFitxa;
	fitxer >> posicio;
	fitxer.close();
}

void Posicio::escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio) {
	ofstream fitxer(nomFitxer);
	fitxer << tipusFitxa << " ";
	fitxer << posicio;
	fitxer.close();
}