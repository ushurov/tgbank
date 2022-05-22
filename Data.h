//
// Created by Emir on 22.05.2022.
//

#ifndef UNTITLED3_DATA_H
#define UNTITLED3_DATA_H

#include "User.h"
#include "Transaction.h"
#include <cstdlib>
#include <vector>
#include <tgbot/Bot.h>

class Data {

private:
    std::vector<User> users;
    std::vector<Transaction> transactions;

public:
    void pay(TgBot::Bot* bot, TgBot::Message::Ptr message);
    void send(TgBot::Bot* bot, TgBot::Message::Ptr message);
    void start();
    User* getUser(std::string id);
};





#endif //UNTITLED3_DATA_H
