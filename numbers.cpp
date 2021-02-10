#include <iostream>
#include <cmath>
using namespace std;


int main()
{
    int j = 0;
    while (j < 3)
    {
        cout << "enter iteration" << j << endl;
        if (j == 1)
            break; // stop iteration completely
            //continue; //stop current iteration, start next iteration immediately
        cout << "leave Iteation" << j << endl;
        j++;
    } // enclosing loop of break
    return 0;
}