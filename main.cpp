#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include "data.h"
#include "server.h"
#include "job.h"
#include "solucaoHeuristica.h"
#include "modelo.h"

using namespace std;

float calculadorAGAP(int valor, int valorOtimo) {
    double result = ((static_cast<double>(valor) - valorOtimo) / valorOtimo);
    return (result * 100);
}

int main() {
    string resultado = "resultado.txt";
    ofstream arquivoDeResultado(resultado);

    if (!arquivoDeResultado.is_open()) {
        cerr << "arquivo com erro " << endl;
        return 1;
    }

    /* -- valores ótimos para as instâncias de teste
    n5m15A = 261
    n5m15B = 269
    n25m5A = 438
    n30m5A = 423
    n60m10 = 954
    n60m10A = 973
    */

    
    Data data = Data("instancias/n5m15A.txt", 261);
    
    vector<Data> instances;
    instances.push_back(data);

     for (size_t z = 0; z < instances.size(); z++) {
        Data data = instances[z];
        Modelo modelo (
            data.getNumeroDeJobs(),
            data.getNumeroDeServidores(),
            data.getCustoFixoJobLocal()
        );

        vector<vector<int>> matrizTempo = data.getMatrizDeTempo();
        vector<vector<int>> matrizCusto = data.getMatrizDeCusto();

        vector<int> capacidadeDeServidores =  data.getCapacidadeDosServidores();


        vector<Job> listaJobs;
        vector<Server> listaServer;

        int id = 0;
        for(int i = 0; i < modelo.numeroDeServidores  ; i++) {
                for(int j = 0; j < modelo.numeroDejobs ; j++) {
                    Job job(++id,i,matrizTempo[i][j], matrizCusto[i][j],false);
                    listaJobs.push_back(job);
                }
                Server server(i,capacidadeDeServidores[i]);
                listaServer.push_back(server);
        }

        auto startTimeHeuristicSolution = chrono::high_resolution_clock::now();

        SolucaoHeuristica solucaoHeuristica = SolucaoHeuristica(
            listaServer,
            listaJobs,
            modelo);

        

        arquivoDeResultado << "------------------------------- " << data.getPath() << " -------------------------------" << endl;
        arquivoDeResultado << "Ótimo: "<< data.getValorOtimo() << endl;
        arquivoDeResultado << "----- HEURÍSTICA CONSTRUTIVA -----" << endl;
        arquivoDeResultado << "Valor solução: " << solucaoHeuristica.solucao.total << endl;
        auto endTimeHeuristicSolution = chrono::high_resolution_clock::now();


        chrono::duration<double> elapsedTime = endTimeHeuristicSolution - startTimeHeuristicSolution;
        double elapsedSeconds = elapsedTime.count();
        arquivoDeResultado << "Tempo: " << elapsedSeconds << " segundos" << endl;
        arquivoDeResultado << "gap: " << calculadorAGAP(solucaoHeuristica.solucao.total, data.getValorOtimo()) << endl;


       auto startTimeVND = chrono::high_resolution_clock::now();
        // Vizinhança 1: Trocar a atribuição de um trabalho entre dois servidores
        for (size_t i = 0; i < listaServer.size(); i++) {
            for (size_t j = i + 1; j < listaServer.size(); j++) {
                for (size_t k = 0; k < listaJobs.size(); k++) {
                    Job job = listaJobs[k];
                    if (job.id!= i && job.idServer!= j) {
                        continue;
                    }
                    int oldServer = job.idServer;
                    job.idServer = (job.idServer == i)? j : i;
                    SolucaoHeuristica newSol = SolucaoHeuristica(listaServer, listaJobs, modelo);
                    if (newSol.solucao.total < solucaoHeuristica.solucao.total) {
                        solucaoHeuristica = newSol;
                    }
                    job.idServer = oldServer;
                }
            }
        }

        // Vizinhança 2: Mover um trabalho de um servidor para outro servidor com capacidade disponível
        for (size_t i = 0; i < listaJobs.size(); i++) {
            Job job = listaJobs[i];
            for (size_t j = 0; j < listaServer.size(); j++) {
                Server server = listaServer[j];
                if (server.capacidade < job.tempoExec) {
                    continue;
                }
                int oldServer = job.idServer;
                job.idServer = j;
                SolucaoHeuristica newSol = SolucaoHeuristica(listaServer, listaJobs, modelo);
                if (newSol.solucao.total < solucaoHeuristica.solucao.total) {
                    solucaoHeuristica = newSol;
                }
                job.idServer = oldServer;
            }
        }

        // Vizinhança 3: Trocar a atribuição de dois trabalhos entre dois servidores
        for (size_t i = 0; i < listaJobs.size(); i++) {
            for (size_t j = i + 1; j < listaJobs.size(); j++) {
                Job job1 = listaJobs[i];
                Job job2 = listaJobs[j];
                if (job1.idServer!= job2.idServer) {
                    continue;
                }
                int oldServer1 = job1.idServer;
                int oldServer2 = job2.idServer;
                job1.idServer = (job1.idServer == oldServer1)? oldServer2 : oldServer1;
                job2.idServer = (job2.idServer == oldServer1)? oldServer2 : oldServer1;
                SolucaoHeuristica newSol = SolucaoHeuristica(listaServer, listaJobs, modelo);
                if (newSol.solucao.total < solucaoHeuristica.solucao.total) {
                    solucaoHeuristica = newSol;
                }
                job1.idServer = oldServer1;
                job2.idServer = oldServer2;
            }
        } 

        
        arquivoDeResultado << "----- VND -----"<< endl;
        arquivoDeResultado << "Valor solução: " << solucaoHeuristica.solucao.total << endl;

        auto endTimeVND = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsedTimeVND = endTimeVND - startTimeVND;
        double elapsedSecondsVND = elapsedTimeVND.count();
        arquivoDeResultado << "Tempo: " << elapsedSecondsVND << " segundos" << endl;
        arquivoDeResultado << "gap: " << calculadorAGAP(solucaoHeuristica.solucao.total, data.getValorOtimo()) << endl;
        arquivoDeResultado << "-------------------------------------------------------------------------------------" << endl;

    }
    return 0;
}