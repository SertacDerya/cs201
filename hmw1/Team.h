//Sertaç Derya sec1 22003208
#ifndef TEAM
#define TEAM
#include <string>
using namespace std;

class Player;
class Team {
    public:
        Team(const string name, const int year);
        Team(const Team&);
        Team();
        ~Team();
        //getters
        string getTeamName() const;
        int getYearFounded() const;
        Player* getPlayerArr() const;
        int getTotalSalary() const;
        int getPlayerSize() const;
        //adder & remove
        bool addPlayer(Player& player);
        bool removePlayer(string name);
        //changer
        void changeSalary(int amount);
        friend ostream& operator<<(ostream& os, const Team& team);
        Team& operator=(const Team&);
    private:
        string teamName{};
        int yearFounded{0};
        Player* playersArr{nullptr};
        int playerArrSize{0};
        int totalSalary{0};
};
//#include "Team.cpp"
#endif
