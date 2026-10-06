//
//  Dictionary.hpp
//  chatBot
//
//  Created by Štěpán Fašina on 29.09.2026.
//

#ifndef Dictionary_hpp
#define Dictionary_hpp

#include <string>
#include <vector>
#include <utility>

class Dictionary {
private:
    std::vector<std::pair<std::string, std::string>> entries;
    static const std::string FALLBACK;
    void add_to_entries(std::ifstream &file);

public:
    Dictionary(const std::string& fileName);
    std::string find_response(const std::string& query) const;
};

#endif /* Dictionary_hpp */