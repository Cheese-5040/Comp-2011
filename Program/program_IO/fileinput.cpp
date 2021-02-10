#include <iostream>
#include <fstream>
using namespace std;

int main (){
    ifstream new_file("asdk,.jfh");
    string line;
    new_file.open("asldkjfh");
    char c; new_file.get(c);
    while (!new_file.eof()){
        cout << "preman"<< c << endl;

        new_file.get(c);
    }
    new_file.close();
    return 0;
}