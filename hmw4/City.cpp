//Sertaç Derya 22003208 Sec1
#include "City.h"

City::City() {
    this->name = "";
    this->visited = false;
}

City::City(string name) {
    this->name = name;
    this->visited = false;
}

string City::getName() const {
    return this->name;
}

bool City::getVisited() const {
    return this->visited;
}

void City::setVisited(bool visited) {
    this->visited = visited;
}

bool City::operator<(const City& c) const {
    return this->name < c.getName();
}