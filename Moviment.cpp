#include "Moviment.h"

// Constructor por defecto
Moviment::Moviment() : nPassos(0), nCaptures(0), captura(false) {}

// Constructor con posición inicial y tipo de ficha
Moviment::Moviment(const Posicio& inici, TipusFitxa tipus) : nPassos(1), nCaptures(0), captura(false), tipusFitxa(tipus) {
    trajecte[0] = inici; // La posición inicial es el primer paso
}



// Añade una posición al movimiento
void Moviment::afegirPosicio(const Posicio& pos) 
{
    if (nPassos < MAX_PASSOS) 
    {
        trajecte[nPassos] = pos;
        nPassos++;
    }
}

// Elimina la última posición del movimiento
void Moviment::eliminarUltimaPosicio() 
{
    if (nPassos > 0) {
        nPassos=nPassos-1;
    }
}

// Limpia el movimiento (reinicia el estado)
void Moviment::netejar() 
{
    nPassos = 0;
    nCaptures = 0;
    captura = false;
}

// Añade una ficha capturada al movimiento
void Moviment::afegirFitxaCapturada(const Posicio& pos) 
{
    if (nCaptures < MAX_CAPTURES) 
    {
        fitxesCapturades[nCaptures] = pos;
        nCaptures++;
        captura = true; // Indica que el movimiento implica capturas
    }
}

// Devuelve la posición inicial del movimiento
Posicio Moviment::inici() const 
{
    if (nPassos > 0) 
    {
        return trajecte[0];
    }
    return Posicio(); // Devuelve una posición vacía si no hay pasos
}

// Devuelve la posición final del movimiento
Posicio Moviment::fi() const 
{
    if (nPassos > 0) {
        return trajecte[nPassos - 1];
    }
    return Posicio(); // Devuelve una posición vacía si no hay pasos
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
    return captura;
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

// Comprueba si una posición es válida
bool Moviment::posicioValida(const Posicio& pos, const Tauler& tauler) const 
{
    // Implementación básica: verifica si la posición está dentro de los límites del tablero
    int fila = pos.getFila();
    int columna = pos.getColumna();
	if (fila >= 0 && fila < 8 && columna >= 0 && columna < 8) 
    {
		return true;
	}
    return false; 
}

// Duplica el movimiento actual
Moviment Moviment::auxMoviment() const 
{
    Moviment aux;
    aux.nPassos = nPassos;
    aux.nCaptures = nCaptures;
    aux.captura = captura;
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

bool Moviment::operator==(const Moviment& mov) const //lo usaremos para evitar añadir movimientos repetidos
{
    // Compara el tipo de ficha asociada al movimiento
    if (tipusFitxa != mov.tipusFitxa)
    {
        return false;
    }

    // Compara el número de pasos
    if (nPassos != mov.nPassos)
    {
        return false;
    }

    // Compara el trayecto (todas las posiciones)
    for (int i = 0; i < nPassos; i++) 
    {
        if (!(trajecte[i] == mov.trajecte[i])) 
        { // Usa el operador == de Posicio
            return false;
        }
    }

    // Compara el número de capturas
    if (nCaptures != mov.nCaptures) 
    {
        return false;
    }

    // Compara las posiciones de las fichas capturadas
    for (int i = 0; i < nCaptures; i++) 
    {
        if (!(fitxesCapturades[i] == mov.fitxesCapturades[i])) 
        { // Usa el operador == de Posicio
            return false;
        }
    }

    // Compara si ambos movimientos son de captura
    if (captura != mov.captura) 
    {
        return false;
    }

    return true;
}


