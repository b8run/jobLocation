#ifndef SERVER_H
#define SERVER_H

struct Server {
    int id;
    int capacidade;
    
    Server() {}
    Server(int _id, int _capacidade) : id(_id),capacidade(_capacidade) {}
};

#endif