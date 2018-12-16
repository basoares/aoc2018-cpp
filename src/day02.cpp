#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <algorithm>

#include "../include/utils.h"
#include "../include/tinytest.h"

//Part One
int computeChecksum(std::vector<std::string> boxIDs) {
    //the boxID contains only lower case letters 
    //we can save the counts in a vector of 26 elements
    std::vector<unsigned int> counts(26);
    unsigned int two_of_the_same=0;
    unsigned int three_of_the_same=0;

    for (const auto& id : boxIDs) {
        for (const auto& l : id) {
            counts[l - 'a']++; 
        }
        if (std::find(counts.begin(), counts.end(), 2) != counts.end()) {
            two_of_the_same += 1;
        }
        if (std::find(counts.begin(), counts.end(), 3) != counts.end()) {
            three_of_the_same += 1;
        }
        std::fill(counts.begin(), counts.end(), 0);
    } 

    return two_of_the_same * three_of_the_same;
}

//Part Two
//Given two box IDs returns the number of different chars at the same position
int numDifferentChars(const std::string& id1, const std::string& id2) {
    int num_different_chars = 0;
    auto it1 = id1.begin();
    auto it2 = id2.begin();

    for ( ; it1 != id1.end(); ++it1, ++it2) {
        if (*it1 != *it2) {
            num_different_chars += 1;
        }
    }
    return num_different_chars;
}

//returns the two box ids that differ by one char
std::pair<std::string, std::string> differByOne(
                                    std::vector<std::string> boxIDs) {
    for (const auto& id1 : boxIDs) {
        for (const auto& id2 : boxIDs) {
            if (numDifferentChars(id1, id2) == 1) {
                return std::make_pair(id1, id2);
            }
        }
    }
    return {"", ""};
}

//chars in common between the two box IDs
std::string commonChars(std::pair<std::string, std::string> ids) {
    std::ostringstream common;
    auto it1 = ids.first.begin();
    auto it2 = ids.second.begin();

    for (; it1 != ids.first.end(); ++it1, ++it2) {
        if (*it1 == *it2) {
            common << *it1;
        }
    }
    return common.str();
}

int main(int argc, char* argv[]) {
    std::cout << "Advent of Code 2018 Day 2 - Inventory Management System\n\n";

    std::cout << "Running test cases\n";
    int r = RUN_TESTS();
    std::cout << r << " test(s) failed\n\n";
    
    auto boxIDs = utils::getInputLines(argc, argv, "day02");

    std::cout << "Puzzle answers\n";
    auto ans = computeChecksum(boxIDs);
    std::cout << "Part 1: " << ans << std::endl;

    auto ans2 = commonChars(differByOne(boxIDs));
    std::cout << "Part 2: " << ans2 << std::endl;

    return 0;
}

/*
 * Test cases
 */

TINY_TEST(example1) {
    std::vector<std::string> v = {"abcdef", "bababc", "abbcde", "abcccd", 
                             "aabcdd", "abcdee", "ababab"};
    TINY_CHECK("num_ids_with_2 * num_ids_with_3", computeChecksum(v) == 12);
}

TINY_TEST(example2) {
    std::vector<std::string> v = {"abcde", "fghij", "klmno", "pqrst", 
                             "fguij", "axcye", "wvxyz"};
    TINY_CHECK("chars in common", commonChars(differByOne(v)) == "fgij");
}

