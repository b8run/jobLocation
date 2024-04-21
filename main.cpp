#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include "data.h"

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

    arquivoDeResultado << "------------------------------- " << data.getPath() << " -------------------------------" << endl;
    arquivoDeResultado << "Ótimo: " << data.getCustoFixoJobLocal() << endl;
    arquivoDeResultado.close();
    return 0;
}