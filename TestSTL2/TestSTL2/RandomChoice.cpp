#include "Function.h"

std::string& Trim(std::string& ss, const std::string& pat) {
    ss.erase(0, ss.find_first_not_of(pat));
    ss.erase(ss.find_last_not_of(pat) + 1);
    return ss;
}

std::string Trim(const std::string& ss, const std::string& pat) {
    std::string sl = ss;
    sl.erase(0, sl.find_first_not_of(pat));
    sl.erase(sl.find_last_not_of(pat) + 1);
    return sl;
}

std::vector<std::string> Split(const std::string& ss, const std::string& sep) {
    std::vector<std::string> elems;
    size_t start = 0;
    size_t extra = 0;
    size_t end = 0;
    while ((end = ss.find(sep, start + extra)) != ss.npos) {
        elems.push_back(ss.substr(start, end - start));
        start = end + sep.length();
        extra = sep.length() == 0 ? 1 : 0;
    }
    elems.push_back(ss.substr(start));
    return elems;
}

void Replace(std::string& ss, const std::string& from, const std::string& to) {
    auto pos = ss.find(from);
    while (pos != std::string::npos) {
        ss.replace(pos, from.length(), to);
        pos = ss.find(from, pos + to.length());
    }
}