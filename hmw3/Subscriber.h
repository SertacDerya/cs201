//Sertaç Derya 22003208 Sec1
#ifndef SUB
#define SUB
#include "LinkedList.h"
#include "Transaction.h"

class Subscriber {
    public:
        Subscriber();
        Subscriber(int id);
        Subscriber(const Subscriber& copy);
        ~Subscriber();

        int getID() const;
        LinkedList<Transaction> getTransactionCopy() const;
        void setTransactionList(const LinkedList<Transaction>& tList);
        Subscriber& operator=(const Subscriber& assign);
    private:
        LinkedList<Transaction> transactions;
        int id;
};
//#include "Subscriber.cpp"

#endif