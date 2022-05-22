//
// Created by Emir on 21.05.2022.
//

#include "Data.h"
#include <typeinfo>
#include <utility>
#include <tgbot/net/TgLongPoll.h>
#include <tgbot/TgException.h>
#include <iostream>

void Data::start() {
    User test("User", "abc", 0.0, "454977072");
    users.push_back(test);
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    std::vector<TgBot::InlineKeyboardButton::Ptr> row0;
    TgBot::InlineKeyboardButton::Ptr checkButton(new TgBot::InlineKeyboardButton);
    checkButton->text = "Пополнить";
    checkButton->callbackData = "pay";
    row0.push_back(checkButton);
    TgBot::InlineKeyboardButton::Ptr checkButton1(new TgBot::InlineKeyboardButton);
    checkButton1->text = "Перевести";
    checkButton1->callbackData = "sendmoney";
    row0.push_back(checkButton1);
    keyboard->inlineKeyboard.push_back(row0);
    TgBot::Bot bot("5390504795:AAFxeKJnrxI-SLbiGxjg4SXJVowM5f6HulY");
    bot.getEvents().onCommand("start", [&bot, &keyboard, this](TgBot::Message::Ptr message){
        User* u = this->getUser(message->chat->username);
        if(u==&users[0]){
            u = new User(message->chat->firstName, message->chat->username, 0.0, std::to_string(message->chat->id));
            std::cout<<message->chat->id<<"\n";
            users.push_back(*u);
        }
        bot.getApi().sendMessage(message->chat->id, "Здравствуйте, " + message->chat->firstName + "\nВаш баланс: " + std::to_string(u->getBalance()), false, 0, keyboard);
        std::for_each(users.begin(), users.end(), [](User u){
            printf("%s\n", u.getId().c_str());
        });
    });
    bot.getEvents().onCallbackQuery([&bot, &keyboard, this](TgBot::CallbackQuery::Ptr query){
        if(query->data=="sendmoney") {
            bot.getApi().sendMessage(query->message->chat->id, query->from->firstName+", введите -id, пользователя и сумму через пробел (Пример:'-user 300')");
        }
        if(query->data=="pay") {
            bot.getApi().sendMessage(query->message->chat->id, query->from->firstName+", введите сумму, которой хотите пополнить со знаком + (Пример:'+300')");
        }
    });
    bot.getEvents().onAnyMessage([&bot, this, keyboard](TgBot::Message::Ptr message) {
        if(StringTools::startsWith(message->text, "+")){
            this->pay(&bot, message);
        }
        if(StringTools::startsWith(message->text, "@")){
            this->send(&bot, message);
        }
    });
        try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
            printf("error: %s\n", e.what());
        }

}

void Data::pay(TgBot::Bot *bot, TgBot::Message::Ptr message) {
    srand((unsigned)time(0));
    std::vector< TgBot::LabeledPrice::Ptr > pr;
    TgBot::LabeledPrice::Ptr prl(new TgBot::LabeledPrice);
    prl->label=message->text.c_str();
    prl->amount=std::atoi(message->text.c_str())*100;
    pr.push_back(prl);
    bot->getApi().sendInvoice(message->chat->id,
                              "Пополнение",
                              "Пополнить "+message->text,
                              std::to_string(rand()%10000)+std::to_string(rand()%10000),
                              "381764678:TEST:37500",
                              "abcadasdas",
                              "RUB",
                              pr);
    User* upay = this->getUser(message->chat->username);
    Transaction t(users[0], *upay, std::atoi(message->text.c_str()));
    transactions.push_back(t);
    upay->setBalance(upay->getBalance() + std::atof(message->text.c_str()));
    bot->getApi().sendMessage(message->chat->id, "Ваш баланс: " + std::to_string(this->getUser(message->chat->username)->getBalance()));

}

void Data::send(TgBot::Bot *bot, TgBot::Message::Ptr message){
    User *from = this->getUser(message->chat->username);
    double sum = std::atof(message->text.substr(message->text.find(" "), message->text.size()).c_str());
    std::string to_id(message->text.substr(1, message->text.find(" ")-1));
    User *to = this->getUser(to_id);
    to->setBalance(to->getBalance()+sum);
    std::cout << to_id << "|" << sum << "\n";
    from->setBalance(from->getBalance()-sum);
    Transaction t(*from, *to, sum);
    transactions.push_back(t);
    bot->getApi().sendMessage(message->chat->id, "Ваш баланс: " + std::to_string(this->getUser(message->chat->username)->getBalance()));
    bot->getApi().sendMessage(std::stoi(to->getChat()), from->getName() + " перевел Вам " + std::to_string(sum) + "\n Ваш баланс: " + std::to_string(this->getUser(to_id)->getBalance()));
}

User* Data::getUser(std::string id) {
    for(int i=0; i<this->users.size(); i++){
        if(users[i].getId()==id) return &users[i];
    }
    return &users[0];
}

