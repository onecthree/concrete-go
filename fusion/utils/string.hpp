#pragma once

#include <vector>
#include <string>

namespace utils {
    std::vector<std::string> str_split(std::string separate, std::string a_string) {
        std::vector<std::string> tmp = {""};

        for(auto &e : a_string) {
            if(std::string(1, e) != separate) {
                tmp[tmp.size() - 1] += e;
            } else {
                tmp.push_back("");
            }
        }

        return tmp;
    }
}