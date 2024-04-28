#ifndef JOB_H
#define JOB_H

struct Job {
    int id;
    int idServer;
    int tempoExec;
    int custoExec;
    bool solucaoValida;

  Job(int _id, int _idServer,int _tempoExec,int _custoExec, bool _solucaoValida) : id(_id), idServer(_idServer),tempoExec(_tempoExec),custoExec(_custoExec), solucaoValida(_solucaoValida) {}};

#endif