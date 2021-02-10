// pa2.cpp

// COMP2011 (Fall 2020)
// Assignment 2: Subtring Pattern Matching
//
// Name: Chee Seng, OW YONG
// Student ID: 20659467
// Email: csowyong@connect.ust.hk

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

int matchSub(const char str[], const char pattern[], int &length, int start);
int matchSubWithDot(const char str[], const char pattern[], int &length, int start);
int matchSubWithQmark(const char str[], const char pattern[], int &length, int start);
int matchSubWithPercent(const char str[], const char pattern[], int &length, int start);
int findSubLenAtStrPosWithDot(const char str[], const char pattern[], int strPos, int patPos);
// task 1 helper functions
//helper func to find Qmark
int findSubLenAtStrPosWithQmark(const char str[], const char pattern[], int strPos, int patPos);
// helper func to remove Qmark and output position of next char if found, else output not found
int remove_SYMBOL (const char pattern[], int patPos, char symbol);
//remove question mark, output position of next char

// task 2 helper functions
int findSubLenAtStrPosWithPercent(const char str[], const char pattern[], int strPos, int patPos);
// count num  of characters untill end of string
int count_char_end(const char array[], int arrPos);
// count next occuring symbol
int check_other_pos_char(const char string[], int strPos, char symbol);


//task 3 helper functions
int findSubLenAtStrPosWithall(const char str[], const char pattern [], int start,int patPos);
int remove_all_SYMBOL(const char pattern[], int patPos, char symbol1,char symbol2);

// Declare additional helper functions below when necessary


// Helper for Task 0.
// Returns the length of the substring in `str` located at `strPos` that
// matches `pattern`.
// If `pattern` is not found, returns the value `NOT_FOUND`.
// The `pattern` may contain the single character wildcard (`.`).
int findSubLenAtStrPosWithDot(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    if (pattern[patPos] != NULL_CHAR && str[strPos] == NULL_CHAR) // the substring is shorter than the pattern to match
        // if the pattern index of position patpos is not termination character and the string is empty
        return NOT_FOUND; // this means that you cannot find a pattern inside the string 
    if (pattern[patPos] == DOT || pattern[patPos] == str[strPos])
    {
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithDot(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    return NOT_FOUND;
}

// Task 0 (0 point)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the length of the substring matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the single character wildcard (`.`).
int matchSubWithDot(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR) // if the string char in the index is not found
        return NOT_FOUND; // return not found & length of substring = 0
    int testLength = findSubLenAtStrPosWithDot(str, pattern, start);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithDot(str, pattern, length, start + 1);
}

// Task 1 (40 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the zero or single character wildcard (`?`).
int matchSubWithQmark(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    int result=0;
    if (str[start] == NULL_CHAR) // if the string char in the index is not found
        return NOT_FOUND; // return not found & length of substring = 0
    int testLength = findSubLenAtStrPosWithQmark(str, pattern, start,0);//check with the  ta
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithQmark(str, pattern, length, start + 1);
}
// helper func to find if match or not per char in pattern to string 
int findSubLenAtStrPosWithQmark(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    // establish if there is a next character after q mark and keep the position if it is true 
    int remove_QMARK_answer = remove_SYMBOL(pattern, patPos,QMARK);
    int  next_char_patPos;
    int return_value;
    int num_of_reoccuring_QMARK=0;
    if (remove_QMARK_answer != NOT_FOUND && remove_QMARK_answer<=700){
        next_char_patPos = remove_QMARK_answer;
    }
    //Base case
    if (str[strPos] == NULL_CHAR) // the substring is shorter than the pattern to match
    {
        if ( pattern[patPos] != QMARK && remove_QMARK_answer != NOT_FOUND )
        // if the pattern index of position patpos is not termination character and the string is empty
        // if pattern index of pos patpos is a question mark and there is a character at the end of QMARKS
        {
            return NOT_FOUND;
        }
    }
    // recursive part
    if (pattern[patPos] == QMARK || pattern[patPos] == str[strPos] || pattern[next_char_patPos] == str[strPos])
    {
        
        if (pattern[patPos+1]==QMARK && remove_QMARK_answer==NOT_FOUND) {
            int result = findSubLenAtStrPosWithQmark(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                        // matches with that of the substring
            if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                return 1 + result;        }
        else if (pattern[next_char_patPos] == str[strPos]){ // if the next char is the same as the string element of string char
            if (check_other_pos_char(str, strPos+1, pattern[next_char_patPos])!=NOT_FOUND ){ //check if another same char is in string
                
                if ((check_other_pos_char(str, strPos+1, pattern[next_char_patPos])-strPos)<= (next_char_patPos-patPos)){
                    //maybe check another next position
                    int str_jump= check_other_pos_char(str, strPos+1, pattern[next_char_patPos])-strPos+1;
                    return str_jump;

                }
                else{
                    patPos = next_char_patPos;
                }
                // bbabi b???b???
                                //str babi patterrn is b???bi
            }
            else{
                patPos = next_char_patPos;
            }
            if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched (pattern[patPos + 1] == QMARK  && 
                return 1;
            //TODO
            if (pattern[patPos + 1]== QMARK && remove_SYMBOL(pattern,patPos+1,QMARK)==NOT_FOUND){ // if the next  character is a question mark and there are no  more characters after the question mark
                if (str[strPos+1]==NULL_CHAR){
                    return 1;
                }
                else{
                    if(count_char_end(str, strPos)<= count_char_end(pattern,patPos)){
                        return count_char_end(str, strPos);
                    }
                    else{
                        return count_char_end(pattern,patPos);
                    }
                }
            }
            // otherwise, the match is only part way through
            int result = findSubLenAtStrPosWithQmark(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                        // matches with that of the substring
            if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                return 1 + result;
        }
        
        
        // if (pattern[next_char_patPos] == str[strPos]){ // if the next char is the same as the string element of string char
        // //let pattern position become next character position (skip the between quuestion marks)
        //     patPos= next_char_patPos;
        // }
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched (pattern[patPos + 1] == QMARK  && 
            return 1;
            //TODO
        if (pattern[patPos + 1]== QMARK && remove_SYMBOL(pattern,patPos+1,QMARK)==NOT_FOUND){ // if the next  character is a question mark and there are no  more characters after the question mark
            if (str[strPos+1]==NULL_CHAR){
                    return 1;
                }
                else{
                    if(count_char_end(str, strPos)<= count_char_end(pattern,patPos)){
                        return count_char_end(str, strPos);
                    }
                    else{
                        return count_char_end(pattern,patPos);
                    }
                }
        }
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithQmark(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    return NOT_FOUND;
}
// recursion function
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
    return remove_SYMBOL(pattern, patPos+1, symbol);
}



// Task 2 (35 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the zero or more character wildcard (`%`).
int matchSubWithPercent(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    int result=0;
    if (str[start] == NULL_CHAR) // if the string char in the index is not found
        return NOT_FOUND; // return not found & length of substring = 0
    int testLength = findSubLenAtStrPosWithPercent(str, pattern, start,0);//check with the  ta
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithPercent(str, pattern, length, start + 1); 
}
int findSubLenAtStrPosWithPercent(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    // establish if there is a next character after q mark and keep the position if it is true 
    int remove_PERCENT_answer = remove_SYMBOL(pattern, patPos, PERCENT);
    int  next_char_patPos, next_char_strPos;
    int return_value;
    int str_jump;
    int num_str_left;
    if (remove_PERCENT_answer != NOT_FOUND){
        next_char_patPos = remove_PERCENT_answer;
    }
    if (remove_SYMBOL(str, strPos, pattern[next_char_patPos]) != NOT_FOUND){
        next_char_strPos = remove_SYMBOL(str, strPos, pattern[next_char_patPos]);
    }
    //Base case
    if (str[strPos] == NULL_CHAR){ // the substring is shorter than the pattern to match
        if ( pattern[patPos] != PERCENT && remove_PERCENT_answer != NOT_FOUND ) {
        // if the pattern index of position patpos is not termination character and the string is empty
        // if pattern index of pos patpos is a question mark and there is a character at the end of PERCENT
            return NOT_FOUND;
        }
    }
    // recursive part
    if (pattern[patPos] == str[strPos]){ //one non percent character match with str character, normal one 
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched (pattern[patPos + 1] == QMARK  && 
            return 1;
        else if (pattern[patPos + 1]== PERCENT && remove_SYMBOL(pattern,patPos+1,PERCENT)==NOT_FOUND){ // if the next character is a percent sign and there are no  more characters after the question mark
            num_str_left= count_char_end(str,strPos) ;//settled case with percentage at the end of the pattern
            return num_str_left; 
        }
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }

    else if (pattern[patPos] == PERCENT ){ // percent with a character at the end after recursion
        //treat percent as empty char
        // cout<<strPos<<endl;
        if (remove_PERCENT_answer != NOT_FOUND ){ // if there is a char after the percent
            //TODO
            if (check_other_pos_char(str, strPos+1, pattern[next_char_patPos])!=NOT_FOUND){// check if there at least 1 same char in string same as next char in pattern 
                int new_str_pos = strPos+1;
                // cout<<strPos<<endl;
                // cout << check_other_pos_char(str, strPos+1, pattern[next_char_patPos])<< endl;
                str_jump= check_other_pos_char(str, new_str_pos, pattern[next_char_patPos])-strPos;
                //the pattern is only part way through 
                if (findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str,new_str_pos,pattern[next_char_patPos]), patPos)!=NOT_FOUND){
                    int result = str_jump + findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str,new_str_pos,pattern[next_char_patPos]), patPos);
                    if (result != NOT_FOUND && result != str_jump+NOT_FOUND) // only return a match when the entire pattern is matched
                        return  result;
                }
                else{
                    int result = findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str, strPos, pattern[next_char_patPos])+1, next_char_patPos+1); // check if the remaining part of the pattern 
                    if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                        return 1 + result;
                }
                
                
            }// check if the remaining part of the pattern 
            else{ // if there is only one char in the string that match the position of the pattern
                if (pattern[next_char_patPos]==str[strPos]){ // if there is no multiple characters in string, check if the single unrepeated char is the next char
                    patPos= next_char_patPos;
                }
                else {// if next char of pattern is not inside the string, then pattern is not found
                    return NOT_FOUND;
                }
            }
        }
        else { // if the pattern is percent without any char behind or in front 
            num_str_left= count_char_end(str,strPos) ;//settled case with percentage at the end of the pattern
            return num_str_left; 
        }
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched (pattern[patPos + 1] == QMARK  && 
            return 1;
        else if (pattern[patPos + 1]== PERCENT && remove_SYMBOL(pattern,patPos+1,PERCENT)==NOT_FOUND){ // if the next  character is a question mark and there are no  more characters after the question mark
            num_str_left= count_char_end(str,strPos) ;//settled case with percentage at the end of the pattern
            return num_str_left; 
        }
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    return NOT_FOUND;
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
    return NOT_FOUND;
}
int check_other_pos_char(const char string[], int strPos, char symbol){
// base case
    if (string[strPos]==NULL_CHAR){
        return NOT_FOUND;
    }
    else{
        if(string[strPos]==symbol){
            return strPos;//outout of the position of the char in the string once it is found
        }
        else{
            check_other_pos_char(string, strPos+1, symbol);
        }                    
    }
    return check_other_pos_char(string, strPos+1, symbol);
    // return strPos+1;someone help my ass pls 
}
// Task 3 (25 points)
// Returns the first index in `str` where `pattern` is found,
// and sets `length` to be the longest possible length of the substring that can be matched.
// If `pattern` is not found, returns the value `NOT_FOUND`,
// and sets `length` to be 0.
// The `pattern` may contain the '^', '.', '?', and '%' wildcards.
int matchSub(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    int result=0;
    if (str[start] == NULL_CHAR) // if the string char in the index is not found
        return NOT_FOUND; // return not found & length of substring = 0
    if(pattern[0]==CARET){
        int testlength = findSubLenAtStrPosWithall(str,pattern,start,1);
        if (testlength != NOT_FOUND){
            length = testlength;
            return start;
        }
        else{
            return NOT_FOUND;
        }
    }
    int testLength = findSubLenAtStrPosWithall(str, pattern, start,0);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSub(str, pattern, length, start + 1); 
}
int findSubLenAtStrPosWithall(const char str[], const char pattern [], int strPos =0,int patPos=0){
    int  next_char_patPos_QMARK = NOT_FOUND,next_char_patPos_PERCENT = NOT_FOUND, next_char_strPos = NOT_FOUND;
    int return_value;
    int str_jump;
    int num_str_left;
    // helpful statements to help with recursion

    //for removing symbols of question marrk
    int remove_QMARK_answer = remove_SYMBOL(pattern, patPos,QMARK);
    if (remove_QMARK_answer != NOT_FOUND){
        next_char_patPos_QMARK = remove_QMARK_answer;
    }//for removing  percent sign
    int remove_PERCENT_answer = remove_SYMBOL(pattern, patPos, PERCENT);
    if (remove_PERCENT_answer != NOT_FOUND){
        next_char_patPos_PERCENT = remove_PERCENT_answer;
    }
    if (remove_SYMBOL(str, strPos, pattern[next_char_patPos_PERCENT]) != NOT_FOUND){
        next_char_strPos = remove_SYMBOL(str, strPos, pattern[next_char_patPos_PERCENT]);
    }
    
    //Base case
    if (str[strPos] == NULL_CHAR){ // the substring is shorter than the pattern to match
        if (pattern[patPos] != PERCENT  &&  pattern[patPos] != QMARK) { //normal character
        // if pattern index of pos patpos is a question mark and there is a character at the end of PERCENT
            return NOT_FOUND;
        }
        else{
            if(remove_all_SYMBOL(pattern, patPos, PERCENT, QMARK)== NOT_FOUND && remove_SYMBOL(pattern,patPos, DOT)==NOT_FOUND){
                return 0;
            }
            else{
                return NOT_FOUND;
            }
        }
    }

    //case if pattern[patpos] is a normal char or a DOT
    if (pattern[patPos] == DOT || pattern[patPos] == str[strPos] )
    {
        
        // simplest end case        
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        else if (pattern[patPos + 1]== PERCENT && remove_SYMBOL(pattern,patPos+1,PERCENT)==NOT_FOUND){ // if the next character is a percent sign and there are no  more characters after the question mark
            num_str_left= count_char_end(str,strPos) ;//settled case with percentage at the end of the pattern
            return num_str_left; 
        }
        else if (pattern[patPos + 1]== QMARK && remove_SYMBOL(pattern,patPos+1,QMARK)==NOT_FOUND){ // if the next  character is a question mark and there are no  more characters after the question mark
            return 1;
        }
        
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithall(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                    // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    //case if pattern[patpos] is a question mark
    else if (pattern[patPos]==QMARK){

        if (pattern[next_char_patPos_QMARK] == str[strPos]){ // if the next char is the same as the string element of string char
            if (check_other_pos_char(str, strPos+1, pattern[next_char_patPos_QMARK])!=NOT_FOUND ){ //check if another same char is in string
                if ((check_other_pos_char(str, strPos+1, pattern[next_char_patPos_QMARK])-strPos)<= (next_char_patPos_QMARK-patPos)){
                    int str_jump= check_other_pos_char(str, strPos+1, pattern[next_char_patPos_QMARK])-strPos+1;
                    return str_jump;
                }
                else{
                    patPos = next_char_patPos_QMARK;
                }
            }
            else{
                patPos = next_char_patPos_QMARK;
            }
            if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched (pattern[patPos + 1] == QMARK  && 
                return 1;
            if (pattern[patPos + 1]== QMARK && remove_SYMBOL(pattern,patPos+1,QMARK)==NOT_FOUND){ // if the next  character is a question mark and there are no  more characters after the question mark
                if (str[strPos+1]==NULL_CHAR){
                    return 1;
                }
                else{
                    if(count_char_end(str, strPos)<= count_char_end(pattern,patPos)){
                        return count_char_end(str, strPos);
                    }
                    else{
                        return count_char_end(pattern,patPos);
                    }
                }
            }
            // otherwise, the match is only part way through
            int result = findSubLenAtStrPosWithQmark(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                        // matches with that of the substring
            if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                return 1 + result;
        }
        else if (pattern[next_char_patPos_QMARK]==PERCENT){//case where % is after ?

            int result = findSubLenAtStrPosWithQmark(str, pattern, strPos, next_char_patPos_QMARK); // check if the remaining part of the pattern 
                                                                                        // matches with that of the substring
            if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                return 1 + result;
        }
      
        // simplest end case        
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        else if (pattern[patPos + 1]== PERCENT && remove_SYMBOL(pattern,patPos+1,PERCENT)==NOT_FOUND){ 
            num_str_left= count_char_end(str,strPos) ;
            return num_str_left; 
        }
        else if (pattern[patPos + 1]== QMARK && remove_SYMBOL(pattern,patPos+1,QMARK)==NOT_FOUND){ // if the next  character is a question mark and there are no  more characters after the question mark
            if (str[strPos+1]==NULL_CHAR){
                return 1;
            }
            else{
                if(count_char_end(str, strPos)<= count_char_end(pattern,patPos)){
                    return count_char_end(str, strPos);
                }
                else{
                    return count_char_end(pattern,patPos);
                }
            }
        }
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithall(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                    // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    //case if pattern[patpos] is a percent 
    //TODO
    else if (pattern[patPos]==PERCENT){
        //treat percent as empty char
        
        if(remove_all_SYMBOL(pattern, patPos, PERCENT, QMARK)== NOT_FOUND && remove_SYMBOL(pattern,patPos, DOT)==NOT_FOUND){
            if (str[strPos+1]==NULL_CHAR){
                return 0;
            }
            else{
                return count_char_end(str, strPos+1);
            }
        }
       
        
        else if (remove_PERCENT_answer != NOT_FOUND ){ // if there is a char after the percent
            
            if (check_other_pos_char(str, strPos+1, pattern[next_char_patPos_PERCENT])!=NOT_FOUND){// check if there are multiple same char in string same as next char in pattern 
                int new_str_pos = strPos+1;
                str_jump= check_other_pos_char(str, new_str_pos, pattern[next_char_patPos_PERCENT])-strPos;
                //the pattern is only part way through 
                
                if (findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str,new_str_pos,pattern[next_char_patPos_PERCENT]), patPos)!=NOT_FOUND){
                    int result = str_jump + findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str,new_str_pos,pattern[next_char_patPos_PERCENT]), patPos);
                    if (result != NOT_FOUND && result != str_jump+NOT_FOUND) // only return a match when the entire pattern is matched
                        return  result;
                }
                else{
                    int result = findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str, strPos, pattern[next_char_patPos_PERCENT])+1, next_char_patPos_PERCENT+1); // check if the remaining part of the pattern 
                    if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                        return 1 + result;
                }
            }// check if the remaining part of the pattern   
            else{ // if there is only one char or no char in the string that match the position of the pattern
                if (pattern[next_char_patPos_PERCENT]==str[strPos]){ // if there is no multiple characters in string, check if the single unrepeated char is the next char
                    patPos= next_char_patPos_PERCENT;
                }
                else if (pattern[next_char_patPos_PERCENT]==QMARK){//case where ? is after %
                    // babi%?
                    int remove_QMARK_answer = remove_SYMBOL(pattern, next_char_patPos_PERCENT,QMARK);//check for any characters after question mark 
                    if (remove_QMARK_answer != NOT_FOUND){
                        next_char_patPos_QMARK = remove_QMARK_answer;
                    }

                    if (check_other_pos_char(str, strPos+1, pattern[next_char_patPos_QMARK])!=NOT_FOUND){
                        
                        int new_str_pos = strPos+1;
                        str_jump= check_other_pos_char(str, new_str_pos, pattern[next_char_patPos_QMARK])-strPos;
                        int result =  str_jump + findSubLenAtStrPosWithall(str, pattern, check_other_pos_char(str,strPos,pattern[next_char_patPos_QMARK]), patPos);
                        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                        return 1+result;
                        if (findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str,new_str_pos,pattern[next_char_patPos_QMARK]), patPos)!=NOT_FOUND){
                            int result = str_jump + findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str,new_str_pos,pattern[next_char_patPos_QMARK]), patPos);
                        }
                        if (result != NOT_FOUND && result != str_jump+NOT_FOUND){ // only return a match when the entire pattern is matched
                            return  result;
                        }
                    }
                }
                else if (pattern[next_char_patPos_PERCENT]==DOT){
                    int result =  findSubLenAtStrPosWithall(str, pattern, strPos+1, next_char_patPos_PERCENT+1);
                    if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                        return result;
                }
                else{
                    int result = findSubLenAtStrPosWithPercent(str, pattern, check_other_pos_char(str, strPos, pattern[next_char_patPos_PERCENT])+1, next_char_patPos_PERCENT+1); // check if the remaining part of the pattern 
                    if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                        return 1 + result;
                    
                    else if (pattern[next_char_patPos_QMARK]==PERCENT){
                        int result =  findSubLenAtStrPosWithall(str, pattern, strPos, next_char_patPos_QMARK);
                        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                            return result;
                        
                    }
                    else {
                        
                        int result =  findSubLenAtStrPosWithall(str, pattern, strPos, next_char_patPos_QMARK);
                        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
                            return result;
                    }
                    
                }
                
              
            }
        }
        else { // if the pattern is percent without any char behind or in front 
            num_str_left= count_char_end(str,strPos) ;//settled case with percentage at the end of the pattern
            return num_str_left; 
        }
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched (pattern[patPos + 1] == QMARK  && 
            return 1;
        if (pattern[patPos + 1]== PERCENT && remove_SYMBOL(pattern,patPos+1,PERCENT)==NOT_FOUND){ // if the next  character is a question mark and there are no  more characters after the question mark
            num_str_left= count_char_end(str,strPos) ;//settled case with percentage at the end of the pattern
            return num_str_left; 
        }
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithall(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    } 
    return NOT_FOUND;
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
    return NOT_FOUND;
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

// Given `str`, prints the substring that begins at `start` with length `length`.
// Raises an assertion error when an attempt is made to print beyond the available length.
// You are not allowed to use loops in your solution, though we use them here.
void printString(const char str[], const int start, const int length)
{
    for (int i = start; i < start + length; i++)
        assert(str[i] != NULL_CHAR);
    for (int i = start; i < start + length; i++)
        cout << str[i];
}

// A driver program for testing your solution.
int main()
{
    const int MAX_LENGTH = 1000;
    char pattern[MAX_LENGTH];
    char str[MAX_LENGTH];
    int option, pos, length;

    while (true)
    {
        cout << "Task No. (-1 to exit): "; cin >> option;
        if (cin.fail())
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (option == -1)
            break;
        if (option < 0 || option > 3)
            continue;
        cout << endl;
        cout << "Enter the string to match: "; cin >> str;
        cout << "Enter the pattern to match: "; cin >> pattern;
        length = 0;
        switch (option)
        {
            case 0:
                pos = matchSubWithDot(str, pattern, length);
                break;
            case 1:
                pos = matchSubWithQmark(str, pattern, length);
                break;
            case 2:
                pos = matchSubWithPercent(str, pattern, length);
                break;
            case 3:
                pos = matchSub(str, pattern, length);
                break;
        }
        cout << endl;
        if (pos == NOT_FOUND)
        {
            cout << "Pattern is not found." << endl;
        }
        else
        {
            cout << "Pattern's first occurence is at " << pos << ", with longest possible length = " << length << "." << endl;
            cout << "Matched substring is '"; printString(str, pos, length); cout << "'." << endl;
        }
        cout << "---------------------------------------------------------------------" << endl;
    }
    cout << "bye" << endl;
}