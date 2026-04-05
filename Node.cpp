#include "Order.hpp"

#include "Node.hpp"


OrderNodeControl::OrderNodeControl() {
    this->tamanho = 0;
    this->primeiro = nullptr;
}

OrderNodeControl::~OrderNodeControl() {
    OrderNode* atual = primeiro;
    while (atual != nullptr) {
        OrderNode* proximo = atual->next;
        delete atual;
        atual = proximo;
    }
    primeiro = nullptr;
    this->tamanho = 0;
}

bool OrderNodeControl::inserir (Order order) {
    OrderNode* elemento = new OrderNode{order, nullptr};
    elemento->next = this->primeiro;
    primeiro = elemento;
    this->tamanho++;
    return true;
}

bool OrderNodeControl::remover (int id) {
    OrderNode* atual = primeiro;
    OrderNode* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->order.getId() == id) {
            if (atual == primeiro) {
                primeiro = atual->next;
            }
            else {
                anterior->next = atual->next;
            }
            delete atual;
            this->tamanho--;
            return true;
        }

        anterior = atual;
        atual = atual->next;
    }
    return false;

}

int OrderNodeControl::getTamanho() {
    return this->tamanho;
}

Order* OrderNodeControl::toArray() {

    if (this->tamanho == 0) {
        return nullptr;
    }
    Order* array = new Order[this->tamanho];
    OrderNode* atual = this->primeiro;
    int i = this->tamanho - 1;
    while (atual != nullptr) {
        array[i] = atual->order;
        i--;
        atual = atual->next;
    }

    return array;
}


TransactionNodeControl::TransactionNodeControl() {
    this->tamanho = 0;
    this->primeiro = nullptr;
}

TransactionNodeControl::~TransactionNodeControl() {
    TransactionNode* atual = primeiro;
    while (atual != nullptr) {
        TransactionNode* proximo = atual->next;
        delete atual;
        atual = proximo;
    }
    primeiro = nullptr;
    this->tamanho = 0;
}

bool TransactionNodeControl::inserir (Transaction Transaction) {
    TransactionNode* elemento = new TransactionNode{Transaction, nullptr};
    elemento->next = this->primeiro;
    primeiro = elemento;
    this->tamanho++;
    return true;
}


int TransactionNodeControl::getTamanho() {
    return this->tamanho;
}


Transaction* TransactionNodeControl::toArray() {

    if (this->tamanho == 0) {
        return nullptr;
    }
    Transaction* array = new Transaction[this->tamanho];
    TransactionNode* atual = this->primeiro;
    int i = this->tamanho - 1;
    while (atual != nullptr) {
        array[i] = atual->transaction;
        i--;
        atual = atual->next;
    }

    return array;
}