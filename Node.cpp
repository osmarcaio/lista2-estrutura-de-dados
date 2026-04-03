#include "Order.hpp"
#include "Transaction.hpp"

struct OrderNode {
    OrderNode* next;
    Order order;

    OrderNode(Order order) : order(order), next(nullptr) {}
};

struct TransactionNode {
    TransactionNode* next;
    Transaction transaction;

    TransactionNode(Transaction transaction) : transaction(transaction), next(nullptr) {}
};