#include "Moviment.h"

// Constructor por defecto
Moviment::Moviment() : nPassos(0), nCaptures(0), captura(false) {}

// Constructor con posici�n inicial y tipo de ficha
Moviment::Moviment(const Posicio& inici, TipusFitxa tipus) : nPassos(1), nCaptures(0), captura(false), tipusFitxa(tipus) {
    trajecte[0] = inici; // La posici�n inicial es el primer paso
}



// A�ade una posici�n al movimiento
void Moviment::afegirPosicio(const Posicio& pos) 
{
    if (nPassos < MAX_PASSOS) 
    {
        trajecte[nPassos] = pos;
        nPassos++;
    }
}

// Elimina la �ltima posici�n del movimiento
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

// A�ade una ficha capturada al movimiento
void Moviment::afegirFitxaCapturada(const Posicio& pos) 
{
    if (nCaptures < MAX_CAPTURES) 
    {
        fitxesCapturades[nCaptures] = pos;
        nCaptures++;
        captura = true; // Indica que el movimiento implica capturas
    }
}

// Devuelve la posici�n inicial del movimiento
Posicio Moviment::inici() const 
{
    if (nPassos > 0) 
    {
        return trajecte[0];
    }
    return Posicio(); // Devuelve una posici�n vac�a si no hay pasos
}

// Devuelve la posici�n final del movimiento
Posicio Moviment::fi() const 
{
    if (nPassos > 0) {
        return trajecte[nPassos - 1];
    }
    return Posicio(); // Devuelve una posici�n vac�a si no hay pasos
}

// Devuelve el n�mero de pasos en el movimiento
int Moviment::getNumPassos() const 
{
    return nPassos;
}

// Devuelve el n�mero de fichas capturadas
int Moviment::getNumCaptures() const 
{
    return nCaptures;
}

// Indica si el movimiento es una captura
bool Moviment::esCaptura() const 
{
    return captura;
}

// Comprueba si el movimiento es v�lido
bool Moviment::esValid(const Tauler& tauler) const 
{
    // Implementaci�n b�sica: un movimiento es v�lido si tiene al menos un paso
    if (nPassos > 1)
    {
        return true;
    }
    return false;
}

// Comprueba si una posici�n es v�lida
bool Moviment::posicioValida(const Posicio& pos, const Tauler& tauler) const 
{
    // Implementaci�n b�sica: verifica si la posici�n est� dentro de los l�mites del tablero
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

bool Moviment::operator==(const Moviment& mov) const //lo usaremos para evitar a�adir movimientos repetidos
{
    // Compara el tipo de ficha asociada al movimiento
    if (tipusFitxa != mov.tipusFitxa)
    {
        return false;
    }

    // Compara el n�mero de pasos
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

    // Compara el n�mero de capturas
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


