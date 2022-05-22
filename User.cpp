//
// Created by Emir on 22.05.2022.
//

#include "User.h"
User::User(std::string name, std::string id, double balance, std::string chat_id) {
    this->name = name;
    this->id = id;
    this->balance = balance;
    this->chat_id = chat_id;
}

double User::getBalance() {
    return balance;
}

std::string User::getName()  {
    return name;
}

void User::setBalance(double balance) {
    this->balance=balance;
}

std::string User::getId()  {
    return id;
}

std::string User::getChat() {
    return chat_id;
}

void User::setChat(std::string chat_id) {
    this->chat_id=chat_id;
}

User::User() {}
