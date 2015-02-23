//This is the file where you will implement the datastructure. main.cc
//and interface for datastructure.hh will be found from julkinen/hw<X>,
//and they should be copied in this directory.


/*Name. Apurva Nandan Student No. 238766
The purpose of this file is to implement the interface functions from datastructure.hh file and also implement our own member functions
There basic operations that we need to do for the graph of the familytree is adding a new person, adding spousal relationships,
adding child for particular parents, checking if two people are related or not, printing the family tree for a person and cleaning up everything
This file contains the actual implementation code of all the given interface functions and other necessary functions
*/

#include "datastructure.hh"

//Constructor
Datastructure::Datastructure()
{
	
}

//Destructor
Datastructure::~Datastructure(){
	
	remove(); //Call remove and clear everything
}

/** Add the given person in the familytree graph using the given data
 * @param gender the gender of the person to be added
 * @param name the name of the person
 * @param ID the ID of the person
 * @param born the birth year
 * @param died the died year
 * @return if the person was added then true else false
 **/

bool Datastructure::add(Gender gender, std::string& name, int ID, int born, int died)
{

	if ( familytree.find(ID) == familytree.end() ) //Check if the person doesn't exists already
    {
		Person* p = new Person(); //Create the pointer to the person struct
		//Populate with the given data
		p->gender = gender;
		p->ID = ID;
		p->name = name;
		p->born = born;
		p->died = died;
		
	
		p->hasParents = false; //Initially the person doesn't have parents
		familytree.insert(graph::value_type(ID,p)); //Insert the pair into the familytree graph
		
	}
	
	else
	{
		return false;
	}
  
	return true;
	
}

/** This function creates a spousal relationship between two given people. If the relationship already exists then nothing is done
 * else it is created.
 * @param ID1 The ID of the first person
 * @param ID2 The ID of the second person
 * @return true If the spousal relationship was created / already exists, false if one or more people were not found in the graph
**/

bool Datastructure::addPartner(int ID1, int ID2)
{
	
	//Check if both the person already exist in the graph
	if ( familytree.find(ID1) == familytree.end() || familytree.find(ID2) == familytree.end())
	{
		return false; //return false, if one or more were not found
	}
	else //otherwise continue
	{
		//Obtain the pointers to the persons
		Person* p1 = familytree.at(ID1);
		Person* p2 = familytree.at(ID2);
		

		if ( p1->spouses.find (ID2) == p1->spouses.end()) //If The spouse relation is not there right now
		{
			//Push the spousal relationship in the vector for maintaing the order
			p1->spouses_vec.push_back(p2); 
			p2->spouses_vec.push_back(p1);
			
			//Also add in the map to avoid duplicacy and also for constant time searching
			p1->spouses.insert({ID2,p2});
			p2->spouses.insert({ID1,p1});
			
		}
		
	}
	return true;
}

/** Build the relationship between child and parents. If the spousal relationship is not there between parents, create it.
 * Add the child if it doesn't have parents before.
 * @param IDChild The ID of the child to be added
 * @param IDwoman The ID of the female / mother
 * @param IDman The ID of the male/father
 * @return true if the child was added , false if not
**/

bool Datastructure::addChild(int IDChild, int IDwoman, int IDman)
{
	

	//Check if all the people already exist in the graph
	if ( familytree.find(IDChild) == familytree.end() || familytree.find(IDwoman) == familytree.end() || familytree.find(IDman) == familytree.end())
	{
		return false;
	}
	
	//Check if the IDwoman is female , IDman is male and the child doesn't have parents already
	else if(((familytree.at(IDwoman))->gender == FEMALE) && ((familytree.at(IDman))->gender == MALE) && ((familytree.at(IDChild))->hasParents == false))  
	{
		//Obtain the parents by using the pointers to the individual people
		Person* mother = familytree.at(IDwoman);
		Person* father = familytree.at(IDman);
		
		
		//Process the mother
		
		//First Find the ID of the man in the woman's/mother's spouses map
		std::unordered_map<int,Person*>::const_iterator wf_it = mother->spouses.find(IDman);
		
		if ( wf_it == mother->spouses.end()) //If there's no man with the specified ID in the spouses list
		{
			mother->childrens.insert(familytree.at(IDChild)); //Insert the child in mother's children set
			mother->spouses_vec.push_back(father); //Also create the spousal relationship with the father/man
			
			mother->spouses.insert({IDman,father}); //Also, store the spousal relationship in hash map for constant time searching and duplicacy avoidance
		}
		else //Get the existin pointer to the spouse of the woman with the specified spouse, if spouse is already present
		{
			mother->childrens.insert(familytree.at(IDChild)); //Insert the child into childrens set
		}
		
		
		
		//Process the father
		
		//First Find the ID of the woman in the man's/father's spouses map
		std::unordered_map<int,Person*>::const_iterator mf_it = father->spouses.find(IDwoman);
		
		if ( mf_it == father->spouses.end()) //If there's no woman with the specified ID in the spouses list
		{
			
			father->childrens.insert(familytree.at(IDChild)); //Insert the child in father's children set
			father->spouses_vec.push_back(mother); //Also create the spousal relationship with the father/man
			
			father->spouses.insert({IDwoman,mother}); //Also, store the spousal relationship in hash map for constant time searching and duplicacy avoidance
		}
		else //Get the existin pointer to the spouse of the man with the specified spouse
		{
			father->childrens.insert(familytree.at(IDChild)); //Insert the child into childrens set
		}
		
		//Update the child's parents property
		familytree.at(IDChild)->hasParents = true; //Set that the child has parents 
		familytree.at(IDChild)->parents.at(0) = familytree.at(IDwoman); //Set the mother of the person with the woman ID given
		familytree.at(IDChild)->parents.at(1) = familytree.at(IDman); //Set the father of the person with the father ID given
		
	}
	else //If any of the above conditions are not valid then the function returns false
	{
		return false;
	}
	
	return true;
}


/** This function checks if two given people are related or not, it actually uses Breadth First Search to traverse up the 
 * ancestor tree by traversing searching the parents of the given node and their parents and so on until it matches a common ancestor for both the people
 * If no match is found then it is reported as false. Also all the nodes have to be tracked using pie pointer to keep a track from which
 * person a particular node was reached, if it was reached from both the nodes that means, it is a common ancestor
 * @param ID1 The ID of the first person
 * @param ID2 The ID of the second person
 * @return RELATED if two people are related, NOT_RELATED if not related and INVALID_ID if one or more was not found in the tree
 * */


Relation Datastructure::relation(int ID1, int ID2)
{
	std::queue<Person*> queue; //We use the queue for Breadth First Search here
	
	std::vector<Person*> changelist; //The list which has the nodes processed which are changed to initial values after searching
	
	//If any of the IDs are not found in the familytree
	if ( familytree.find(ID1) == familytree.end() || familytree.find(ID2) == familytree.end())
	{
		return INVALID_ID;
	}
	else 
	{
		if(ID1 == ID2) //If the person is himself/herself
		{
			return RELATED;
		}
		
		// Start checking the ancestors of two persons if they share same parents it means they are related
		
		Person* p1 = familytree.at(ID1); //Obtain the people
		Person* p2 = familytree.at(ID2);
		
		p1->pie = p1; //Store the root as pie pointer, root would be where we actually began the search ID1 or ID2
		p2->pie = p2;
		
		//Push into a queue
		queue.push(p1);
		queue.push(p2);
		
		//Instead of initializing the graph everytime, store the pointers in a vector where we could set them back into original state
		changelist.push_back(p1);
		changelist.push_back(p2);
		
		//Loop until the queue is not empty
		while(queue.size()!=0)
		{
			
			Person* p = queue.front(); //Obtain the first element from the queue in a FIFO fashion
		
			queue.pop(); //Remove the element
			
			// Process the mother first
			
				if(p->parents.at(0)!=NULL) 
				{
					Person* parent_w = p->parents.at(0); //Obtain the mother for the given person
				
				
					if(parent_w->pie == NULL) //If there's no pie pointer storing the root of the search, means the node has been not visited
					{
						parent_w->pie = p->pie; //Set the pie pointer to the root which tells from which of the ids ID1 or ID2 we reached this node
						queue.push(parent_w); //Push the parent (mother) in the queue for processing 
						changelist.push_back(parent_w); //Put the node in the changelist
					}
					else
					{
						//If the pie pointer is there that means the node was visited before and if now we check that the node was visited by the other person's tree
						// it thus means, the current person's ancestory tree and other person's ancestory tree has one ancestor in common
						if(parent_w->pie->ID != p->pie->ID) //Found the COMMON Ancestor
						{
							//Change all the visited nodes to initial values
							for(auto it1 = changelist.begin();it1!=changelist.end();++it1)
							{
								Person* u = *it1;
								u->pie = NULL;
							}
							return RELATED; //return that they are related
						}
							
						
					}
				}
				
				//Process the father now, instead of using the loop two times, I have written like this for better understanding for the user
				
				if(p->parents.at(1)!=NULL) 
				{
					Person* parent_m = p->parents.at(1); //Get the male parent/father
					
					
					if(parent_m->pie == NULL)
					{
						parent_m->pie = p->pie; //Set the pie pointer to the root which tells from which of the ids ID1 or ID2 we reached this node
						queue.push(parent_m); //Push the parent (father) in the queue for processing 
						changelist.push_back(parent_m); //Put the node in the changelist
					}
					else
					{
						//If the pie pointer is there that means the node was visited before and if now we check that the node was visited by the other person's tree
						// it thus means, the current person's ancestory tree and other person's ancestory tree has one ancestor in common
						if(parent_m->pie->ID != p->pie->ID)
						{
							//Change all the visited nodes to initial values
							for(auto it2 = changelist.begin();it2!=changelist.end();++it2)
							{
								Person* u = *it2;
								u->pie = NULL;
							}
							return RELATED;
						}
							
						
					}
					
				}
				
		}
		
		
		
	}
	
//Once we are done doing the search, change all the vertices used back into initial conditions
	for(auto it3 = changelist.begin();it3!=changelist.end();++it3)
	{
		Person* u = *it3;
		u->pie = NULL;
	}
	return NOT_RELATED;
	 
		
}

/** This function prints the family tree in indented manner. This actually performs a Depth First Search on our
 * graph of family tree that we have and keeps on printing the persons , spouses and their children
 * @param ID The ID of the root element from which we want to start the search
 * */


void Datastructure::print(int ID)
{
	std::stack<Person*> personstack; //First stack to keep a track of pointers of type Person using vector
	
	

	if ( familytree.find(ID) == familytree.end()) //Just check if the root actually exists before going through the tree
		std::cout << "V\n";
	
	else //If the person exists continue
	{
		
		Person* p = familytree.at(ID); //Get the person using the ID
		
		p->level.push_back(0); //Keep a track of level for indentation, since it is root, the level is zero
		p->isSpouse.push_back(false); //Keep a track weather the given person is printed as a spouse
		
		personstack.push(p); //Push into the stack for processing in LIFO manner
		
		int level;
		bool isSpouse;
		std::cout << std::endl;
		
		while(personstack.size()!=0) // Loop until the stack is not empty
		{
		
			Person* u = personstack.top(); //Get the person on top of the stack
			level = u->level.back(); //Get the level of the person which we obtained just now
			u->level.pop_back(); //pop the level from the vector
			
			isSpouse = u->isSpouse.back(); //Get the info weather the person is stored as spouse or normal
			u->isSpouse.pop_back(); //pop back the info from the vector
			
			personstack.pop(); //Pop the person from the stack
			
			
			
			if(isSpouse == false) //If the person is 'normal' i.e. he/she is not stored as a spouse then process his/her children and get the spouse info
			{
				//Print the required information and fill the indentation spaces according to the helper function
				if(u->died==0) std::cout << fillSpaces(level) << u->name << " " << u->born << " - " << std::endl; //If died is 0, then print a space only
				else std::cout << fillSpaces(level) << u->name << " " << u->born << " - " << u->died << std::endl;
			
			
			//Get the spouses for the person using reverse iterator i.e this means in the order as they were intially stored
				for (std::vector<Person*>::reverse_iterator rev_fam_it = u->spouses_vec.rbegin(); rev_fam_it!= u->spouses_vec.rend(); ++rev_fam_it) //Reverse Traversal
				{
						Person* s = *rev_fam_it; //Spouse
						s->isSpouse.push_back(true); //Set the spouse info to true indicating this pointer is a spouse
						s->level.push_back(level);  // Put the level info for the spouse as the current level
					
					//Iterate over the sorted set according to the birth year for children, if they are same then it maintains the order in which they were added
						for (std::set<Person*,bornsort>::iterator child_it = u->childrens.begin(); child_it!= u->childrens.end(); ++child_it)
						{
							Person* child = *child_it; // Get the child
									
							if(child->parents.at(0)->ID == s->ID || child->parents.at(1)->ID == s->ID) //Check if the obtained child is from the spouse that we obtained just now
							{
								child->level.push_back(level + 1); //Push the level information for the child incremented by 1 so that we get indentation spaces
								child->isSpouse.push_back(false); //They should be further investigated as normal person not as spouse
								personstack.push(child); //Push the child onto the main stack
							}
						}
						
						
						personstack.push(s); //Finally push back the spouse on top of the children so that it gets printed first and then followed by children
						
				}
			}
			
			else //Case where the person is actually is a spouse
			{
				//Print only the name and details of the person with an '&' at the same level of the person whose spouse this is 
				if(u->died==0) std::cout << fillSpaces(level) << "& " << u->name << " " << u->born << " - " << std::endl;
				else std::cout << fillSpaces(level) << "& " << u->name << " " << u->born << " - " << u->died << std::endl;
				
			}
			u = NULL;
		}
		
		
		
	}
	
	
}



/** A helper function which takes in the level and generated the amount of spaces required for indentation
 * @param level : The level to generate the spaces for
 * **/
 
std::string Datastructure::fillSpaces(int level)
{
	std::string res = "";
	for(int i=0;i<level;i++)
	{
		res.append("    "); //Keep appending the spaces according to the loop
	}
	return res;
}


/** Function to clear the datastructure by clearing all the elements of the familytree graph and 
 * cleaning all the references
 * **/
 

void Datastructure::remove()
{
	
	//Start traversing over the familytree graph
	for (auto it = familytree.begin(); it != familytree.end(); ++it )
	{
		Person* p  = it->second;
		
		
		p->parents.at(0) = NULL; p->parents.at(1) = NULL;
		
		for (auto sit = p->spouses.begin(); sit != p->spouses.end(); ++sit )
		{
			sit->second = NULL;
		}
		
		p->spouses.clear();
			
		p->spouses_vec.clear();
		p->isSpouse.clear();
		p->level.clear();
		
		delete p; //Delete the pointer
		p = NULL; //Set the reference to null to avoid dangling pointer
	}
	
	familytree.clear(); //Clear the map to make it empty
	
}

