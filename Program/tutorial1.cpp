#include <iostream> 
using namespace std; 

int main()
{
    /*
        There are 4 errors in total. Can you catch them all? :)
 
        See the expected output section on the lab page to see what is expected from the corrected program.
    */
    int number; // first error, variable declaration
    cout << "Welcome to the exciting, fun, and awesome programming world! "
         << "Enter a positive integer, and I can tell something about you! " << endl;
    cin >> number;
 
    if (number <= 0) // second error, the < position before =
        cout << "You must be fun at parties... XD" << endl;
    else
    {
        if (10 < number && number < 100) // splitting the range into seperate ranges and including and statement
            cout << "You are an awesome person!" << endl;
        else
            cout << "You must be very excited! Me too!" << endl;
    }
 
    return 0; // semicolon after return statement
}