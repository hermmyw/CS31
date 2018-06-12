//
//  main.cpp
//  Project 5
//
//  Created by Huimin Wang on 11/6/17.
//  Copyright © 2017 Huimin Wang. All rights reserved.
//

#include "utilities.h"
#include <iostream>
#include <cstring>
#include <fstream>
#define _CRT_SECURE_NO_DEPRECATE
using namespace std;

const char WORDFILENAME[] = "/Users/hermmy/Documents/2017-2018/CS 31/Project 5/stars/smallwords.txt";
const int MAXWORDS = 9000;

int findStars(const char word[MAXWORDLEN+1], const char secret[MAXWORDLEN+1]) {
    int s = 0;
    int len;
    
    //find the shorter word between probe word and secret word
    if (strlen(word) < strlen(secret))
        len = strlen(word);
    else
        len = strlen(secret);
    
    for (int i = 0; i < len; i++)
        if (word[i] == secret[i])
            s++;//if corresponding letters are equal, increment star
    
    return s;
}

int findPlanets(char word[MAXWORDLEN+1], const char secret[MAXWORDLEN+1]) {
    int p = 0;
    for (int i = 0; i < strlen(secret); i++) {
        if (secret[i] == word[i])
            word[i] = ' '; //replace every star with a blank space
        else {
            for (int j = 0; j < strlen(word); j++) {
                if (i != j && word[j] != secret[j] && word[j] == secret[i] ) { //if a letter in probe is equal to some letter in secret and is a star
                    word[j] = ' '; //replace this letter with a blank space
                    p++;
                    break; //immediately breaks out of the loop to avoid repeated counting
                }
            }
        }
    }
    return p;
}

bool contain(const char a[], const char b[][MAXWORDLEN+1], int n) {
    for (int i = 0; i < n; i++)
        if (strcmp(b[i], a) == 0) //find a word in array that is equal to the target word
            return true;
    return false;
}

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum){
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) //if the arguments are not valid, terminate the function
        return -1;
    
    char secret[MAXWORDLEN+1];
    strcpy(secret, words[wordnum]); //declare a c-string to store the secret word
    
    char probe[100]; //declare a probe c-string that is large enough
    
    int score = 0;
    for(;;) {
        cout << "Probe word: ";
        cin.getline(probe, 100); //prompt user for probe words
        
        if (strlen(probe) < MINWORDLEN || strlen(probe) > MAXWORDLEN) {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue; //go on to the next iteration if the length of the probe word is valid
        }
        else {
            bool lowerCase = true;
            for (int i = 0; probe[i] != '\0'; i++) {
                if (!islower(probe[i])) {
                    cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                    lowerCase = false;
                    break; //break out of the loop as soon as a letter that is not lower-case is found
                }
            }
            if (lowerCase == false)
                continue; //if any invalid letter is found, go on to the next iteration
        }
        
        if (!contain(probe, words, nWords)) {
            cout << "I don't know that word." << endl;
            continue; //if a probe word is not in the valid word array, go on to the next iteration
        }
        
        if (strcmp(probe, secret) == 0)
            return score+1; //if user gets the secret word, write the score
        
        cout << "Stars: " << findStars(probe, secret) << ", Planets: " << findPlanets(probe, secret) << endl; //write stars and planets
        score++;
    }
    return score;
}

int main(){
    char w[MAXWORDS][MAXWORDLEN+1];
    int n = getWords(w, MAXWORDS, WORDFILENAME); //load word list
    
    //check if the loaded word list is valid
    if (n < 1) {
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }
    else if (n > MAXWORDS)
        return 0;
        
    int round;
    int roundCount = 1;
    
    //prompt user for the number of rounds
    cout << "How many rounds do you want to play? ";
    cin >> round;
    cin.ignore(1000,'\n');
    cout << endl;
    
    //check if the user enters a valid round number
    if (round < 0) {
        cout << "The number of rounds must be positive. ";
        return -1;
    }
    
    int total = 0;
    int min = MAXWORDS; //initialize min to be a large number
    int max = 0;
    
    while (roundCount <= round) {
        char secret[MAXWORDLEN+1];
        
        //generate a random secret word from the array
        int r = randInt(0, n-1);
        strcpy(secret, w[r]);
        
        cout << "Round " << roundCount << endl;
        cout << "The secret word is " << strlen(secret) << " letters long." << endl;
        
        //call runOneRound to get the score
        int score = runOneRound(w, n, r);
        
        //write the result to the user
        if (score == 1)
            cout << "You got it in " << score << " try." << endl;
        else
            cout << "You got it in " << score << " tries." << endl;
        
        double avg = 0.0;
        total += score;
        avg = static_cast<double>(total)/roundCount;
        
        //update max and min
        if (score > max)
            max = score;
        
        if (score < min)
            min = score;
        
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << avg << ", minimum: " << min << ", maximum: " << max << endl;
        cout << endl;
        roundCount++;
    }
}
