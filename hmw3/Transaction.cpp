//Sertaç Derya 22003208 Sec1
#include "Transaction.h"

Transaction::Transaction(int subscriberID, int movieID) {
    this->subscriberID = subscriberID; 
    this->movieID = movieID; 
    this->returned = false;
}

Transaction::Transaction() {
    this->subscriberID = 0; 
    this->movieID = 0; 
    this->returned = false;
}

bool Transaction::completeTransaction() {
    if(!returned) {
        this->returned = true;
        return true;
    }
    return false;
}

int Transaction::getMovieID() {
    return this->movieID;
}

int Transaction::getSubID() {
    return this->subscriberID;
}

bool Transaction::getReturned() {
    return this->returned;
}