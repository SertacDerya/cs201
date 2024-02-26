//Sertaç Derya sec1 22003208
#ifndef PLAYER
#define PLAYER
#include <string>
using namespace std;
class Team;
class Player {
    public:
        Player(string name, int jerseyNo, int salary);
        Player(const Player&);
        Player();
        //getters
        string getName() const;
        int getJerseyNo() const;
        string getTeam() const;
        int getSalary() const;
        //changers
        void changeJerseyNo(int jerseyNo);
        void changeTeam(string nTeam);
        friend ostream& operator<<(ostream& os, const Player& player);
    private:
        string name{};
        int jerseyNo{0};
        string teamName{};
        int salary{0};
};
//#include "Player.cpp"
#endif
