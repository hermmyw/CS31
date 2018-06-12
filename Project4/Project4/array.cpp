//
//  array.cpp
//  Project 4
//
//  Created by Huimin Wang on 10/31/17.
//  Copyright © 2017 Huimin Wang. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) { //append value to the end of each of the n elements of the array and return n
    if (n < 0)
        return -1;
    for (int k = 0; k < n; k++)
        a[k] += value;
    return n;
}

int lookup(const string a[], int n, string target) { //return the position of a string in the array that is equal to target
    if (n < 0)
        return -1;
    for  (int k = 0; k < n; k++) {
        if (a[k] == target)
            return k; //return the position as soon as the target is found
    }
    return -1;
}

int positionOfMax(const string a[], int n) { //return the position of a string in the array such that that string is >= every string in the array.
    string max = "";
    int position = 0;
    if (n <= 0) //return -1 if the array is empty
        return -1;
    
    for (int k = 0; k < n; k++) {
        if (a[k] > max) {
            max = a[k]; //replace max with the current max string
            position = k;
        }
    }
    return position;
}

int rotateLeft(string a[], int n, int pos) { //Eliminate the item at position pos by copying all elements after it one place to the left
    if (n <= 0 || pos < 0 || pos >= n) //if the pos is not valid or n is less than 0, return -1
        return -1;
    string eliminateString = a[pos]; //Store the string that will be moved to the end in a new string
    for (int k = pos+1; k < n; k++) {
        a[k-1] = a[k]; //move the rest of the array to the left
    }
    a[n-1] = eliminateString; //Assign the last string to the string that was stored earlier
    return pos;
}

int countRuns(const string a[], int n) { //return the number of sequences of one or more consecutive identical items in a
    int count = 1;
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    
    for (int k = 0; k < n-1; k++) {
        if (a[k+1] != a[k])
            count++; //if the next item is different from the current item, a new sequence starts and count increments.
    }
    return count;
}

int flip(string a[], int n) { //reverse an array
    if (n < 0)
        return -1;
    for (int k = 0; k < n/2; k++) { //Iterate half of the array
        //flip the positions of a pair of elements
        string temp = a[n-1-k];
        a[n-1-k] = a[k];
        a[k] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) { //return the position of the first corresponding elements of a1 and a2 that are not equal
    if (n1 < 0 || n2 < 0)
        return -1;
    int min; //find the shorter array
    if (n1 < n2)
        min = n1;
    else
        min = n2;
    for (int k = 0; k < min; k++){
        if (a1[k] != a2[k])
            return k; //return the position as soon as the unequal pair is found
    }
    return min; //if he arrays are equal up to the point where one or both runs out, return the smaller (or equal) n
    
}

int subsequence(const string a1[], int n1, const string a2[], int n2) { //return the first position of a2 if a2 is contained in a1
    bool contain = true;
    if (n1 < 0 || n2 < 0)
        return -1;
    if (n2 == 0) //a sequence of 0 elements is a subsequence of any sequence at position 0
        return 0;
    
    for (int k = 0; k < n1; k++) {
        if (a1[k] == a2[0]) { //if the first item of a2 is found in a1, start to compare a1 and a2 from that position
            for (int i = 0; i < n2; i++)
                if (a1[k+i] != a2[i])
                    contain = false;
            if (contain == true)
                return k; //return the position after the comparison is done and all the items are contained
        }
    }
    return -1; //return -1 if a2 is not contained in a1
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) { //Return the smallest position in a1 of an element that is equal to any of the elements in a2
    if (n1 < 0 || n2 < 0)
        return -1;
    
    //compare an element in a1 with all the elements in a2. If equal, return the position of that element in a1
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a2[j] == a1[i])
                return i;
        }
    }
    return -1; //return -1 if all the elements are different
}

int split(string a[], int n, string splitter) {
    int pos = 0;
    if (n < 0)
        return -1;
    
    //if an element is smaller that the splitter, swap it with the element in the front and repeat the loop starting from the next position
    for (int k = 0; k < n; k++) {
        if (a[k] < splitter) {
            string temp = a[pos];
            a[pos] = a[k];
            a[k] = temp;
            pos++;
        }
    }
    //if an element is larger that the splitter, move it to the end
    for (int k = pos; k < n; k++){
        for (int i = pos; i < n; i++){
            if (a[i] > splitter) {
                string temp = a[i];
                for (int j = i+1; j < n; j++)
                    a[j-1] = a[j];
                a[n-1] = temp;
            }
        }
    }
    //return the position with the first element that is equal or larger than the splitter
    for (int i = 0; i < n; i++) {
        if (a[i] >= splitter)
            return i;
    }
    return n;
}

int main() {
    string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
    string h2[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
    string g[4] = { "selina", "reed", "peter", "sue" };
    string e[4] = { "diana", "tony", "", "logan" };
    string d[5] = { "reed", "reed", "reed", "tony", "tony" };
    string f[3] = { "peter", "diana", "steve" };
    string k[0] = {};
    string l[1] = { "peter" };
    string x[9] = { "e", "h", "b", "d", "z", "x", "a", "a", "c" };
    string y[9] = { "aa", "bruce", "steve", "steve", "diana", "diana", "diana", "steve", "steve"
    };
    string names[10] = { "logan", "reed", "sue", "selina", "bruce", "peter" };
    string set2[10] = { "tony", "diana" };
    //assert(appendToAll(h, 4, "?") == 4 && h[0] == "selina?" && h[4] == "");
    assert(lookup(x, 6, "") == -1);
    assert(lookup(h, 0, "reed") == -1 && h[1] == "reed");
    assert(lookup(d, 5, "reed") == 0 && d[1] == "reed");
    assert(positionOfMax(g, 0) == -1);
    assert(positionOfMax(g, 1) == 0);
    assert(positionOfMax(d, 4) == 3);
    assert(positionOfMax(k, 0) == -1);
    assert(positionOfMax(l, 1) == 0);
    assert(rotateLeft(f, 3, 1) == 1);
    assert(rotateLeft(f, 0, 6) == -1);
    assert(countRuns(y, 0) == 0);
    assert(flip(k, 0) == 0);
    assert(differ(h, 0, h2, 0) == 0);
    assert(subsequence(h, 7, l, 1) == 6);
    assert(subsequence(h, 7, d, 5) == -1);
    //(Consider a sequence of 0 elements to be a subsequence of any sequence, even one with no elements, starting at position 0.)
    assert(subsequence (k, 0, x, 0) == 0);
    assert(subsequence (h, 7, e, 4) == 2);
    assert(lookupAny(d, 5, y, 0) == -1);
    assert(lookupAny(k, 0, d, 0) == -1);
    assert(lookupAny(names, 6, set2, 2) == -1);
    assert(split(y, 0, "diana") == 0);
    assert(split(y, 9, "z") == 9);
    assert(split(x, 9, "b") == 2);
    assert(split(h, 7, "") == 0);
    cerr << "All tests succeeded" << endl;
    
}
