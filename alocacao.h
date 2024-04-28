#ifndef ALOCACAO_H
#define ALOCACAO_H

#include <vector>
#include "Job.h"

using namespace std;

struct Alocacao {
    vector<Job> jobsDone;
    int custoTotal;

    Alocacao() {}
    Alocacao(vector<Job> _jobsDone, int _custoTotal) : jobsDone(_jobsDone), custoTotal(_custoTotal) {}
};

#endif