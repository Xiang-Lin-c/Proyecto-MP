#include "Fitxa.h"

TipusFitxa Fitxa::getTipus() const {
    return tipus;
}

ColorFitxa Fitxa::getColor() const {
    return color;
}

Posicio Fitxa::getPosicio() const {
    return posicio;
}

bool Fitxa::esBuida() const {
    return tipus == TIPUS_EMPTY;
}

