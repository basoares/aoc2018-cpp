#ifndef AOC_UTILS_H_
#define AOC_UTILS_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

#include "error.h"

namespace utils {

template<typename Out>
void split(const std::string& s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

auto getFilename(int argc, char* argv[], const std::string& day) {
    if (argc == 1) {
        return "../input/" + day + ".txt";
    }
    std::vector<std::string> vargs {argv, argv + argc};

    if (argc == 2 && vargs[1] == "-t") {
        return "..input/" + day + "-test-input.txt";
    }
    return vargs[1];
}

template<typename ...Args>
auto getInputString(const Args& ...args) {
    std::string filename = getFilename(args...);
    std::ifstream ifs(filename);
    if (!ifs) {
        throw AoCError("Could not open file " + filename);
    }

    std::string line;
    std::getline(ifs, line);
    return line;
}

template<typename ...Args>
auto getInputLines(const Args& ...args) {
    std::string filename = getFilename(args...);
    std::ifstream ifs(filename);
    if (!ifs) {
        throw AoCError("Could not open file " + filename);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(ifs, line)) {
        lines.push_back(std::move(line));
    }

    return lines;
}

template<typename T, typename ...Args>
auto getInputValues(const Args& ...args) {
    std::string filename = getFilename(args...);
    std::ifstream ifs(filename);
    if (!ifs) {
        throw AoCError("Could not open file " + filename);
    }

    std::vector<T> v;
    std::string line;
    for (T val; ifs >> val; ) {
        v.push_back(val);
    }
    return v;
}

} //namespace utils

#endif
