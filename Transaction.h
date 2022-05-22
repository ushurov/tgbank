//
// Created by Emir on 22.05.2022.
//

#ifndef UNTITLED3_TRANSACTION_H
#define UNTITLED3_TRANSACTION_H
#include <cstdlib>
#include <ctime>
#include "User.h"

class Transaction {

private:
    time_t time;
    User from;
    User to;
    double sum;

public:
    Transaction(User from, User to, double sum);

    time_t getTime();

    const User getFrom();

    const User getTo();

    double getSum();

};



#endif //UNTITLED3_TRANSACTION_H
