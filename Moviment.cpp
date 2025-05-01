#include "Moviment.h"


Moviment::Moviment(const Posicio& inici, TipusFitxa tipus) : nPassos(1), nCaptures(0), m_captura(false), tipusFitxa(tipus) 
{
    trajecte[0] = inici; 
}


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


void Moviment::afegirFitxaCapturada(const Posicio& pos) 
{
    if (nCaptures < MAX_CAPTURES) 
    {
        fitxesCapturades[nCaptures] = pos;
        nCaptures++;
        m_captura = true; 
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
	return Posicio();
}

int Moviment::getNumPassos() const 
{
    return nPassos;
}


int Moviment::getNumCaptures() const 
{
    return nCaptures;
}

int Moviment::getNumDamaCapturada() const 
{
    return nDamaCapturada;
}


int Moviment::getEstatCaptures(int i) const 
{
    if (i >= 0 && i < nCaptures) 
    {
        return EstatCaptures[i];
    }
    return 0; 
}

Posicio Moviment::getFitxaCapturada(int i) const 
{
    if (i >= 0 && i < nCaptures) 
    {
        return fitxesCapturades[i];
    }
    return Posicio(); 
}

bool Moviment::esCaptura() const 
{
    return m_captura;
}

bool Moviment::esValid(const Tauler& tauler) const 
{
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


void Moviment::eliminarFitxaCapturada(const Posicio& pos)
{
    bool aux = false; 

    for (int i = 0; i < nCaptures; i++)
    {
        if (!aux && fitxesCapturades[i] == pos)
        {
            for (int j = i; j < nCaptures - 1; j++)
            {
                fitxesCapturades[j] = fitxesCapturades[j + 1];
            }
            aux = true;
        }

        if (aux && i < nCaptures - 1)
        {
            fitxesCapturades[i] = fitxesCapturades[i + 1];
        }
    }
    if (aux)
    {
        nCaptures--;
    }
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

    if (m_captura != mov.m_captura) 
    {
        return false;
    }

    return true;
}


