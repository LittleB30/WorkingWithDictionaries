// Alex Smith
// This is an implementation of the Dictionary file

#include "Dictionary.h"
#include <fstream>

/*----Constructors----*/
void fillPrimes(vector<int>& primes) {
    int temp;
    ifstream inFile("primesThrough3Mil.txt");
    while (inFile >> temp) {
        primes.push_back(temp);
    }
    inFile.close();
}

Dictionary::Dictionary() {
    fillPrimes(primes);
    curPrimeIndex = 26 - 1; //101
    array.size = 0;
    array.capacity = primes[curPrimeIndex];
    array.arr = new HashEntry[array.capacity];
}

Dictionary::Dictionary(const Dictionary& orig) {
    copyDict(orig);
}

/*-----Destructor-----*/
Dictionary::~Dictionary() {
    deleteDict();
}

/*-----Operators-----*/
Dictionary& Dictionary::operator=(const Dictionary& orig) {
    if (this != &orig) {
        deleteDict();
        copyDict(orig);
    }
    return *this;
}

/*------Methods------*/
void Dictionary::addEntry(string anEntry) {
    int curPostion = findPosition(anEntry);
    if (!isActive(curPostion)) {
        array.arr[curPostion].word = anEntry;
        array.arr[curPostion].status = Active;

        if (++array.size > array.capacity / 2) rehash();
    }
}

bool Dictionary::findEntry(string key) {
    return isActive(findPosition(key));
}

void Dictionary::printSorted(ostream& outStream) {
    for (int i = 0; i < array.capacity; ++i) {
        if (array.arr[i].status == Active) outStream << array.arr[i].word << endl;
    }
}

bool Dictionary::isActive(int index) {
    return array.arr[index].status == Active;
}

int Dictionary::findPosition(const string& word) {
    int curPosition = hash(word);
    for (int offset = 1; array.arr[curPosition].status != Empty && array.arr[curPosition].word != word; curPosition %= array.capacity) {
        curPosition += offset;
        offset += 2;
    }
    return curPosition;
}

unsigned int Dictionary::hash(const string& key) {
    unsigned int hashVal = 0;
    for (char ch : key) hashVal = 37 * hashVal + ch;
    return hashVal % array.capacity;
}

int getNextCapacity(vector<int>& array, int& index) {
    int startIndex = index;
    while (array[index++] < array[startIndex] * 2);
    return array[index];
}

void Dictionary::rehash() {
    int prevCapacity = array.capacity;
    array.capacity = getNextCapacity(primes, curPrimeIndex);
    HashEntry* temp = array.arr;
    array.arr = new HashEntry[array.capacity];
    for (int i = 0; i < prevCapacity; ++i) {
        if (temp[i].status == Active) {
            addEntry(temp[i].word);
        }
    }
    delete[] temp;
}

void Dictionary::copyDict(const Dictionary& orig) {
    array.size = orig.array.size;
    array.capacity = orig.array.capacity;
    HashEntry* temp = new HashEntry[array.capacity];
    for (int i = 0; i < array.size; i++) {
        temp[i] = array.arr[i];
    }
    array.arr = temp;
}

void Dictionary::deleteDict() {
    delete[] array.arr;
}