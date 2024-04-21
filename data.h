
#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;

class Data {
    private:
        int numeroDeJobs; // n
        int numeroDeServidores; // m
        int custoFixoJobLocal; // p

        vector<int> capacidadeDosServidores; // b

        vector< vector<int> > matrizDeTempo; // t
        vector< vector<int> > matrizDeCusto; // c

        int valorOtimo;
        string caminho;

    public:
        Data(string caminho, int valorOtimo);

        int getNumeroDeJobs();
        int getNumeroDeServidores();
        int getCustoFixoJobLocal();

        vector<int> getCapacidadeDosServidores();

        vector< vector<int> > getMatrizDeTempo();
        vector< vector<int> > getMatrizDeCusto();
        string getPath();
};

#endif