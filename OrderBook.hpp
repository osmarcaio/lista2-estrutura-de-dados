#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "Order.hpp"
#include "Node.hpp"

#include "Transaction.hpp"


class OrderBook {

private:

    OrderNodeControl lista_de_vendas;
    OrderNodeControl lista_de_compras;
    TransactionNodeControl lista_de_transacoes;


public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
};

#endif