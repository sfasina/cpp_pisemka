//
//  ChatBot.cpp
//  chatBot
//
//  Created by Štěpán Fašina on 29.09.2026.
//

#include "ChatBot.hpp"
#include <iostream>

// Dictionary nemá výchozí konstruktor, proto ho inicializujeme v inicializačním seznamu
ChatBot::ChatBot() : dict(CHAT_NAME) {
}

void ChatBot::reply(const std::string& text) const {
    std::cout << "P: " << text << std::endl;
}

void ChatBot::chat() {
    std::string question;
    while (true) {
        std::cout << "U: ";
        if (!std::getline(std::cin, question)) {
            break; // konec vstupu
        }
        if (question == "konec" || question == "Konec") {
            break;
        }
        reply(dict.find_response(question));
    }
}