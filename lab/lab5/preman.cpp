#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define N 20


// search for a word in the input file, return true if found
bool lookup(const char filename[], const char word[]){
	ifstream file(filename);
	if (!file){ 
		cerr << "Error: Can’t open \"" << filename << "\"\n"; return -1; 
	} else {
		char fileword[100];
		while (!file.eof()){
			file >> fileword;
			if (strcmp(word, fileword) == 0) {
        		return true;
   			}
		}
	}

	file.close();
	

	return false;
}


// delete a word in the input file
// the result should not contain blank lines
void delete_word(const char filename[], const char word[]){
	if (lookup(filename, word)){
		rename(filename, "temporary.txt");
		ifstream new_file("temporary.txt");
		ofstream file(filename);
		char c[20];

		while (new_file.getline(c, 20, '\n')){
			if (strcmp(word, c) != 0){
				for (int i = 0; c[i] != '\0' ; i++){
					file.put(c[i]);
				}
				file.put('\n');
			}
			memset(c, 0, sizeof(c));
		}

		new_file.close();
		file.close();
		remove( "./temporary.txt" );

		if (lookup(filename, word)){
			cerr << "The word \""<< word <<"\" is not in the file!" << endl;
		} else {
			cout << "The word \""<< word <<"\" is deleted successfully!" << endl;
		}

	} else {
		cout << "The word \""<< word <<"\" is not in the file!" << endl;
	}
}


// insert a word in the input file such that the words are in ascending order
// it should not insert duplicate word
void insert_word(const char filename[], const char word[]){
	if (!lookup(filename, word)){
		rename(filename, "temporary.txt");
		ifstream new_file("temporary.txt");
		ofstream file(filename);

		char c; new_file.get(c);
		while (!new_file.eof()){
			file.put(c);
			new_file.get(c);
		}

		new_file.close();
		remove( "./temporary.txt" );
		

		for (int i = 0; i < sizeof(word)/sizeof(word[0]); i++){
			if (word[i] != '\0'){
				file.put(word[i]);
			}
			
		}

		file.put('\n');
		file.close();
		if (lookup(filename, word)){
			cout << "The word \""<< word <<"\" is inserted successfully!" << endl;
		} else {
			cerr << "Error inserting word \"" << word << "\"" << endl;
		}

	} else {
		cout << "The word \"" << word << "\" already exists!" << endl;
	}
}


int main(){

	const char filename[] = "words.txt";
	char choice; 
	char word[N];

	while (true){
		memset(word, 0, sizeof(word));

		cout << "1 for lookup; 2 for insertion; 3 for deletion; q for quit: ";
		cin >> choice;

		if (choice == '1'){
			cout << "Please enter the word you want to search for: ";
			cin >> word;
			if (lookup(filename, word)){
				cout << "The word \"" << word << "\" is found!" << endl;
			}else{
				cout << "The word \"" << word << "\" is not found!" << endl;
			}
		}else if (choice == '2'){
			cout << "Please enter the word you want to insert: ";
			cin >> word;
			insert_word(filename, word);
		}else if (choice == '3'){
			cout << "Please enter the word you want to delete: ";
			cin >> word;
			delete_word(filename, word);
		}else if (choice == 'q'){
			break;
		}else{
			cout << "Invalid input. Please input again." << endl;
		}
		cout << endl;
	}

	return 0;
}