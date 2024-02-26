//Sertaç Derya 22003208 Sec1
#include <iostream>
#include <fstream>
#include "MovieRentalSystem.h"


MovieRentalSystem::MovieRentalSystem() {}

MovieRentalSystem::MovieRentalSystem(const string movieInfoFileName,
        const string subscriberInfoFileName) {

    ifstream inputFileMovie(movieInfoFileName.c_str(), ios_base::in);
    int movieCount;
    int movieID;
    int mSpecificAmount;

    ifstream inputFileSubs(subscriberInfoFileName.c_str(), ios_base::in);
    int subCount;
    int subID;
    if(!inputFileSubs.good() & !inputFileMovie.good()) {
        std::cout << "Input file " << subscriberInfoFileName << " & " << movieInfoFileName << " does not exist" << std::endl;
    } else if(!inputFileMovie.good()) {
        std::cout << "Input file " << movieInfoFileName << " does not exist" << std::endl;
    } else if(!inputFileSubs.good()) {
        std::cout << "Input file " << subscriberInfoFileName << " does not exist" << std::endl;
    } else {
        //inputFileMovie.open(movieInfoFileName.c_str(), ios_base::in);
        int j = 0;
        inputFileMovie >> movieCount;
        while(inputFileMovie.eof() == false & j < movieCount) {
            inputFileMovie >> movieID;
            inputFileMovie >> mSpecificAmount;
            this->addMovieBeginning(movieID, mSpecificAmount);//sort while adding with addMovie method? or just sort when adding to the list ?
            j++;
        }

        j = 0;
        inputFileSubs >> subCount;
        while(inputFileSubs.eof() == false & j < subCount) {// insert the subscribers already sorted
            inputFileSubs >> subID;
            this->addSub(subID);
            j++;
            /* Subscriber sub(subID);
            bool bigger = true;
            if(this->subscriberList.getLength() == 0) {
                this->subscriberList.insert(sub, 0);
            } else {
                for(int i = 0; i < this->subscriberList.getLength(); i++) {
                    if(this->subscriberList.getEntry(i).getID() > subID) {
                        this->subscriberList.insert(sub, i);
                        bigger = false;
                    }
                }
                if(bigger) {
                    this->subscriberList.insert(sub, this->subscriberList.getLength());
                }
            } */
        }
        std::cout << subCount << " subscribers and " << movieCount << " movies have been loaded" << std::endl;
    }
}

MovieRentalSystem::~MovieRentalSystem() {
    this->movieList.clear();
    this->subscriberList.clear();
}

void MovieRentalSystem::removeMovie( const int movieId ) {//movies don't have a list of transactions
    //check if the movies are not rented
    bool found = false;
    for(int i = 0; (i < this->movieList.getLength()) & !found; i++) {
        if(this->movieList.getEntry(i).getID() == movieId) {
            if(this->movieList.getEntry(i).getCopyAmount() == this->movieList.getEntry(i).getCurrentAmount()) {
                this->movieList.remove(i);
                std::cout << "Movie " << movieId << " has been removed" << std::endl;
            } else {
                std::cout << "Movie " << movieId << " cannot be removed -- at least one copy has not been returned" << std::endl;
            }
            found = true;
        }
    }
    if(!found) {
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    }
}

void MovieRentalSystem::addMovie( const int movieId, const int numCopies ) {
    bool alreadyExists = false;
    for(int i = 0; (i < this->movieList.getLength()) & !alreadyExists; i++) {
        if(movieId == this->movieList.getEntry(i).getID()) {
            std::cout << "Movie " << movieId << " already exists" << std::endl;
            alreadyExists = true;
        }
    }
    if(!alreadyExists) {
        Movie movie(movieId, numCopies);
        bool bigger = true;
        bool done = false;
        if(this->movieList.getLength() == 0) {
            this->movieList.insert(movie, 0);
        } else {
            for(int i = 0; i < this->movieList.getLength() & !done; i++) {
                if(this->movieList.getEntry(i).getID() > movieId) {
                    this->movieList.insert(movie, i);
                    bigger = false;
                    done = true;
                }
            }
            if(bigger) {
                this->movieList.insert(movie, this->movieList.getLength());
            }
        }
        std::cout << "Movie " << movieId << " has been added" << std::endl;
    }
}

void MovieRentalSystem::addSub( const int subId) {
    bool alreadyExists = false;
    for(int i = 0; (i < this->subscriberList.getLength()) & !alreadyExists; i++) {
        if(subId == this->subscriberList.getEntry(i).getID()) {
            //std::cout << "Subscriber " << subId << " already exists" << std::endl;
            alreadyExists = true;
        }
    }
    if(!alreadyExists) {
        Subscriber sub(subId);
        bool bigger = true;
        bool done = false;
        if(this->subscriberList.getLength() == 0) {
            this->subscriberList.insert(sub, 0);
        } else {
            for(int i = 0; i < this->subscriberList.getLength() & !done; i++) {
                if(this->subscriberList.getEntry(i).getID() > subId) {
                    this->subscriberList.insert(sub, i);
                    bigger = false;
                    done = true;
                }
            }
            if(bigger) {
                this->subscriberList.insert(sub, this->subscriberList.getLength());
            }
        }
        //std::cout << "Subscriber " << subId << " has been added" << std::endl;
    }
}

void MovieRentalSystem::addMovieBeginning( const int movieId, const int numCopies ) {
    bool alreadyExists = false;
    for(int i = 0; (i < this->movieList.getLength()) & !alreadyExists; i++) {
        if(movieId == this->movieList.getEntry(i).getID()) {
            //std::cout << "Movie " << movieId << " already exists" << std::endl;
            alreadyExists = true;
        }
    }
    if(!alreadyExists) {
        Movie movie(movieId, numCopies);
        bool bigger = true;
        bool done = false;
        if(this->movieList.getLength() == 0) {
            this->movieList.insert(movie, 0);
        } else {
            for(int i = 0; i < this->movieList.getLength() & !done; i++) {
                if(this->movieList.getEntry(i).getID() > movieId) {
                    this->movieList.insert(movie, i);
                    bigger = false;
                    done = true;
                }
            }
            if(bigger) {
                this->movieList.insert(movie, this->movieList.getLength());
            }
        }
        //std::cout << "Movie " << movieId << " has been added" << std::endl;
    }
}

void MovieRentalSystem::removeSubscriber( const int subscriberId ) {
    //delete the transactions that contain this subscriber
    bool allReturned = true;
    bool found = false;
    int index;
    for(int i = 0; (i < this->subscriberList.getLength()) & !found; i++) {
        if(this->subscriberList.getEntry(i).getID() == subscriberId) {
            index = i;
            found = true;
            int limit = this->subscriberList.getEntry(index).getTransactionCopy().getLength();
            for(int j = 0; j < this->subscriberList.getEntry(index).getTransactionCopy().getLength() & allReturned; j++) {
                /* if(this->subscriberList.getEntry(index).getTransactionCopy().g) {

                } */
                if(this->subscriberList.getEntry(index).getTransactionCopy().getEntry(j).getReturned() == false) {
                    allReturned = false;
                }
            }
            if(!allReturned) {
                std::cout << "Subscriber " << subscriberId << " cannot be removed -- at least one movie has not been returned" << std::endl;
            } else {
                this->subscriberList.remove(index);
                std::cout << "Subscriber " << subscriberId << " has been removed" << std::endl;
            }
        }
    }
    if(!found) {
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    }
}

void MovieRentalSystem::rentMovie( const int subscriberId, const int movieId ) {
    //check if movie exists
    bool movieFound = false;
    int movieIndex = 0;
    bool movieCopyAvailable = false;
    Movie thatMovie;
    bool done = false;
    for(int i = 0; (i < this->movieList.getLength()) & !movieFound & !done; i++) {
        if(this->movieList.getEntry(i).getID() == movieId) {
            movieFound = true;
            if(this->movieList.getEntry(i).getCurrentAmount() > 0) {
                movieCopyAvailable = true;
            }
            movieIndex = i;
            thatMovie = this->movieList.getEntry(i);
        } else if(this->movieList.getEntry(i).getID() > movieId) {
            done = true;
        }
    }
    //if it does not: warning message
    //warning messages in the end because if both movie and subscriber dne different warning message        
    //else    
    //check if subscriber exists
    
    bool subscriberFound = false;
    Subscriber thatSub;
    int subIndex = 0;
    for(int i = 0; (i < this->subscriberList.getLength()) & !subscriberFound; i++) {
        if(this->subscriberList.getEntry(i).getID() == subscriberId) {
            subscriberFound = true;
            subIndex = i;
            thatSub = this->subscriberList.getEntry(i);
        }
    }

    if(!movieFound & !subscriberFound) {
        std::cout << "Subscriber " << subscriberId << " and movie " << movieId << " do not exist" << std::endl;
    } else if(!movieFound) {
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    } else if(!subscriberFound) {
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    } else if(!movieCopyAvailable) {
        std::cout << "Movie " << movieId << " has no available copy for renting" << std::endl;
    } else {
        Transaction t1(subscriberId, movieId);
        //add this transaction to the subscriber
        LinkedList<Transaction> tListSub = thatSub.getTransactionCopy();
        bool bigger = true;
        bool done = false;
        if(tListSub.getLength() == 0) {
            tListSub.insert(t1, 0);
        } else {
            for(int i = 0; i < tListSub.getLength() & !done; i++) {
                if(tListSub.getEntry(i).getMovieID() > movieId) {
                    tListSub.insert(t1, i);
                    done = true;
                    bigger = false;
                }
            }
            if(bigger) {
                tListSub.insert(t1, tListSub.getLength());
            }
        }
        thatSub.setTransactionList(tListSub);
        this->subscriberList.setEntry(subIndex, thatSub);        
        
        //add transaction to the movie
        /* LinkedList<Transaction> tListMovie = thatMovie.getTransactCopy();
        Transaction t1(subscriberId, movieId);
        bool bigger = true;
        if(tListMovie.getLength() == 0) {
            tListMovie.insert(t1, 0);
        } else {
            for(int i = 0; i < tListMovie.getLength(); i++) {
                if(tListMovie.getEntry(i).getSubID() > subscriberId) {
                    tListMovie.insert(t1, i);
                    bigger = false;
                }
            }
            if(bigger) {
                tListMovie.insert(t1, tListMovie.getLength());
            }
        }
        thatMovie.setTransactList(tListMovie); */
        //decreaase the current copy of movie
        thatMovie.rentMovie();
        this->movieList.setEntry(movieIndex, thatMovie);    

        std::cout << "Movie " << movieId << " has been rented by subscriber " << subscriberId << std::endl;
    }
    
        //if it does not: warning message
    //check if the movie has a copy available
        // if it does not 
    //if all checks are okay rent the movie
        //decrease the copy of movie
        //create a transaction and save it in subscriber's linked list
}

void MovieRentalSystem::returnMovie( const int subscriberId, const int movieId ) {
    //check if movie exists
    bool movieFound = false;
    int movieIndex = 0;
    Movie thatMovie;
    for(int i = 0; (i < this->movieList.getLength()) & !movieFound; i++) {
        if(this->movieList.getEntry(i).getID() == movieId) {
            movieFound = true;
            movieIndex = i;
            thatMovie = this->movieList.getEntry(i);
        }
    }
    //if it does not: warning message
    //warning messages in the end because if both movie and subscriber dne different warning message        
    //else    
    //check if subscriber exists
    
    bool subscriberFound = false;
    Subscriber thatSub;
    int subIndex = 0;
    LinkedList<Transaction> tList;
    for(int i = 0; (i < this->subscriberList.getLength()) & !subscriberFound; i++) {
        if(this->subscriberList.getEntry(i).getID() == subscriberId) {
            subscriberFound = true;
            subIndex = i;
            thatSub = this->subscriberList.getEntry(i);
            tList = thatSub.getTransactionCopy();
        }
    }

    bool transactionFound = false;
    int traIndex = 0;
    Transaction thatTra;
    for(int j = 0; j < tList.getLength(); j++) {
        if(tList.getEntry(j).getMovieID() == movieId && tList.getEntry(j).getReturned() == false) {
            transactionFound = true;
            traIndex = j;
            thatTra = tList.getEntry(j);
        }
    }

    if(!movieFound & !subscriberFound) {
    std::cout << "Subscriber " << subscriberId << " and movie " << movieId << " do not exist" << std::endl;
    } else if(!movieFound) {
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    } else if(!subscriberFound) {
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    } else if(!transactionFound) {
        std::cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << std::endl;
    } else {
        //update transaction list of sub
        thatTra.completeTransaction();
        tList.setEntry(traIndex, thatTra);
        thatSub.setTransactionList(tList);
        this->subscriberList.setEntry(subIndex, thatSub);
        //return movie
        thatMovie.returnMovie();
        this->movieList.setEntry(movieIndex, thatMovie);
        std::cout << "Movie " << movieId << " has been returned by subscriber " << subscriberId << std::endl;
    }
    //check if there is a transaction between the given ids
        //if there is: warning message
        //else complete the transaction and message that movie can now be rented by others
}

void MovieRentalSystem::showMoviesRentedBy( const int subscriberId ) const {
    //show the movies rented by this particular subscriber
    //if the subsrciber dne: warning message
    bool subFound = false;
    Subscriber thatSub;
    LinkedList<Transaction> tList;
    bool rented = false;
    for(int i = 0; (i < this->subscriberList.getLength()) & !subFound; i++) {
        if(this->subscriberList.getEntry(i).getID() == subscriberId) {
            subFound = true;
            thatSub = this->subscriberList.getEntry(i);
            tList = thatSub.getTransactionCopy();
            if(tList.getLength() > 0) {
                rented = true;
            }
        }
    }
    if(!subFound) {
        std::cout << "Subscriber " << subscriberId << " does not exist" << std::endl;
    } else if(!rented) {
        std::cout << "Subscriber " << subscriberId << " has not rented any movies" << std::endl;
    } else {
        std::cout << "Subscriber " << subscriberId << " has rented the following movies:" << std::endl;
        for(int i = 0; i < tList.getLength(); i++) {
            if(tList.getEntry(i).getReturned() == true) {
                std::cout << tList.getEntry(i).getMovieID() << " returned" << std::endl;
            } else if(tList.getEntry(i).getReturned() == false) {
                std::cout << tList.getEntry(i).getMovieID() << " not returned" << std::endl;
            }
        }
    }
    //if the subscriber didnt rent any movie: warning message

}

void MovieRentalSystem::showSubscribersWhoRentedMovie( const int movieId ) const {
    //show the subscribers that rented this movie
    //if movie dne: warning message
    bool movieFound = false;
    Movie thatMovie;
    bool rented = false;
    for(int i = 0; (i < this->movieList.getLength()) & !movieFound; i++) {
        if(this->movieList.getEntry(i).getID() == movieId) {
            movieFound = true;
            thatMovie = this->movieList.getEntry(i);
        }
    }
    if(movieFound) {
        for(int i = 0; i < this->subscriberList.getLength(); i++) {
            Subscriber thatSub = this->subscriberList.getEntry(i);
            LinkedList<Transaction> tList = thatSub.getTransactionCopy();
            for(int j = 0; j < tList.getLength(); j++) {
                Transaction t1 = tList.getEntry(j);
                if(t1.getMovieID() == movieId) {
                    if(!rented) {
                        std::cout << "Movie " << movieId << " has been rented by the following subscribers:" << std::endl;
                    }
                    rented = true;
                    if(t1.getReturned() == false) {
                        std::cout << thatSub.getID() << " not returned" << std::endl;
                    } else if(t1.getReturned() == true) {
                        std::cout << thatSub.getID() << " returned" << std::endl;
                    }
                }
            }
        }
        if(!rented) {
            std::cout << "Movie " << movieId << " has not been rented by any subscriber" << std::endl;
        }
    } else {
        std::cout << "Movie " << movieId << " does not exist" << std::endl;
    }
    //if movie wasnt rented: warning message

}

void MovieRentalSystem::showAllMovies() const {
    //display each movie with its id and copy number
    std::cout << "Movies in the movie rental system:" << std::endl;
    for(int i = 0; i < this->movieList.getLength(); i++) {
        Movie movie = this->movieList.getEntry(i);
        std::cout << movie.getID() << " " << movie.getCopyAmount() << std::endl;
    }
}

void MovieRentalSystem::showAllSubscribers() const {
    //display every subscriber and their ids !!! not movies rented by them
    std::cout << "Subscribers in the movie rental system:" << std::endl;
    for(int i = 0; i < this->subscriberList.getLength(); i++) {
        Subscriber sub = this->subscriberList.getEntry(i);
        std::cout << sub.getID() << std::endl;
    }
}