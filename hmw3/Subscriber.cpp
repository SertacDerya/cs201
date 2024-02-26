//Sertaç Derya 22003208 Sec1
#include "Subscriber.h"
//make some functions const
Subscriber::Subscriber() {
    this->id = 0;
}

Subscriber::Subscriber(int id) {
    this->id = id;
}

Subscriber::Subscriber(const Subscriber& copySub) {
    this->id = copySub.getID();
    this->transactions.clear();
    this->transactions = copySub.getTransactionCopy();
}

Subscriber::~Subscriber() {
    this->transactions.clear();
}

void Subscriber::setTransactionList(const LinkedList<Transaction>& tList) {
    this->transactions.clear();
    this->transactions = tList;
}

int Subscriber::getID() const {
    return this->id;
}

LinkedList<Transaction> Subscriber::getTransactionCopy() const {
    return this->transactions;
}

Subscriber& Subscriber::operator=(const Subscriber& aSub) {
    this->id = aSub.getID();
    this->transactions.clear();
    this->transactions = aSub.getTransactionCopy();
    return *this;
}