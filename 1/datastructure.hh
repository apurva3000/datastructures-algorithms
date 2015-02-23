// Definition of Datastructure class for UDS/Tiraka homework 1 -

/*Name. Apurva Nandan Student No. 238766
This file is used for defining the datastructure class and providing method signatures for its public interface functions, that we need to implement.
Also, We have added our own member functions on the private side for implementing the sorting algorithms and other helper functions.
All the implementation is being done in the datastructure.cc file
*/

#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

const char SEPARATOR = ' ';
const std::string MSG_EMPTY_DS = "Data structure is empty.\n";

class Datastructure {

public:

   Datastructure();

   ~Datastructure();

   // Adds one value to the datastructure
   void add(std::string rank, unsigned int birthYear, unsigned int enlistingYear, std::string shirtColor, std::string name);

   // Finds and prints person with index
   void find(unsigned int index);

   // Finds and prints youngest person
   void youngest();

   // Finds and prints oldest person
   void oldest();

   // Empties the datastructure
   void empty();

   // returns the size of the datastructure
   size_t size();


private:

    //The struct to store the information about a person with all the necessary fields
    typedef struct
    {
        unsigned int birthYear;
        unsigned int enlistingYear;
        std::string rank;
        std::string shirtColor;
        std::string name;
    }Person;

    // The vector to store all the elements
    std::vector <Person*> personVect;
    //The main merge sort function
    void merge_sort(std::vector<Person*>& input, unsigned int first, unsigned int last);
    // The helper function to merge_sort function for comarison and merging the parts
    void merge(std::vector<Person*>& input, unsigned int first, unsigned int mid, unsigned int last);

    // THe function for printing the information related to a particular person
    void print(Person* p);

    // The boolean variable to check if the array is sorted or not
    bool sorted;

   // Copy constructor is forbidden
   Datastructure(const Datastructure&);
   // Assignment operator is forbidden
   Datastructure& operator=(const Datastructure&);
};



#endif
