#include "Moviment.h"





void Moviment::afegirPosicio(const Posicio& pos) 
{
    if (nPassos < MAX_PASSOS) 
    {
        trajecte[nPassos] = pos;
        EstatCaptures[nPassos] = nCaptures;
        nPassos++;
    }
}


void Moviment::eliminarUltimaPosicio() 
{ 
    if (nPassos > 0) {
        nPassos=nPassos-1;
    }
}


void Moviment::netejar() 
{
    nPassos = 0;
    nCaptures = 0;
    m_captura = false;
}


void Moviment::afegirFitxaCapturada(Posicio& pos) 
{
    if (nCaptures < MAX_CAPTURES) 
    {
        fitxesCapturades[nCaptures] = pos;
        nCaptures++;
        m_captura = true; // Indica que el movimiento implica capturas
    }
}
void Moviment::afegirDamaCapturada()
{
    nDamaCapturada++;

}

Posicio Moviment::inici() const 
{
    if (nPassos > 0) 
    {
        return trajecte[0];
    }
    return Posicio(); 
}


Posicio Moviment::fi() const 
{
    if (nPassos > 0) {
        return trajecte[nPassos - 1];
    }
    return Posicio();
}
Posicio Moviment::getPosicio(int index) const
{
	if (index >= 0 && index < nPassos)
	{
		return trajecte[index];
	}
	return Posicio(); // Devuelve una posición vacía si el índice no es válido
}
// Devuelve el número de pasos en el movimiento
int Moviment::getNumPassos() const 
{
    return nPassos;
}

// Devuelve el número de fichas capturadas
int Moviment::getNumCaptures() const 
{
    return nCaptures;
}
int Moviment::getNumDamaCapturada() const
{
	return nDamaCapturada;
}
int Moviment::getEstatCaptures(int index) const {
    return EstatCaptures[index];
}
// Indica si el movimiento es una captura
bool Moviment::esCaptura() const 
{
    return m_captura;
}

Posicio Moviment::getFitxaCapturada(int index) const
{
	if (index >= 0 && index < nCaptures)
	{
		return fitxesCapturades[index];
	}
	return Posicio(); // Devuelve una posición vacía si el índice no es válido
}
// Comprueba si el movimiento es válido





Moviment Moviment::auxMoviment() const 
{
    Moviment aux;
    aux.nPassos = nPassos;
    aux.nCaptures = nCaptures;
    aux.m_captura = m_captura;
    for (int i = 0; i < nPassos; i++) 
    {
        aux.trajecte[i] = trajecte[i];
    }
    for (int i = 0; i < nCaptures; i++) 
    {
        aux.fitxesCapturades[i] = fitxesCapturades[i];
    }
    return aux;
}



