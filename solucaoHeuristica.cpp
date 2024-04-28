#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include "solucaoHeuristica.h"
#include "server.h"
#include "job.h"
#include "solucaoGulosa.h"
#include "modelo.h"

using namespace std;

SolucaoHeuristica::SolucaoHeuristica(vector<Server> server, vector<Job> job, Modelo modelo)
{
    int aux = 0;
    vector<Alocacao> alocacao;
    int capacidadeAnalise = 0;

    Alocacao AlocacaoDone;
    AlocacaoDone.custoTotal = 0;

    int n_jobs = job.size();

    vector<double> vetMedioCustoExec;

    for (int k = 0; k < n_jobs; k++)
    {
        float custoTempo = static_cast<float>(job.at(k).custoExec) / (job.at(k).tempoExec);
        vetMedioCustoExec.push_back(custoTempo);
    }

    for (int i = 0; i < modelo.numeroDejobs; i++)
    {
        float menorCusto = 10000;
        int jobnumber = 0;
        for (int k = 0; k < vetMedioCustoExec.size(); k++)
        {
            float custoAtual = vetMedioCustoExec[k];
            if (job[k].solucaoValida == true ||
                job[k].idServer != aux)
            {
                continue;
            }
            if (custoAtual < menorCusto)
            {
                menorCusto = custoAtual;
                jobnumber = k;
            }
        }
        // cout << "ESCOLHEU: "<< job[jobnumber].id << endl;
        Job jobAnalise = job[jobnumber];
        int capacidadeProv = capacidadeAnalise + jobAnalise.tempoExec;

        if (capacidadeProv <= server[aux].capacidade)
        {
            capacidadeAnalise += jobAnalise.tempoExec;
            job[jobnumber].solucaoValida = true;
            job[jobnumber + modelo.numeroDeServidores].solucaoValida = true;
            AlocacaoDone.custoTotal += jobAnalise.tempoExec;
            AlocacaoDone.jobsDone.push_back(jobAnalise);
            // continue;
        }
        else if (capacidadeProv > server[aux].capacidade && aux + 1 < modelo.numeroDeServidores)
        {
            capacidadeAnalise = 0;
            aux++;
        }
    }
    int JobsNaoAlocados = 0;
    for (int j = 0; j < n_jobs; j++)
    {
        if (job[j].solucaoValida == false)
        {
            JobsNaoAlocados += 1;
        }
    }
    
    alocacao.push_back(AlocacaoDone);

    int valorTotal = 0;
    for(int i = 0; i < AlocacaoDone.jobsDone.size()  ; i++) {
        valorTotal+= AlocacaoDone.jobsDone[i].custoExec;
    }

    SolucaoGulosa solucao = SolucaoGulosa();
    solucao.alocacao = alocacao;
    solucao.total = valorTotal + (JobsNaoAlocados*modelo.custoFixoJobLocal);

    this->solucao = solucao;

}
