#ifndef SOLUCAOGULOSA_H
#define SOLUCAOGULOSA_H
#include "alocacao.h"

using namespace std;

struct SolucaoGulosa {
    vector<Alocacao> alocacao;
    int custoTotalPorAlocacao;
    int total;

    SolucaoGulosa() {}
    SolucaoGulosa(vector<Alocacao> _alocacao, int _custoTotalPorAlocacao, int _total) : alocacao(_alocacao), custoTotalPorAlocacao(_custoTotalPorAlocacao), total(_total) {}
};

#endif