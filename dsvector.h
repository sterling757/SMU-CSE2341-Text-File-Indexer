#ifndef DSVECTOR_H
#define DSVECTOR_H
#include "../../lib/dsstring.h"
#include <iostream>
#include <fstream>
#include <cstring>

template <class T>
class dsVector
{
public:

    /*
     The constructors
    */

    dsVector(); //default constructor
    dsVector(const dsVector<T>&); //Copy constructor
    dsVector(int);

    /*
     The overloaded operators
    */

    dsVector& operator= (const dsVector<T>&);
    T& operator[] (int position) const;

    //overloads stream insertion operator ("<<")
    template <typename J>
    friend std::ostream& operator<< (std::ostream&, const dsVector<J>&);

    /*
    vector class functions
    */

    //gets a character at an index
    T& at(int index) const;

    //sorts a vector alphabetically
    void sort();

    //adds values to vector
    void push_back(const T& thingToInsert);

    //returns size of the vector
    int size()const;

    //returns true if the vector is empty
    bool empty() const;

    //deletes all elements from the vector
    void clear();

    //removes the value at the last index of the array
    void pop_back();

    //inserts an element at a position
    void insert(int position, const T& thingToInsert);

    //assigns elements to the vector
    void assign(int position, const T& thingToInsert);

    //destructor for the vector class
    ~dsVector();

private:
    //templated array
    T* array;

    //length of the array
    int length;

    //size of ther array
    int arrSize;

    //checks if in bonunds
    bool isInBounds(int position) const;

    //resizes the vector
    void resize(int newSize);
};

//START OF THE CUSTOM VECTOR DATA STRUCTURE

/*
a function to change the size of a vector, used in pop_back
*/
template <class T>
void dsVector<T>::resize(int newSize){

    //makes a bigger array for storage
    T* biggerArray = new T[newSize];

    //for loop to put contents of old array into bigger array
    for(int i = 0; i < length; i++){
        biggerArray[i] = array[i];
    }

    //deleting old array
    delete [] array;

    array = biggerArray;
    arrSize = newSize;
}

/*
A class to check whether the index entered is inbounds
~~error checking
*/
template <class T>
bool dsVector<T>::isInBounds(int position) const{

    if(position >= 0 && position < length){
        return true;
    }
    else{
        cerr << "THIS VECTOR INDEX ENTERED IS OUT OF BOUNDS!" << endl;
    }
    return false;
}

/*
Default Constructor
~~Initializes Variables to 0
*/
template <class T>
dsVector<T>::dsVector(){

    length = 0;
    arrSize = 0; //capacity
    array = new T[arrSize];
}

/*
Constructor
~~Initializes vector
*/
template <class T>
dsVector<T>::dsVector(int cap){

    arrSize = cap;
    T* array = new T[arrSize];
    length = 0;
}

/*
Copy Constructor
~~copies contents of the vector passed in into an array
*/
template <class T>
dsVector<T>::dsVector(const dsVector<T>& vec){

    length = vec.length;
    arrSize = vec.arrSize;
    array = new T[arrSize];

    for(int i = 0; i < length; i++){
        array[i] = vec[i];
    }
}

/*
at function
~~gets a char at a specific index
*/
template<class T>
T& dsVector<T>::at(int pos) const{

    isInBounds(pos);
    return array[pos];
}

/*
 overloads extraction operator ('<<')
*/
template <class T>
std::ostream& operator << (std::ostream& output, const dsVector<T>& vec){

     for(int i = 0; i < vec.size(); i++){
         output << vec[i] << " ";
     }

     output << endl;
     //returns contents of the string
     return output;
 }

/*
overloads = operator
*/
template<class T>
dsVector<T>& dsVector<T>::operator=(const dsVector<T>& inputVector){

    // deallocates array to prevent memory leaks
    delete [] array;
    length = inputVector.length;
    arrSize = inputVector.arrSize;
    T array = new T[arrSize];

    for(int i = 0; i < inputVector.size(); i++){
         //puts contents of list vector into array
        array[i] = inputVector[i];
    }

    return *this;
}

/*
overloads [] operator
*/
template<class T>
T& dsVector<T>::operator[](int position) const{

    isInBounds(position);
    return array[position];
}

/*
Push_Back function
~~inserts an element into a vector if it full
*/
template<class T>
void dsVector<T>::push_back(const T& thingToInsert){

    if(length == arrSize){
        resize(arrSize += 15);
    }

    array[length] = thingToInsert;
    length++;
}

/*
Size function
~~returns the size of the vector
*/
template <class T>
int dsVector<T>::size()const{

    return length;
}

/*
Empty function
~~checks if there is nothing in the vector
*/
template <class T>
bool dsVector<T>::empty()const{

    return length == 0;
}

/*
clear function
~~clears the contents the vector
*/
template <class T>
void dsVector<T>::clear(){

    length = 0;
    resize(0);
}

/*
pop_back function
~~removes an item at a specific index
*/
template <class T>
void dsVector<T>::pop_back(){

    if(length == 0){
        cerr << "YOUR ARRAY HAS NOTHING IN IT! NOTHING TO POP" << endl;
    }
    length--;
}


/*
insert function
~~inserts something at a specific index into vector
*/
template<class T>
void dsVector<T>::insert(int position, const T& thingToInsert){

    //inserts element into vector
    if(length == position){
        push_back(thingToInsert);
    }
    else{
        isInBounds(position);
        //makes room for element if there is none
        if(length == arrSize){
            resize(arrSize *= 2);
        }
        //shifts elements down to accomodate for insert
        for(int i = length; i >= position + 1; i--){
                   array[i] =array[i-1];
               }
               array[position] = thingToInsert;
       length++;
    }

}

/*
assign function
~~assigns elements to the vector
*/
template<class T>
void dsVector<T>::assign(int position, const T &thingToInsert){

    isInBounds(position);
    array[position] = thingToInsert;
}

template<class T>
void dsVector<T>::sort(){

    //uses int to find index to swap
    int j =0;
    //temp variable
    T t = 0;
    for(int i = 0; i < length; i++)
    {
        //swap data
        for(j = i; j > 0 && array[j-1] > array[j]; j--)
        {
            t = array[j];
            array[j] = array[j-1];
            array[j-1] = t;
        }
    }
}

/*
Destructor
~~deallocates vector array
*/
template<class T>
dsVector<T>::~dsVector(){
    if(array != nullptr)
    {
        delete[] array;
    }
}
#endif // DSVECTOR_H
