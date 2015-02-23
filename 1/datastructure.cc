//this is the file where you'll write implementation of the datastructure

/*Name. Apurva Nandan Student No. 238766
The purpose of this file is to implement the interface functions from datastructure.hh file and also implement our own member functions
There basic operations that we need to do with the given persons data, such as adding a new person, finding the person at a given index,
finding the youngest person, finding the oldest person from the given list. For this we need to make use of efficient sorting algoritms to sort the given list,
which in turn makes these operations easy. We use merge sort in this assignment which has worst case complexity of nlogn and is efficient
*/

#include "datastructure.hh"


// Datastructure constructor
Datastructure::Datastructure(){

}


//Destructor for Datastructure class, free memory by calling empty method to clear the elements.
Datastructure::~Datastructure(){
empty();
}

/**
The method for adding a new element to the vector using the given set of information
@param rank The rank of the person as string
@param birthYear the birth year of the person as integer
@param enlistingYear the year when the person enlisted in the team as integer
@param shirtColor the color of the shirt of the person as string
@param name the name of the person as string
**/

void Datastructure::add(std::string rank, unsigned int birthYear, unsigned int enlistingYear, std::string shirtColor, std::string name){

// Create a new pointer to Person struct
Person* p = new Person();
p->rank = rank;
p->birthYear = birthYear;
p->enlistingYear = enlistingYear;
p->shirtColor = shirtColor;
p->name = name;

// Push the element on the vector
personVect.push_back(p);
//Set the sorted flag to true so that we can keep track that the array has new elements and it needs to be sorted
sorted = true;
}

/**
Finds and prints the person with the given index
@param index the given index
**/

void Datastructure::find(unsigned int index){

//Check of the vector is not empty using the size() function of DataStructure
if(size()!=0)
{
    //Check for sorted flag, if it is true it means there has been a new addition and the vector needs to be sorted first
    if(sorted==true)
        merge_sort(personVect,0,(unsigned int)size()-1); //Call the merge_sort function to sort it

    //If we have a sorted list, we can directly go the index of the vector but the indexing in vector begins from zero, so we need to shift our index by 1
    Person* o = personVect.at(index-1);
    // Print the information of the Person using our own print function
    print(o);
    //Set the sorted to false, so that we do not sort the array again unless there's no new additions
    sorted=false;
}
else
    std::cout << MSG_EMPTY_DS; //Print that the list is empty

}


/**
Finds the youngest Person from the officers vector and prints his information
**/

void Datastructure::youngest(){

//Check for sorted flag, if it is true it means there has been a new addition and the vector needs to be sorted first
if(size()!=0)
{
    if(sorted==true)
        merge_sort(personVect,0,(unsigned int)size()-1); //Call the merge_sort function to sort it


//Basically after sorting, the youngest Person will have the highest value for enlistingYear and thus it would be the last element of the vector
// or if its equal for multiple officers then the highest birthdate corresponds to the youngest Person which is the last element.
    Person* p = personVect.back();

// Print the information of the Person using our own print function
    print(p);

//Set the sorted to false, so that we do not sort the array again unless there's no new additions
    sorted=false;
}
    else
        std::cout << MSG_EMPTY_DS; //Print that the list is empty

}

/**
Finds the oldest Person from the personVect vector and prints his information
**/

void Datastructure::oldest(){

if(size()!=0)
{
//Check for sorted, if it is true it means there has been a new addition and the vector needs to be sorted first
    if(sorted==true)
        merge_sort(personVect,0,(unsigned int)size()-1); //Call the merge_sort function to sort it

//Basically after sorting, the oldest Person will have the lowest value for enlistingYear and thus it would be the first element of the vector
// or if its equal for multiple officers then the lowest birthdate corresponds to the oldest Person which is the first element.
    Person* p = personVect.front();

// Print the information of the Person using our own print function
    print(p);

//Set the sorted to false, so that we do not sort the array again unless there's no new additions
    sorted=false;
 }
 else
    std::cout << MSG_EMPTY_DS; //Print that the list is empty
 }

/**

Empties the Datastructure by removing all the elements present in the persons vector

**/

void Datastructure::empty(){

    //Check if it is not already empty
    if(size()!=0)
    {
        // Recursively delete all the pointers to the Person class and remove them from vector
        while(!personVect.empty())
        {

            delete personVect.back();
            personVect.pop_back();

        }
    }
}

/**
Provides the size of the Datastructure by essentially returning the number of elements present in the sorted input vector
**/

size_t Datastructure::size(){


    return personVect.size();

}


/**
THis function prints the Person information in the given format
@param p pointer to the Person class which contains all the data about the Person
**/

void Datastructure::print(Person* p){

std::cout << p->name << SEPARATOR << p->rank << SEPARATOR << p->birthYear << SEPARATOR << p->enlistingYear << SEPARATOR << p->shirtColor << std::endl;
}


/**
This function performs the comparison and then merges the sub-parts together
@param input The reference to the vector containing the Person data
@param first The starting index of the first subpart of the vector
@param mid the mid point of the vector
@param last The ending index of the second subpart of the vector

**/

void Datastructure::merge(std::vector<Person*>& input, unsigned int first, unsigned int mid, unsigned int last)
{

    //The starting index of the first subpart (left side) of the input vector
    unsigned int i = first;

    //The starting index of the second subpart (right side) of the input vector
    unsigned int k = mid + 1;

    // Create a Temporary vector to store temporararily sorted results
    std::vector<Person*> tempVec;


    // Merge by comparing the elements from the left side of the input vector with the right side of the input vector
    while ( i <= mid && k <= last )
    {
        Person* p1 = input.at(i);
        Person* p2 = input.at(k);

        // Compare the enlisting years of the two officers, if the Person 1 has lower value for enlistingYear means he is senior and he shall be added
        if (p1->enlistingYear < p2->enlistingYear)
        {
            tempVec.push_back(p1);
            // Increase the index position in the first subpart (left side)
            i++;
        }
        // If the enlisting years are equal for both
        else if(p1->enlistingYear == p2->enlistingYear)
        {

            //Start comparing the birth dates of the officers, the older Person will be added first
            if(p1->birthYear < p2->birthYear)
            {

                    tempVec.push_back(p1);
                    i++; // Increase the index position in the first subpart (left side)
            }
            else
            {
                tempVec.push_back(p2);
                k++; // Increase the index position in the second subpart (right side)
            }

        }
        // Else the last case is where the second Person had lower value for enlistingYear, he is senior and he will be added
        else
        {
            tempVec.push_back(p2);
            k++; // Increase the index position in the second subpart (right side)
        }
    }

    // Merge the remaining elements in first subpart (left part) of input vector
    while ( i <= mid )
    {
        Person* p1 = input.at(i);
        tempVec.push_back(p1);
        i++;
    }
    // Merge the remaining elements in second subpart (right part) of input vector
    while ( k <= last )
    {
        Person* p2 = input.at(k);
        tempVec.push_back(p2);
        k++;
    }

    // Finally,copy the elements from temporary vector to our main input vector, hereby merging the two sub parts
    // This loop smartly copies only the sorted merged subparts which were sorted in this phase, instead of whole input back into the main input vector
    for ( unsigned int m = first; m <= last; m++ )
      input.at(m) = tempVec.at(m-first);


}


/** The main merge sort method which takes the input and sorts by keep splitting the input into two subparts recursively, and then calls merge to
merge back into final output.
@param input reference to the input vector used for sorting
@param first the index which tells where to start
@param last the index which signifies where to stop
**/
void Datastructure::merge_sort(std::vector<Person*>& input, unsigned int first, unsigned int last)
{
    //Checks if the last index is greater than the first
    if ( first < last )
    {
        //Calculate the mid point of the vector
        unsigned int mid = (first + last) / 2;
        //Split recursively from first index to the mid point
        merge_sort(input, first, mid);
        // Split recursively from midpoint + 1 index to the last index
        merge_sort(input, mid + 1, last);

        //Perform the sorting and merge the sub parts back
        merge(input, first, mid, last);
    }
}
