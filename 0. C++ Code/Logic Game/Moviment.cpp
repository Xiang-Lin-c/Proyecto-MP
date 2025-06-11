#include "Moviment.h"





void Moviment::afegirPosicio(Posicio& pos)
{
    if (nPassos < m_maxPassos)
    {
        bool trobat = false;
        for (int i = 0; i < trajecte.size(); i++) {
            if (trajecte[i] == pos) {
                trobat = true;
                break;
            }
        }
        if (trobat)
            return;

        trajecte.push_back(pos);
        setnCaptures();
        EstatCaptures.push_back(nCaptures);
        nPassos++;
    }
}
void Moviment::afegirFitxaCapturada(const Posicio& pos) {
    fitxesCapturades.push_back(pos);
}


void Moviment::afegirDamaCapturada()
{
    nDamaCapturada++;

}

void Moviment::eliminarUltimaPosicio()
{
    trajecte.pop_back();
    nPassos--;

}


void Moviment::netejar()
{
    nCaptures = 0;
    m_captura = false;
    trajecte.clear();
    fitxesCapturades.clear();
    EstatCaptures.clear();
    nPassos = 0;
    nDamaCapturada = 0;
    direccio = Posicio(0, 0);
}


Posicio Moviment::inici() const
{
    if (trajecte.size() > 0)
    {
        return trajecte.front();
    }
    return Posicio();
}


Posicio Moviment::fi() const
{
    if (trajecte.size() > 0) {
        return trajecte.back();
    }
    return Posicio();
}
Posicio Moviment::getPosicio(int index) const
{
    if (index >= 0 && index < trajecte.size())
    {
        return trajecte[index];
    }
    return Posicio();
}

Posicio Moviment::getUltimaPosicio() const {
    if (!trajecte.empty()) {
        return trajecte.back();
    }
    else
        return Posicio();
}


int Moviment::getNumPassos() const
{
    return trajecte.size();
}


int Moviment::getNumCaptures() const
{
    return nCaptures;
}

int Moviment::getNumDamaCapturada() const
{
    return nDamaCapturada;
}
int Moviment::getIndexPosicio(const Posicio& pos) const {
    for (int i = 0; i < trajecte.size(); i++) {
        if (trajecte[i] == pos) {
            return i;
        }
    }

    return -1;
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
    if (i < fitxesCapturades.size())
        return fitxesCapturades[i];

    else
        return Posicio();

}

bool Moviment::esCaptura() const
{

    return m_captura;
}


bool Moviment::esPosicioVisitada(const Posicio& pos) const {
    for (int i = 0; i < trajecte.size(); ++i) {
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

void Moviment::setnCaptures() {
    nCaptures = 0;

    for (int i = 0; i < trajecte.size(); i++) {
        if (trajecte[i].getCaptura())
        {
            nCaptures++;
        }

    }
    if (nCaptures > 0)
        m_captura = true;
    else
        m_captura = false;
}
