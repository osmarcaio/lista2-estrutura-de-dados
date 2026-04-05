#ifndef NODE_HPP
#define NODE_HPP

#include "Order.hpp"
#include "Transaction.hpp"


struct OrderNode {
    Order order;
    OrderNode* next;
};

class OrderNodeControl {
private:

    OrderNode* primeiro;
    int tamanho;
    
public:

    OrderNodeControl();

    ~OrderNodeControl();

    bool inserir (Order order);

    bool remover (int id);

    int getTamanho();


    Order* toArray();


};

struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;
};

class TransactionNodeControl {
private:

    TransactionNode* primeiro;
    int tamanho;
public:

    TransactionNodeControl();

    ~TransactionNodeControl();

    bool inserir (Transaction order);


    int getTamanho();


    Transaction* toArray();


};

#endif