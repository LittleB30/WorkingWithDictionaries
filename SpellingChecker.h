// Alex Smith
// This is a file for a spelling checker that uses a dictionary class to suggest corrections 
// to misspelled words in a given text file.

#ifndef SPELLINGCHECKER_H
#define SPELLINGCHECKER_H

#include "Dictionary.h"

class SpellingChecker {
private:
    Dictionary dictionary;

public:
    /*----Constructors----*/
    SpellingChecker();
    SpellingChecker(const SpellingChecker& orig);
    
    /*-----Destructor-----*/
    virtual ~SpellingChecker();

    /*-----Operators-----*/
    SpellingChecker& operator=(const SpellingChecker& orig);
    
    /*------Methods------*/
    void checkSpelling();
    // Checks the spelling of the words in a file supplied by the user

private:
    void fillDictionary();
    // Fills the dictionary with words that are correctly spelled

    void checkLine(string& line, int& lineNum); 
    // Checks the spelling of words in a single line
};

#endif