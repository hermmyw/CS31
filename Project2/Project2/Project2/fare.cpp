//
//  fare.cpp
//  Project2
//
//  Created by Huimin Wang on 10/11/17.
//  Copyright © 2017 Huimin Wang. All rights reserved.
//
#include <iostream>
#include <string>

using namespace std;

int main() {
    
    int age;
    string student;
    string destination;
    int zoneCrossed;
    double fare;
    
    cout << "Age of rider: ";
    cin >> age;
    cin.ignore(10000, '\n');
    if (age < 0) {
        cout << "---" << endl;
        cout << "The age must not be negative" << endl;
        return 1; //Terminate the program if the age is negative
    }
    
    cout << "Student? (y/n): ";
    getline(cin, student);
    if (student != "y" && student != "n") {
        cout << "---" << endl;
        cout << "You must enter y or n" << endl;
        return 1; //Terminate the program if the user does not give a valid input
    }
    
    cout << "Destination: ";
    getline(cin, destination);
    if (destination == "") {
        cout << "---" << endl;
        cout << "You must enter a destination" << endl;
        return 1; //Terminate the program if the user does not enter a destination
    }
    
    cout << "Number of zone boundaries crossed: ";
    cin >> zoneCrossed;
    cin.ignore(10000, '\n');
    if (zoneCrossed < 0) {
        cout << "---" << endl;
        cout << "The number of zone boundaries crossed must not be negative" << endl;
        return 1; //Terminate the program if the number of zone boundaries crossed is negative
    }
    
    //There are three groups categorized by ages
    
    //The first group is senior
    if (age > 65) {
        if (zoneCrossed == 0){
            fare = 0.45;
        }
        else if (student == "y" && zoneCrossed == 1)
            fare = 0.65;
        else
            fare = 0.55 + 0.25 * zoneCrossed;
    }
    
    //The second group is minor
    else if (age < 18) {
        if (zoneCrossed <= 1)
            fare = 0.65;
        else
            fare = 1.35 + 0.55 * zoneCrossed;
    }
    //The third group is adults
    else {
        if (student == "y" && zoneCrossed <= 1)
            fare = 0.65;
        else
            fare = 1.35 + 0.55 * zoneCrossed;
    }
    
    
    
    cout << "---" << endl;
    
    //Set the decimal places to 2
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "The fare to " << destination << " is $" << fare << endl;
    return 0;
}

