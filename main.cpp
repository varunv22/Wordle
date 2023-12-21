#include <iostream>
#include <cstring>
#include <string>
#include "utilities.h"
#include <iomanip>
using namespace std;

int countGold(char probe[MAXWORDLEN + 1], char actual[MAXWORDLEN + 1]);
int countSilver(char probe[MAXWORDLEN + 1], char actual[MAXWORDLEN + 1]);
bool wordSyntax(const char[MAXWORDLEN + 1]);
bool validWord(const char guess[MAXWORDLEN + 1], const char wordList[9000][MAXWORDLEN + 1]);
int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);

const int MAXWORDS = 9000;

int main(){
    double average = 0;
    int maximum = 0;
    int minimum = 0;
    int nRounds = 0;
    char wordList[MAXWORDS][MAXWORDLEN + 1];
    const char WORDFILENAME[] = "/Users/vknr/Desktop/Project 5/Words.txt";
        
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME); // to get words
    
    if(nWords < 1){ // if no words were loaded
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    cout << "How many rounds do you want to play? ";
    cin >> nRounds;
    cout << endl;
    cin.ignore(10000, '\n'); // clean buffer
    if(nRounds < 0){
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    for(int x = 1; x <= nRounds; x++){
        int num;
        cout << "Round " << x << endl;
        int rand = randInt(0, nWords - 1);
        char word[MAXWORDLEN + 1];
        strcpy(word, wordList[rand]);
        cout << "The hidden word is " << strlen(word) << " letters long." << endl;
        
        num = playOneRound(wordList, nWords, rand);
        if(x == 1){ // for when it is the first round
            maximum = num;
            minimum = num;
            average = num;
        } else{
            average += num;
        }
        if(num < 1){
            cout << "Score cannot be less than 1" << endl;
            return -1;
        }
        if(num == 1){
            cout << "You got it in 1 try." << endl;
        } else{
            cout << "You got it in " << num << " tries." << endl;
        }
        if(num > maximum){
            maximum = num;
        }
        if(num < minimum){
            minimum = num;
        }

        cout << "Average: " << fixed << setprecision(2) << average / x << ", minimum: " << minimum << ", maximum: " << maximum << endl << endl;
    }
    
    return 0;
}


int playOneRound(const char words[][7], int nWords, int wordnum){
    int guessCount = 0;
//    cout << rand << endl;
    char guess[MAXWORDLEN + 1];
    char actual[MAXWORDLEN + 1];
    char actual2[MAXWORDLEN + 1]; // make a copy so you can later use the copy to do strcopy(actual, actual2)
    char guess2[MAXWORDLEN + 1]; // make a copy so you can later use the copy to do strcopy(guess, guess2)
    strcpy(actual, words[wordnum]);
    strcpy(actual2, actual);
    
    if(nWords < 0 || wordnum < 0 || wordnum >= nWords){
        return -1;
    }
    
    
    
    for(;;){
        cin.clear(); // clean buffer
        fflush(stdin);
        cout << "Probe word: ";
        cin.getline(guess, MAXWORDLEN + 1);
        strcpy(guess2, guess);
        
        guessCount++;
        
        if(!wordSyntax(guess)){ // check for correct word syntax
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
        } else if(!validWord(guess, words)){ // check for valid words
            cout << "I don't know that word." << endl;
        } else if(strcmp(guess, actual) != 0){ // if it is a valid guess word, cout numgold and numsilver
            int numGold = countGold(guess, actual);
            int numSilvers = countSilver(guess,actual);
            cout << "Golds: " << numGold << ", Silvers: " << numSilvers << endl;
        }
        strcpy(actual, actual2); // change the word back into what it was before it was run through countgold and countsilver
        strcpy(guess, guess2); // change the word back into what it was before it was run through countgold and countsilver
        
        if(strcmp(guess, actual) == 0){ // condition for when to exit the function
            return guessCount;
        }
        
    }
    
    return guessCount;
}




int countGold(char probe[MAXWORDLEN + 1], char actual[MAXWORDLEN + 1]){
//    checks for golds. if there is a gold, change the matching letters to some number that will never be matched with the other stuff
    int numGold = 0;
    
    for(int z = 0; z < strlen(actual); z++){
        if(probe[z] == actual[z]){
            numGold++;
            actual[z] = '0';
            probe[z] = '1';
        }
    }
    
    return numGold;
}

int countSilver(char probe[MAXWORDLEN + 1], char actual[MAXWORDLEN + 1]){
// checks for silvers. if there is a silver, change the matching letters to some number that will never be matched with the other stuff
    int numSilver = 0;
    
    for(int z = 0; z < strlen(probe); z++){
        for(int y = 0; y < strlen(actual); y++){
            if(probe[z] == actual[y]){
                numSilver++;
                actual[y] = '0';
                probe[z] = '1';
            }
        }
    }
    return numSilver;
}

bool wordSyntax(const char guess[MAXWORDLEN + 1]){
//    if the length is less than 4, return false. if the length is greater than 6, return false. check every letter in the cstring for lowercase letters.
    if(strlen(guess) < MINWORDLEN){
        return false;
    }
    if(strlen(guess) > MAXWORDLEN){
        return false;
    }
    for(int x = 0; x < strlen(guess); x++){
        if(!islower(guess[x])){
            return false;
        }
    }
    
    return true;
}

bool validWord(const char guess[MAXWORDLEN + 1], const char wordList[9000][MAXWORDLEN + 1]){
//    using a for loop, run the guess word through all the words in the list and return true if there is a match
    for(int x = 0; x < 9000; x++){
        if(strcmp(guess, wordList[x]) == 0){
            return true;
        }
    }
    return false;
}
