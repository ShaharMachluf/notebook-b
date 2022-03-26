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

void Notebook::write(int page, int row, int column, Direction direction, string const &to_write){
    if(column >= 100 || (direction == Direction::Horizontal && (unsigned long)column + to_write.length() >= 100)){
        throw("A line has only 100 columns");
    }
    if (to_write.find('~') != string::npos || to_write.find('\n') != string::npos || to_write.find('\r') != string::npos){
        throw("String contains illigal char");
    }
    if(direction == Direction::Horizontal){
        if(this->pages.find(page) == this->pages.end()){
            vector <char> vec(LINE_LEN, '_');
            unordered_map<int, vector<char>> m;
            m.at(row) = vec;
            this->pages.at(page) = m;
            //fill(this->pages.at(page).at(row).at(LINE_START), this->pages.at(page).at(row).at(LINE_LEN - 1), '_'); //initialize vector with '_'
        } else if(this->pages.at(page).find(row) == this->pages.at(page).end()){
            vector <char> vec(LINE_LEN, '_');
            this->pages.at(page).at(row) = vec;
        }
        for(int i=0; i<to_write.length(); i++){ //check errors
            if(this->pages.at(page).at(row).at((size_t)(column+i)) != '_'){
                throw("Can't write somewhere that's already written/erased");
            }
        }
        for(int i=0; i<to_write.length(); i++){ //write the string in the notebook
            this->pages.at(page).at(row).at((size_t)(column+i)) = to_write.at((size_t)i);
        }
    } 
    else if(direction == Direction::Vertical){
        for(int i=0; i<to_write.length(); i++){
            if(this->pages.find(page) == this->pages.end()){
                vector <char> vec(LINE_LEN, '_');
                unordered_map<int, vector<char>> m;
                m.at(row) = vec;
                this->pages.at(page) = m;
            //fill(this->pages.at(page).at(row).at(LINE_START), this->pages.at(page).at(row).at(LINE_LEN - 1), '_'); //initialize vector with '_'
            } else if(this->pages.at(page).find(row) == this->pages.at(page).end()){
                vector <char> vec(LINE_LEN, '_');
                this->pages.at(page).at(row) = vec;
            }
                //fill(this->pages.at(page).at(row + i).at(LINE_START), this->pages.at(page).at(row + i).at(LINE_LEN - 1), '_'); //initialize vector with '_'
        }
        for(int i=0; i<to_write.length(); i++){ //check errors
            if(this->pages.at(page).at(row+i).at((size_t)column) != '_'){
                throw("Can't write somewhere that's already written/erased");
            }
        }
        for(int i=0; i<to_write.length(); i++){ //write the string in the notebook
            this->pages.at(page).at(row + i).at((size_t)column) = to_write.at((size_t)i);
        }
    }
}

string Notebook::read(int page, int row, int column, Direction direction, int to_read) const{
    string result = ""; 
    if(column >= 100 || (direction == Direction::Horizontal && column + to_read >= 100)){
        throw("A line has only 100 columns");
    }
    if(direction == Direction::Horizontal){
        //if the key "row" or "page" are not in the map 
        if(this->pages.find(page) == this->pages.end() || this->pages.at(page).find(row) == this->pages.at(page).end()){
            for(int i = 0; i< to_read; i++){
                result += '_';
            }
        }
        else{
            for(int i = 0; i< to_read; i++){
                result.append(1, this->pages.at(page).at(row).at((size_t)(column+i)));
            }
        } 
    }
    else if(direction == Direction::Vertical){
        for(int i = 0; i < to_read; i++){
            //if the key "row" or "page" are not in the map 
            if(this->pages.find(page) == this->pages.end() || this->pages.at(page).find(row + i) == this->pages.at(page).end()){
                result += "_\n";
            
            }else{
                result.append(1, this->pages.at(page).at(row + i).at((size_t)column)) + "\n";
            }
        }
    }
    return(result);
}

void Notebook::erase(int page, int row, int column, Direction direction, int to_erase){
        if(column >= 100 || (direction == Direction::Horizontal && column + to_erase >= 100)){
        throw("A line has only 100 columns");
    }
    if(direction == Direction::Horizontal){
        if(this->pages.find(page) == this->pages.end() || this->pages.at(page).find(row) == this->pages.at(page).end()){
            // this->pages.at(page).at(row) = vec(LINE_LEN, '_');
            vector <char> vec(LINE_LEN, '_');
            unordered_map<int, vector<char>> m;
            m.at(row) = vec;
            this->pages.at(page) = m;
            //fill(this->pages.at(page).at(row).at(LINE_START), this->pages.at(page).at(row).at(LINE_LEN - 1), '_'); //initialize vector with '_'
        } 
        for(int i=0; i<to_erase; i++){ //erase the string in the notebook
            this->pages.at(page).at(row).at((size_t)(column+i)) = '~';
        }
    } 
    else if(direction == Direction::Vertical){
        for(int i=0; i<to_erase; i++){
            if(this->pages.find(page) == this->pages.end() || this->pages.at(page).find(row + i) == this->pages.at(page).end()){
                vector <char> vec(LINE_LEN, '_');
                unordered_map<int, vector<char>> m;
                m.at(row) = vec;
                this->pages.at(page) = m;
                //fill(this->pages.at(page).at(row + i).at(LINE_START), this->pages.at(page).at(row + i).at(LINE_LEN - 1), '_'); //initialize vector with '_'
            } 
        }
        for(int i=0; i<to_erase; i++){ //erase the string in the notebook
            this->pages.at(page).at(row + i).at((size_t)column) = '~';
        }
    }
}

void Notebook::show(int page) const{
    int min_width = LINE_LEN - 1;
    int min_hight = UINT16_MAX;
    int max_width = LINE_START;
    int max_hight = LINE_START;
    string to_show = "";
    if(this->pages.find(page) == this->pages.end()){  //the page is empty
        cout<<"_____\n_____\n_____\n_____\n_____"<<endl;
    }
    else{
        unordered_map<int,vector<char>> m = this->pages.at(page);
        for(auto i:m){  //find the boundries of the page that are writen
            if(i.first < min_hight){
                min_hight = i.first;
            } else if(i.first > max_hight){
                max_hight = i.first;
            }
            for(int j=LINE_START; j<LINE_LEN;j++){
                if(i.second.at((size_t)j) != '_' && j < min_width){
                    min_width = j;
                } else if(i.second.at((size_t)j) != '_' && j > max_width){
                    max_width = j;
                }
            }
        }
        for(int i=min_hight;i<=max_hight;i++){  //write to the result string
            to_show += to_string(i) + ": ";
            if(m.find(i) == m.end()){
                for(int j = min_width; j<= max_width; j++){
                    to_show += "_";
                }
            } else{
                for(int j = min_width; j<= max_width; j++){
                    to_show += m.at(i).at((size_t)j);
                }
            }
            to_show += "\n";
        }
        cout<<to_show<<endl;
    }
}
