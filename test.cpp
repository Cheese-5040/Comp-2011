#include <iostream>

using namespace std;

int power(int n, int p)
{
    for (int i = 1; i < p; i++)
    {
        n = n * 2;
    }
    return n;
}
int remainder(int number, int divisor){
    int exact_num,remainder;
    exact_num=number/divisor;
    remainder = number - exact_num * divisor;
    return remainder;
}


int main(){
    cout<< power(2,3)<<endl;
    cout << remainder (25,7)<<endl;
    return 0;
}