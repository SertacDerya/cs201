//Sertaç Derya 22003208 Sec1
#include "Flight.h"

Flight::Flight() {
    this->id = 0; 
    this->depart = "";
    this->arrive = "";
    this->price = 0; 
}

Flight::Flight(int id, string depart, string arrive, int price) {
    this->id = id;
    this->depart = depart;
    this->arrive = arrive;
    this->price = price;
}

int Flight::getID() {
    return this->id;
}

string Flight::getDeptName() {
    return this->depart;
}

string Flight::getArriveName() {
    return this->arrive;
}

void Flight::setDept(string dept) {
    this->depart = dept;
}

void Flight::setArrive(string arrive) {
    this->arrive = arrive;
}

int Flight::getPrice() {
    return this->price;
}

bool Flight::operator<(const Flight& f) const {
    return this->arrive < f.arrive;
}