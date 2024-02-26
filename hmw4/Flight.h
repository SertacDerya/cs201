//Sertaç Derya 22003208 Sec1
#pragma once
#include <string>
using namespace std;
class Flight {
    public:
        Flight();
        Flight(int id, string depart, string arrive, int price);
        int getID();
        string getDeptName();
        string getArriveName();
        void setDept(string dept);
        void setArrive(string arrive);
        int getPrice();
        Flight& getNextFlight();
        bool operator<(const Flight& f) const;
    private:
        int id;
        string depart;
        string arrive;
        int price;
};
//#include "Flight.cpp"