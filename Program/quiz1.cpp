#include<iostream>
#include<cmath>
using namespace std;

int main (){
    cout << "sizeof(bool) = " << sizeof(bool) <<endl;
    cout << 'z'-'a'<<endl;
    cout << "z" - "a" <<'\0'<<endl;
    int a =10, b=10,c=10,d=10;
    a=++b;
    cout << a << b << endl;
    c=d++;
    cout << c << d << endl;
    bool x = true;
    bool y = false;
    // Default output format of booleans
    cout << x << " && " << y << " = " << (x && y) << endl << endl;

    cout << boolalpha; // To print booleans in English
    cout << x << " && " << y << " = " << (x && y) << endl << endl;

    cout << noboolalpha; // To print booleans in 1 or 0
    cout << x << " && " << y << " = " << (x && y) << endl; 
    cout << ceil(9/10);
    return 0;
}
