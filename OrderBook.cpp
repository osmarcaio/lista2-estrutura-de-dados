#include <iostream>

#include "Order.hpp"
#include "Transaction.hpp"

#include "OrderBook.hpp"
#include "Node.hpp"


OrderBook::OrderBook() {

}

OrderBook::~OrderBook() {
}

bool OrderBook::submit(Order order) {
    if (order.getType() == 'B') {
        int tamanho = -1;
        Order* array_vendas = getSellOrders(&tamanho);
        bool pareou = false;
        if (tamanho == 0) {
            lista_de_compras.inserir(order);
            return false;
        }
        Order candidato = {-1, ' ', 0.0, -1};

        for (int i = 0; i < tamanho; i++) {
            Order ordem_venda = array_vendas[i];
            if (candidato.getId() == -1) {
                if (ordem_venda.getPrice() <= order.getPrice()) {
                    candidato = ordem_venda;
                    pareou = true;
                }
            }

            else if (ordem_venda.getPrice() < candidato.getPrice() or (ordem_venda.getPrice() == candidato.getPrice() and ordem_venda.getTimestamp() < candidato.getTimestamp())) {
                candidato = ordem_venda;
                pareou = true;
            }
        }

        delete[] array_vendas;

        if (pareou) {
            Transaction transaction(order.getId(), candidato.getId(), candidato.getPrice());
            this->lista_de_transacoes.inserir(transaction);
            this->lista_de_vendas.remover(candidato.getId());
            return true;
        }
        

        lista_de_compras.inserir(order);
        return false;
    }
        
        
    else if (order.getType() == 'S') {
        int tamanho = -1;

        Order* array_compras = getBuyOrders(&tamanho);
        bool pareou = false;
        if (tamanho == 0) {
            lista_de_vendas.inserir(order);
            return false;
        }
        Order candidato = {-1, ' ', 0.0, -1};

        for (int i = 0; i < tamanho; i++) {
            Order ordem_compra = array_compras[i];
            if (candidato.getId() == -1) {
                if (ordem_compra.getPrice() >= order.getPrice()) {
                    candidato = ordem_compra;
                    pareou = true;
                }
            }

            else if (ordem_compra.getPrice() > candidato.getPrice() or (ordem_compra.getPrice() == candidato.getPrice() and ordem_compra.getTimestamp() < candidato.getTimestamp())) {
                candidato = ordem_compra;
                pareou = true;
            }
        }

        delete[] array_compras;

        if (pareou) {
            Transaction transaction(candidato.getId(), order.getId(), candidato.getPrice());
            this->lista_de_transacoes.inserir(transaction);
            this->lista_de_compras.remover(candidato.getId());
            return true;
        }
        

        lista_de_vendas.inserir(order);
        return false;
    }

    return false;
}

bool OrderBook::cancel(int id) {
    if (lista_de_compras.remover(id)) {
        return true;
    }
    else if (lista_de_vendas.remover(id)) {
        return true;
    }

    return false;
}

Order* OrderBook::getBuyOrders(int* n) {
    *n = this->lista_de_compras.getTamanho();
    Order* array_vendas = this->lista_de_compras.toArray();

    return array_vendas;

}

Order* OrderBook::getSellOrders(int* n) {
    *n = this->lista_de_vendas.getTamanho();
    Order* array_compras = this->lista_de_vendas.toArray();

    return array_compras;

}

Transaction* OrderBook::getTransactions(int*n) {
    *n = this->lista_de_transacoes.getTamanho();
    Transaction* array_transacoes = lista_de_transacoes.toArray();

    return array_transacoes;
}


void OrderBook::printBuyOrders() {
    int tamanho = -1;

    Order* array_compras = getBuyOrders(&tamanho);

    std::cout << "Buy Orders:" << std::endl;

    if (tamanho == 0) {
        std::cout << "(empty)" << std::endl;
        delete[] array_compras;
        return;
    }

    if (tamanho != 0) {
        for (int i = 0; i < tamanho; i++) {
            Order ordem_compra = array_compras[i];
            std::cout << "[" << ordem_compra.getId() << " | " << ordem_compra.getPrice() << " | " << ordem_compra.getTimestamp() << "]" << std::endl;
        }
    }
    delete[] array_compras;
}

void OrderBook::printSellOrders() {
    int tamanho = -1;

    Order* array_vendas = getSellOrders(&tamanho);

    std::cout << "Sell Orders:" << std::endl;

    if (tamanho == 0) {
        std::cout << "(empty)" << std::endl;
        delete[] array_vendas;
        return;
    }

    if (tamanho != 0) {
        for (int i = 0; i < tamanho; i++) {
            Order ordem_venda = array_vendas[i];
            std::cout << "[" << ordem_venda.getId() << " | " << ordem_venda.getPrice() << " | " << ordem_venda.getTimestamp() << "]" << std::endl;
        }
    }
    delete[] array_vendas;
}

void OrderBook::printTransactions() {
    int tamanho = -1;

    Transaction* array_transactions = getTransactions(&tamanho);

    std::cout << "Transactions:" << std::endl;

    if (tamanho == 0) {
        std::cout << "(empty)" << std::endl;
        delete[] array_transactions;
        return;
    }

    if (tamanho != 0) {
        for (int i = 0; i < tamanho; i++) {
            Transaction transaction = array_transactions[i];
            std::cout << "[" << transaction.getBuyOrderId() << ", " << transaction.getSellOrderId() << ", " << transaction.getExecutionPrice() << "]" << std::endl;
        }
    }
    delete[] array_transactions;
}

