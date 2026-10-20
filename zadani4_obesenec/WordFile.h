//
// Created by fasin on 20.10.2026.
//

#ifndef CPP2PRACTISE_WORDFILE_H
#define CPP2PRACTISE_WORDFILE_H

#include <string>
#include <vector>

// trida na soubor: jen nacte slova (jedno slovo na radek)
// o hre nic nevi - propojeni dela main
class WordFile {
private:
    std::vector<std::string> m_words;

public:
    void loadWords(const std::string& filePath);

    // const& = vrati vektor bez kopirovani a nikdo ho zvenku nezmeni
    const std::vector<std::string>& getWords() const { return m_words; }
};

#endif //CPP2PRACTISE_WORDFILE_H
