#include <iostream>
#include <stdlib.h> // needed for calling rand() function
#include <time.h>   // might need to use for calling time function
using namespace std;

int main()
{
    // random number generation
    srand((unsigned)time(0));   //unsigned integer, represent natural numbers, only positive  values
    // seed for random number generator, current time so the sequence is always random
    int number = rand() % 100 + 1; 
    //generate random number  form [1,100]

    int guess;
    int low = 1, high = 100;
    int player =1;
    do
    {
        cout << "player "<< player << " enter your guess :" << endl;
        cin >> guess;

        while (guess < low || guess > high)
        { //input validaiton loop
            cout << "invalud input, please enter a number between " << \
            low << "and " << high << endl;
            cin >> guess;
        }
        if (guess == number)
        {
            cout << "player "<< player<< " wins" << endl;
        }
        else if (guess < number)
        {
            cout << "sorry the number is  bigger  than " << guess << endl;
            low = guess + 1; // update lower end of guess
        }
        else
        {
            cout << "sorry,  the  number is smaller than " << guess << endl;
            high = guess - 1; // update higher end of guess
        }

        player = (player%2)+1 ;// makes player 1 go to 2 and 2 go to 1, used to switch players
    } while (guess != number);

    return 0;
}