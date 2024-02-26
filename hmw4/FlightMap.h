//Sertaç Derya 22003208 Sec1
#pragma once
#include <string>
#include <list>
#include <map>
#include <vector>
#include <stack>
#include "City.h"
#include "Flight.h"
using namespace std;
class FlightMap {
    public:
        FlightMap( const string cityFile, const string flightFile );
        ~FlightMap();
        void displayAllCities() const;
        void displayAdjacentCities( const string cityName ) const;
        void displayFlightMap() const;
        void findFlights( const string deptCity, const string destCity );
    private:
        vector<list<Flight>> flightList;
        //vector<string> cities;
        vector<City> cities;
        map<string, int> cityIndex;
        void displayAdjacentCitiesWithout( const string cityName ) const;
        void unvisitAll();
        Flight getFlight(string deptName, string arriveName);
        void unmarkAllFlightsForCity(string cityName);
};
//#include "Flight.cpp"
