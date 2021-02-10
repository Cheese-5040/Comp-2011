#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int R=0, P=1, S=2;

int print_choice(char player, int choice){
    if (player == 'C'){
        cout << "comoputer ";
    }
    else if (player=='U'){
        cout << "User ";
    }
    else{
        return -1;
    }

    cout << "picks";
    if (choice == R){
        cout << " rock" << endl;
    }
    else if (choice == P){
        cout << " paper" << endl;
    }
    else if (choice == S){
        cout << " sissors" << endl;
    }
    else
    {
        return -1;
    }
    return 0;
}

void print_game_result(int computer_choice, int user_choice){
    if (computer_choice== user_choice){
        cout << "\t DRAW!" <<endl;
    }
    else if ( computer_choice == R && user_choice == S 
    || computer_choice == S && user_choice == P 
    || computer_choice == P && user_choice == R){
        cout << "\tCOMPUTER WINS"<<endl;
    } 
    else {
        cout << "\t USER WINS"<<endl;
    }

}
int main (){
    int seed;
    cout << "enter an integer: ";
    cin >> seed;
    srand(seed);

    int computer_choice = rand()%3;
    int user_choice = rand()%3;

    if (print_choice('C', computer_choice)!=0){
        return -1;
    }
    if (print_choice('U', user_choice)!=0){
        return -1;
    }
    print_game_result(computer_choice, user_choice);
    return 0;
}