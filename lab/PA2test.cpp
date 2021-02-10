// pa2.cpp

// COMP2011 (Fall 2020)
// Assignment 2: Subtring Pattern Matching
//
// Name: <PUT YOUR NAME HERE>
// Student ID: <PUT YOUR STUDENT ID NUMBER HERE>
// Email: <PUT YOUR EMAIL HERE>

#include <iostream>
#include <limits>
#include <assert.h>

using namespace std;

// C string termination character
const char NULL_CHAR = '\0';

// The "not found" flag
const int NOT_FOUND = -1;

// Single character wildcard
const char DOT = '.';

// Zero or single character wildcard
const char QMARK = '?';

// Zero or more character wildcard
const char PERCENT = '%';

// Matches the beginning of a string
const char CARET = '^';

const int MAX_LENGTH = 1000;
int length, patPos;
char pattern[MAX_LENGTH];
int answer;

// recursion function
int remove_QMARK(const char pattern[], int patPos)
{
    // base case
    if (pattern[patPos] == NULL_CHAR)
    {
        return NOT_FOUND;
    }
    else
    {
        if (pattern[patPos] != QMARK)
        {
            return patPos;
        }
        else
        {
            remove_QMARK(pattern, patPos + 1);
        }
    }
}
int remove_null_char(const char array[], int arrPos)
{
    if (array[arrPos] != NULL_CHAR)
    {
        return arrPos;
    }
    else
    {
        remove_null_char(array, arrPos - 1);
    }
}
int num_QMARK_at_end(const char pattern[], int patPos)
{
    // base case
    int result;
    if (pattern[patPos] != QMARK)
    {
        return NOT_FOUND;
    }
    else
    {

        result = num_QMARK_at_end(pattern, patPos - 1);
        return 1 + result;
    }
}
int remove_SYMBOL(const char pattern[], int patPos, char symbol){
// base case
    if (pattern[patPos]==NULL_CHAR){
        return NOT_FOUND;
    }
    else{
        if (pattern[patPos] != symbol){
            return patPos;
        }
        else{
            remove_SYMBOL(pattern, patPos+1, symbol);
        }
    }
}
int remove_all_SYMBOL(const char pattern[], int patPos, char symbol1,char symbol2){
// base case
    if (pattern[patPos]==NULL_CHAR){
        return NOT_FOUND;
    }
    else{
        if (pattern[patPos] != symbol1 && pattern[patPos]!= symbol2){
            return patPos;
        }
        else{
            remove_all_SYMBOL(pattern, patPos+1, symbol1,symbol2);
        }
    }
}
int count_char_end(const char array[], int arrPos){
    int result;
    //  base case
    if (array[arrPos]==NULL_CHAR){
        return 0;
    }
    else{
        if (array[arrPos]!= NULL_CHAR){
            result = count_char_end(array, arrPos+1);
            if (result !=0){
                return 1+ result;
            }
            return 1;
        }
    }   
}
int check_other_pos_char(const char string[], int strPos, char symbol){
// base case
    if (string[strPos]==NULL_CHAR){
        return NOT_FOUND;
    }
    else{
    
            
        if(string[strPos]==symbol){
            return strPos;
        }
        else{
            check_other_pos_char(string, strPos+1, symbol);
        }                    
    }
}
int reoccuring_number(int next_char_patPos, int patPos){
    if (next_char_patPos - patPos ==1){
        
    }
}
void helpPrint(const char *str, int pos) {
    for (int i = pos; str[i] != NULL_CHAR; ++i)
        cout << str[i];
    cout << endl;
}
void Debug(const char *str, int strPos, const char *pattern, int patPos) {
    cout << " ------ " << endl;
    helpPrint(str, strPos);
    helpPrint(pattern, patPos);
}
bool AllKeyword(const char *str, int pos = 0) {
    if (str[pos] == NULL_CHAR)
        return true;
    if (str[pos] != PERCENT && str[pos] != QMARK)
        return false;
    return true * AllKeyword(str, pos + 1);
}

#define DEBUGMODE 1

int findSubLenAtStrPosWithDot(const char str[], const char pattern[], int strPos = 0, int patPos = 0) {
    if (pattern[patPos] != NULL_CHAR && str[strPos] == NULL_CHAR)  // the substring is shorter than the pattern to match
        return NOT_FOUND;
    if (pattern[patPos] == DOT || pattern[patPos] == str[strPos]) {
        if (pattern[patPos + 1] == NULL_CHAR)  // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithDot(str, pattern, strPos + 1, patPos + 1);  // check if the remaining part of the pattern
        if (result != NOT_FOUND)                                                       // only return a match when the entire pattern is matched
            return 1 + result;
    }
    return NOT_FOUND;
}
int findSubLenAtStrPos(const char str[], const char pattern[], int strPos = 0, int patPos = 0) {
    if (DEBUGMODE) Debug(str, strPos, pattern, patPos);
    if (str[strPos] == NULL_CHAR && AllKeyword(pattern, patPos)) {
        if (DEBUGMODE) cout << "BASEE7" << endl;
        return 0;
    }
    if (pattern[patPos] != NULL_CHAR && str[strPos] == NULL_CHAR) {  // the substring is shorter than the pattern to match
        if (DEBUGMODE) cout << "BASE5" << endl;
        return NOT_FOUND;
    }
    if (str[strPos] != NULL_CHAR && pattern[patPos] == NULL_CHAR) {
        if (DEBUGMODE) cout << "BASE4" << endl;
        return 0;
    }
    if (str[strPos] != NULL_CHAR && pattern[patPos] != NULL_CHAR
        && str[strPos + 1] == NULL_CHAR && pattern[patPos + 1] == NULL_CHAR
        && str[strPos] == pattern[patPos]) {
        if (DEBUGMODE) cout << "BASE3" << endl;
        return 1;
    }
    if (str[strPos + 1] == NULL_CHAR && pattern[patPos] == NULL_CHAR) {
        if (DEBUGMODE) cout << "BASE0" << endl;
        return 0;
    }
    if (str[strPos] == NULL_CHAR && pattern[patPos] == PERCENT && pattern[patPos + 1] == NULL_CHAR) {
        if (DEBUGMODE) cout << "BASE1" << endl;
        return 0;
    }

    if (str[strPos] == NULL_CHAR && pattern[patPos] != NULL_CHAR) {
        if (DEBUGMODE) cout << "BASE2" << endl;
        return NOT_FOUND;
    }

    if (pattern[patPos] == DOT) {
        if (DEBUGMODE) cout << 3 << endl;

        if (pattern[patPos + 1] == NULL_CHAR)  // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos + 1);  // check if the remaining part of the pattern
        if (result != NOT_FOUND)                                                // only return a match when the entire pattern is matched
            return 1 + result;
    }
    if (pattern[patPos] == QMARK) {
        if (DEBUGMODE) cout << 3 << endl;

        if (pattern[patPos + 1] == NULL_CHAR)  // the entire pattern is matched
            return 1;
        int result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos + 1);  // check if the remaining part of the pattern
        if (result != NOT_FOUND)                                                // only return a match when the entire pattern is matched
            return 1 + result;
        result = findSubLenAtStrPos(str, pattern, strPos, patPos + 1);
        if (result != NOT_FOUND)  // only return a match when the entire pattern is matched
            return result;
    }
    if (pattern[patPos] == PERCENT) {
        if (DEBUGMODE) cout << 1 << endl;
        int result;
        result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos) + 1;
        if (DEBUGMODE) cout << "RES" << result << endl;
        if (result == NOT_FOUND + 1) {
            result = findSubLenAtStrPos(str, pattern, strPos, patPos + 1);
            return result;
        } else
            return result;
    }

    if (pattern[patPos] == str[strPos]) {
        if (DEBUGMODE) cout << 2 << endl;
        int result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos) + 1;  // check if the remaining part of the pattern
        if (result == NOT_FOUND + 1) {
            result -= 1;
            result = findSubLenAtStrPos(str, pattern, strPos + 1, patPos + 1) + 1;  // check if the remaining part of the pattern
            if (result == NOT_FOUND + 1) {
                return result - 1;
            } else
                return result;
        }
        return result - 1;
    }

    return NOT_FOUND;
}

int main()
{
    cout << "Enter the pattern to match: ";
    cin >> pattern;
    cout<< "enter position of the array: ";cin>> patPos;
    // ++patPos;
    // cout << count_char_end(pattern, patPos) <<endl;
    // cout<< "enter length "; cin >> length;
    // cout << "enter pattern position";
    // cin >> patPos;
    // patPos=0;
    // char character; 
    // cout << "enter character " ; cin >> character;
    // answer = check_other_pos_char(pattern, patPos, character);
    // if (answer == NOT_FOUND)
    // {
    //     cout << "no additional characters repeated" << endl;
    // }
    // else
    // {
    //     cout << "the next position of character "<< pattern[answer] <<" is at position " << answer << endl;
    // }
    cout << remove_SYMBOL(pattern, patPos,QMARK) << endl;
    int result = remove_SYMBOL(pattern, patPos,QMARK);
    
    if  (result == NOT_FOUND){
        cout  << "the pattern did not end  with QMARKS"<< endl;
    }
    else{
        cout <<"there are  "<< result << " many consecutive QMARKS at the end of the pattern" <<endl;
    }
    

}
