#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstring>

using namespace std;

int main()
{
    int guess;
    int compcount = 0;
    int compnumber;
    int humancount = 0;
    int compguess = 50;
    // srand (time(NULL));
    int number;
    number =rand()%100+1; //randomly pick a number from 1-100

    cout << number;

    do
    {
        cout << "please enter your guess :" << endl; // enter input of human guess
        cin >> guess;
        humancount++;                                                        // increment number of times humans guess
        cout << "this is the " << humancount << " guess for humans" << endl; // display it in the terminal
        
        if (compguess != number){
            cout << "the computer guess is " << compguess << endl;                //display the computer guess in the terminal
            compcount++;                                                          // increment the number of times
            cout << "this is the " << compcount << " guess for computer" << endl; // display comp count on the computer
            if (compguess < number)// if the computer guess is smaller than the number
            {                                          
                compguess = compguess + compguess / 2; // increment the computer guess by adding half of the previous number onto it
            }
            else if (compguess > number)// if the computer guess is larger than the number
            {                                          
                compguess = compguess - compguess / 2; // decrease the current guess by half of itself
            }
        }

        if (guess < number) // if human guess is less than the number
        {
            cout << " the number is bigger than " << guess << endl; // output that the secret number is bigger than the guess
        }
        else if (guess > number) // if human guess is more than the number
        {
            cout << "the number is smaller than " << guess << endl; // output that the secret number is smaller than the guess
        }
        
        
        cout << endl;

       
    } while (guess != number); // while the guess does not equal the number 
    cout  << humancount << compcount << endl;
    if (humancount < compcount+1 & compguess != guess)
        { // if humans took less tries to guess the correct number
            cout << "Human won" << endl;
            cout << "you took " << humancount << " tries" << endl;                 // human won
            cout << "computer took " << compcount << " tries and failed" << endl; // computer failed
        }
    else if (humancount > compcount)
    { // if computer took less tries to guess the correct number
        cout << "Computer Won" << endl;
        cout << "you took " << humancount << " tries and failed" << endl; // human failed
        cout << "computer took " << compcount << " tries" << endl;       // computer won
    }
    else if (humancount== compcount & guess == compguess)
    { // if computer took less tries to guess the correct number
        cout << "you both won" << endl;
        cout << "you took " << humancount << " tries " << endl; // human won
        cout << "computer took " << compcount << " tries" << endl;       // computer won
    }
    return 0;
}