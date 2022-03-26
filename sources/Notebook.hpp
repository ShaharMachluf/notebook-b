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
        void write(int, int, int, Direction, string const &);
        string read(int, int, int, Direction, int) const;
        void erase(int, int, int, Direction, int);
        void show(int) const;
    };
};