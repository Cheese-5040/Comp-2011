#include <iostream>

using namespace std;

//helper function for power
int power(int n, int p)
{
    for (int i = 1; i < p; i++)
    {
        n = n * 2;
    }
    return n;
}
// Task 1
int get_min_bits_length(int x)
{
    int number;
    int negative = 0;
    int bits = 1; //most significant vlaue included
    // postive values
    if (x > 0)
    {
        number = x;
        //counting bits
        while (number != 0)
        {
            number = number / 2;
            ++bits; //increment the bits based on the input integer
        }
    }
    //for negative values
    else if (x < 0)
    {
        number = -x;
        negative = 1;
        //counting bits
        while (number != 0)
        {
            number = number / 2;
            ++bits;  //increment bits based on input 
        }
        if (power(2, bits - 2) == -x)
        {
            --bits; //minus the one bit for negative values in power 2
        }
    }

    else if (x == 0)//special case where x ==0
    {
        number = x;
        bits = 2;
    }
    return bits;
}

int main()
{
    cout << power(2, 6);
    while (true)
    {
        int number;
        cout << "Enter a number: ";
        cin >> number;
        cout << number << " needs " << get_min_bits_length(number) << " bits." << endl;
    }

    return 0;
}
