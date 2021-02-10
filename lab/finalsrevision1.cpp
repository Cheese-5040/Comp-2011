#include <iostream> 
using namespace std;


int main(){ 
    int x=5;
    cout << x << endl; //value of x
    cout << &x << endl;  //address of x
    int &y=x; 
    cout << y << endl; //value of y
    cout << &y << endl;  //address of y

    return 0;
}