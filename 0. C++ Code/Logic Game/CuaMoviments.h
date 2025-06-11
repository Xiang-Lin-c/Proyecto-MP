#pragma once
#include "Moviment.h"

class CuaMoviments
{
private:
    struct Node
    {
        Moviment m_valor;
        Node* seguent;
        Node(const Moviment& mov) : m_valor(mov), seguent(nullptr) {}
    };
    Node* m_inici;
    Node* m_final;

public:
    CuaMoviments();
    ~CuaMoviments();

    void afegeix(const Moviment& moviment);

    bool primerMoviment(Moviment& moviment);

    void buidaCua();

    bool esBuida() const;

    bool carregaDeFitxer(const string& nomFitxer);

    bool guardaEnFitxer(const string& nomFitxer) const;
};