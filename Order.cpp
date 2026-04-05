#include "Order.hpp"


Order::Order() {
    this->id = -1;
    this->type = ' ';
    this->price = 0;
    this->timestamp = 0;
}

Order::Order(int id, char type, float price, int timestamp) {
    this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
}

Order::~Order() {

}

int Order::getId() {
    return this->id;
}

char Order::getType() {
    return this->type;
}

float Order::getPrice() {
    return this->price;
}

int Order::getTimestamp() {
    return this->timestamp;
}


