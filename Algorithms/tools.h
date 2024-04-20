#pragma once

#include <string>

std::string gen_random(const int len) {
    static const char alphanum[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

std::string index_to_string(int64_t index) {
    std::string out;
    int char_number = '~' - '!';
    while (true) {
        if (index >= char_number) {
            char tmp = index % char_number;
            tmp = tmp + '!';
            index = index / char_number;
            out = tmp + out;
        } else {
            char tmp = index + '!';
            out = tmp + out;
            return out;
        }
    }
}