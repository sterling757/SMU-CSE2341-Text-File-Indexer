#include "readinandparse.h"
#include<fstream>
#include <iostream>
#include "word.h"
#include <algorithm>
#include <cstring>

readInAndParse::readInAndParse()
{
//default
}

//reads in dictionary file from argv[1]
void readInAndParse::readInput(char* input_file, char* outpath){

    ifstream inFile(input_file);

    //checks if dictFile isnt opening
    if (!inFile)
        cout <<"Houston we have a problem!!!!!!!!!!!" << endl;

    //can use index[0].w to call the variable or whatever in getPageNums
    char buffer[80];
    int pageNum;
    dsString word;

    //while the file isnt at the end
    while(!inFile.eof()){

        inFile.getline(buffer, 80);

        dsString line(buffer);

        // is page number
        if(line[0] == '<' && line[-1] == '>') {

            //converts string pageNum to int pageNum
            pageNum = atoi(line.substring(1,-1).c_str());

            // end of file
            if(pageNum == -1)
               break;

        }

        else{
            int start = 0;
            bool brackets = false;

            //for loop for parsing words line by line
            for(int i = 0; i < line.size(); i++){

                //loops until end of word is found
                if((!brackets && line[i] == ' ') || (brackets && line[i] == ']')
                        || (line[i+1] == '\0')) {

                    //removes punctuation
                    if(line[i-1] == '.' || line[i-1] == '!' || line[i-1] == '?' ||
                            line[i-1] == ',' || line[i-1] == '-'){

                        line[i-1] = line[i];
                    }
                    //handles random spaces between words
                    while(line[i] == ' ' && line[i+1] == ' '){

                      if(line[i] == ' ' && line[i+1] == ' '){
                          i++;
                      }

                    }
                    //handles whitespace caused by tabs
                    if(line[start] == '\t'){
                        start++;
                    }

                    //handles the end of the line
                    if(line[i+1] == '\0'){
                        i++;
                    }

                    //handles if the line starts with an opening bracket
                    if(line[start] == '['){
                        brackets = true;
                        start++;

                        //increments i until end bracket is found
                        while(line[i] != ']'){
                            i++;
                        }

                    }


                    //handles if the line ends with a closing bracket
                    if(line[i-1] == ']' && line[i] == '\0'){
                        i--;
                    }

                     //creates a word from a substring
                     word = line.substring(start, i);

                     //makes all words lowercase
                     word.toLower(word);


                     // cout << word << " - " << pageNum << endl;
                     bool isAlreadyAWord = false;

                     //puts each word into indexOfWords vector
                     for(int j = 0; j< indexOfWords.size(); j++){

                         if(indexOfWords[j]->getWord() == word){

                         isAlreadyAWord = true;


                         indexOfWords[j]->addPage(pageNum);

                         break;


                         }
                     }
                    if(isAlreadyAWord == false){

                    Word* indexWord = new Word(word, pageNum);

                    //adds words and page nums to vector
                    indexOfWords.push_back(indexWord);

                    }


                    start = i + 1;

                    //handles the opening bracket
                    if(line[start] == '['){
                        start++;
                        brackets = true;
                    }

                    //pushes the indexes up by one after closing bracket
                    else if(line[start-1] == ']'){
                        brackets = false;
                        start++;
                        i++;
                    }


                }

            }
        }

    }

    //makes ostream to output.txt
    ofstream theIndex(outpath);
    alphabetSort(indexOfWords);
    char c = ' ';
    /* this block prints to output file
    */
    for(int i = 0; i < indexOfWords.size(); i++){
        //handles the letter in brackets
        if(!(c == indexOfWords[i]->getWord().c_str()[0])){

            c = indexOfWords[i]->getWord().c_str()[0];
            theIndex << "[" << (char) toupper(c) << "]" << endl;

        }
        //prints out word
        theIndex << indexOfWords[i]->getWord() <<": ";
        //prints sorted page nums
        for(int j =0; j<indexOfWords[i]->getPageNums().size(); j++){

            if(j<indexOfWords[i]->getPageNums().size()-1){

                theIndex << indexOfWords[i]->getPageNums().at(j) << ", ";
            }
            else{
                theIndex << indexOfWords[i]->getPageNums().at(j) << endl;
            }
        }
    }

 }


/* sorts alphabetically
~sorts the vector alphabetically
*/
void readInAndParse::alphabetSort(dsVector<Word*>& vec){
    for(int i = 0; i < vec.size()-1; i++){

        for(int j = i; j < vec.size(); j++){

          if((vec[i]->getWord()) > (vec[j]->getWord())){

            swap(vec.at(i),vec.at(j));

          }
        }
      }
}
readInAndParse::~readInAndParse(){
    for ( int i = 0; i < indexOfWords.size(); i++)
    {
        delete indexOfWords[i];
    }
}


