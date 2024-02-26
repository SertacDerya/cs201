//Sertaç Derya 22003208 Sec1
#pragma once
#include <string>
#include <list>
using namespace std;
class City {
    public:
        City();
        City(string name);
        string getName() const;
        bool getVisited() const;
        void setVisited(bool visited);
        bool operator<(const City& c) const;
    private:
        string name;
        bool visited;
};
//#include "City.cpp"