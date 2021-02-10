#include "lab8.h"
// #include <ctime>

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
void init_player(Player& plys,  char name[]){
    strncpy(plys.name,name, MAX_NAME_LENGTH);
    int num[] = {1,2,3,4,5,6,7,8,9,10,\
                11,12,13,14,15,16,17,18,19,20,\
                21,22,23,24,25};
    // random_shuffle(&num[0], &num[25]); // shuffle all elements in the array and rearrange them
    random_shuffle(begin(num), end(num));

    int count = 0;
    for (int i=0; i < 5; i++){
        for (int j=0; j<5; j++){
            plys.card_status[i][j]=0;
            plys.bingo = false;
            plys.bingo_card[i][j]=num[count];
            ++count;
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
    for (int i=0; i<PLAYER_NUM; i++){
        cout << "___________________________________________________" << endl;
        cout << "Name: " << plys[i].name << endl;
        cout << "Bingo card ('*' means the number has been picked)"<< endl;
        for (int j=0; j<5; j++){
            cout << endl; // enter when there is five numbers in a row
            for (int k=0; k<5; k++){
                //always goes through this loop and passes this statement 
                if(plys[i].card_status[k][j]==1){// if player picked the number, then it is 
                    cout << plys[i].bingo_card[k][j] << "*\t" ;
                }
                else{
                    cout << plys[i].bingo_card[k][j] << "\t" ;
                }
            }
            cout << endl;
        }
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
    for (int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            if (plys.bingo_card[i][j] == selected_number){
                // cout<< "found!" <<endl;
                plys.card_status[i][j] = 1;
            }
            // cout<< "not found!" <<endl;

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
