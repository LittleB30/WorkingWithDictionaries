// Alex Smith
// This is a file to implement a hash table of Entry objects

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dictionary {
private:
    enum Status {Active, Empty, Deleted};

    struct HashEntry {
        string word;
        Status status;

        HashEntry() {
            status = Empty;
        }
    };

    struct DynArray {
        HashEntry* arr;
        int size;
        int capacity;
    };

    DynArray array;
    vector<int> primes;
    int curPrimeIndex;

public:
    /*----Constructors----*/
    Dictionary();
    Dictionary(const Dictionary& orig);

    /*-----Destructor-----*/
    virtual ~Dictionary();

    /*-----Operators-----*/
    Dictionary& operator=(const Dictionary& orig);
    
    /*------Methods------*/
    void addEntry(string anEntry);
    // Preconditions:  anEntry has a key not already in the dictionary
    // Postconditions: anEntry has been added to the dictionary

    bool findEntry(string key);
    // Postconditions: if key is found in the dictionary, returns true 
    //                 and anEntry is the entry with key; otherwise returns false

    void printSorted(ostream& outStream);
    // Postconditions: has printed contents of the dictionary in order

private:
    bool isActive(int index);
    // checks if the HashEntry at index is Active or not

    int findPosition(const string& word);
    // finds an availible index for word

    unsigned int hash(const string& key);
    // basic hashing function for strings

    void rehash();
    // creates a new array of increased capacity and rehashes all previous HashEntries

    void copyDict(const Dictionary& orig);
    // copies the contents of orig to this dictionary

    void deleteDict();
    // properly frees all memory occupied by this dictionary
};

#endif