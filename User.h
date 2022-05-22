//
// Created by Emir on 22.05.2022.
//

#ifndef UNTITLED3_USER_H
#define UNTITLED3_USER_H


#include <string>

class User {

private:
    std::string name, id, chat_id;
    double balance;

public:
    std::string getName();
    std::string getId();
    std::string getChat();
    void setChat(std::string chat_id);
    void setBalance(double balance);
    User(std::string name, std::string id, double balance, std::string chat_id);

    User();

    double getBalance();
};


#endif //UNTITLED3_USER_H
