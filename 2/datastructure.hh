// Definition of Datastructure class for UDS/Tiraka homework 2 trie.
//
/*Name. Apurva Nandan Student No. 238766
This file is used for defining the datastructure class and providing method signatures for its public interface functions, that we need to implement.
Also,We have added our own member functions and variables on the private side for implementing the trie effectively.
Also we have added a struct for constructing the node of the trie. All the implementation is being done in the datastructure.cc file
*/

#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#include <iostream>
#include <string>
// SEPARATOR is recommended to use when printing contents of the data
// structure
const char SEPARATOR = ' ';
 

 

class Datastructure
{

 public:

   Datastructure();

   ~Datastructure();

   // Returns true if word was added and false otherwise.
   bool add(std::string& word);

   // Returns true if word was removed and false otherwise.
   bool remove(std::string& word);

   // Returns true if word was found and false otherwise.
   bool search(std::string& word);

   // Solves and returns amount of words in datastructure.
   unsigned int amountOfWords();

   // Empties the datastructure.
   void empty();

   // Prints contents of the data structure.
   void print();
 
private:
   // Copy constructor is forbidden
   Datastructure(const Datastructure&);
   // Assignment operator is forbidden
   Datastructure& operator=(const Datastructure&);
   // Students implementation comes here
   struct TrieNode
	{
		char value;             // the character value (a-z)
		bool isWord;               // indicates whether the node completes a word
		TrieNode* childNodes[26];    // represents the 26 letters of the alphabet system as child nodes
		TrieNode(char init_value)
		{
		isWord = false;
		this->value = init_value; //initialize the value of the node with the given initial value
		
		// Initialize all the child nodes with NULL value
		for (unsigned int i = 0; i < 26; ++i)
			{
				childNodes[i] = NULL;
			}
		}
	};
	
   TrieNode * root; //Declare the root of the trie, which should be the topmost point in the tree and rest will be child nodes

   unsigned int wordcount; //variable to store the word count
   void recursivePrint(TrieNode* curr_node, std::string& prefix); //prints the results recursively by traversing the trie
   void recursiveDelete(TrieNode* curr_node); //for delete also we need to traverse the trie and keep on deleting on the way
};

#endif
