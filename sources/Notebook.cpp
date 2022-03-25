#include <iostream>
#include <unordered_map>
#include <vector>
#include "Direction.hpp"
#include "Notebook.hpp"

#define LINE_LEN 100
#define LINE_START 0

using ariel::Direction;
using namespace std;
using namespace ariel;

Notebook::Notebook(){
    
}

void Notebook::write(unsigned int page, unsigned int row, unsigned int column, Direction direction, string const &to_write) const{
    if(column >= 100 || (direction == Direction::Horizontal && column + to_write.length() >= 100)){
        throw("A line has only 100 columns");
    }
    if (to_write.find('~') != string::npos || to_write.find('\n') != string::npos || to_write.find('\r') != string::npos){
        throw("String contains illigal char");
    }
    if(direction == Direction::Horizontal){
        if(this->pages.find(page) == this->pages.end() || this->pages.at(page).find(row) == this->pages.at(page).end()){
            fill(this->pages.at(page).at(row).at(LINE_START), this->pages.at(page).at(row).at(LINE_LEN - 1), '_'); //initialize vector with '_'
        } 
        for(int i=0; i<to_write.length(); i++){ //check errors
            if(this->pages.at(page).at(row).at(column+i) != '_'){
                throw("Can't write somewhere that's already written/earased");
            }
        }
        for(int i=0; i<to_write.length(); i++){ //write the string in the notebook
            this->pages.at(page).at(row).at(column+i) == to_write.at(i);
        }
    } 
    if(direction == Direction::Vertical){
        for(int i=0; i<to_write.length(); i++){
            if(this->pages.find(page) == this->pages.end() || this->pages.at(page).find(row + i) == this->pages.at(page).end()){
                fill(this->pages.at(page).at(row + i).at(LINE_START), this->pages.at(page).at(row + i).at(LINE_LEN - 1), '_'); //initialize vector with '_'
            } 
        }
        for(int i=0; i<to_write.length(); i++){ //check errors
            if(this->pages.at(page).at(row+i).at(column) != '_'){
                throw("Can't write somewhere that's already written/earased");
            }
        }
        for(int i=0; i<to_write.length(); i++){ //write the string in the notebook
            this->pages.at(page).at(row + i).at(column) == to_write.at(i);
        }
    }
}

string Notebook::read(unsigned int page, unsigned int row, unsigned int column, Direction direction, int to_read) const{
    return("ok");
}

void Notebook::erase(unsigned int page, unsigned int row, unsigned int column, Direction direction, int to_erase) const{
}

void Notebook::show(unsigned int page) const{
    
}

Notebook::~Notebook(){
    
}