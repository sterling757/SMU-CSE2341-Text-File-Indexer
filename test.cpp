#include "catch.hpp"

#include <cstring>
#include "dsstring.h"
#include "dsvector.h"
#include "DsList.h"
#include "DsStack.h"


TEST_CASE("String", "[string]"){

    dsString s[10];
    s[0] = dsString("testString");
    s[1] = dsString("a test string");
    s[2] = dsString("");
    s[3] = dsString("THIS IS AN UPPERCASE STRING");
    s[4] = dsString("this is an uppercase string");
    s[5] = dsString("\n");
    s[6] = dsString("");
    s[7] = dsString("  split  split  split  ");
    s[8] = dsString("                          ");
    s[9] = dsString("testString");

    SECTION("Equality operators"){
        REQUIRE(s[0] == dsString("testString"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Assignment operators"){
        dsString str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = dsString("testString");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = dsString("\n");
        REQUIRE(str == s[5]);
    }

    SECTION("Addition operator"){
        REQUIRE(dsString("testStringtestString") == s[0]+s[9]);
        REQUIRE(s[6] + s[6] == "");
        REQUIRE(s[5] + s[6] == dsString("\n"));
        REQUIRE(s[0] + s[1] + s[2] == "testStringa test string");
    }

    SECTION("Greater than operator"){
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("[] Operator"){
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[9][-1] == 'g');
        REQUIRE(s[3][-3] == 'I');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
    }

    SECTION("Size function"){
        REQUIRE(s[9].size() == 10);
        REQUIRE(s[2].size() == 0);
        REQUIRE(s[8].size() == 26);
        REQUIRE(s[3].size() == 27);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].substring(0, 5) == "testS");
        REQUIRE(s[1].substring(-6, -1) == "tring");
        REQUIRE(s[9].substring(0, -3) == "testStri");
        REQUIRE(s[9].substring(0, -1) == s[9]);
        REQUIRE(s[4].substring(0, 4) == "this");
    }

    SECTION("c_str function"){
        REQUIRE(strcmp(s[0].c_str(), "testString") == 0);
        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        REQUIRE(strcmp(s[2].c_str(), "") == 0);
    }

}

TEST_CASE("Vector class", "[Vector]")
{
    dsVector<int> vec;
    for(int i = 0; i < 50; i++)
        vec.push_back(i);

    SECTION("Accessors")
    {
        REQUIRE(vec[0] == 0);
        REQUIRE(vec.at(10) == 10);
    }


    SECTION("Constructors")
    {
        dsVector<int> testing(vec);
        for(int i = 0; i < testing.size(); i++)
        {
            REQUIRE(vec.at(i) == testing[i]);
        }
    }

    SECTION("Removal Functions")
    {
        int v = vec.size();
        for(int i = 0; i < v; i++)
        {
            vec.pop_back();
        }
        REQUIRE(vec.empty() == true);

        for(int i = 0; i < 10; i++)
            vec.push_back(i);


    }

    SECTION("Size Functions")
    {
        REQUIRE(vec.empty() == false);
        REQUIRE(vec.size() == 50);
        vec.clear();
        REQUIRE(vec.size() == 0);

    }

    SECTION("Adders")
    {
        for(int i = 30; i < 60; i++)
            vec.push_back(i);
        for(int i = 0; i < 60; i++)
        {
            vec.insert(0, 1);
        }
        for(int i = 0; i < 60; i++)
        {
            REQUIRE(vec[i] == 1);
        }
        for(int i = 0; i < vec.size(); i++)
        {
            vec.assign(i, i+10);
        }
        for(int i = 0; i < vec.size(); i++)
        {
            REQUIRE(vec[i] == 10 + i);
        }

    }



}

template<class T>
void aList(DsList<T>& list)
{
    list.clearList();
    for(int i = 0; i < 100; i++)
    {
        list.push_back(i);
    }

}
TEST_CASE("Linked List", "[DsList]")
{
    DsList<int> list;
    aList(list);

    SECTION("Constructors and assignment operators")
    {
        DsList<int> copy = list;
        DsList<int> copy2(list);

        for(int i = 0; i < list.getLength(); i++)
        {
            REQUIRE(list.get(i) == copy.get(i));
            REQUIRE(copy.get(i) == copy2.get(i));


        }
    }

    SECTION("Accessing Elements")
    {
        SECTION("first() - get first element")
        {
            REQUIRE(list.first() == 0);
        }

        SECTION("last() - get last element")
        {
            REQUIRE(list.last() == 99);
        }
        SECTION("'[]' operator - get data at in index by reference")
        {
            for(int i = 0; i < list.getLength(); i++)
            {
                REQUIRE(list[i] == i);
                list[i] = 0;
                REQUIRE(list[i] == 0);
            }
        }
        SECTION("get() - get elements in the middle indexes of the list")
        {
            REQUIRE(list.get(2) == 2);
            REQUIRE(list.get(6) == 6);
            REQUIRE(list.get(99) == 99);
        }
    }

    SECTION("Modifiers")
    {
        SECTION("insert() - adds elements at an index")
        {

            for(int i = 0; i < 3; i++)
            {
                list.insert(0, 3000000);
            }

            REQUIRE(list.get(0) == 3000000);
            REQUIRE(list.get(1) == 3000000);
            REQUIRE(list.get(2) == 3000000);
            REQUIRE(list.get(3) == 0);
        }



        SECTION("push_first - adds elements at the beggining")
        {

            for(int i = 0; i < 3; i++)
            {
                list.push_first(3000000);
            }


            REQUIRE(list.get(0) == 3000000);
            REQUIRE(list.get(1) == 3000000);
            REQUIRE(list.get(2) == 3000000);
            REQUIRE(list.get(3) == 0);

            list.clearList();

            for(int i = 0; i < 15; i++)
            {
                list.push_first(14-i);
            }
            for(int i = 0; i < 15; i++)
            {
                REQUIRE(list[i] == i);
            }
        }


        SECTION("Insert - adding elements at a specified index")
        {

            for(int i = 0; i < 3; i++)
            {
                list.insert(i, 7);
            }


            REQUIRE(list.get(0) == 7);
            REQUIRE(list.get(1) == 7);
            REQUIRE(list.get(2) == 7);
            REQUIRE(list.get(3) == 0);
        }

        SECTION("push_back() - adding elements at the end")
        {

            for(int i = 0; i < 5; i++)
            {
                list.push_back(7);
            }


            REQUIRE(list.get(list.getLength() - 1) == 7);
            REQUIRE(list.get(list.getLength() - 2) == 7);
            REQUIRE(list.get(list.getLength() - 3) == 7);
            REQUIRE(list.get(list.getLength() - 4) == 7);

            list.clearList();;

            for(int i = 0; i < 10; i++)
            {
                list.push_back(i);
            }
            for(int i = 0; i < 10; i++)
            {
                REQUIRE(list[i] == i);
            }
        }

        SECTION("assign - setter for elements")
        {

            for(int i = 0; i < list.getLength(); i++)
            {
                list.assign(i, 10);
            }


            REQUIRE(list.get(10) == 10);
            REQUIRE(list.get(list.getLength() - 1) == 10);
            REQUIRE(list.get(5) == 10);
        }
    }

    SECTION("Removing elements")
    {
        SECTION("removeElement() - removes an element at a given index")
        {
            while(list.getLength() != 100)
                list.removeElement(0);

            REQUIRE(list.get(0) == 0);
            REQUIRE(list.get(1) == 1);
            REQUIRE(list.get(20) == 20);
        }

        SECTION("popFirst() - removal at beginning of list")
        {
            for(int i = 0; i < 10; i++)
                list.popFirst();

            REQUIRE(list.get(0) == 10);
            REQUIRE(list.get(5) == 15);
            REQUIRE(list.get(list.getLength()-1) == 99);
        }

        SECTION("popBack() - removal at end of list")
        {
            for(int i = 0; i < 10; i++)
                list.popBack();

            REQUIRE(list.get(2) == 2);
            REQUIRE(list.get(4) == 4);
            REQUIRE(list.get(6) == 6);
        }

    }

}

TEST_CASE("Stack", "[Stack]")
{

    DsStack<int> stack;

    for(int i = 0; i < 10; i++)
    {
        stack.push(i);
    }

    SECTION("push() - puts elements onto stack")
    {
        for(int i = 0; i < 20; i++)
            stack.push(i);
        REQUIRE(stack.peek() == 19);
        stack.pop();
        REQUIRE(stack.peek() == 18);
    }

    SECTION("pop() - takes off stack")
    {
        int x;
        while(!stack.isEmpty())
        {
            x = stack.pop();
        }
        REQUIRE(x == 0);
    }

    SECTION("peek() - looks at whats at an element in the stack")
    {
        REQUIRE(stack.peek() == 9);
    }

    SECTION("isEmpty() - checks if stack is empty")
    {
        REQUIRE(stack.isEmpty() == false);
        REQUIRE(!stack.isEmpty());
        while(!stack.isEmpty())
            stack.pop();
    }

}
