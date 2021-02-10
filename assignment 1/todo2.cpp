//ONLY SUBMIT THIS FILE TO ZINC
//prepared by: Ow Yong Chee Seng
// COMP 2011 PA3
// Student ID : 20659467
#include "given.h"
#include "todo.h"
#include <iostream>
using namespace std;
//be reminded that you should NOT include any additional library, please read "Additional Notes" on the PA3 webpage

//there can be more than one type of monster in each cell so we need linked list to store them (eg Mace and Dagger)
//task 1
//todo
Node ***generateMap(int width, int height)
{
    Node ***map = new Node **[height]; //create node for height
    for (int i = 0; i < height; i++)
    {
        map[i] = new Node *[width]; // create node for width
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            map[i][j] = nullptr;
        }
    }
    return map;
}
//task 2
void printHeroStatus(const HeroStatus &heroStatus)
{
    cout << "Hero status: x=" << heroStatus.x << " y=" << heroStatus.y << " #mace=" << \
    heroStatus.maceCount << " #dagger=" << heroStatus.daggerCount << " #sword=" << heroStatus.swordCount << endl;
}
//task 3
void printMonsterCount(Node ***map, int width, int height)
{
    int M_count=getMonsterCount(map, width, height);
    //todo
    if(M_count == 1){
        cout << "There is still one more monster left!" <<endl;
    }
    else{
        cout << "There are "<<M_count<<" monsters left in the world!"<<endl;
    }
}
//task 4
int getLinkedListLength(const Node *head)
{
    if (head == nullptr){
        return 0;
    }
    int count = 0;
    for (const Node *node = head; node!= nullptr; node = node->next)
        count++;
    return count;
}
//add the quantity of the specified thing to the specified cell (x and y position) in the map of map size
//task 5
bool addThing(Node ***map, int width, int height, int x, int y, Thing thing, int quantity)
{
    //if outside boundary of the map, return false
    if (x < 0 || x > width || y < 0 || y > height)
    {
        return false;
    }
    Node *node = map[y][x];

    if (node == nullptr){
        map[y][x] = new Node;
        map[y][x] -> thing = thing;
        map[y][x] -> quantity = quantity;
        map[y][x] -> next = nullptr;
        // head = nullptr;
        delete node;
        node = nullptr;
        return true; 

    }
   
    for (; node->thing == thing||node->next != nullptr; node = node->next){//go through each element of linked list 
        if(node->thing == thing){
            node->quantity += quantity; 
            //todo 
            //check why cannot add delete node
            // delete node;
            // node = nullptr;
            return true;
        }
    }
    node->next = new Node;
    node ->next -> thing = thing;
    node ->next -> quantity = quantity;
    node ->next -> next = nullptr;
    
    //todo 
    //check why cannot add delete node
    // delete node->next; //added this
    // node ->next= nullptr; // added this too
    return true;
}
//todo
//task 6
bool removeThing(Node ***map, int width, int height, int x, int y, Thing thing, int quantity)
{
    //if position is invalid, then do nothing and return false
    if (x < 0 || x > width || y < 0 || y > height){
        return false;
    }
    // cout << "hello" <<endl;
    if(!map[y][x]){
        return false;
    }
    // cout << "hello2" <<endl;

    //if at beginning of the node
    if (map[y][x]->thing == thing && map[y][x]->next == nullptr){ //head with no other stuff inside
        // cout << "runs the first loop" << endl;
         //quantity less than specified quantity
        if (map[y][x]->quantity < quantity){
            return false;
        }
        //quantity is more than specified quantity
        else if (map[y][x]->quantity > quantity){
            map[y][x]->quantity -=quantity;
            return true;
        }
        Node *next = map[y][x] -> next;
        delete map[y][x];
        map[y][x] = nullptr;
        return true;
    }

    else if (map[y][x]->thing == thing && map[y][x]->next != nullptr){ //head with  other stuff inside
            // cout << "runs the second loop" << endl;

         //quantity less than specified quantity
        if (map[y][x]->quantity < quantity){
            return false;
        }
        //quantity is more than specified quantity
        else if (map[y][x]->quantity > quantity){
            map[y][x]->quantity -=quantity;
            return true;
        }
        Node *next = map[y][x] -> next;
        delete map[y][x];
        map[y][x] = nullptr;
        map[y][x]=next;
        return true;
    }
    else if (map[y][x]->thing != thing && map[y][x]->next == nullptr){ //head with no other stuff inside, and not equal to thing
        return false;
    }
    // if position is valid, and not beginning
    //linked list has node that represents specified thing
    // cout << "hello3" <<endl;

    Node *prev = map[y][x] ;
    Node *current = prev -> next;
    for (; current->thing == thing||current->next != nullptr; prev=current, current = current->next){//go through each node of linked list 
        // cout << "runs the third loop" << endl;

        //if a node match specified thing
        if (current->thing==thing){
            //quantity less than specified quantity
            if (current->quantity < quantity){
                return false;
            }
            //quantity is more than specified quantity
            else if (current->quantity > quantity){
                current->quantity -=quantity;
                return true;
            }
            //quantity is equal to the specified quantity
            Node *next = current -> next;
            delete current; //remove the node completely, return true
            current = nullptr;
            if (next = nullptr){
                prev->next = nullptr;
                return true;
            }
            else{
                prev-> next = next;
                return true;
            }
        }
        // else{
        //     return false;
        // }
    }
    // cout << "skip all" << endl;

    return true;
}
//task 7
void deleteLinkedList(Node *&head)
{
    if (head == nullptr){
        return;
    }
    if (head -> next){
        deleteLinkedList(head->next);
    }
    delete head;
    head = nullptr;
}
//task 8
void deleteMap(Node ***map, int width, int height)
{
    // for (int i=0; i<height; i++){//commented this out
    //     for (int j=0; j<width; j++){
    //         // if (map[i][j]==nullptr){//removed this
    //         //     return;
    //         // }
    //         deleteLinkedList(map[i][j]);
    //     }
    // }
    for (int i=0; i < height; i++){
        delete []map[i];
        map[i]=nullptr;
    }
    delete[] map;
    map= nullptr;
}
//task 9
bool moveHero(char move, Node ***map, int width, int height, HeroStatus &heroStatus)
{
    int old_x_coor = heroStatus.x;
    int old_y_coor = heroStatus.y;
    if (move == 'w'){
        if (heroStatus.y==0){
            return false;
        }
        else{
            heroStatus.y-=1;
        }
    }
    else if (move == 'a'){
        if (heroStatus.x==0){
            return false;
        }
        else{
            heroStatus.x-=1;
        }
    }
    else if (move == 's'){
        if (heroStatus.y==height-1){
            return false;
        }
        else{
            heroStatus.y+=1;
        }
    }
    else if (move == 'd'){
        if (heroStatus.x==width -1){
            return false;
        }
        else{
            heroStatus.x+=1;
        }
    }
    
    // move hero from old cell to new one
    //remove hero from old cell
    bool temp = removeThing(map,width,height,old_x_coor, old_y_coor, HERO, 1);
    //make a list to store the 6 different item quantity in enum Thing
    int item[6]={0};
    //go through each node in the new map position of the hero
    for (Node *node = map[heroStatus.y][heroStatus.x]; node != nullptr; node = node-> next){
        // cout << node->thing << " : " << node-> quantity<<endl;
        item[node->thing]+=node->quantity;//store the quantity of the thing inside position node->thing in item array
    }
    //update status of weapon if land on weapon box
    heroStatus.swordCount += item[SWORD];
    heroStatus.maceCount += item[MACE];
    heroStatus.daggerCount += item[DAGGER];
    // cout << "dagger count :" << heroStatus.daggerCount <<endl;
    //remove all weapon from new cell
    removeThing(map,width,height,heroStatus.x,heroStatus.y,SWORD, item[SWORD]);
    removeThing(map,width,height,heroStatus.x,heroStatus.y,MACE,item[MACE]);
    removeThing(map,width,height,heroStatus.x,heroStatus.y,DAGGER,item[DAGGER]);

    //if land on monster box
    //for each type of monster, check if enough weapon for it
    //check if enough sword to kill dragon,enough dagger to kill vampire,enough mace to kill skeleton
    if (heroStatus.swordCount >= item[DRAGON] && heroStatus.daggerCount >= item[VAMPIRE] && heroStatus.maceCount >= item[SKELETON]){
        //if number of weapons are always more than or equal to the monster, just simply reduce them 
        heroStatus.swordCount -= item[DRAGON];
        heroStatus.daggerCount -= item[VAMPIRE];
        heroStatus.maceCount -= item[SKELETON];

        //remove the weapons on the box
        removeThing(map,width,height,heroStatus.x,heroStatus.y,DRAGON,item[DRAGON]);
        removeThing(map,width,height,heroStatus.x,heroStatus.y,VAMPIRE,item[VAMPIRE]);
        removeThing(map,width,height,heroStatus.x,heroStatus.y,SKELETON,item[SKELETON]);

        //add hero on new space
        addThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
    }
    // num of weapons lesser than num of monsters, hero die
    else{
        removeThing(map,width,height,heroStatus.x, heroStatus.y, HERO, 1);
        heroStatus.alive= false;
    }
    return true;
}
//task 10
int getMonsterCount(Node ***map, int width, int height)
{
    int count = 0;
    for (int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            for (Node *node = map[i][j]; node!= nullptr; node = node->next){//go through each element of linked list 
                if(node->thing == SKELETON|| node->thing == VAMPIRE || node->thing == DRAGON){
                    count += node -> quantity;
                }
            }

        }
    }
    return count;
}
