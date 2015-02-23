#include "datastructure.hh"
/*Name. Apurva Nandan Student No. 238766
The purpose of this file is to implement the interface functions from datastructure.hh file and also implement our own member functions
There basic operations that we need to do with the trie such as adding a new word in the trie, searching for a word in the trie,
deleting a word from the trie, printing the contents in the trie, returning the amount of words in the trie. 
For this we have make use of efficient techniques and concept of Trie for performing the necessary operations.
This file contains the actual implementation code of all the given interface functions and other necessary functions
*/
 
 
/**
* Constructor method for Datastructure class
*/
Datastructure::Datastructure()
{
   root = NULL;  //initialize the root to null;
   wordcount = 0; //initialize the wordcount to zero
}
 
/**
* Destructor method for Datastructure class
*/
Datastructure::~Datastructure()
{
     if(root!=NULL)		//check if the root is not equal to null, and then empty the trie
         empty();
}
 
 
 /** Adds the given word in the trie by traversing down the trie and adding it to the right position
  * Also increases the word count by by 1 if the word was added successfully 
* @param word reference of the word which needs to be added
* returns 1 if the word was added 
* 0 if the word was already there and hence not added
* **/
 
bool Datastructure::add(std::string& word)
{
	if(root==NULL) //check if the root is not there then initialize it first
		root = new TrieNode(' ');
		
	TrieNode * curr_node = root; //set the current node to root

    for (unsigned int i = 0; i < word.size(); ++i) //start looping for the size of the word
    {
        char curr_char = (char)tolower(word.at(i)); //extract the character of the word one by one
        int index = curr_char - 'a'; //convert the character value into an integer form (index) to use for indexing the childNodes array
		if (curr_node->childNodes[index] != NULL) //check if the node has branch at specified index
        {
            
            curr_node = curr_node->childNodes[index]; //the child node becomes the current node now
        }
        else
        {
            // the current node doesn't have the current character value as one of its decendants
            TrieNode * newNode = new TrieNode(curr_char); //create a new node with the current character value
            curr_node->childNodes[index] = newNode; //set it as a child of the current node we are processing
            curr_node = newNode; //the new node becomes the current node for now and traversing continues
        }
        if (i == word.size() - 1) // check if we are at the last character of the word
        {
            
            if(!curr_node->isWord) //if the current node has no indicator which tells if it was already a word in the trie 
			{
				curr_node->isWord = true; //then set the indicator as true to tell , we have a word at that position
				wordcount = wordcount + 1; // increase the word count in the trie by 1
				return true; //return true indicating the word was not there and hence added
				
			}
			
			
        }
    }
	//if it doesn't return true before this line it means, it wasn't added to the trie and hence return false
	return false;
}

/** Searches for the word in the trie and deletes by setting the property isWord to false
Also reduces the word by 1 if the word was removed successfully
* @param word The word being removed
* returns 1 if the word was removed else 0
* **/

bool Datastructure::remove(std::string& word)
{
    if(root==NULL)
		return false;
	
	TrieNode * curr_node = root; //set the current node as root
    
	for (unsigned int i = 0; i < word.size(); ++i) //start looping for the size of the word
    {
        char curr_char = (char)tolower(word.at(i)); //obtain the character value by lowercasing it and then typecasting it
        int index = curr_char - 'a'; //convert the character value into an integer form (index) to use for indexing the childNodes array
        
        // if the current node has the current character value as one of its decendants
        if (curr_node->childNodes[index] != NULL) //check if the node has branch at specified index
		{
            curr_node = curr_node->childNodes[index]; //the child node becomes the current node now
			
		}
		// the current node doesn't have the current character which means the word is not in the trie
       
		if (i == word.size() - 1 && curr_node->isWord)
            {
				curr_node->isWord = false; //set the indicator to false, signifying we do not have a word at that position
				wordcount = wordcount - 1; //decrease the word count because we removed the word
				return true; //return true because we have successfully removed the word
			}
    }
	//if it does not return true before this line that means, it wasn't there in the trie and hence output false
	return false;
}

/** Searches for the word in the trie using the given word as input
* @param word The word being searched for
* returns 1 if the word if found else 0
* **/

bool Datastructure::search(std::string& word)
{
    if(root==NULL) //if the root is already null then trie is empty , no need for search
		return false;
		
	TrieNode * curr_node = root; //set the current node to root to start from the top of the trie
    for (unsigned int i = 0; i < word.size(); ++i) //start looping for the size of the word
    {
        char curr_char = (char)tolower(word.at(i)); //extract the character of the word one by one
        int index = curr_char - 'a'; //convert the character value into an integer form (index) to use for indexing the childNodes array
       
        // if the current node has the current character as one of its decendants
        if (curr_node->childNodes[index] != NULL) //check if the node has branch at specified index
            curr_node = curr_node->childNodes[index]; //the child node becomes the current node now
        else
            return false; //stop the word is not there
        // makes sure the last node is marked as an end for a word
        if (i == word.size() - 1 && !curr_node->isWord)
            return false; //stop the word is not there
    }
	// if it doesn't return false before this part, it means we have a match and hence return true
    return true;
}


/** Prints the words in the tries in alphabetic order
Makes use of recursion for traversing down the nodes of the trie
 * **/

void Datastructure::print()
{
	if(root!=NULL)
	{
		std::string s = ""; //intialize the base string to empty for now
		recursivePrint(root, s); //call recursive print here
		std::cout << std::endl; //print a newline after printing all the words
	}
}

/** The helper recursive function being used in print() function for printing words in the trie
 @param curr_node the current trie node which we are traversing
 @param prefix the base string which was forwarded and will be appended with further characters
**/
void Datastructure::recursivePrint(TrieNode* curr_node, std::string& prefix)
{
	
    if (curr_node->isWord) //if the node indicates that it is the leaf node marked as a word then print it with a separator
        std::cout << prefix << SEPARATOR;
    for (unsigned int i = 0; i < 26; ++i) //start traversing down the child nodes
    {
        if (curr_node->childNodes[i] != NULL) //check if the node has branch at specified index
        {
            std::string currentString = prefix + curr_node->childNodes[i]->value; //keep adding the character values to the already defined base string
            recursivePrint(curr_node->childNodes[i], currentString); //recursive call to itself by sending whatever string we formed as base string for next level
        }
    }
}


/** Returns the amount of words stored in the trie by returning the variable which is always incremented
 * upon addition of a word **/
unsigned int Datastructure::amountOfWords(){

    return wordcount; //simply return the value which is being updated upon every addition and deletion

}


/** Empties the trie by recursively deleting all the nodes in the trie **/
void Datastructure::empty()
{
	recursiveDelete(root); //recursively traverse and delete the nodes further
	root = NULL; //set the root to null
	wordcount = 0; //set the wordcount to zero
	
}

/** The helper recursive function for deleting the nodes in the trie
@param curr_node the trie node which needs to traversed down further
**/
void Datastructure::recursiveDelete(TrieNode* curr_node)
{
	
    for (unsigned int i = 0; i < 26; ++i) // Traversing according to the 26 alphabets
    {
        if (curr_node->childNodes[i] != NULL) //check if the node has branch at specified index
        {
            TrieNode* branch = curr_node->childNodes[i];
			recursiveDelete(branch); //recursive call to itself
        }
    }
	delete curr_node; //call actual delete here
	curr_node = NULL; //set the reference to null otherwise it can point to undefined memory address
	
}
