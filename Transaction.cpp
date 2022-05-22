//
// Created by Emir on 22.05.2022.
//

//
// Created by Emir on 21.05.2022.
//

#include "Transaction.h"
#include <ctime>
#include "User.h"
Transaction::Transaction(User from, User to, double sum) {
    asctime(localtime(&this->time));
}

time_t Transaction::getTime() {
    return time;
}

const User Transaction::getFrom() {
    return from;
}

const User Transaction::getTo() {
    return to;
}

double Transaction::getSum() {
    return sum;
}
