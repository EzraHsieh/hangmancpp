// Author: Ezra Hsieh
// Inspired by Angela Yu's "100 Days of Python"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "hangman_words.hpp"
#include "hangman_art.hpp"

using namespace std;

// Function to print out the current guessed and unknown characters. 
void printDisplay (char display[], int word_length) {
    for (int i=0; i<word_length; i++) {
        cout << display[i] << " ";
    }
    cout << endl;
    cout << endl;
}


int main() {
    //Choose a random word from the word list
    int word_list_size = sizeof(word_list)/sizeof(string);
    srand(static_cast<unsigned int>(time(nullptr)));
    int chosen_index = rand() % word_list_size;
    string chosen_word = word_list[chosen_index];

    cout << logo << endl;
    cout << stages[6] << endl;
    //cout << "Chosen word: " << chosen_word << endl;

    bool end_of_game = false;
    int lives = 6;
    int chosen_word_length = chosen_word.length();
    int letters_left = chosen_word_length;
    vector<char> guessed_char;

    // Set up the character display of the chosen word. 
    char display [chosen_word_length];
    for (int i=0; i<chosen_word_length; i++) {
        display[i] = '_';
    }
    printDisplay(display, chosen_word_length);

    while (!end_of_game)
    {
        char user_char;
        cout << "Guess a letter: ";
        cin >> user_char;
        cout << endl;
    
    // Test if the user input letter has already been tried.
        bool found = false;
        for (int i=0; i<guessed_char.size(); i++) {
            if (guessed_char[i] == user_char) {
                found = true;
                break;
            }
        }

        // Check each user input letter against the chosen word
        if (found == false){
            guessed_char.push_back(user_char);
            int old_letters_left = letters_left;
            for (int i=0; i<chosen_word_length; i++) {
                if (user_char == chosen_word[i]) {
                    display[i] = user_char;
                    letters_left --;
                }
                else if (i == chosen_word_length-1 && old_letters_left == letters_left) {
                    cout << "Wrong guess!" << endl;
                    lives --;
                    // print out hangman here.
                    cout << stages[lives] << endl;
                }
            }
            
            printDisplay(display, chosen_word_length);

            if (lives == 0) {
                cout << "You LOSE! The word is " << chosen_word << endl;
                end_of_game = true;
            }
            else if (letters_left == 0) {
                cout << "You WIN!" << endl;
                end_of_game = true;
            }
        }

        else {
            cout << "Already tried that letter. Please try another." << endl;
            cout << endl;
        }
    }

    cout << "GAME OVER! Enter anything to quit." << endl;
    string q;
    cin >> q;
    return 0;
}