// Definition of Datastructure class for UDS/Tiraka homework 2 -
// Family tree.

/*Name. Apurva Nandan Student No. 238766
This file is used for defining the datastructure class and providing method signatures for its public interface functions, that we need to implement.
Also,We have added our own member functions and variables on the private side for implementing the familytree effectively.
The person struct was constructed by us to store the main data about a person and implement it using a graph representation
Also we have added a struct for sorting purposes only. All the implementation is being done in the datastructure.cc file
*/

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <unordered_map>

#include <set>
#include <stack>
#include <queue>
#include <array>

#ifndef  DATASTRUCTURE_HH
#define  DATASTRUCTURE_HH

enum Gender { MALE, FEMALE };

enum Relation {INVALID_ID, RELATED, NOT_RELATED };

class Datastructure {
   
 public:
   
    Datastructure();
    ~Datastructure();
    
    // adds a new person
    bool add(Gender gender, std::string& name, int ID, int born, 
	     int died);
   
    //Adds ID1 and ID2 as partners
    bool addPartner(int ID1, int ID2);
    
    //Adds a child to the given people
    bool addChild(int IDChild, int IDwoman, int IDman);
    
    //Checks if the two people are related
    Relation relation(int ID1, int ID2);
   
    //Empties the data structure
    void remove();
   
    //Prints the family tree
    void print(int ID);

private:
   
 
 struct Person; //Define the person struct
 
 
 //The struct which will be used only for sorting purpose, it overrides the operator function and will be passed in a set 
  struct bornsort
{
    bool operator() (const Person* struct1, const Person* struct2)
    {
        return (struct1->born >= struct2->born);
    }
};
 
 //Declare the person struct
	struct Person
    {
	   
		Gender gender; //Gender
	    int ID; //Unique ID
		std::string name; //Name of the person
		int born; //Birth date
		int died; //Died
		
		
		bool hasParents; //To check if the person has parents
		std::set<Person*,bornsort> childrens;	//Set with sorting based on birth for children
		std::array<Person*,2> parents; //Fixed sized array for parents because they will be 2 , and this improves readiblity to the user
		std::unordered_map <int,Person*> spouses; //For searching the spouses in constant time
		std::vector<Person*> spouses_vec; //Spouse vector to maintain the order, I could have used a map but it has more time complexibity, hence used two data structures
		
		Person* pie; //Information on the root node from where the breadth first search has begun
		
		std::vector<bool> isSpouse; //The information weather the given node will be processed normally or like a spouse everytime it is pushed into a stack
		std::vector<int> level; //The level of the node in the depth first search, everytime a node will be pushed into the stack normally, as spouse or as children
       
	   
    };
   
   
   typedef std::unordered_map <int,Person*> graph; //Create a typedef of unordered_map to store the information on persons
   graph familytree; //familytree is the map which will be used centrally across all functions to search for persons
  
   std::string fillSpaces(int); // The helper function to generate the amount of spaces according to a given level
};

#endif

