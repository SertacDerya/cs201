//Sertaç Derya 22003208 Sec1
#ifndef MOVIE
#define MOVIE

class Movie {
    public:
        Movie();
        Movie(const Movie& aMovie);
        Movie(int movId, int copyAmount);
        int getID() const;
        bool rentMovie();
        bool returnMovie(); 
        int getCurrentAmount();
        int getCopyAmount();
    private:
        int movId;
        int copyAmount;
        int currentAmount;
};
//#include "Movie.cpp"

#endif