 /** AUTHORS: Shahar Machluf
 * 
 * Date: 3-19-2022
 */

#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

Notebook notebook;
TEST_CASE("Bad input"){
    CHECK_THROWS(notebook.write(1, 5, 101, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 5, 99, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 5, 99, Direction::Horizontal, "a\t"));
    CHECK_THROWS(notebook.write(1, 5, 99, Direction::Horizontal, "a\n"));
    CHECK_THROWS(notebook.write(1, 5, 55, Direction::Horizontal, "ab~d"));
}

TEST_CASE("Read") {
    notebook.write(5, 5, 5, Direction::Horizontal, "abcd");
	CHECK(nospaces(notebook.read(5,5,5,Direction::Horizontal,4)) == nospaces("abcd"));
	CHECK(nospaces(notebook.read(5,5,4,Direction::Horizontal,4)) == nospaces("_abc"));
    CHECK(nospaces(notebook.read(5,5,3,Direction::Horizontal,4)) == nospaces("__ab"));
    CHECK(nospaces(notebook.read(5,5,2,Direction::Horizontal,4)) == nospaces("___a"));
    CHECK(nospaces(notebook.read(5,5,1,Direction::Horizontal,4)) == nospaces("____"));
    CHECK(nospaces(notebook.read(5,5,6,Direction::Horizontal,4)) == nospaces("bcd_"));
    CHECK(nospaces(notebook.read(5,5,7,Direction::Horizontal,4)) == nospaces("cd__"));
    CHECK(nospaces(notebook.read(5,5,8,Direction::Horizontal,4)) == nospaces("d___"));
    CHECK(nospaces(notebook.read(5,5,9,Direction::Horizontal,4)) == nospaces("____"));
    CHECK(nospaces(notebook.read(5,5,5,Direction::Vertical,4)) == nospaces("a\n_\n_\n_"));
    CHECK(nospaces(notebook.read(5,4,5,Direction::Vertical,4)) == nospaces("_\na\n_\n_"));
    CHECK(nospaces(notebook.read(5,3,5,Direction::Vertical,4)) == nospaces("_\n_\na\n_"));
    CHECK(nospaces(notebook.read(5,2,5,Direction::Vertical,4)) == nospaces("_\n_\n_\na"));
    CHECK(nospaces(notebook.read(5,5,6,Direction::Vertical,4)) == nospaces("b\n_\n_\n_"));
}

TEST_CASE("Write"){
    notebook.write(1, 5, 5, Direction::Horizontal, "abcd");
    CHECK_THROWS(notebook.write(1, 5, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 5, 2, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 5, 8, Direction::Horizontal, "abcd"));
    CHECK_NOTHROW(notebook.write(1, 5, 1, Direction::Horizontal, "abcd"));
    CHECK_NOTHROW(notebook.write(1, 5, 9, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 5, 5, Direction::Vertical, "abcd"));
    CHECK_THROWS(notebook.write(1, 4, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 3, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 2, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 5, 8, Direction::Horizontal, "abcd"));
    CHECK_NOTHROW(notebook.write(1, 5, 0, Direction::Horizontal, "abcd"));
    CHECK_NOTHROW(notebook.write(1, 5, 13, Direction::Horizontal, "abcd"));
}

TEST_CASE("Erase"){
    notebook.write(2, 5, 5, Direction::Horizontal, "abcd");
    notebook.erase(2, 5, 5, Direction::Horizontal, 1);
    CHECK(nospaces(notebook.read(2,5,5,Direction::Horizontal,4)) == nospaces("~bcd"));
    notebook.erase(2,5,6,Direction::Horizontal,2);
    CHECK(nospaces(notebook.read(2,5,5,Direction::Horizontal,4)) == nospaces("~~~d"));
    notebook.erase(2,3,8, Direction::Vertical,3);
    CHECK(nospaces(notebook.read(2,5,5,Direction::Horizontal,4)) == nospaces("~~~~"));
    CHECK(nospaces(notebook.read(2,3,8, Direction::Vertical,3)) == nospaces("~\n~\n~"));
    CHECK_THROWS(notebook.write(2,5,5,Direction::Horizontal,"ef"));
}