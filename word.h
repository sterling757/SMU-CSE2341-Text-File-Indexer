#ifndef Word_H
#define Word_H

#include "readinandparse.h"
#include<fstream>
#include <iostream>
#include "dsstring.h"
#include "dsvector.h"
#include "word.h"

class Word
{
public:

    //default constructor
    Word();

    //constructor that sets and adds items
    Word(dsString str, int pgNum);

    //adds page to vector
    void addPage(int pageNum);

    //returns word
    dsString getWord();

    //returns the pages
    const dsVector<int>& getPageNums();

    //sorts pages from low to high
    void sortPages();

private:

    //word string
    dsString w;

    //int vector holding the page nums
    dsVector<int> pages;
};

#endif // GETPAGENUMS_H
