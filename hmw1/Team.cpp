//Sertaç Derya sec1 22003208
#include <iostream>
#include <string>
#include "Team.h"
#include "Player.h"

Team::Team(const string name, const int year) {
    this->teamName = name;
    this->yearFounded = year;
    this->playersArr = nullptr;
    this->playerArrSize = 0;
    this->totalSalary = 0;
}
Team::Team(const Team& team) {
    this->playerArrSize = team.getPlayerSize();
    delete[] this->playersArr;
    this->playersArr = new Player[team.getPlayerSize()];
    for(int i = 0; i < team.getPlayerSize(); i++) {
        this->playersArr[i] = team.getPlayerArr()[i];
    }
    this->teamName = team.getTeamName();
    this->totalSalary = team.getTotalSalary();
    this->yearFounded = team.getYearFounded();
}
Team::Team() {

}
Team::~Team() {
    //cout << "The team is deleted!" << endl;
    delete[] this->playersArr;//this also deletes if a copy is gone out of 
}
string Team::getTeamName() const{
    return this->teamName;
}
int Team::getYearFounded() const{
    return this->yearFounded;
}
Player* Team::getPlayerArr() const{
    return this->playersArr;
}
int Team::getTotalSalary() const{
    return this->totalSalary;
}
int Team::getPlayerSize() const {
    return this->playerArrSize;
}

bool Team::addPlayer(Player& player) {
    //look if a player with the same jersey number exists
    for(int i = 0; i < this->playerArrSize; i++) {
        if(this->playersArr[i].getJerseyNo() == player.getJerseyNo()) {
            return false;
        }
    }
    player.changeTeam(this->teamName);
    this->changeSalary(player.getSalary());
    //create a temp array that will have the same value as playersArr
    Player* tempArr = new Player[this->playerArrSize];
    for(int i = 0; i < this->playerArrSize; i++) {
        tempArr[i] = this->playersArr[i];
    }
    //create a new playersArr with more space and copy the tempArr into it
    delete[] this->playersArr;
    this->playersArr = nullptr;

    this->playersArr = new Player[this->playerArrSize + 1];
    for(int i = 0; i < this->playerArrSize; i++) {
        this->playersArr[i] = tempArr[i];
    }
    //add the new player
    this->playersArr[this->playerArrSize] = player;
    this->playerArrSize++;
    //delete tempArr and empty it
    delete[] tempArr;
    tempArr = nullptr;
    return true;
}
bool Team::removePlayer(string name) {
    //tries to find the player to be removed
    int indexOfPlayer = 0;
    bool found = false;
    for(int i = 0; i < this->playerArrSize && !found; i++) {
        if(this->playersArr[i].getName().compare(name) == 0) {
            indexOfPlayer = i;
            found = true;
            this->changeSalary(-this->playersArr[i].getSalary());
        }
    }
    //if found then creates a tempArr and change playersArr with a lower element count
    if(found) {
        int index = 0;
        //copy
        Player* tempArr = new Player[this->playerArrSize];
        for(int i = 0; i < this->playerArrSize; i++) {
            tempArr[i] = this->playersArr[i];
        }
        //delete and set
        delete[] this->playersArr;
        this->playersArr = new Player[this->playerArrSize - 1];
        for(int i = 0; i < this->playerArrSize; i++) {
            if(i == indexOfPlayer) {
                //don't add this player
            } else {
                this->playersArr[index] = tempArr[i];
                index++;
            }
        }
        delete[] tempArr;
        tempArr = nullptr;
        this->playerArrSize--;
        return true;
    }
    return false;
}
void Team::changeSalary(int amount) {
    this->totalSalary = this->totalSalary + amount;
}

ostream& operator<<(ostream& os, const Team& team) {
    return os << team.getTeamName() << ", " + to_string(team.getYearFounded()) << ", "
    << to_string(team.getPlayerSize()) + " players, " + to_string(team.getTotalSalary()) + " TL total salary";
}

Team& Team::operator=(const Team& team) {
    this->yearFounded = team.getYearFounded();
    this->teamName = team.getTeamName();
    this->totalSalary = team.getTotalSalary();
    this->playerArrSize = team.getPlayerSize();
    //important
    delete[] this->playersArr;
    this->playersArr = new Player[team.getPlayerSize()];
    for(int i = 0; i < this->playerArrSize; i++) {
        this->playersArr[i] = team.getPlayerArr()[i];
    }
    return *this;
}
