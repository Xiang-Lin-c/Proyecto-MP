#include "Fitxa.h"

TipusFitxa Fitxa::getTipus() const {
    return m_tipus;
}

ColorFitxa Fitxa::getColor() const {
    return m_color;
}

Posicio Fitxa::getPosicio() const {
    return m_posicio;
}

bool Fitxa::esBuida() const {
    return m_tipus == TIPUS_EMPTY;
}

//Me toca a mi hacerlo