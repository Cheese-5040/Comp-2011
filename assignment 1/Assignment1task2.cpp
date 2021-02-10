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
// Task 2
int get_bit_positive(int x, int n)
{
	int min_bits;
    int bit_value=10;
    int number;
    
    // get the minimum bits length first
    min_bits= get_min_bits_length(x);
    if (n<0 || x<0){
        bit_value=-1;
    }
    else if (n>= min_bits){
        bit_value=0;
    }

    else{
        number=x;
        for (int i=0; i<n; i++){// divide the number by n-2 times as you need to divide it again
            number= number/2;
        }
        bit_value=number%2;
    }
	return bit_value;
}


// int get_bit_positive(int x, int n)
// {
// 	int min_bits;
//     int bit_value=10;
//     int number;
//     n=n-1;
//     // get the minimum bits length first
//     min_bits= get_min_bits_length(x);
//     if (n+1<0 || x<0){
//         bit_value=9;
//     }
//     else if (n-2>= min_bits){
//         bit_value=8;
//     }

//     else{
//         number=x;
//         for (int i=0; i<n; i++){// divide the number by n-2 times as you need to divide it again
//             number= number/2;
//         }
//         bit_value=number%2;
//     }
// 	return bit_value;
// }

int main(){
 
    int number;
    int bit;
    while (true)
    {
        cout << "Enter a number: ";
    cin >> number;

    cout << "Which bit? ";
    cin >> bit;

    cout << "The number " << bit << " bit of " << number << " is " << get_bit_positive(number, bit) << endl;
    }
    
	
}