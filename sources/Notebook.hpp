#include <iostream>
#include <unordered_map>
#include <vector>
#include "Direction.hpp"

#define LINE_LEN 100

using ariel::Direction;
using namespace std;

namespace ariel{
    class Notebook{
        unordered_map<int, unordered_map<int, vector<char>>> pages;
        public:
        Notebook();
        void write(unsigned int, unsigned int, unsigned int, Direction, string const &) const;
        string read(unsigned int, unsigned int, unsigned int, Direction, int) const;
        void erase(unsigned int, unsigned int, unsigned int, Direction, int) const;
        void show(unsigned int) const;
        ~Notebook();
    };
};