#include "Moviment.h"





void Moviment::afegirPosicio(Posicio& pos)
{
    if (nPassos < m_maxPassos)
    {
        trajecte[nPassos] = pos;
        EstatCaptures[nPassos] = nCaptures;
        nPassos++;
    }
}

void Moviment::afegirFitxaCapturada(Posicio pos)
{
    if (nCaptures < m_maxCaptures)
    {
        fitxesCapturades[nCaptures] = pos;
        nCaptures++;
        EstatCaptures[nPassos - 1] = nCaptures;
        m_captura = true;
    }
}
void Moviment::afegirDamaCapturada()
{
    nDamaCapturada++;

}

void Moviment::eliminarUltimaPosicio()
{
    if (nPassos > 0) {
        nPassos = nPassos - 1;
    }
}


void Moviment::netejar()
{
    nPassos = 0;
    nCaptures = 0;
    m_captura = false;
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

    return fitxesCapturades[i];

}

bool Moviment::esCaptura() const
{
    return m_captura;
}


bool Moviment::esPosicioVisitada(const Posicio& pos) const {
    for (int i = 0; i < nPassos; ++i) {
        if (trajecte[i] == pos)
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

