//
//  main.cpp
//  chatBot
//
//  Created by Štěpán Fašina on 29.09.2026.
//

#include <cstdlib>
#include "ChatBot.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
//nastaveni windows treminalu
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    ChatBot bot;
    bot.chat();

    return EXIT_SUCCESS;
}