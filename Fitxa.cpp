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
		m_movimentsValids[i].netejar(); // Limpia cada movimiento válido
	}
}

void Fitxa::afegeixMovimentValid(const Moviment& moviment) 
{
    if (m_numMoviments < MAX_MOVIMENTS) 
    {
        m_movimentsValids[m_numMoviments] = moviment;
        m_numMoviments++;
    }
}
void Fitxa::ModificaUltimMoviment(const Posicio& posicio) {
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
    return Moviment(); // Devuelve un movimiento vacío si el índice no es válido
}


void Fitxa::convertirDama() 
{
    if (m_tipus == TIPUS_NORMAL) 
    {
        m_tipus = TIPUS_DAMA;
        netejaMovimentsValids(); // Limpia los movimientos válidos al cambiar el tipo
    }
}

// Verifica si la ficha está vacía, por lo tanto se trata de una casilla vacía
bool Fitxa::esBuida() const 
{
    return m_tipus == TIPUS_EMPTY;
}

bool Fitxa::esDama() const {
    return m_tipus == TIPUS_DAMA;
}

//depenede del tipo de ficha
void Fitxa::generarMovimentsValids(const Tauler& tauler) 
{
    netejaMovimentsValids(); // Limpia los movimientos válidos actuales

    // Crea un movimiento inicial con la posición actual de la ficha
    Moviment movimentActual(m_posicio, m_tipus);
    Moviment movimentsPendents[MAX_MOVIMENTS];
    int nMovimentsPendents = 0;
    movimentsPendents[nMovimentsPendents++] = movimentActual;

    // Procesa los movimientos pendientes
    while (nMovimentsPendents > 0) {
        movimentActual = movimentsPendents[--nMovimentsPendents];
        Posicio posicioActual = movimentActual.fi();

        // Obtiene las posiciones válidas desde la posición actual
        Posicio posValides[MAX_PASSOS];
        int nPosValides = 0;
        tauler.getPosicionsPossibles(posicioActual, nPosValides, posValides);

        // Procesa cada posición válida
        for (int i = 0; i < nPosValides; i++) {
            Posicio novaPosicio = posValides[i];
            Moviment movimentPendent = movimentActual.auxMoviment();
            movimentPendent.afegirPosicio(novaPosicio);

            // Si es una captura, añade la ficha capturada
            if (tauler.esMovimentValid(posicioActual, novaPosicio)) {
                movimentPendent.afegirFitxaCapturada(novaPosicio);
            }

            // Añade el nuevo movimiento pendiente
            movimentsPendents[nMovimentsPendents++] = movimentPendent;
        }

        // Si el movimiento actual es válido, lo añade a los movimientos válidos
        if (movimentActual.esValid(tauler)) {
            afegeixMovimentValid(movimentActual);
        }
    }
}

