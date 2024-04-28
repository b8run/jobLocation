#ifndef MODELO_H
#define MODELO_H

struct Modelo {
    int numeroDejobs; // Q
    int numeroDeServidores; // r
    int custoFixoJobLocal; // k

    Modelo() {}
    Modelo(int _numeroDejobs, int _numeroDeServidores, int _custoFixoJobLocal) : numeroDejobs(_numeroDejobs), numeroDeServidores(_numeroDeServidores), custoFixoJobLocal(_custoFixoJobLocal) {}
};

#endif