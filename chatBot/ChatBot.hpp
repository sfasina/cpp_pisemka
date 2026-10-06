//
//  ChatBot.hpp
//  chatBot
//
//  Created by Štěpán Fašina on 29.09.2026.
//

#ifndef ChatBot_hpp
#define ChatBot_hpp

#include <string>
#include "Dictionary.hpp"

class ChatBot {
private:
    const std::string CHAT_NAME = "chat.txt";
    Dictionary dict;

    void reply(const std::string& text) const;

public:
    ChatBot();
    void chat();
};

#endif /* ChatBot_hpp */