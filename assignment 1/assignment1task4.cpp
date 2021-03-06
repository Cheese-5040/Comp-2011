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
            ++bits; //increment bits based on input
        }
        if (power(2, bits - 2) == -x)
        {
            --bits; //minus the one bit for negative values in power 2
        }
    }

    else if (x == 0) //special case where x ==0
    {
        number = x;
        bits = 2;
    }
    return bits;
}

// Task 2
int get_bit_positive(int x, int n)
{
    int min_bits;
    int bit_value;
    int number;

    // get the minimum bits length first
    min_bits = get_min_bits_length(x);
    if (n < 0 || x < 0)
    {
        bit_value = -1;
    }
    else if (n >= min_bits)
    {
        bit_value = 0;
    }

    else
    {
        number = x;
        for (int i = 0; i < n; i++)
        { // divide the number by n-2 times as you need to divide it again
            number = number / 2;
        }
        bit_value = number % 2;
    }
    return bit_value;
}

// Task 3
int get_bit_negative(int x, int n)
{
    int bit_value;
    int number;
    int flip_bit;
    int new_flip_bit = 0;
    int unflip_bit;
    int carry_over_bit = 1;
    int min_bits;
    // get the minimum bits length first
    min_bits = get_min_bits_length(-x);
    if (n < 0 || x >= 0)
    {
        bit_value = -1;
    }
    else if (n >= min_bits)
    {
        bit_value = 1;
    }
    else
    {
        for (int i = 0; i < n + 1; i++)
        {
            // obtaining the unflipped bit for positve int
            unflip_bit = get_bit_positive(-x, i);

            // Flipping the bits
            if (unflip_bit == 0)
            {
                flip_bit = 1;
            }
            else if (unflip_bit == 1)
            {
                flip_bit = 0;
            }

            //addition of one bit
            if (flip_bit == 0 && carry_over_bit == 1)
            {
                //after addition
                new_flip_bit = 1;
                carry_over_bit = 0;
            }
            else if (flip_bit == 1 && carry_over_bit == 1)
            {
                //after addition
                new_flip_bit = 0;
                carry_over_bit = 1;
            }
            else if (flip_bit == 1 && carry_over_bit == 0)
            {
                //no change in the bits
                new_flip_bit = flip_bit;
            }
            else if (flip_bit == 0 && carry_over_bit == 0)
            {
                //no change in the bits
                new_flip_bit = flip_bit;
            }
        }
        //set the output of the bits
        bit_value = new_flip_bit;
    }
    return bit_value;
}
// task 4
void print_2s_complement_representation(int x)
{
    int min_bits;

    // get the minimum bits length first
    min_bits = get_min_bits_length(x);
    if (x >= 0)
    {
        // for (int i=0; i<min_bits; i++){
        //     cout<< get_bit_positive(x,i);
        // }
        for (int i = min_bits - 1; i >= 0; i--)//min_bits minus 1 because it is the most significant bit
        {
            cout << get_bit_positive(x, i);
        }
        cout << endl;
    }
    else if (x<0){
        for (int i = min_bits - 1; i >= 0; i--)//min_bits minus 1 because it is the most significant bit
        {
            cout << get_bit_negative(x, i);
        }
        cout << endl;
    }
}
int main()
{
    while (true)
    {
        int number;
        cout << "Enter a number: ";
        cin >> number;
        cout << "The 2's complement representation of " << number << " is:" << endl;
        print_2s_complement_representation(number);
    }

    return 0;
}