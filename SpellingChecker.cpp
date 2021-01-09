// Alex Smith
// This is an implementation of the spelling checker file

#include "SpellingChecker.h"
#include "Dictionary.h"                   
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>

const string alpha[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

SpellingChecker::SpellingChecker() {
    fillDictionary();
}

SpellingChecker::SpellingChecker(const SpellingChecker& orig) {
    dictionary = orig.dictionary;
}

SpellingChecker::~SpellingChecker() {}

SpellingChecker& SpellingChecker::operator=(const SpellingChecker& orig) {
    dictionary = orig.dictionary;
    return *this;
}

void formatText(string& text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower); // make lowercase
    for (int i = 0; i < text.length(); i++) { // remove all non letters
        if (!isalpha(text[i])) {
            text.replace(i, 1, " ");
        }
    }
}

void SpellingChecker::checkSpelling() {
    string filePath;
    cout << "Please enter the name of the file to spell check (example.txt): ";
    cin >> filePath;
    cout << endl;

    int lineNum = 0;
    string line;
    ifstream inFile(filePath);
    while (getline(inFile, line)) {
        checkLine(line, lineNum);
    }
    inFile.close();

    if (lineNum == 0) { 
        cout << "No text found\n" << endl;
        checkSpelling();
    } else cout << endl;
}

void SpellingChecker::fillDictionary() {
    string word;
    string part;
    string files[] = {"dict.txt", "mydict.txt"};
    for (string i : files) {
        ifstream inFile(i);
        while (inFile >> word) {
            formatText(word);
            stringstream ss(word);
            while (ss >> part) {
                if (!dictionary.findEntry(part)) {
                    dictionary.addEntry(part);
                }
            }
        }
        inFile.close();
    }
}

bool addIfValid(string& word, Dictionary& dictionary, list<string>& valid) {
    if (!(find(valid.begin(), valid.end(), word) != valid.end()) && dictionary.findEntry(word)) {
        valid.push_back(word);
    }
}

void addLetter(string& word, Dictionary& dictionary, list<string>& valid) {
    string temp;
    for (int i = 0; i < word.length() + 1; ++i) {
        for (string letter : alpha) { 
            temp = word;
            temp.insert(i, letter);
            addIfValid(temp, dictionary, valid);
        }
    }
}

void removeLetter(string& word, Dictionary& dictionary, list<string>& valid) {
    string temp;
    for (int i = 0; i < word.length(); ++i){
        temp = word;
        temp.erase(i, 1);
        addIfValid(temp, dictionary, valid);
    }
}

void replaceLetter(string& word, Dictionary& dictionary, list<string>& valid) {
    string temp;
    for (int i = 0; i < word.length(); ++i) {
        for (string letter : alpha) { 
            temp = word;
            temp.replace(i, 1, letter);
            addIfValid(temp, dictionary, valid);
        }
    }
}

void swapLetters(string& word, Dictionary& dictionary, list<string>& valid) {
    string temp;
    for (int indexOne = 0, gap = 1; indexOne+gap < word.length(); indexOne = 0, ++gap) {
        for (int indexTwo = indexOne+gap; indexTwo < word.length(); ++indexTwo, ++indexOne) {
            temp = word;
            swap(temp[indexOne], temp[indexTwo]);
            addIfValid(temp, dictionary, valid);
        }
    }
}

void printAlternatives(string& word, list<string>& valid, int& lineNum) {
    int offset = 2;
    if (lineNum < 10) offset += 1;
    else if (lineNum < 100) offset += 2;
    else if (lineNum < 1000) offset += 3;
    else offset += 4;
    
    cout << lineNum << "- " << word;

    if (word.length() + offset < 8) cout << "\t\t\t";
    else if (word.length() + offset < 16) cout << "\t\t";
    else cout << "\t";
    if (valid.size() > 0) {
        cout << "(";
        int count = 0;
        for (string temp2 : valid) {
            cout << temp2 << ", ";
            ++count;
            if (count % 10 == 0 && temp2 != valid.back()) {
                cout << "\n\t\t\t ";
            }
        }
        cout << "\b\b)" << endl;
    } else {
        cout << "(No suggestions found)" << endl;
    }
}

void findAlternatives(string& word, int& lineNum, Dictionary& dictionary) {
    string temp;
    list<string> valid;

    addLetter(word, dictionary, valid);
    removeLetter(word, dictionary, valid);
    replaceLetter(word, dictionary, valid);
    swapLetters(word, dictionary, valid);

    printAlternatives(word, valid, lineNum);
}

void SpellingChecker::checkLine(string& line, int& lineNum) {
    formatText(line);
    ++lineNum;

    string word;
    stringstream ss(line);
    while (ss >> word) {
        if (!dictionary.findEntry(word)) {
            findAlternatives(word, lineNum, dictionary);
        }
    }
}

