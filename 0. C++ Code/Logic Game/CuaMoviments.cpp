#include "CuaMoviments.h"

CuaMoviments::CuaMoviments() : m_inici(nullptr), m_final(nullptr) {}

CuaMoviments::~CuaMoviments() 
{
    buidaCua();
}

void CuaMoviments::afegeix(const Moviment& moviment) 
{
    Node* nou = new Node(moviment);
    if (m_final == nullptr) {
        m_inici = m_final = nou;
    } else {
        m_final->seguent = nou;
        m_final = nou;
    }
}

bool CuaMoviments::primerMoviment(Moviment& moviment)
{
    if (m_inici == nullptr)
        return false;
    Node* aux = m_inici;
    moviment = aux->m_valor;
    m_inici = m_inici->seguent;
    if (m_inici == nullptr)
        m_final = nullptr;
    delete aux;
    return true;
}

void CuaMoviments::buidaCua()
{
    Node* actual = m_inici;
    while (actual != nullptr) 
    {
        Node* aux = actual->seguent;
        delete actual;
        actual = aux;
    }
    m_inici = nullptr;
    m_final = nullptr;
}

bool CuaMoviments::esBuida() const 
{
    if (m_inici == nullptr)
        return true;
    else
        return false;
}

bool CuaMoviments::carregaDeFitxer(const string& nomFitxer) 
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open()==false)
        return false;

    buidaCua();

    string origen, desti;
    while (fitxer >> origen >> desti) 
    {
        Posicio posOrigen(origen);
        Posicio posDesti(desti);
        Moviment mov;
        mov.afegirPosicio(posOrigen);
        mov.afegirPosicio(posDesti);
        afegeix(mov);
    }
    fitxer.close();
    return true;
}

bool CuaMoviments::guardaEnFitxer(const string& nomFitxer) const 
{
    ofstream fitxer(nomFitxer);
    if (fitxer.is_open() == false)
        return false;

    Node* actual = m_inici;
    while (actual != nullptr) {
        fitxer << actual->m_valor.inici().toString() << " " << actual->m_valor.fi().toString() << endl;
        actual = actual->seguent;
    }
    fitxer.close();
    return true;
}

