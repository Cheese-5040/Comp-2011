#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    cout << "welcome to the Nim game!" << endl;

    srand((unsigned)time(0)); //unsigned integer, represent natural numbers, only positive  values
    // seed for random number generator, current time so the sequence is always random

    int num_A = rand() % 4 + 3; // choose random number form [3,6]
    int num_B = rand() % 4 + 3;
    int num_C = rand() % 4 + 3;
    int player = -1; //initialise count as it will increment every round 
    int winning_player; //  used to store the number of player who won
    int selected; // indicate the choice of the heap and stores the value of the number of coins in the heap 
    char heap;// indicates the choice of the heap 
    int num_coins;// indicate number of coins the player want to remove

    do
    {
        ++player;//count of the game
        cout<< endl;
        cout <<endl<< "Round " << player +1 << ".  A: " << num_A << " B: " << num_B << " C: " << num_C << endl;
        // prints the round number and remaining coins in each pile 
        cout << "Player " <<(player % 2) + 1 << ", please select a heap (A,B or C): ";
        cin >> heap;
        // asks player to select heap and stores in variable heap

        if (heap != 'A' && heap != 'B' && heap != 'C') 
        // error checking for input if is in the cases stated above
        {
            cout << "invalid input, please enter a character (A,B or C): " << endl;
            // error messege displayed, thje program deducts the count and reruns as the same player number
            --player; //count deducted
            continue; //skip to the end of the loop
        }
        else
        {
            cout << "Player " << (player % 2) + 1<< ", please select the number of coins to remove (1,2,or 3): " ;
            cin >> num_coins;
            // prompts player to enter num of coins and stores in variable num_coins
            switch (heap)
            // switch statement used for all the choices the player made 
            {
            case 'A':
                selected = num_A;
                // stores the number of remaining coins at pile A into "selected" variable
                break;
                //exits the switch statement to proceed to the next part
            case 'B':
                selected = num_B;
                break;
            case 'C':
                selected = num_C;
                break;
            default:
                cout << "error"<< endl;
                // outputs error if there is nothing in the case mentioned
                break;
                // exit loop 
            }
            if (num_coins < 1 || num_coins > 3 || selected < num_coins)
            // check if the number of coins entered by the player is within [1,3] or is more than the remaining coins in the pile
            {
                cout << "invalid input, please enter within range [1,3] or lesser than remaining coins from pile: " << endl;
                //display error messege
                --player;
                //decrement player count, so that we can start with the same player at the next loop due to error
                continue;
                //skip this portion and continue with the code
            }
            else
            {
                switch (heap)
                {
                case 'A':
                    num_A -= num_coins;
                    //number of coins in A will be ddudcted by the number of coins selected by the player
                    break;
                    //exit the switch statement and loop
                case 'B':
                    num_B -= num_coins;
                    break;
                case 'C':
                    num_C -= num_coins;
                    break;
                default:
                    cout << "invalid input, please re-enter your value" << endl;
                    //display error messege and restart the loop 
                    break;
                }

                cout << "Player " << (player % 2) + 1 << " removes " << num_coins << " coin(s) from heap " << heap << "." << endl;
                // display the action of the player in the loop 
            }

        }
    }while (num_A || num_B || num_C != 0);
    // check if all the piles of coins are zero, if not, keep running th eloop until it turns zero

    winning_player = (player % 2) + 1;
    // select the winning player
    cout << "player " << winning_player << " removes the last coin. Player "
        << winning_player << " wins the game!" << endl;
    // output the winning player in the messege 
    return 0;

}