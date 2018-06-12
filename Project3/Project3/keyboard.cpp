//
//  keyboard.cpp
//  Project3
//
//  Created by Huimin Wang on 10/21/17.
//  Copyright © 2017 Huimin Wang. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

char encodeNote(int octave, char noteLetter, char accidentalSign);
bool hasCorrectSyntax(string song);
int encodeSong(string song, string& instructions, int& badBeat);

int main() {
    string songString;
    string instrs = "xxx";
    int badb = -999;
    
    //Test
    assert(hasCorrectSyntax("D5//D/"));
    assert(!hasCorrectSyntax("D5//Z/"));
    assert(hasCorrectSyntax("A/Bb/C3/F#3//ABbC3F#3/"));
    assert(hasCorrectSyntax(""));
    assert(hasCorrectSyntax("/"));
    assert(hasCorrectSyntax("C/F9G/"));
    assert(!hasCorrectSyntax("C/F4G//@/"));
    
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("D5//D/", instrs, badb) == 0  &&  instrs == "R H"  &&  badb == -999);
    
    // so we can detect whether these get changed
    assert(encodeSong("D5//Z/", instrs, badb) == 1  &&  instrs == "R H"  &&  badb == -999);
    
    instrs = "xxx"; badb = -999;
    assert(encodeSong("A/Bb/C3/F#3//ABbC3F#3/", instrs, badb) == 0  &&  instrs == "Q%,8 [Q%,8]"  &&  badb == -999);
    
    instrs = "xxx"; badb = -999;
    assert(encodeSong(" ", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    
    instrs = "xxx"; badb = -999;
    assert(encodeSong("/", instrs, badb) == 0  &&  instrs == " "  &&  badb == -999);
    
    //Check if instrs remains unchanged
    assert(encodeSong("C/F9G/", instrs, badb) == 2  &&  instrs == " "  &&  badb == 2);
    
    instrs = "xxx"; badb = -999;
    assert(encodeSong("C/F4G//@/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    assert(encodeSong("A3C#E//E//F#3A3D4/A3C#E/", instrs, badb) == 0  &&  instrs == "[D!J] J [8DH][D!J]"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("C0C0DC0DD/E#FbB#Cb/B#9/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 1);
    
    
    assert(encodeSong("A3C#E//E//F#3A3D4/A3C#E/", instrs, badb) == 0  &&  instrs == "[D!J] J [8DH][D!J]"  &&  badb == 1);
    assert(encodeSong("A3C#E//E//F#3A3D4/A3C#E/", instrs, badb) == 0  &&  instrs == "[D!J] J [8DH][D!J]"  &&  badb == 1);
    
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("D5//D/", instrs, badb) == 0  &&  instrs == "R H"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("D5//Z/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    assert(encodeSong("D5//D8/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 3);
    
    cerr << "All tests succeeded" << endl;
    
    return 0;
}

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** encodeNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}


bool hasCorrectSyntax(string song) {
    
    //extreme cases: a song string starts with a digit or an accidental sign
    if (isdigit(song[0]) || song[0] == '#' || song[0] == 'b') {
        return false;
    }
    //extreme cases: an nonempty song string does not end with a slash
    if (song[song.size()-1] != '/' && song.size() != 0) {
        return false;
    }
    //extreme cases: empty song string
    if (song.size() == 0) {
        return true;
    }
    
    //Check if an nonempty song string contains the valid characters:
    //uppercase letters from A to G, digits, /, and accidental signs
    for (int i = 0; i != song.size(); i++) {
        if (isupper(song[i])) {
            if (song[i] > 'G') {
                return false;
            }
        }
        else if (!isdigit(song[i]) && song[i] != '/' && song[i] != '#' && song[i] != 'b') {
            return false;
        }
    }
    
    //Check if an nonempty song string is in the format of valid notes
    for (int j = 0; j < song.size() - 1; j++) {
        
        //a note letter followed by a note letter
        if (isupper(song[j])) {
            if (isupper(song[j+1]))
                j++;
        }
        
        //a digit can be followed by a note letter or a slash
        else if (isdigit(song[j])) {
            if (isdigit(song[j+1]))
                return false;
            if (song[j+1] == 'b' || song[j+1] == '#')
                return false;
        }
        
        //an accidental sign can be followed by a note letter, a digit, or a slash
        else if (song[j] == 'b' || song[j] == '#') {
            if (song[j+1] == 'b' || song[j+1] == '#')
                return false;
        }
        
        //a slash can be followed by a note letter or a slash
        else if (song[j] == '/') {
            if (!isupper(song[j+1]) && song[j+1] != '/')
                return false;
        }
    }
    
    return true;
}


int encodeSong(string song, string& instructions, int& badBeat) {
    string initialInstr = instructions;
    
    if (hasCorrectSyntax(song)) {
        //an extreme case: an empty string is encoded as a space
        if (song.size() == 0) {
            instructions = "";
            return 0;
        }

        instructions = "";
        int numOfNotes = 0;
        int beat = 0;
        
        //if a song string starts with a slash
        if (song[0] == '/') {
            instructions += ' ';
        }
        
        for (int i = 0; i != song.size() - 1; i++) {
                
            //Find every note in the song string
            if (isupper(song[i])) {
                //count the notes
                numOfNotes++;
                //notes with no digit character
                if (isupper(song[i+1])) {
                    instructions.push_back(encodeNote(4, song[i], ' '));
                    if (encodeNote(4, song[i], ' ') == ' ') {
                        badBeat = beat + 1;
                        instructions = initialInstr;
                        return 2;
                    }
                }
                else if (song[i+1] == '/') {
                    instructions.push_back(encodeNote(4, song[i], ' '));
                    if (encodeNote(4, song[i], ' ') == ' ') {
                        badBeat = beat + 1;
                        instructions = initialInstr;
                        return 2;
                    }
                }
                
                //notes with a digit character
                else if (isdigit(song[i+1])) {
                    instructions.push_back(encodeNote(song[i+1] - '0', song[i], ' '));
                    if (encodeNote(song[i+1] - '0', song[i], ' ') == ' '){
                        badBeat = beat + 1;
                        instructions = initialInstr;
                        return 2;
                    }
                }
                
                //notes with an accidental sign
                else if (song[i+1] == 'b' || song[i+1] == '#') {
                    
                    //notes with an accidental sign followed by a digit
                    if (isdigit(song[i+2])) {
                        instructions.push_back(encodeNote(song[i+2] - '0', song[i], song[i+1]));
                        if (encodeNote(song[i+2] - '0', song[i], song[i+1]) == ' ') {
                            badBeat = beat + 1;
                            instructions = initialInstr;
                            return 2;
                        }
                    }
                    //notes with an accidental sign not followed by a digit
                    else {
                        instructions.push_back(encodeNote(4, song[i], song[i+1]));
                        if (encodeNote(4, song[i], song[i+1]) == ' ') {
                            badBeat = beat + 1;
                            instructions = initialInstr;
                            return 2;
                        }
                    }
                }
                
            }
            
            //every beat ends with a slash
            if (song[i+1] == '/') {
                //if the number of notes is greater than one, we use a bracket to wrap the beat
                if (numOfNotes > 1) {
                    instructions.push_back(']');
                    instructions.insert(instructions.size() - numOfNotes - 1, 1, '[');
                }
                //reset the number of notes for a new beat
                numOfNotes = 0;
                //count the number of beats
                beat++;
            }
            
            //If there is a double-slash, replace it with a space
            if (song[i] == '/' && song[i+1] == '/') {
                instructions.push_back(' ');
            }
        }
        return 0;
    }
    //if a song string does not have the correct syntax, return 1
    return 1;
}

