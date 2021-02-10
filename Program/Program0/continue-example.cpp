/* File: continue-example.cpp */
#include <iostream>	
using namespace std;	

int main()	
{
    int j = 0;

    while (j < 3)
    {
        cout << "Enter iterati\0on " << j << endl;

        if (j == 1)
            break;

        cout << "Leave iteration " << j << endl;
        j++;
    }
        
    return 0;
}
