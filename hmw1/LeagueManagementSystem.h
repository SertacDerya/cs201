//Sertaç Derya sec1 22003208
#ifndef _LEAGUE_MANAGEMENT
#define _LEAGUE_MANAGEMENT
#include <string>
#include "Team.h"
#include "Player.h"
using namespace std;

class LeagueManagementSystem {
    public:
        LeagueManagementSystem();
        ~LeagueManagementSystem();
        void addTeam( const string name, const int year );
        void removeTeam( const string name );
        void addPlayer( const string teamName, const string playerName,
        const int jersey, const int salary );
        void removePlayer( const string teamName, const string playerName );
        void transferPlayer( const string playerName,
        const string departTeamName, const string arriveTeamName );
        void showAllTeams() const;
        void showTeam( const string name ) const;
        void showPlayer( const string name ) const;
    
    private:
        Team* teamArr;
        int teamArrSize;
        Player* playerArr;
        int playerArrSize;
};
//#include "LeagueManagementSystem.cpp"
#endif
