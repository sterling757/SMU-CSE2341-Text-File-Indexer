#include "readinandparse.h"
#include<fstream>
#include <iostream>
#include "../../lib/dsstring.h"
#include "../../lib/dsvector.h"
#include "word.h"
#include <stdio.h>
#include <stdlib.h>

Word::Word(){
//default
}

/*
Constructor
~~Makes word values
*/
Word::Word(dsString str, int pgNum){

    w = str;
    pages.push_back(pgNum);

}

/*
addPage function
~~adds a page to the pages vector
*/
void Word::addPage(int pageNum){

    for(int i = 0; i < pages.size(); i++){

        if(pages[i] == pageNum){

            return;

        }
    }
    //adds the page to the vector
    pages.push_back(pageNum);
}

/*
getWord function
~~returns the given word
*/
dsString Word::getWord(){
    return w;
}


/*
sortPages function
~~sorts the pages in accending numerical order
*/
void Word::sortPages(){
    for (int i = 0; i < pages.size(); ++i){

            for (int j = 0; j < pages.size()-i-1; ++j){

                // Comparing consecutive data and switching values if value at j > j+1.
                if (pages[j] > pages[j+1]){

                    pages[j] = pages[j]+pages[j+1];
                    pages[j+1] = pages[j]-pages[j + 1];
                    pages[j] = pages[j]-pages[j + 1];

                }
            }
            // Value at n-i-1 will be maximum of all the values below this index.
        }
}

/*
getPageNums function
~~returns the page numbers in the vector
*/
const dsVector<int>& Word::getPageNums(){

        //sorts the page numebrs numerically
        sortPages();

        return pages;
}

