//Sertaç Derya 22003208 Sec1
#include "FlightMap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

FlightMap::FlightMap( const string cityFile, const string flightFile ) {
    ifstream inputFileCity(cityFile.c_str(), ios_base::in);
    int cityCount;
    string cityName;

    ifstream inputFileFlights(flightFile.c_str(), ios_base::in);
    string departCity;
    string arriveCity;
    int flightID;
    int flightCost;

    if(!inputFileCity.good() & !inputFileFlights.good()) {
        cout << "Input file " << cityFile << " & " << flightFile << " does not exist" << std::endl;
    } else if(!inputFileCity.good()) {
        cout << "Input file " << cityFile << " does not exist" << std::endl;
    } else if(!inputFileFlights.good()) {
        cout << "Input file " << flightFile << " does not exist" << std::endl;
    } else { 
        while(inputFileCity.eof() == false) {
            inputFileCity >> cityName;
            bool exists = false;
            for(int i = 0; i < this->cities.size(); i++) {
                if(this->cities.at(i).getName() == cityName) {
                    exists = true;
                }
            }
            if(!exists) {
                City c(cityName);
                this->cities.push_back(c);
            }
            
        }
        sort(this->cities.begin(), this->cities.end());

        for(int i = 0; i < cities.size(); i++) {
            this->cityIndex.insert({this->cities.at(i).getName(), i});
        }

        for(int i = 0; i < cities.size(); i++) {
            list<Flight> fl;
            this->flightList.push_back(fl);
        }

        string line;
        int flightCount = 0;
        while(getline(inputFileFlights, line)) {
            flightCount++;
            stringstream flightLine(line);
            string stringID;
            string stringCost;
            getline(flightLine, departCity, ';');
            getline(flightLine, arriveCity, ';');
            getline(flightLine, stringID, ';'); 
            getline(flightLine, stringCost, ';');

            flightID = stoi(stringID);
            flightCost = stoi(stringCost);

            list<Flight> fl = this->flightList.at(this->cityIndex.at(departCity));
            int size = fl.size();
            list<Flight>::iterator it = fl.begin();
            Flight f(flightID, departCity, arriveCity, flightCost);
            bool done = false;
            for(int i = 0; i < size & !done; i++) {
                Flight itF = *it;
                if(itF.getID() == f.getID() & itF.getPrice() == f.getPrice() & itF.getDeptName() == f.getDeptName() & itF.getArriveName() == f.getArriveName()) {
                } else {
                    fl.push_back(f);
                    done = true;
                }
                it++;
            }
            if(fl.size() == 0) {
                fl.push_back(f);
            }
            

            /* struct {
                bool operator()(Flight a, Flight b) const { return a.getDeptName() < b.getDeptName(); }
            } customLess; */

            this->flightList.at(this->cityIndex.at(departCity)) = fl;
        }
        for(int i = 0; i < this->flightList.size(); i++) {
            this->flightList.at(i).sort();
        }
        cout << this->cities.size() << " cities and " << flightCount << " flights have been loaded" << endl;
    }
}

FlightMap::~FlightMap() {

}

void FlightMap::displayAllCities() const {
    cout << "The list of the cities that HPAir serves is given below:" << endl;
    for(int i = 0; i < this->cities.size(); i++) {
        cout << this->cities.at(i).getName() << ", ";
    }
    cout << endl;
}

void FlightMap::displayAdjacentCities( const string cityName ) const {
    cout << "The cities adjacent to " << cityName << " are:" << endl;
    cout << cityName << " -> ";
    int index = this->cityIndex.at(cityName);
    list<Flight> fl = this->flightList.at(index);
    list<Flight>::iterator iterator = fl.begin();
    for(int i = 0; i < fl.size(); i++) {
        Flight f = *iterator;
        cout << f.getArriveName() << ", ";
        iterator++;
    }
    cout << endl;
}

void FlightMap::displayAdjacentCitiesWithout( const string cityName ) const {
    cout << cityName << " -> ";
    int index = this->cityIndex.at(cityName);
    list<Flight> fl = this->flightList.at(index);
    list<Flight>::iterator iterator = fl.begin();
    for(int i = 0; i < fl.size(); i++) {
        Flight f = *iterator;
        cout << f.getArriveName() << ", ";
        iterator++;
    }   
    cout << endl; 
}

void FlightMap::displayFlightMap() const {
    cout << "The whole flight map is given below:" << endl;
    for(int i = 0; i < this->cities.size(); i++) {
        displayAdjacentCitiesWithout(this->cities.at(i).getName());
    }
}

void FlightMap::unvisitAll() {
    for(int i = 0; i < this->cities.size(); i++) {
        this->cities.at(i).setVisited(false);
    }
}

Flight FlightMap::getFlight(string deptName, string arriveName) {//return the flight from the selected city to a city that wasn't visited before
    if(deptName == "") {
        Flight f(0, deptName, "", 0);
        return f;
    }
    int index = this->cityIndex.at(deptName);
    bool found = false;
    Flight foundFlight;
    list<Flight> fl = this->flightList.at(index);
    list<Flight>::iterator iterator = fl.begin();

    if(fl.size() > 0) {
        for(int i = 0; i < fl.size(); i++) {
            Flight f = *iterator;
            int cityIndex = this->cityIndex.at(f.getArriveName());
            if(this->cities.at(cityIndex).getVisited() == false /* || this->cities.at(cityIndex).getName() == arriveName */) {
                return f;
            } else if(this->cities.at(cityIndex).getName() == arriveName){
                found = true;
                foundFlight = f;
                iterator++;
            } else {
                iterator++;
            }
        }
    }
    if(found) {
        return foundFlight;
    }
    Flight f(0, deptName, "", 0);
    return f;
  
}

void FlightMap::unmarkAllFlightsForCity(string cityName) {
    int index = this->cityIndex.at(cityName);
    list<Flight> fl = this->flightList.at(index);
    list<Flight>::iterator iterator = fl.begin();
    for(int i = 0; i < fl.size(); i++) {
        int cIndex = this->cityIndex.at((*iterator).getArriveName());
        this->cities.at(cIndex).setVisited(false);
        iterator++;
    }
}

void FlightMap::findFlights( const string deptCity, const string destCity ) {
    vector<stack<Flight>> allPaths;
    stack<Flight> flightStack;
    stack<Flight> reverse;
     // Clear marks on all flights
    int deptIndex = this->cityIndex.at(deptCity);
    cout << "Request is to fly from " << deptCity << " to " << destCity << ":" << endl;

    list<Flight> fl = this->flightList.at(deptIndex);
    list<Flight>::iterator iterator = fl.begin();
    for(int i = 0; i < fl.size(); i++) {//for all the
        unvisitAll();
        Flight nextFlight = *iterator;
        flightStack.push(nextFlight);
        int flightCityID = this->cityIndex.at(nextFlight.getDeptName());
        this->cities.at(flightCityID).setVisited(true);
        flightCityID = this->cityIndex.at(nextFlight.getArriveName());
        this->cities.at(flightCityID).setVisited(true);//marks the city thta has been arrived now as visited
        
        while(flightStack.size() > 0) {
            if(nextFlight.getArriveName() == destCity) {
                allPaths.push_back(flightStack);//adds the stack that can go to destination to the array
                flightStack.pop();//pops the last flight from stack
                if(flightStack.size() > 0) {
                    nextFlight = flightStack.top();
                    unmarkAllFlightsForCity(nextFlight.getArriveName());
                    flightStack.pop();
                    if(flightStack.size() > 0) {
                        nextFlight = flightStack.top();
                    }
                    
                }
            } else if(nextFlight.getArriveName() == "") {
                unmarkAllFlightsForCity(nextFlight.getDeptName());
                flightStack.pop();
                if(flightStack.size() > 0) {
                    flightStack.pop();
                    if(flightStack.size() > 0) {
                        nextFlight = flightStack.top();
                    }
                    
                }
            } else {
                nextFlight = getFlight(nextFlight.getArriveName(), destCity);
                flightStack.push(nextFlight);
                if(nextFlight.getArriveName() != "") {
                    flightCityID = this->cityIndex.at(nextFlight.getArriveName());
                    this->cities.at(flightCityID).setVisited(true);
                }                
            }
        }
        
        iterator++;
    }
    vector<int> price(allPaths.size());
    if(allPaths.size() == 0) {
        cout << "Sorry. HPAir does not fly from " << deptCity << " to " << destCity << "." << endl;
    } else {
        for(int j = 0; j < allPaths.size(); j++) {
            stack<Flight> reverse;
            flightStack = allPaths.at(j);
            int size = flightStack.size();
            for(int i = 0; i < size; i++) {
                price.at(j) = price.at(j) + flightStack.top().getPrice();
                reverse.push(flightStack.top());
                flightStack.pop();
            }
            allPaths.at(j) = reverse;
        }
        for(int i = 0; i < allPaths.size(); i++) {
            for(int j = 0; j < allPaths.size() - 1 - i; j++) {
                if(price.at(j) > price.at(j + 1)) {
                    int temp = price.at(j);
                    price.at(j) = price.at(j + 1);
                    price.at(j + 1) = temp;

                    stack<Flight> tempS = allPaths.at(j);
                    allPaths.at(j) = allPaths.at(j + 1);
                    allPaths.at(j + 1) = tempS;
                }
            }
        }
        stack<Flight> that;
        for(int i = 0; i < allPaths.size(); i++) {
            that = allPaths.at(i);
            int size = that.size();
            for(int j = 0; j < size; j++) {
                cout << "Flight #" << that.top().getID() << " from " << that.top().getDeptName() << " to " << that.top().getArriveName() << ", Cost: " << that.top().getPrice() << " TL" << endl;
                that.pop();
            }
            cout << "Total Cost: " << price.at(i) << " TL" << endl;
        }
    }
}
