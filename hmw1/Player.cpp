//Sertaç Derya sec1 22003208
#include <iostream>
#include <string>
#include "Player.h"

Player::Player(string name, int jerseyNo, int salary) {
    this->name = name;
    this->jerseyNo = jerseyNo;
    this->salary = salary;
    this->teamName = "";
}
Player::Player(const Player& player) {
    this->name = player.getName();
    this->jerseyNo = player.getJerseyNo();
    this->salary = player.getSalary();
    this->teamName = player.getTeam();
}
Player::Player() {
}

string Player::getName() const{
    return this->name;
}
int Player::getJerseyNo() const{
    return this->jerseyNo;
}
string Player::getTeam() const{
    return this->teamName;
}
int Player::getSalary() const{
    return this->salary;
}

void Player::changeJerseyNo(int jerseyNo) {
    this->jerseyNo = jerseyNo;
}
void Player::changeTeam(string nTeam) {
    this->teamName = nTeam;
}

ostream& operator<<(ostream& os, const Player& player) {
    return os << player.getName() << ", jersey " << player.getJerseyNo() << ", " << player.getSalary() <<
    " TL salary";
}
