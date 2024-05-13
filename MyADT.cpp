/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 * 
 * Class Invariant: Data collection with the following characteristics:
 *                  - This is a value-oriented data collection and 
 *                    the elements are kept in ascending sort order of search key.
 *                  - Each element is unique (no duplicates). 
 *                  - Its data structure (CDT) is not expandable. This signifies that 
 *                    when this data collection becomes full, you do not have to resize 
 *                    its data structure (not in this Assignment 1). 
 *
 * Author: AL and <Kyle Wong>
 * Last modified on: Jan.31, 2024
 */


#include <iostream>
#include <cctype>
#include "MyADT.h"     // Header file of MyADT file
#include "Profile.h"   // Header file of Profile class

using std::cout;
using std::endl;
using std::cin;

    
// Default constructor. 
MyADT::MyADT() {

   for (unsigned int i = 0 ; i < MyADT::MAX_ALPHA ; i++){

      elements[i] = new Profile[MyADT::MAX_ELEMENTS]; // Creating new profile arrays for element
      elementCount[i] = 0; // Set elementCount = 0 for each array 

   }
   
}  

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   
   for (unsigned int i = 0 ; i < MyADT::MAX_ALPHA ; i++){

      elements[i] = new Profile[MyADT::MAX_ELEMENTS]; // Creating new profile arrays for element 
      elementCount[i] = rhs.elementCount[i]; // Copying elementCount 

      for(unsigned int j = 0; j < MyADT::MAX_ELEMENTS ; j++){

         elements[i][j] = rhs.elements[i][j]; // Deep copy elements 

      }

   }

}  

// Overloaded assignment operator - Covered in Lab 5
// Therefore, we shall not be overloading this operator in our Assignment 1
// MyADT & MyADT::operator=(const MyADT& rhs) {
   // cout << "MyADT::operator= executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this overloaded assignment = operator is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
   
   /* Put your code here */

//}
    
// Destructor
// Description: Destroys this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   
   for (unsigned int i = 0 ; i < MyADT::MAX_ALPHA ; i++){

      for (unsigned int j = 0 ; j < MyADT::MAX_ELEMENTS; j++){

         delete[] elements[i]; // Deleting memory allocated on the heap 
         elements[i] = nullptr; // Setting memory to null

      }
      elementCount[i] = 0;

   }
   
   
}  


// Description: Returns the total number of elements currently stored in the data collection MyADT.  
unsigned int MyADT::getElementCount() const {

   unsigned int countTotal = 0;
   for(unsigned int i = 0 ; i < MAX_ALPHA ; i++){

      countTotal += elementCount[i]; // Storing values of elementCount into countTotal

   }

   return countTotal; // Returns # of elementCounts

}


// Description: Inserts an element in the data collection MyADT.
// Precondition: newElement must not already be in the data collection MyADT.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
//                Returns "true" when the insertion is successfull, otherwise "false".
bool MyADT::insert(const Profile& newElement) {
 
   unsigned int indexLetter;
   char Alower = 'a';
   char firstLetter;
   firstLetter = newElement.getSearchKey(); // Assigning the first (lowercase) letter of userName to a firstLetter
   indexLetter = firstLetter - Alower; // Subtracting lowercase 'a' from firstLetter to acquire correct array index for userName

   if (elementCount[indexLetter] == MAX_ELEMENTS){ // Checking if the array is full
      cout << "The array is full, insertion failed" << endl; 
      return false; 
   }

   for (unsigned int i = 0 ; i < elementCount[indexLetter] ; i++){

      if (elements[indexLetter][i] == newElement){ // Checking through elements for userName

         cout << "Username has already been taken" << endl;
         return false; 

      } 
      else {

         cout << "Username available, insertion success" << endl;
         break;

      }

   }

   // If array is empty, insert newElement at the first index and increment elementCount
   if(elementCount[indexLetter] == 0) {

      elements[indexLetter][0] = newElement;
      this->elementCount[indexLetter] += 1;
      return true;

   } 
   // If the array is not empty, compare elements 
   else if (elementCount[indexLetter] != 0){
       
      for (unsigned int i = 0; i < MAX_ELEMENTS; i++){

         if(elements[indexLetter][i] > newElement){
            
            unsigned int j = (elementCount[indexLetter]); // Set j = elementCount
            
            while(j > i){

               elements[indexLetter][j] = elements[indexLetter][j-1]; // Shift element positions
               j--; // Shift until element is in correct position 

            }

            elements[indexLetter][i] = newElement;
            this->elementCount[indexLetter] += 1;
            return true;

         } 
         // If index is equal to elementCount
         else if(i == (elementCount[indexLetter])){
            
            elements[indexLetter][i] = newElement;
            this->elementCount[indexLetter] += 1;
            return true;

         } 
         // If there is only one element inside array 
         else if(i == 0 && elementCount[indexLetter] == 1){
             
            elements[indexLetter][i+1] = newElement;
            this->elementCount[indexLetter] += 1;
            return true;

         } 
         else {
            continue;
         }
      }
   }
   return false; 
}  

// Description: Removes an element from the data collection MyADT. 
// Postcondition: toBeRemoved (if found) is removed and the appropriate elementCount is decremented.
//                Returns "true" when the removal is successfull, otherwise "false".  
bool MyADT::remove(const Profile& toBeRemoved) {

   unsigned int indexLetter;
   char Alower = 'a';
   char firstLetter;
   firstLetter = toBeRemoved.getSearchKey(); // Assigning the first (lowercase) letter of userName to a firstLetter
   indexLetter = firstLetter - Alower; // Subtracting lowercase 'a' from firstLetter to acquire correct array index for userName

   // Looping through the array to find a match for toBeRemoved object 
   for(unsigned int i = 0 ; i < elementCount[indexLetter] ; i++){

      if (elements[indexLetter][i] == toBeRemoved){
         
         unsigned int j = i +1; // Setting j to one position after current index

         while(j < elementCount[indexLetter]){

            elements[indexLetter][i] = elements[indexLetter][j];
            i++; 
            j++; 

         }
         // Decrementing elementCount and return true if match is found
         this->elementCount[indexLetter] -= 1; 
         return true;
      
      } 
      else {

         continue; 

      }
   }
   // If no match is found, returns false
   cout << "No matching username to remove" << endl;
   return false;
   
}  


// Description: Removes all elements from the data collection MyADT. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
void MyADT::removeAll() {
   
   // Looping through elements and setting elementCount to 0 for all arrays 
   for (unsigned int i = 0 ; i < MyADT::MAX_ALPHA ; i++){

      this->elementCount[i] = 0;

   }

}   

// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {
    
   unsigned int indexLetter;
   char Alower = 'a';
   char firstLetter; 
   firstLetter = target.getSearchKey(); // Assigning the first (lowercase) letter of userName to a firstLetter
   indexLetter = firstLetter - Alower; // Subtracting lowercase 'a' from firstLetter to acquire correct array index for userName

   // Looping through elements until a match for 'target' is found inside array 
   for (unsigned int i = 0; i < elementCount[indexLetter]; i++){

      // If user is found, return the location of the user
      if (elements[indexLetter][i] == target){
         cout << "The requested Username has been found" << endl;
         cout << "Username location: " << &elements[indexLetter][i] << endl;
         return &elements[indexLetter][i]; 
      
      } 
      else {
         continue;
      }
   }
   cout << "The requested Username was not found in our system" << endl;
   return elements[0]; // Returns the first element in the array

}  


// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
void MyADT::print() {
   
   if(this->getElementCount() == 0){

      cout << "FriendsBook Application is empty\n" << endl;

   }

   for(unsigned int i = 0 ; i < MyADT::MAX_ALPHA ; i++){

      if(elements[i] != nullptr && elementCount[i] > 0){

         for(unsigned int j = 0 ; j < elementCount[i] ; j++){

            cout << elements[i][j] << endl; // Loop through the array and print out its elements using operator overload

         }

      }

   } 

} 

//  End of implementation file
