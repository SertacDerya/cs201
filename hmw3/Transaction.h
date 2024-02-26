//Sertaç Derya 22003208 Sec1
#ifndef TRANSACTION
#define TRANSACTION

class Transaction {
    public:
        Transaction();
        Transaction(int subscriberID, int movieID);
        int getMovieID();
        int getSubID();
        bool completeTransaction();
        bool getReturned();
    private:
        int subscriberID;
        int movieID;
        bool returned;
};
//#include "Transaction.cpp"

#endif