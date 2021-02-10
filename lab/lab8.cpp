#include "lab8.h"

using namespace std;

/*
Task 1
Initialize the players:
Assign the name
Randomly generate a bingo card
Initialize card_status to all zeros and bingo to false
Hint: you can use "std::random_shuffle()" function to generate 1d array with size 25, and resize it to 5x5 2d array
*/

// function name: init_player
// Your code here
void init_player(Player &plys, char name[]){
    int arr[25];
    for (int i = 0; i< 25; i++){
        arr[i] = i+1;
    }

    random_shuffle(begin(arr), end(arr));


    strncpy(plys.name,  name, MAX_NAME_LENGTH);
    int current = 0;
    for (int i = 0; i<5; i++){
        for (int j = 0; j<5; j++){
            plys.bingo_card[i][j] = arr[current];
            plys.bingo = false;
            plys.card_status[i][j] = 0;
            current++;
        }
    }
    
}



 
/*
Task 2:
Display five players' information:
If the number has been picked, add '*' after it. 
The output for each player looks like this:
___________________________________________________
Name: Peter
Bingo card ('*' means the number has been picked)
20      4       15      16      11
3       23      25      9*      5
21      8       6       12      2
10      1       22      14      19
13      24      7       17      18
*/
// function name: display_info
// Your code here
void display_info(Player plys[], int PLAYER_NUM){
    for (int i = 0; i < PLAYER_NUM; i++){
        cout << "___________________________________________________" << endl;
        cout << "Name: " << plys[i].name[PLAYER_NUM] << endl;
        cout << "Bingo card ('*' means the number has been picked)" ;
        for (int j = 0; j < 5; j++){
            cout << endl;
            for (int k = 0; k<5 ; k++){
                if (plys[i].card_status[k][j])
                    cout << plys[i].bingo_card[k][j] << "*\t";
                else
                    cout << plys[i].bingo_card[k][j] << "\t";
            }
        }
        cout << endl; 
    }
}



/*
Task 3:
Change the status for picked number:
You should find the position of the number you picked in bingo card and update the status.
*/

// function name: change_status
// Your code here
void change_status(Player &plys, int selected_number){  
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (plys.bingo_card[j][i] == selected_number)
                plys.card_status[j][i] = 1;
        }
    }
}

/*
Task 4:
Check bingo:
You should check the status for all rows, columns and two diagonals. 
Return true if there is an entire occupied line, otherwise, return false.
*/

// function name: check_bingo
// Your code here
bool check_bingo(Player &plys){
    for (int i = 0; i < 5 ; i++){
        if (plys.card_status[i][0] && plys.card_status[i][1] && plys.card_status[i][2] && plys.card_status[i][3] && plys.card_status[i][4]){
            plys.bingo = true;
            return true;
        }
            
    }

    for (int i = 0; i < 5 ; i++){
        if (plys.card_status[0][i] && plys.card_status[1][i] && plys.card_status[2][i] && plys.card_status[3][i] && plys.card_status[4][i]){
            plys.bingo = true;
            return true;
        }
            
    }

    if (plys.card_status[0][0] && plys.card_status[01][1] && plys.card_status[02][02] && plys.card_status[03][03] && plys.card_status[04][04]){
        plys.bingo = true;
        return true;
    }
        
    
    if (plys.card_status[0][4] && plys.card_status[01][03] && plys.card_status[02][2] && plys.card_status[03][01] && plys.card_status[04][0]){
        plys.bingo = true;
        return true;
    }
        

    return false;
}

// external funciton declarations
