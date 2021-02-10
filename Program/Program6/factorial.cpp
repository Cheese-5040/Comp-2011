#include <iostream>
using namespace std;
int factorial(int n)    /* factorial.cpp */
{
    int k;
    if (n < 0)          // Error checking
        return -1;
    else if (n == 0)    // Base case; ending case too!
        return 1;
    // Recursive case
    for(int i =0; i < (n); i++){
        cout << "\t" ;
    }
    cout <<"calling factorial " <<  n << endl;
    k= n * factorial(n-1);
    cout << " returning " << n << "!= " << k << endl;
    return k;
}
int main (){
    cout << factorial(7)<< endl;
}