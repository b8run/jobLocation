#ifndef SOLUCAOHEURISTICA_H
#define SOLUCAOHEURISTICA_H
#include <iostream>
#include <vector>
#include "Job.h"
#include "server.h"
#include "alocacao.h"
#include "solucaoGulosa.h"
#include "modelo.h"

using namespace std;

class SolucaoHeuristica {
    private:
        vector<Job> jobs;
        vector<Server> server;

        int solutionCost;

        public:
            SolucaoGulosa solucao;
            SolucaoHeuristica(vector<Server> server ,vector<Job> jobs,Modelo modelo);
};

#endif