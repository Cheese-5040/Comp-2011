/*
 * COMP2011 (Fall 2020) Assignment 1: Binary Numbers
 *
 * Student name: OW YONG Chee Seng
 * Student ID: 20659467
 * Student email: csowyong@connect.ust.hk
 *
 * Note:
 * 1. You CANNOT define and use any arrays.
 * 2. You CANNOT define and use any global variables.
 * 3. You CANNOT use the static keyword.
 * 4. You CANNOT include any extra libraries other than iostream.
 * 5. You CANNOT use any bitwise operators: ~, ^, |, & (since they are not taught in this course).
 * 6. You CANNOT change the function headers of the functions given in the tasks.
 * 7. You CANNOT use any string operations.
 * 8. You can add helper functions.
 */

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
				// increment carry over bit
				carry_over_bit = 0;
			}
			else if (flip_bit == 1 && carry_over_bit == 1)
			{
				//after addition
				new_flip_bit = 0;
				// increment carry over bit
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

// Task 4
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
		for (int i = min_bits - 1; i >= 0; i--) //min_bits minus 1 because it is the most significant bit
		{
			cout << get_bit_positive(x, i);
		}
		cout << endl;
	}
	else if (x < 0)
	{
		for (int i = min_bits - 1; i >= 0; i--) //min_bits minus 1 because it is the most significant bit
		{
			cout << get_bit_negative(x, i);
		}
		cout << endl;
	}
}

// Task 5
void print_addition_carry_out(int a, int b)
{
	int carry_over_bit = 0;
	int min_bits_a = get_min_bits_length(a);
	int min_bits_b = get_min_bits_length(b);
	int larger_min_bits, return_value;
	int final_return_value;
	(min_bits_a >= min_bits_b) ? larger_min_bits = min_bits_a : larger_min_bits = min_bits_b;

	for (int j = 0; j < larger_min_bits; j++)
	{
		int carry_over_bit = 0;
		for (int i = 0; i < larger_min_bits - j; i++)
		{
			int a_bit = (a < 0) ? get_bit_negative(a, i) : get_bit_positive(a, i);
			int b_bit = (b < 0) ? get_bit_negative(b, i) : get_bit_positive(b, i);

			if (a_bit == 1 && b_bit == 1)
			{
				(carry_over_bit == 0) ? return_value = 1, carry_over_bit = 1 : (carry_over_bit == 1) ? return_value = 1, carry_over_bit = 1 : carry_over_bit = 0;
			}
			else if (a_bit == 1 && b_bit == 0)
			{
				(carry_over_bit == 0) ? return_value = 0 : (carry_over_bit == 1) ? return_value = 1, carry_over_bit = 1 : carry_over_bit = 0;
			}
			else if (a_bit == 0 && b_bit == 1)
			{
				(carry_over_bit == 0) ? return_value = 0 : (carry_over_bit == 1) ? return_value = 1, carry_over_bit = 1 : carry_over_bit = 0;
			}
			else if (a_bit == 0 && b_bit == 0)
			{
				(carry_over_bit == 0) ? return_value = 0 : (carry_over_bit == 1) ? return_value = 0, carry_over_bit = 0 : carry_over_bit = 0;
			}

			// cout << return_value;
		}
		cout << return_value;
	}
	cout << endl;
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

int main()
{
	while (true)
	{
		int option = 0;

		do
		{
			cout << "1. Task 1" << endl;
			cout << "2. Task 2" << endl;
			cout << "3. Task 3" << endl;
			cout << "4. Task 4" << endl;
			cout << "5. Task 5" << endl;
			cout << "0. Exit" << endl;
			cout << "Enter an option (0-5): ";
			cin >> option;
		} while (option < 0 || option > 5);

		if (option == 0)
			break;
		else if (option == 1)
		{
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << number << " needs " << get_min_bits_length(number) << " bits." << endl;
		}
		else if (option == 2)
		{
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;

			cout << "The number " << bit << " bit of " << number << " is " << get_bit_positive(number, bit) << endl;
		}
		else if (option == 3)
		{
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;

			cout << "The number " << bit << " bit of " << number << " is " << get_bit_negative(number, bit) << endl;
		}
		else if (option == 4)
		{
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << "The 2's complement representation of " << number << " is:" << endl;
			print_2s_complement_representation(number);
		}
		else if (option == 5)
		{
			int a, b;
			cout << "Enter number A: ";
			cin >> a;
			cout << "Enter number B: ";
			cin >> b;
			cout << "The sum of " << a << " and " << b << " is " << a + b << ". The carry bits are:" << endl;
			print_addition_carry_out(a, b);
		}

		cout << endl;
	}

	return 0;
}