//Sertaç Derya 22003208 Sec1
#ifndef MOV_SYSTEM
#define MOV_SYSTEM
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "Subscriber.h"
#include "Movie.h"

class MovieRentalSystem {
    public:
        MovieRentalSystem( const string movieInfoFileName,
        const string subscriberInfoFileName );
        ~MovieRentalSystem();
        void removeMovie( const int movieId );
        void addMovie( const int movieId, const int numCopies );
        void removeSubscriber( const int subscriberId );
        void rentMovie( const int subscriberId, const int movieId );
        void returnMovie( const int subscriberId, const int movieId );
        void showMoviesRentedBy( const int subscriberId ) const;
        void showSubscribersWhoRentedMovie( const int movieId ) const;
        void showAllMovies() const;
        void showAllSubscribers() const;

        void addSub( const int subId);
        MovieRentalSystem();
    private:
        LinkedList<Subscriber> subscriberList;
        LinkedList<Movie> movieList;
        //LinkedList<Transaction> transactionsList;
        void addMovieBeginning( const int movieId, const int numCopies );
};
//#include "MovieRentalSystem.cpp"
#endif