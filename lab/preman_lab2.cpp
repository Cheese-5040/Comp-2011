#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
using namespace std;

int main() {
    int heapA, heapB, heapC;
    srand(time(NULL));
    heapA = rand() % 3 + 4 ;
    heapB = rand() % 3 + 4 ;
    heapC = rand() % 3 + 4 ;
    char heap;

    int playerCount =  -1;
    int numberChoice = 7;
    int selected;
    string selectedText;

    cout << "Welcome to the Nim game! \n" ;

    while (heapA + heapB + heapC > 0){
        ++playerCount;
        cout << "Round "<< playerCount +1 << ".   "<<  "A: "<< heapA << " B: " << heapB << " C: " << heapC << endl;
        heap = 'D' ;
        cout << "Player "<< playerCount % 2 + 1 << ", please select a heap (A, B or C): " ;
        cin >> heap;
        cout << heap << "<--" << endl;
        if ((heap != 'A') && (heap != 'B') && (heap != 'C')){
            cout << "Invalid heap entered! Please retry." << endl ;
            --playerCount;
            continue ;
        } else {

            cout << "Player "<< playerCount % 2 + 1 <<", please select the number of coins to remove (1, 2 or 3): " ;
            cin >> numberChoice ;

            switch (heap) {
                case 'A':{
                    selected = heapA ;
                    selectedText = "Heap A" ;
                    break;
                }
                case 'B':{
                    selected = heapB ;
                    selectedText = "Heap B" ;
                    break;
                }
               case 'C':{
                    selected = heapC ;
                    selectedText = "Heap C" ;
                    break;
                }
                default: 
                    break;
            }

            if ((numberChoice < 1) || (numberChoice > 3) ){
                cout << "Invalid amount entered! Please retry. " << endl ;
                --playerCount ;
                continue ;
            } else {
                switch (heap) {
                    case 'A':{
                        heapA -= numberChoice ;
                        break;
                    }
                    case 'B':{
                        heapB -= numberChoice ;
                        break;
                    }
                    case 'C':{
                        heapC -= numberChoice ;
                        break;
                    }
                    default: 
                        break;
                }
            }
            
            cout << "Player " << playerCount % 2 + 1 << " removes " << numberChoice << " coin(s) from " << selectedText << endl ;

        }
    }


    cout << "Player " << playerCount % 2 + 1 << " removes the last coin. " << "Player " << playerCount % 2 + 1 << " wins the game!" << endl;


}