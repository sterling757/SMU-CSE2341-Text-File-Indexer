#ifndef READINANDPARSE_H
#define READINANDPARSE_H
#include <iostream>
#include "word.h"
#include "dsvector.h"
#include "dsstring.h"
class readInAndParse
{
private:

    //private vector of Word class
    dsVector<Word*> indexOfWords;
    int lineCount;

    //sorts the vector alphabetically
    void alphabetSort(dsVector<Word*>&);

public:

    //default constructor
    readInAndParse();

    //reads input from argvs
    void readInput(char* input_file, char* outpath);
    ~readInAndParse();


};

#endif // READINANDPARSE_H
