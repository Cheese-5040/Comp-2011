#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/* Global constant */

const int STR_LEN = 30;

const int NUM_PEN_TYPES = 3; // Number of pen types

enum PEN_TYPE { FOUNTAIN, BALLPOINT, GEL };

const char pen_type_names[NUM_PEN_TYPES][STR_LEN] = {"Fountain pen", "Ballpoint pen", "Gel pen"};

const int STORE_COUNT = 2; // Number of stores


/* Structure Definitions */
struct Pen {
    PEN_TYPE pen_type;
    int price;
    int amount;
};

struct Store 
{
    int store_ID;
    Pen pen[NUM_PEN_TYPES];
};

/* Utility functions for struct Pen */
// Given
void print_pen(const Pen &pen) 
{
    cout.width(15);
    cout << pen_type_names[pen.pen_type] << ", price: " << pen.price << ", amount: " << pen.amount << endl;
}

/* Utility functions for struct Store*/
// Given
void print_store(const Store &store, int num_pen_types) 
{
    cout << "Store ID: " << store.store_ID << endl;

    for (int i = 0; i < num_pen_types; i++)
        print_pen(store.pen[i]);

}

// FUNCTION 1 
/**
   TODO: Initialize a pen, i.e. the type, price and amount.
      The price and amount are generated randomly.
   The range of amount: [20, 30); The range of price: [10, 20).
 **/
void init_pen(Pen &pen, PEN_TYPE type)
{
    int fa,ba,ga,fp,bp,gp;
    fa = rand() % 10+20;
    ba = rand() % 10+20;
    ga = rand() % 10+20;
    fp = rand() % 10+10;
    bp = rand() % 10+10;
    gp = rand() % 10+10;
    pen.pen_type = type;
    if (type == FOUNTAIN){
        pen.amount =fa;
        pen.price =fp;
    }
    else if (type == BALLPOINT){
        pen.amount =ba;
        pen.price= bp;
    }
    else if (type == GEL){
        pen.amount =ga;
        pen.price= gp;
    }
}



// FUNCTION 2 
/**
   TODO: Initialize a store, i.e. the ID of each store, and the information of all the pens that the store sells by using the function "init_pen".
   store_id: the id of the store to be initialized;
   type: the number of pen types
 **/
void init_store(Store &store, int store_id, int type)
{
    store.store_ID =  store_id;
    for (int i=0; i<3; i++){
        PEN_TYPE type = static_cast<PEN_TYPE>(i);
        init_pen(store.pen[i],type);
    }
}

/* Functions for purchase strategy */
// Given
void print_decision(int store_ID, PEN_TYPE pen_type, int amount, int remain_money)
{
    cout << "Buy " << amount 
         << " " << pen_type_names[pen_type]
         << " from Store " << store_ID 
         << ", money remaining: " << remain_money << endl;
}

// FUNCTION 3 
/**
   TODO: Find the strategy of buying pens as many as possible.
   Hint: it's a greedy strategy. 
   In each round, you should find the kind of pens with minimum price
   (Note that if several kinds of pens have the same minimum price, you could pick anyone)
    and then buy this kind of pens using your remaing money as many as possible.
   After each round, you should print the information about this purchase by using the function "print_decision".
   If your remaining money can not buy even a single pen or you have bought all pens, return false.
 **/
bool decision_for_each_round(Store stores[], int store_count, int num_pen_types, int &money)
{
    struct smallest{
        PEN_TYPE pen_type;
        int price;
        int amount; 
        int store_ID;
        int final_amount;
        int i;
        int j;
    }smallest;
    smallest.price=30;

    //compare price of the pen to find the smallest amount of price per pen and save it in smallest struct
    for (int i = 0; i < store_count; i++){
        for (int j = 0; j < num_pen_types; j++){
            if (stores[i].pen[j].price < money && stores[i].pen[j].amount > 0){
                // if the price of store at number i and pen at number j is smaller than smallest price
                if (stores[i].pen[j].price < smallest.price){ //store the information into the struct smallest
                    smallest.price = stores[i].pen[j].price;
                    smallest.amount = stores[i].pen[j].amount;
                    smallest.store_ID = stores[i].store_ID;
                    smallest.pen_type = stores[i].pen[j].pen_type;
                    smallest.i = i;
                    smallest.j = j;
                }
            }
        }
    }
    
    //if the smallest amount is smaller than all the amount of pens it has, then store all the pens into smallest.final.amount. 
    //else store the integer amount of pens that we can buy with remaining money inside the variable
    smallest.final_amount = (smallest.amount < ( money / smallest.price) ? smallest.amount : (money / smallest.price));
    
    
    // print the descision out
    print_decision(smallest.store_ID, smallest.pen_type, smallest.final_amount, money - (smallest.final_amount*smallest.price));
    money -= smallest.final_amount * smallest.price;

    // if the money left is smaller than the smallest possible price to buy one pen, or all pens are sold out, or all pens have 0 cost (sold out) then return false 
    if ( money < smallest.price || smallest.amount == 0 || smallest.final_amount == 0){
        return false;
    }
    //change the amount of pen to 0 and change smallest final amount to zero 
    stores[smallest.i].pen[smallest.j].amount = 0;
    smallest.final_amount = 0;
}


int main() 
{
    // set the random seed
    srand(time(0));

    int money;

    cout << "How much money do you have? ";
    cin >> money;

    Store stores[STORE_COUNT];

    for (int i = 0; i < STORE_COUNT; i++)
        init_store(stores[i], i+1, NUM_PEN_TYPES);

    cout << "==========================" << endl;
    cout << " Pen prices of each store " << endl;
    cout << "==========================" << endl;
    for (int i = 0; i < STORE_COUNT; i++)
    {
        print_store(stores[i], NUM_PEN_TYPES);
        cout << "-------------------------" << endl;
    }

    cout << "*******************" << endl;
    cout << " Purchase Strategy " << endl;
    cout << "*******************" << endl;

    int round = 1;
    do
    {
        cout << "Round " << round++ << ": ";
    }
    while (decision_for_each_round(stores, STORE_COUNT, NUM_PEN_TYPES, money));

    cout << "No more purchase!" << endl;

    return 0;
}