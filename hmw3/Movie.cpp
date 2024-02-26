//Sertaç Derya 22003208 Sec1
#include "Movie.h"

Movie::Movie() {
    this->movId = 0; 
    this->copyAmount = 0;
    this->currentAmount = 0;
}

Movie::Movie(int movID, int copyNum) {
    this->movId = movID;
    this->copyAmount = copyNum;
    this->currentAmount = copyNum;
}

Movie::Movie(const Movie& movie) {
    this->movId = movie.getID();
    this->copyAmount = movie.copyAmount;
    this->currentAmount = movie.currentAmount;
}

int Movie::getID() const {
    return this->movId;
}

bool Movie::returnMovie() {
    if(this->copyAmount > this->currentAmount) {
        this->currentAmount++;
        return true;
    }
    return false;
}

bool Movie::rentMovie() {
    if(this->currentAmount > 0) {
        this->currentAmount--;
        return true;
    }
    return false;
}

int Movie::getCurrentAmount() {
    return this->currentAmount;
}

int Movie::getCopyAmount() {
    return this->copyAmount;
}