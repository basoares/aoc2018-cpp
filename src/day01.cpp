#include <iostream>
#include <vector>
#include <numeric>
#include <set>

#include "../include/utils.h"
#include "../include/tinytest.h"

//Part One
//The resulting frequency after all the frequency changes corresponds
//to the sum of all the frequency changes
int resultingFrequency(std::vector<int> frqs) {
    auto ans = std::accumulate(std::begin(frqs), std::end(frqs), 0);

    return ans;
}

//Part Two
//Save in a set all the frequencies reached and the compare
//with the resulting frequency. The first frequency to be found
//in the set is the first frequency to be reached twice
int firstDuplicate(std::vector<int> frqs) {
    int frq = 0;
    std::set<int> visited;
    visited.insert(frq);  //we start at frequency 0

    bool found = false;
    while (!found) {
        for (const auto& c : frqs) {
            frq += c;
            auto it = visited.find(frq);
            if (it != visited.end()) {
                found = true;
                break;
            }
            visited.insert(frq);
        }
    }

    return frq;
}

int main(int argc, char* argv[]) {
    std::cout << "Advent of Code 2018 Day 1 - Chronal Calibration\n\n";

    std::cout << "Running test cases\n";
    int r = RUN_TESTS();
    std::cout << r << " test(s) failed\n\n";
    
    auto frqChanges = utils::getInputValues<int>(argc, argv, "day01");

    std::cout << "Puzzle answers\n";
    auto ans = resultingFrequency(frqChanges);
    std::cout << "Part 1: " << ans << std::endl;

    auto ans2 = firstDuplicate(frqChanges);
    std::cout << "Part 2: " << ans2 << std::endl;

    return 0;
}

/*
 * Test cases
 */

TINY_TEST(example1) {
    std::vector<int> v = {+1, -2, +3, +1};
    TINY_CHECK("+1, -2, +3, +1 => 3", resultingFrequency(v) == 3);
}

TINY_TEST(example2) {
    std::vector<int> v = {+1, +1, +1};
    TINY_CHECK("+1, +1, +1 => 3", 
               resultingFrequency(v) == 3);
}

TINY_TEST(example3) {
    std::vector<int> v = {+1, +1, -2};
    TINY_CHECK("+1, +1, -2 => 0", 
               resultingFrequency(v) == 0);
}

TINY_TEST(example4) {
    std::vector<int> v = {+1, -1};
    TINY_CHECK("+1, -1 => 0", firstDuplicate(v) == 0);
}

TINY_TEST(example5) {
    std::vector<int> v = {+3, +3, +4, -2, -4};
    TINY_CHECK("+3, +3, +4, -2, -4 => 10", 
               firstDuplicate(v) == 10);
}

TINY_TEST(example6) {
    std::vector<int> v = {-6, +3, +8, +5, -6};
    TINY_CHECK("-6, +3, +8, +5, -6 => 5", 
               firstDuplicate(v) == 5);
}

TINY_TEST(example7) {
    std::vector<int> v = {+7, +7, -2, -7, -4};
    TINY_CHECK("+7, +7, -2, -7, -4 => 14", 
               firstDuplicate(v) == 14);
}

