#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "data.h"
#include <vector>

using namespace std;

Data::Data(string caminho, int valorOtimo) {
    this->caminho = caminho;
    this->valorOtimo = valorOtimo;
    
    ifstream arquivo(caminho);

    int aux;

    if (arquivo.is_open()) {
        while (arquivo.good()) {

            arquivo >> numeroDeJobs;
            arquivo >> numeroDeServidores;
            arquivo >> custoFixoJobLocal;


            for(int i = 0; i < numeroDeServidores; i++) {
                arquivo >> aux;
                capacidadeDosServidores.push_back(aux);
            }

            vector<int> vetAux;

            for(int i = 0; i < numeroDeServidores + 1; i++) {
                for(int j = 0; j < numeroDeJobs + 1; j++) {
                    arquivo >> aux;
                    vetAux.push_back(aux);
                }
                matrizDeTempo.push_back(vetAux);
                vetAux.clear();
            }

            for(int i = 0; i < numeroDeServidores + 1; i++) {
                for(int j = 0; j < numeroDeJobs + 1; j++) {
                    arquivo >> aux;
                    vetAux.push_back(aux);
                }
                matrizDeCusto.push_back(vetAux);
                vetAux.clear();
            }

            break;
        }
    }else cout << "Erro ao abrir o arquivo do caminho " << caminho;
}


int Data::getNumeroDeJobs() {
    return numeroDeJobs;
}

int Data::getNumeroDeServidores() {
    return numeroDeServidores;
}

int Data::getCustoFixoJobLocal() {
    return custoFixoJobLocal;
}

vector<int> Data::getCapacidadeDosServidores() {
    return capacidadeDosServidores;
}

vector< vector<int> > Data::getMatrizDeTempo() {
    return matrizDeTempo;
}

vector< vector<int> > Data::getMatrizDeCusto() {
    return matrizDeCusto;
}

string Data::getPath() {
    return caminho;
}