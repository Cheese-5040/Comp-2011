#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define N 20


// search for a word in the input file, return true if found
bool lookup(const char filename[], const char word[]){
	int array_size; ifs >> array_size;
	int word[20];

	for (int j	]=0; j< array_size; j++){
		ifs >> word[j];

	}
	ifs.close();
	return false;
}


// delete a word in the input file
// the result should not contain blank lines
void delete_word(const char filename[], const char word[]){
}


// insert a word in the input file such that the words are in ascending order
// it should not insert duplicate word
void insert_word(const char filename[], const char word[]){
}


int main(){

	const char filename[] = "words.txt";
	char choice;
	char word[N];

	while (true){
		cout << "1 for lookup; 2 for insertion; 3 for deletion; q for quit: ";
		cin >> choice;

		if (choice == '1'){
			cout << "Please enter the word you want to search for: ";
			cin >> word;
			if (lookup(filename, word)){ // search for filename and word and see if it is inside the file
				cout << "The word \"" << word << "\" is found!" << endl;
			}else{
				cout << "The word \"" << word << "\" is not found!" << endl;
			}
		}else if (choice == '2'){ // insert a new word into the word list, and check if it already appears in word bank (task 1)
			cout << "Please enter the word you want to insert: ";
			cin >> word;
			insert_word(filename, word);
		}else if (choice == '3'){ // delete word from word bank, including the empty lines in the text file
			cout << "Please enter the word you want to delete: ";
			cin >> word;
			delete_word(filename, word);
		}else if (choice == 'q'){ // if user quits
			break;
		}else{
			cout << "Invalid input. Please input again." << endl;
		}
		cout << endl;
	}

	return 0;
}