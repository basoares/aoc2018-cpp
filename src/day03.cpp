#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include "../include/utils.h"
#include "../include/tinytest.h"

using Fabric = std::map<std::pair<int, int>, int>;

struct Claim
{
    int id;
    int x;
    int y;
    int w;
    int h;
};

std::istream& operator>>(std::istream& is, Claim& claim) {
    char ignore;
    int id, x, y, w, h;

    //#1 @ 151,671: 11x15
    is >> ignore >> id >> ignore >> x >> ignore >> y >> ignore >> w >> ignore >> h;

    claim = Claim{ id, x, y, w, h };

    return is;
}

Fabric lay_claims(const std::vector<Claim>& claims) {
    Fabric fabric;
    std::for_each(std::begin(claims), std::end(claims),
            [&fabric](const Claim& c) {
                for (int i = c.y; i < c.y + c.h; ++i)
                    for (int j = c.x; j < c.x + c.w; ++j)
                        ++fabric[{i, j}];
            });

    return fabric;
}

//Part One
int claimed_multiple_times(Fabric& fabric) {
    int count = 0;
    for (auto const& f : fabric)
        if (f.second > 1)
            ++count;
    return count;
}

//Part Two
auto intact_claim(Fabric& fabric, std::vector<Claim> claims) {
    return std::find_if(claims.begin(), claims.end(), [&](auto& c){
            int count = 0;
            for (int i = c.y; i < c.y + c.h; ++i)
                for (int j = c.x; j < c.x + c.w; ++j)
                    count += fabric[{i, j}];
            return c.w*c.h == count;
            }); 
    }

int main(int argc, char* argv[]) {
    std::cout << "Advent of Code 2018 Day 3 - No Matter How You Slice It\n\n";

    std::cout << "Running test cases\n";
    int r = RUN_TESTS();
    std::cout << r << " test(s) failed\n\n";
    
    auto claims = utils::getInputValues<Claim>(argc, argv, "day03");
    auto fabric = lay_claims(claims);

    std::cout << "Puzzle answers\n" << std::endl;
    auto part1 = claimed_multiple_times(fabric);
    std::cout << "Part 1: " << part1 << std::endl;

    auto part2 = intact_claim(fabric, claims);
    std::cout << "Part 2: " << part2[0].id << std::endl;

    return 0;
}

/*
 * Test cases
 */

TINY_TEST(example1) {
    std::istringstream iss("#1 @ 1,3: 4x4\n#2 @ 3,1: 4x4\n#3 @ 5,5: 2x2");
    std::vector<Claim> claims;
    for (Claim c; iss >> c; ) {
        claims.push_back(c);
    }
    auto fabric = lay_claims(claims);
    TINY_CHECK("Num square inches within two or more claims", claimed_multiple_times(fabric) == 4);
}

TINY_TEST(example2) {
    std::istringstream iss("#1 @ 1,3: 4x4\n#2 @ 3,1: 4x4\n#3 @ 5,5: 2x2");
    std::vector<Claim> claims;
    for (Claim c; iss >> c; ) {
        claims.push_back(c);
    }
    auto fabric = lay_claims(claims);
    TINY_CHECK("Intact claim", intact_claim(fabric, claims)[0].id == 3);
}

