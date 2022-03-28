#include <iostream>
#include <unordered_map>
#include <vector>
#include "Direction.hpp"
#include "Notebook.hpp"

using ariel::Direction;
using namespace std;
using namespace ariel;

int main(){
    while(true){
        int choice;
        int page;
        int row;
        int column;
        int len;
        string direction;
        Direction dir;
        string text;
        Notebook notebook;
        cout<<"To write press 1, to read press 2, to erase press 3, to show the notebook press 4, to quit press 5:"<<endl;
        cin>>choice;
        if(choice == 1){ //write
            cout<<"Please enter the page, row, column, direction, and string you want to write (seperated by space):"<<endl;
            cin>>page>>row>>column>>direction;
            getline(cin, text);
            if(direction.compare("horisontal") == 0){
                dir = Direction::Horizontal;
            } else{
                dir = Direction::Vertical;
            }try{
                notebook.write(page, row, column, dir, text);
            }
            catch(const exception& e){
                cout<<e.what()<<endl;
            }
        } else if(choice == 2){ //read
            cout<<"Please enter the page, row, column, direction, and length of the string you want to read (seperated by space):"<<endl;
            cin>>page>>row>>column>>direction>>len;
            if(direction.compare("horisontal") == 0){
                dir = Direction::Horizontal;
            } else{
                dir = Direction::Vertical;
            }
            try{
                notebook.read(page, row, column, dir, len);
            }
            catch(const exception& e){
                cout<<e.what()<<endl;
            }
        } else if(choice == 3){ //erase
            cout<<"Please enter the page, row, column, direction, and length of the string you want to erase (seperated by space):"<<endl;
            cin>>page>>row>>column>>direction>>len;
            if(direction.compare("horisontal") == 0){
                dir = Direction::Horizontal;
            } else{
                dir = Direction::Vertical;
            }
            try{
                notebook.erase(page, row, column, dir, len);
            }
            catch(const exception& e){
                cout<<e.what()<<endl;
            }
        } else if(choice == 4){ //show
            cout<<"Please enter the page you want to show:"<<endl;
            cin>>page;
            try{
                notebook.show(page);
            }
            catch(const exception& e){
                cout<<e.what()<<endl;
            }
        } else{ //quit
            return 0;
        }
    }
}