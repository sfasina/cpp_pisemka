#include <array>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Board.h"
#include "PieceTable.h"
#include "Position.h"
#include "Rules.h"

// main = lepidlo: Board (pole), PieceTable (mapa) a Rules o sobe nevedi
int main() {
    Board board;
    PieceTable pieces;
    if (!board.load("sachovnice.txt") || !pieces.load("figurky.txt")) {
        return 1;
    }

    bool whiteTurn = true;
    std::array<int, 2> points{0, 0};   // pole: [0] = bily, [1] = cerny
    std::map<char, int> captured;      // mapa: znak figurky -> kolikrat byla sebrana

    while (true) {
        board.print();
        std::cout << (whiteTurn ? "Bily" : "Cerny")
                  << " na tahu (napr. e2 e4, quit = konec): ";

        std::string line;
        if (!std::getline(std::cin, line) || line == "quit") {
            std::cout << "Konec hry." << std::endl;
            break;
        }

        // "e2 e4" -> dve slova oddelena mezerou -> >> je rozdeli samo
        std::istringstream ss(line);
        std::string fromStr, toStr;
        Position from{}, to{};
        if (!(ss >> fromStr >> toStr) || !parsePosition(fromStr, from) || !parsePosition(toStr, to)) {
            std::cout << "Zadej tah jako: e2 e4" << std::endl;
            continue;
        }

        std::string error;
        if (!Rules::canMove(board, from, to, whiteTurn, error)) {
            std::cout << error << std::endl;
            continue;   // stejny hrac hraje znovu
        }

        char piece = board.get(from);
        char target = board.get(to);

        // brani
        if (target != '.') {
            ++captured[target];   // m[klic]: chybejici klic se vytvori s 0, pak ++
            points[whiteTurn ? 0 : 1] += pieces.value(target);
            std::cout << pieces.name(piece) << " bere: " << pieces.name(target) << std::endl;
        }

        // samotny tah: na cil dat figurku, start vyprazdnit
        board.set(to, piece);
        board.set(from, '.');

        // pesec na konci sachovnice se zmeni na damu
        if (std::tolower(static_cast<unsigned char>(piece)) == 'p' && (to.row == 0 || to.row == Board::SIZE - 1)) {
            board.set(to, whiteTurn ? 'Q' : 'q');
            std::cout << "Pesec se meni na damu!" << std::endl;
        }

        // sebrany kral = konec
        if (std::tolower(static_cast<unsigned char>(target)) == 'k') {
            board.print();
            std::cout << (whiteTurn ? "Bily" : "Cerny") << " vyhral!" << std::endl;
            break;
        }

        whiteTurn = !whiteTurn;   // stridani hracu
    }

    // souhrn: pruchod mapou je vzdy serazeny podle klice
    std::cout << std::endl << "Body - bily: " << points[0] << ", cerny: " << points[1] << std::endl;
    if (!captured.empty()) {
        std::cout << "Sebrane figurky:" << std::endl;
        for (const auto& [symbol, count] : captured) {   // [klic, hodnota] = structured binding
            std::cout << "  " << (Rules::isWhite(symbol) ? "bily " : "cerny ")
                      << pieces.name(symbol) << ": " << count << "x" << std::endl;
        }
    }
    return 0;
}
