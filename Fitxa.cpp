#include "Fitxa.h"


Fitxa::Fitxa() : m_tipus(TIPUS_EMPTY), m_color(COLOR_NEGRE), m_numMoviments(0) {}


Fitxa::Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio posicio): m_tipus(tipus), m_color(color), m_posicio(posicio), m_numMoviments(0) {}


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
    m_numMoviments = 0; 
	for (int i = 0; i < MAX_MOVIMENTS; i++)
	{
		m_movimentsValids[i].netejar(); 
	}
}

void Fitxa::afegeixMovimentValid(Moviment& moviment) 
{
    if (m_numMoviments < MAX_MOVIMENTS) 
    {
        m_movimentsValids[m_numMoviments] = moviment;
        m_numMoviments++;
    }
}
void Fitxa::ModificaUltimMoviment( Posicio& posicio) {
    m_movimentsValids[m_numMoviments].afegirPosicio(posicio);
}
int Fitxa::getNumMoviments() const 
{
    return m_numMoviments;
}


Moviment Fitxa::getMovimentValid(int i) const 
{
    if (i >= 0 && i < m_numMoviments) 
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

int Fitxa::getnumDamesCapturades(int index) const {
	if (index >= 0 && index < m_numMoviments) {
		return m_movimentsValids[index].getNumDamaCapturada();
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
void Fitxa::afegirCaptura(Posicio& pos)
{
	if (m_numMoviments < MAX_MOVIMENTS)
	{
		m_movimentsValids[m_numMoviments].afegirFitxaCapturada(pos);
	}
}
void Fitxa::afegirCapturaDama() {
    if (m_numMoviments < MAX_MOVIMENTS)
    {
        m_movimentsValids[m_numMoviments].afegirDamaCapturada();
    }
}



