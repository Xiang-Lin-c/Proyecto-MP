#include "Fitxa.h"

Fitxa::Fitxa() {
    m_tipus = TIPUS_EMPTY;
    m_color = COLOR_BUIT;
    m_posicio = Posicio();

}

TipusFitxa Fitxa::getTipus() const
{
    return m_tipus;
}


ColorFitxa Fitxa::getColor() const
{
    return m_color;
}

Posicio Fitxa::getPosicio() const
{
    return m_posicio;
}

void Fitxa::setTipus(TipusFitxa tipus)
{
    m_tipus = tipus;
}

void Fitxa::setColor(ColorFitxa color)
{
    m_color = color;
}

void Fitxa::setPosicio(Posicio posicio)
{
    m_posicio = posicio;
}

void Fitxa::netejaMovimentsValids()
{
    m_movimentsValids.clear();
    m_possicionsPosibles.clear();
}

void Fitxa::afegeixMovimentValid(Moviment& moviment)
{

    m_movimentsValids.push_back(moviment);

}

int Fitxa::getNumMoviments() const
{
    return m_movimentsValids.size();
}


Moviment Fitxa::getMovimentValid(int i) const
{
    if (i >= 0 && i < m_movimentsValids.size())
    {
        return m_movimentsValids[i];
    }
    return Moviment();
}


void Fitxa::convertirDama()
{
    if (m_tipus == TIPUS_NORMAL)
    {
        m_tipus = TIPUS_DAMA;
        netejaMovimentsValids();
    }
}

int Fitxa::getnumDamesCapturades(int i) const
{
    if (i >= 0 && i < m_movimentsValids.size()) {
        return m_movimentsValids[i].getNumDamaCapturada();
    }
    return 0;
}

bool Fitxa::esBuida() const
{
    return m_tipus == TIPUS_EMPTY;
}

bool Fitxa::esDama() const {
    return m_tipus == TIPUS_DAMA;
}

void Fitxa::afegirCapturaDama() {
    if (m_movimentsValids.size() < MAX_MOVIMENTS)
    {
        m_movimentsValids[m_movimentsValids.size()].afegirDamaCapturada();
    }
}
bool Fitxa::esMovimentValid(const Posicio& posicio) const {
    for (int i = 0; i < m_movimentsValids.size(); i++) {
        if (m_movimentsValids[i].esPosicioVisitada(posicio)) {
            return false;
        }
    }
    return true;
}
Moviment Fitxa::getMovimentActual() const {
    if (!m_movimentsValids.empty())
        return m_movimentsValids.back();

    return Moviment();
}

void Fitxa::afegirPosicionsPossibles(const Posicio& pos) {
    m_possicionsPosibles.push_back(pos);
}

bool Fitxa::esPosicioVisitada(const Posicio& pos) const {
    for (int i = 0; i < m_possicionsPosibles.size(); i++) {
        if (m_possicionsPosibles[i] == pos) {
            return true;
        }
    }
    return false;
}
