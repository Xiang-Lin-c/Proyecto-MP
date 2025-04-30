#include "Moviment.h"


Moviment::Moviment(const Posicio& inici, TipusFitxa tipus) : nPassos(1), nCaptures(0), captura(false), tipusFitxa(tipus) 
{
    trajecte[0] = inici; 
}


void Moviment::afegirPosicio(const Posicio& pos) 
{
    if (nPassos < MAX_PASSOS) 
    {
        trajecte[nPassos] = pos;
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


void Moviment::afegirFitxaCapturada(const Posicio& pos) 
{
    if (nCaptures < MAX_CAPTURES) 
    {
        fitxesCapturades[nCaptures] = pos;
        nCaptures++;
        m_captura = true; // Indica que el movimiento implica capturas
    }
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

// Indica si el movimiento es una captura
bool Moviment::esCaptura() const 
{
    return m_captura;
}

// Comprueba si el movimiento es válido
bool Moviment::esValid(const Tauler& tauler) const 
{
    // Implementación básica: un movimiento es válido si tiene al menos un paso
    if (nPassos > 1)
    {
        return true;
    }
    return false;
}


bool Moviment::posicioValida(const Posicio& pos, const Tauler& tauler) const 
{

    int fila = pos.getFila();
    int columna = pos.getColumna();
	if (fila >= 0 && fila < 8 && columna >= 0 && columna < 8) 
    {
		return true;
	}
    return false; 
}


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

bool Moviment::operator==(const Moviment& mov) const 
{
   
    if (tipusFitxa != mov.tipusFitxa)
    {
        return false;
    }

    if (nPassos != mov.nPassos)
    {
        return false;
    }

    for (int i = 0; i < nPassos; i++) 
    {
        if ((trajecte[i] == mov.trajecte[i])) 
        { 
            return false;
        }
    }

    
    if (nCaptures != mov.nCaptures) 
    {
        return false;
    }

    
    for (int i = 0; i < nCaptures; i++) 
    {
        if (!(fitxesCapturades[i] == mov.fitxesCapturades[i])) 
        { 
            return false;
        }
    }

    // Compara si ambos movimientos son de captura
    if (m_captura != mov.m_captura) 
    {
        return false;
    }

    return true;
}


