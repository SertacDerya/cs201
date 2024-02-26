//Sertaç Derya sec1 22003208
#include <iostream>
#include <string>
#include "LeagueManagementSystem.h"

LeagueManagementSystem::LeagueManagementSystem() {
    this->teamArr = nullptr;
    this->teamArrSize = 0;
    this->playerArr = nullptr;
    this->playerArrSize = 0;
}
LeagueManagementSystem::~LeagueManagementSystem() {
    delete[] this->teamArr;
    this->teamArr = nullptr;
    delete[] this->playerArr;
    this->playerArr = nullptr;
}

void LeagueManagementSystem::addTeam( const string name, const int year ) {//adds the team
    //look if a team with the same name exists
    for(int i = 0; i < this->teamArrSize; i++) {
        if(this->teamArr[i].getTeamName().compare(name) == 0) {
            cout << "Cannot add team. Team " << name << " already exists." << endl;
            return;
        }
    }
    //to add the team create a temp array and increase the size of teamArr
    Team newTeam(name, year);
    Team* tempTeamArr = new Team[this->teamArrSize];
    for(int i = 0; i < this->teamArrSize; i++) {
        tempTeamArr[i] = this->teamArr[i];
    }
    delete[] this->teamArr;
    this->teamArr = new Team[this->teamArrSize + 1];
    //copy all the teams into new array
    for(int i = 0; i < this->teamArrSize; i++) {
        this->teamArr[i] = tempTeamArr[i];
    }
    this->teamArr[this->teamArrSize] = newTeam;
    this->teamArrSize++;
    //delete the tempTeamArr
    delete[] tempTeamArr;
    tempTeamArr = nullptr;
    cout << "Added team " << name << "." << endl;
}
void LeagueManagementSystem::removeTeam( const string name ) {//removes team and also players of that team from the league
    int indexOfTeam;
    bool found = false;
    for(int i = 0; i < this->teamArrSize && !found; i++) {
        if(this->teamArr[i].getTeamName().compare(name) == 0) {
            indexOfTeam = i;
            found = true;
        }
    }
    if(found) {
        //create a temp array that will have the old value of teamArr
        Team* tempTeamArr = this->teamArr;
        this->teamArr = new Team[this->teamArrSize - 1];
        int index = 0;
        //copy teampArr into teamArr but don't add the removed team
        for(int i = 0; i < this->teamArrSize; i++) {
            if(i == indexOfTeam) {
                //don't add this team
            } else {
                this->teamArr[index] = tempTeamArr[i];
                index++;
            }
        }
        //delete temp
        delete[] tempTeamArr;
        tempTeamArr = nullptr;
        this->teamArrSize--;
        cout << "Removed team " << name << "." << endl;
        //delete all the players from this team in the playersArr
        Player* tempPlayerArr = new Player[this->playerArrSize];
        int newPlayerArrSize = 0;
        //int newPlayerArrSize = this->playerArrSize; might not need it
        for(int i = 0; i < this->playerArrSize; i++) {
            if(this->playerArr[i].getTeam().compare(name) == 0) {
                //do nothing
            }
            else {
                tempPlayerArr[newPlayerArrSize] = this->playerArr[i];
                newPlayerArrSize++;
            }
        }
        //create new playerArr
        this->playerArrSize = newPlayerArrSize;
        delete[] this->playerArr;
        this->playerArr = new Player[this->playerArrSize];
        for(int i = 0; i < this->playerArrSize; i++) {
            this->playerArr[i] = tempPlayerArr[i];
        }
        //delete temp array
        delete[] tempPlayerArr;
        tempPlayerArr = nullptr;
    } else {
        cout << "Cannot remove team. Team " << name << " does not exist." << endl;
    }

}
void LeagueManagementSystem::addPlayer( const string teamName, const string playerName,
const int jersey, const int salary ) {
    //first check if a team exists
    bool teamFound = false;
    for(int i = 0; i < this->teamArrSize && !teamFound; i++) {
        if(this->teamArr[i].getTeamName().compare(teamName) == 0) {
            teamFound = true;
            //create the player object
            Player newPlayer(playerName, jersey, salary);
            //if exists check if a player with the same jersey no exists
            bool added = false;
            added = this->teamArr[i].addPlayer(newPlayer);
            //add the player to playerArr
            if(added) {
                Player* tempPlayerArr = this->playerArr;
                this->playerArr = new Player[this->playerArrSize + 1];
                for(int j = 0; j < this->playerArrSize; j++) {
                    this->playerArr[j] = tempPlayerArr[j];
                }
                this->playerArr[this->playerArrSize] = newPlayer;
                this->playerArrSize++;

                delete[] tempPlayerArr;
                tempPlayerArr = nullptr;
                cout << "Added player " << playerName << " to team " << teamName << "." << endl;
            } else {
                cout << "Cannot add player. Jersey number " << jersey << " already exists in team " << teamName << "." << endl;
            }
            
        }
    }
    //if not display a message
    if(!teamFound) {
        cout << "Cannot add player. Team " << teamName << " does not exist." << endl;
    }
}
void LeagueManagementSystem::removePlayer( const string teamName, const string playerName ) {
    //find team if it exists, if not print a message
    bool teamFound = false;
    bool playerFound = false;
    for(int i = 0; i < this->teamArrSize && !teamFound; i++) {
        if(this->teamArr[i].getTeamName().compare(teamName) == 0) {
            teamFound = true;
            playerFound = this->teamArr[i].removePlayer(playerName);
        }
    }
    if(!teamFound) {
        cout << "Cannot remove player. Team " << teamName << " does not exist." << endl;
    } else if(playerFound) {
        //if team exists and player is in the team, delete player from playerArr
        Player* tempPlayerArr = new Player[this->playerArrSize];
        for(int i = 0; i < this->playerArrSize; i++) {
            tempPlayerArr[i] = this->playerArr[i];
        }
        delete[] this->playerArr;
        this->playerArr = new Player[this->playerArrSize - 1];
        int index = 0;
        for(int i = 0; i < this->playerArrSize; i++) {
            if(tempPlayerArr[i].getName().compare(playerName) == 0) {

            } else {
                this->playerArr[index] = tempPlayerArr[i];
                index++;
            }
        }
        this->playerArrSize--;
        delete[] tempPlayerArr;
        tempPlayerArr = nullptr;
        cout << "Removed player " << playerName << " from team " << teamName << "." << endl;
    } else {
        cout << "Cannot remove player. Player " << playerName << " does not exist." << endl;
    }
}
void LeagueManagementSystem::transferPlayer( const string playerName,
const string departTeamName, const string arriveTeamName ) {
    //looks if the two teams exist
    bool firstTeamFound = false;
    int firstTeamIndex;
    bool secondTeamFound = false;
    int secondTeamIndex;
    for(int i = 0; i < this->teamArrSize && (!firstTeamFound || !secondTeamFound); i++) {
        if(this->teamArr[i].getTeamName().compare(departTeamName) == 0) {
            firstTeamFound = true;
            firstTeamIndex = i;
        } else if(this->teamArr[i].getTeamName().compare(arriveTeamName) == 0) {
            secondTeamFound = true;
            secondTeamIndex = i;
        }
    }
    if(firstTeamFound && secondTeamFound) {
        bool playerInTeam;
        playerInTeam = this->teamArr[firstTeamIndex].removePlayer(playerName);
        if(playerInTeam) {
        //find player in playerArr and gets its details then adds it to the other team. after that changes team name of player
            for(int i = 0; i < this->playerArrSize; i++) {
                if(this->playerArr[i].getName().compare(playerName) == 0) {
                    bool playerAddable = this->teamArr[secondTeamIndex].addPlayer(this->playerArr[i]);
                    if(playerAddable) {
                        this->playerArr[i].changeTeam(arriveTeamName);
                        cout << "Transferred player " << playerName << " from team " << departTeamName << " to team "  << arriveTeamName << "." << endl;
                    } else {
                        cout << "Cannot tranfer player. Jersey number " << this->playerArr[i].getJerseyNo() << " already exists in team " << arriveTeamName << "." << endl;
                        this->teamArr[firstTeamIndex].addPlayer(this->playerArr[i]);
                    }
                }
            }
        } else {
            cout << "Cannot transfer player. Player " << playerName << " does not exist." << endl;
        }
    } else if(!firstTeamFound) {
        cout << "Cannot transfer player. Team " << departTeamName << " does not exist." << endl;
    } else if(!secondTeamFound) {
        cout << "Cannot transfer player. Team " << arriveTeamName << "does not exist." << endl;
    }
}

void LeagueManagementSystem::showAllTeams() const {
    cout << "Teams in the league management system:" << endl;
    if(this->teamArrSize == 0) {
        cout << "None" << endl;
    }
    for(int i = 0; i < this->teamArrSize; i++) {
        cout << this->teamArr[i] << endl;
    }
}
void LeagueManagementSystem::showTeam( const string name ) const {
    bool teamFound = false;
    
    for(int i = 0; i < this->teamArrSize && !teamFound; i++) {
        if(this->teamArr[i].getTeamName().compare(name) == 0) {
            teamFound = true;
            cout << "Team:" << endl;
            cout << this->teamArr[i] << endl;
            cout << "Players:" << endl;
            for(int j = 0; j < this->teamArr[i].getPlayerSize(); j++) {
                cout << this->teamArr[i].getPlayerArr()[j] << endl;
            }
        }
    }
    if(!teamFound) {
        cout << "Team " << name << " does not exist." << endl;
    }
}
void LeagueManagementSystem::showPlayer( const string name ) const {
    bool playerFound = false;
    for(int i = 0; i < this->playerArrSize && !playerFound; i++) {
        if(this->playerArr[i].getName().compare(name) == 0) {
            playerFound = true;
            cout << "Player:" << endl;
            cout << this->playerArr[i] << endl;
            cout << "Plays in team " << this->playerArr[i].getTeam() << "." << endl;
        }
    }
    if(!playerFound) {
        cout << "Player " << name << " does not exist." << endl;
    }
}
