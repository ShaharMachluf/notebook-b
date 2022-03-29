#include <iostream>
#include <unordered_map>
#include <vector>
#include "Direction.hpp"
#include "Notebook.hpp"

constexpr int line_len=100;
constexpr int line_start=0;
constexpr int first_char = 33;
constexpr int last_char = 126;

using ariel::Direction;
using namespace std;
using namespace ariel;

void Notebook::write(int page, int row, int column, Direction direction, string const &to_write){
    if(page < 0 || row < 0 || column < 0){
        throw("All numbers must be positive");
    }
    if(column >= line_len || (direction == Direction::Horizontal && unsigned(column) + to_write.length() > line_len)){
        throw("A line has only 100 columns");
    }
    if(direction == Direction::Horizontal){
        if(this->pages.find(page) == this->pages.end()){ //page is not in the map
            vector <char> vec(line_len, '_');
            unordered_map<int, vector<char>> m;
            m[row] = vec;
            this->pages[page] = m;
        } else if(this->pages.at(page).find(row) == this->pages.at(page).end()){ //row is not in the map
            vector <char> vec(line_len, '_');
            this->pages.at(page)[row] = vec;
        }
        for(unsigned int i=0; i<to_write.length(); i++){ //check errors
            if(this->pages.at(page).at(row).at(unsigned(column)+i) != '_'){
                throw("Can't write somewhere that's already written/erased");
            }
            if(((int)to_write[i] < first_char && to_write[i] != ' ') || ((int)to_write[i] > last_char && to_write[i] != ' ') || to_write[i] == '~'){
                throw("String contains illigal char");
            }
        }
        for(int i=0; i<to_write.length(); i++){ //write the string in the notebook
            this->pages.at(page).at(row).at(unsigned(column+i)) = to_write.at(unsigned(i));
        }
    } 
    else if(direction == Direction::Vertical){
        for(int i=0; i<to_write.length(); i++){
            if(this->pages.find(page) == this->pages.end()){ //page is not in the map
                vector <char> vec(line_len, '_');
                unordered_map<int, vector<char>> m;
                m[row + i] = vec;
                this->pages[page] = m;
            } else if(this->pages.at(page).find(row + i) == this->pages.at(page).end()){ //row is not in the map
                vector <char> vec(line_len, '_');
                this->pages.at(page)[row + i] = vec;
            }
        }
        for(int i=0; i<to_write.length(); i++){ //check errors
            if(this->pages.at(page).at(row+i).at(unsigned(column)) != '_'){
                throw("Can't write somewhere that's already written/erased");
            }
            if(((int)to_write[unsigned(i)] < first_char && to_write[unsigned(i)] != ' ') || ((int)to_write[unsigned(i)] > last_char && to_write[unsigned(i)] != ' ') || to_write[unsigned(i)] == '~'){
                throw("String contains illigal char");
            }
        }
        for(int i=0; i<to_write.length(); i++){ //write the string in the notebook
            this->pages.at(page).at(row + i).at(unsigned(column)) = to_write.at(unsigned(i));
        }
    }
}

string Notebook::read(int page, int row, int column, Direction direction, int to_read) const{
    string result; 
    if(page < 0 || row < 0 || column < 0 || to_read < 0){
        throw("All numbers must be positive");
    }
    if(column >= line_len || (direction == Direction::Horizontal && column + to_read > line_len)){
        throw("A line has only 100 columns");
    }
    if(direction == Direction::Horizontal){
        //if the key "row" or "page" are not in the map 
        if(this->pages.find(page) == this->pages.end()){
            for(int i = 0; i < to_read; i++){
                result += '_';
            }
        }else if(this->pages.at(page).find(row) == this->pages.at(page).end()){
            for(int i = 0; i < to_read; i++){
                result += '_';
            }
        }
        else{//row exist
            for(int i = 0; i< to_read; i++){
                result.append(1, this->pages.at(page).at(row).at(unsigned(column+i)));
            }
        } 
    }
    else if(direction == Direction::Vertical){
        for(int i = 0; i < to_read; i++){
            //if the key "row" or "page" are not in the map 
            if(this->pages.find(page) == this->pages.end() || this->pages.at(page).find(row + i) == this->pages.at(page).end()){
                result += "_";
            
            }else{//row exist
                result.append(1, this->pages.at(page).at(row + i).at(unsigned(column)));
            }
        }
    }
    return(result);
}

void Notebook::erase(int page, int row, int column, Direction direction, int to_erase){
    if(page < 0 || row < 0 || column < 0 || to_erase < 0){
        throw("All numbers must be positive");
    }
    if(column >= line_len || (direction == Direction::Horizontal && column + to_erase > line_len)){
        throw("A line has only 100 columns");
    }
    if(direction == Direction::Horizontal){
        if(this->pages.find(page) == this->pages.end()){ //page is not in the map
            vector <char> vec(line_len, '_');
            unordered_map<int, vector<char>> m;
            m[row] = vec;
            this->pages[page] = m;
        } else if(this->pages.at(page).find(row) == this->pages.at(page).end()){ //row is not in the map
            vector <char> vec(line_len, '_');
            this->pages.at(page)[row] = vec;
        } 
        for(int i=0; i<to_erase; i++){ //erase the string in the notebook
            this->pages.at(page).at(row).at(unsigned(column+i)) = '~';
        }
    } 
    else if(direction == Direction::Vertical){
        for(int i=0; i<to_erase; i++){
            if(this->pages.find(page) == this->pages.end()){ //page is not in the map
                vector <char> vec(line_len, '_');
                unordered_map<int, vector<char>> m;
                m[row + i] = vec;
                this->pages[page] = m;
            } else if(this->pages.at(page).find(row + i) == this->pages.at(page).end()){ //row is not in the map
                vector <char> vec(line_len, '_');
                this->pages.at(page)[row + i] = vec;
            }
        }
        for(int i=0; i<to_erase; i++){ //erase the string in the notebook
            this->pages.at(page).at(row + i).at(unsigned(column)) = '~';
        }
    }
}

void Notebook::show(int page) const{
    if(page < 0){
        throw("Page number must be positive");
    }
    int min_width = line_len - 1;
    int min_hight = INT16_MAX;
    int max_width = line_start;
    int max_hight = line_start;
    string to_show;
    if(this->pages.find(page) == this->pages.end()){  //the page is empty
        cout<<"_____\n_____\n_____\n_____\n_____"<<endl;
    }
    else{
        unordered_map<int,vector<char>> m(this->pages.at(page));
        for(auto i:m){  //find the boundries of the page that are writen
        cout<<i.first<<endl;
            if(i.first < min_hight){
                min_hight = i.first;
            } if(i.first > max_hight){
                max_hight = i.first;
            }
            for(int j=line_start; j<line_len;j++){
                if(i.second.at(unsigned(j)) != '_' && j < min_width){
                    min_width = j;
                } if(i.second.at(unsigned(j)) != '_' && j > max_width){
                    max_width = j;
                }
            }
        }
        cout<<max_hight<<min_hight<<min_width<<max_width<<endl;
        for(int i=min_hight;i<=max_hight;i++){  //write to the result string
            to_show += to_string(i) + ": ";
            if(m.find(i) == m.end()){
                for(int j = min_width; j<= max_width; j++){
                    to_show += "_";
                }
            } else{
                for(int j = min_width; j<= max_width; j++){
                    to_show += m.at(i).at(unsigned(j));
                }
            }
            to_show += "\n";
        }
        cout<<to_show<<endl;
    }
}
