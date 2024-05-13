/*
 * MyADTTestDriver.cpp
 *
 * Description: Test Driver for MyADT class
 * 
 * Author: Kyle Wong
 * Created on: January 27th, 2024
 * 
 */

#include <iostream>
#include <iostream>
#include "Profile.h"
#include "MyADT.h"
#define MAX_ELEMENTS 5

using std::endl;
using std::cout;

int main(){

    // Test 1 - Default Constructor 
    cout << endl << "---------- TESTING CONSTRUCTOR ----------" << endl;

    MyADT * testOBJ = new MyADT();
    cout << "Element count of test object : " << testOBJ->getElementCount() << endl;



    // Test 2 - Insert
    cout << endl << "---------- TESTING INSERT ----------" << endl;

    cout << "\nPrinting array before insertion: \n" << endl;
    testOBJ->print();

    Profile usersA[] = {Profile("alex"), Profile("aaron"), Profile("aura"), Profile("abe"), Profile("amer")};
    Profile usersB[] = {Profile("bob"), Profile("beans"), Profile("bogota"), Profile("bear"), Profile("blick")};
    Profile usersC[] = {Profile("carmen"), Profile("claire"),Profile("chloe"),Profile("cham"),Profile("connor")};

    for(unsigned int i = 0 ; i < MAX_ELEMENTS ; i++){

        if (!testOBJ->insert(usersA[i])){

            cout << "Insert function failed " << endl;

        }

        if (!testOBJ->insert(usersB[i])){

            cout << "Insert function failed " << endl;

        }

        if (!testOBJ->insert(usersC[i])){

            cout << "Insert function failed " << endl;

        }

    }

    cout << "\nPrinting array after insertion: \n" << endl;
    testOBJ->print();

    cout << "Inserting an element into a full array: " << endl;
    Profile moreProfiles[] = {Profile("amy"), Profile("black"), Profile("cate"), Profile("joe"), Profile("sib")};
        
    for(unsigned int i = 0; i < 5; i++){

        if(!testOBJ->insert(moreProfiles[i])){
                
        } 
        else {
            cout << "Additional insert failed" << endl;
        }
    }
    


    //Test 3 - Remove 
    cout << "\n---------- TESTING REMOVE ----------" << endl;

    cout << "Element count before remove function: " << testOBJ->getElementCount() << endl;
    cout << "\nPrinting array before remove function: \n" << endl;
    testOBJ->print();

    if(!testOBJ->remove(Profile("abe"))){
            cout << "Remove failed" << endl;
        }
        else {
            cout << "\nElement count after remove function: " << testOBJ->getElementCount() << endl;
        }

    cout << "\nPrinting array after remove function: \n" << endl;
    testOBJ->print();



    //Test 4 - Search 
    cout << endl << "---------- TESTING SEARCH ----------" << endl;
    
    cout << "Searching for a username in the array: " << endl;
    Profile * removeTest = nullptr;
    removeTest = testOBJ->search(Profile("aaron"));
    if(removeTest == nullptr){
        cout << "Search function failed" << endl;
    } 
    else {
        cout << removeTest->getUserName();
    }
 


    //Test 5 - Copy Constructor 
    cout << endl << "---------- TESTING CONSTRUCTOR ----------" << endl;

    cout << "Element count of original object: " << testOBJ->getElementCount() << endl;
    cout << "\nPrinting original array: \n" << endl; 
    testOBJ->print();
    
    MyADT * testCopyOBJ = new MyADT(*testOBJ);

    cout << "\nElement count of new copy constructor object: " << testCopyOBJ->getElementCount() << endl;
    cout << "\nPrinting new copy constructor object: \n" << endl;
    testCopyOBJ->print();

    if (testOBJ->getElementCount() == testCopyOBJ->getElementCount()){
        cout << "\nCopy success\n" << endl;
    }
    else{
        cout << "Copy failed\n" << endl;
    }

    delete testCopyOBJ;
    delete testOBJ;
    testCopyOBJ = nullptr;
    testOBJ = nullptr;
    
}

