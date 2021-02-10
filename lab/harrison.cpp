// pa2.cpp

// COMP2011 (Fall 2020)
// Assignment 2: Subtring Pattern Matching
//
// Name: Shih-heng, LO
// Student ID: 20654493
// Email: sloab@connect.ust.hk

#include <assert.h>

#include <iostream>
#include <limits>

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
int matchSubWithDot(const char str[], const char pattern[], int &length,
                    int start);
int matchSubWithQmark(const char str[], const char pattern[], int &length,
                      int start);
int matchSubWithPercent(const char str[], const char pattern[], int &length,
                        int start);
int findSubLenAtStrPosWithDot(const char str[], const char pattern[],
                              int strPos, int patPos);

// Declare additional helper functions below when necessary

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

int matchSubWithDot(const char str[], const char pattern[], int &length, int start = 0) {
    length = 0;
    int *size = &length;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithDot(str, pattern, start);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithDot(str, pattern, length, start + 1);
}

int findSubLenAtStrPosWithQmark(const char str[], const char pattern[], int strPos = 0, int patPos = 0) {
    if (DEBUGMODE) Debug(str, strPos, pattern, patPos);

    if (pattern[patPos] != NULL_CHAR && str[strPos] == NULL_CHAR) {  // the substring is shorter than the pattern to match
        return NOT_FOUND;
    }

    if (pattern[patPos] == QMARK || pattern[patPos] == str[strPos]) {
        if (pattern[patPos + 1] == NULL_CHAR)  // the entire pattern is matched
            return 1;
        int result = findSubLenAtStrPosWithQmark(str, pattern, strPos + 1, patPos + 1);  // check if the remaining part of the pattern
        if (result != NOT_FOUND)                                                         // only return a match when the entire pattern is matched
            return 1 + result;
        result = findSubLenAtStrPosWithQmark(str, pattern, strPos, patPos + 1);
        if (result != NOT_FOUND)  // only return a match when the entire pattern is matched
            return result;
    }

    return NOT_FOUND;
}

int matchSubWithQmark(const char str[], const char pattern[], int &length, int start = 0) {
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithQmark(str, pattern, start);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithQmark(str, pattern, length, start + 1);
}

int getLen(const char *str, int pos = 0) {
    if (str[pos] == NULL_CHAR)
        return 0;
    return 1 + getLen(str, pos + 1);
}

bool PercentOnly(const char *str, int pos = 0) {
    if (str[pos] == NULL_CHAR)
        return true;
    if (str[pos] != PERCENT)
        return false;
    return true * PercentOnly(str, pos + 1);
}

bool AllKeyword(const char *str, int pos = 0) {
    if (str[pos] == NULL_CHAR)
        return true;
    if (str[pos] != PERCENT && str[pos] != QMARK)
        return false;
    return true * AllKeyword(str, pos + 1);
}
//task2
int findSubLenAtStrPosWithPercent(const char str[], const char pattern[], int strPos = 0, int patPos = 0) {
    char trash[23];
    // cin.getline(trash, 4);
    if (DEBUGMODE) Debug(str, strPos, pattern, patPos);
    if (str[strPos] == NULL_CHAR && AllKeyword(pattern, patPos)) {
        return 0;
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

    //rec
    if (pattern[patPos] == PERCENT) {
        if (DEBUGMODE) cout << 1 << endl;
        int result;
        result = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos) + 1;
        if (DEBUGMODE) cout << "RES" << result << endl;
        if (result == NOT_FOUND + 1) {
            result = findSubLenAtStrPosWithPercent(str, pattern, strPos, patPos + 1);
            return result;
        } else
            return result;
    }

    if (pattern[patPos] == str[strPos]) {
        if (DEBUGMODE) cout << 2 << endl;
        int result = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos) + 1;  // check if the remaining part of the pattern
        if (result == NOT_FOUND + 1) {
            result -= 1;
            result = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos + 1) + 1;  // check if the remaining part of the pattern
            if (result == NOT_FOUND + 1) {
                return result - 1;
            } else
                return result;
        }
        return result - 1;
    }
    return NOT_FOUND;
}

int matchSubWithPercent(const char str[], const char pattern[], int &length, int start = 0) {
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithPercent(str, pattern, start);
    if (testLength != NOT_FOUND) {
        length = testLength;
        return start;
    }
    return matchSubWithPercent(str, pattern, length, start + 1);
}

// Task 3 (25 points)

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

int matchSub(const char str[], const char pattern[], int &length, int start = 0) {
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    if (pattern[0] == CARET) {
        int testLength = findSubLenAtStrPos(str, pattern, start, 1);
        if (testLength != NOT_FOUND) {
            length = testLength;
            return start;
        } else
            return NOT_FOUND;
    } else {
        int testLength = findSubLenAtStrPos(str, pattern, start);
        if (testLength != NOT_FOUND) {
            length = testLength;
            return start;
        }
    }
    return matchSub(str, pattern, length, start + 1);
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE
// REPLACED

// Given `str`, prints the substring that begins at `start` with length
// `length`. Raises an assertion error when an attempt is made to print beyond
// the available length. You are not allowed to use loops in your solution,
// though we use them here.
void printString(const char str[], const int start, const int length) {
    for (int i = start; i < start + length; i++)
        assert(str[i] != NULL_CHAR);
    for (int i = start; i < start + length; i++)
        cout << str[i];
}

// A driver program for testing your solution.
int main() {
    const int MAX_LENGTH = 1000;
    char pattern[MAX_LENGTH];
    char str[MAX_LENGTH];
    int option, pos, length;

    while (true) {
        cout << "Task No. (-1 to exit): ";
        // cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (option == -1)
            break;
        if (option < 0 || option > 3)
            continue;
        cout << endl;
        cout << "Enter the string to match: ";
        cin >> str;
        cout << "Enter the pattern to match: ";
        cin >> pattern;
        length = 0;
        // cin >> option;
        option = 3;
        switch (option) {
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
        if (pos == NOT_FOUND) {
            cout << "Pattern is not found." << endl;
        } else {
            cout << "Pattern's first occurence is at " << pos
                 << ", with longest possible length = " << length << "."
                 << endl;
            cout << "Matched substring is '";
            printString(str, pos, length);
            cout << "'." << endl;
        }
        cout << "--------------------------------------------------------------"
                "----"
                "---"
             << endl;
    }
    cout << "bye" << endl;
}