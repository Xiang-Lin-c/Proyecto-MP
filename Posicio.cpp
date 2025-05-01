
#include "posicio.hpp"

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

string Posicio::toString() const {
	string posicio = "a1";
	posicio[0] = 'a' + m_columna;
	posicio[1] = '1' + (N_FILES - m_fila - 1);
	return posicio;

}
ostream& operator<<(ostream& out, const Posicio& posicio) {
	string x;
	x = posicio.toString();
	out << x;
	return out;
}