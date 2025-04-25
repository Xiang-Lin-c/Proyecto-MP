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