/*
	Brayden Cowell
	ID: 0844864
	Oct.11th, 2014
	CIS 2520
*/

/*******************
 The 3 linked lists 
********************/

typedef struct Cars
{
	char * plateNum;
	int mileage;
	char repair;
	int returnDate;
	char transaction;
	struct Cars * next;
}Cars;

/* These three functions create the linked lists for each transaction type 
*  The arguments are the car's information
*/
Cars * createAvailable(char * plateNum, int mileage, char repair);
Cars * createRented(char * plateNum, int mileage, int returnDate);
Cars * createRepair(char * plateNum, int mileage, char repair);

/* storeInFile uses fprintf to write all the info of the lists to a file using write mode
*  The arguments are the car's information and the file you want to store to
*/
void storeInFile(Cars * availableList, Cars * rentedList, Cars * repairList, FILE * myFile);

/* print will take the three lists go through them to print each node in each list
*  The arguments are the three linked lists 
*/
void print(Cars * availableList, Cars * rentedList, Cars * repairList);

/* This function is what moves one node of a list into another list 
*  using strcmp and the list's license plate number along with the user-entered plate number
* I search through the lists until I found the node that matched the plate number
*  and then copy that entire node into the new list using my sort algorithms
*/
Cars * moveToList(Cars * oldList, Cars * newList, char * plateNum, int mileage, char transaction, int returnDate, char * destList);

/* After I copy one node from a list to another I remove the leftover node
*  In the original list, leaving only the copied node after it has been moved
* The arguments are the list and the plate number you want to remove the node at
*/
Cars * removeFromList(Cars * theList, char * plateNum);

/* These functions sort the node based on smaller integers
*  By comparing the node and each node of the list I can sort and add the node
* into the new list at the same time
*/
Cars * sortMileage(Cars *  theList, Cars * toBeAdded, int mileage);
Cars * sortReturn(Cars *  theList, Cars * toBeAdded, int mileage);

/* Since the repair list does not need to be sorted we simply add to the front of the list 
*  The arguments are the repair list and the node you want to add to front 
*/
Cars * addRepair(Cars * theList, Cars * toBeAdded, int mileage);

/* These functions simply take in a list and return the matching 
*  information (License Plate, Transaction code, return date, and mileage)
* At a specific node found using strcmp and the license plate 
*/
int checkPlate(Cars * toBeSearched, char * plateNum);
char checkTransaction(Cars * theList, char * plateNum);
int checkReturnDate(Cars * theList, char * plateNum);
int checkMileage(Cars * theList, char * plateNum);

/* Finds the car at the beginning of the available list
*  And then add's it to the rented list and sorts based on return date
* Args are the list you want to search and the list you want to add to
*/
Cars * rentFirstAvailable(Cars * oldList, Cars * newList, int returnDate);

/* This function simply takes the a list and prints the first element
*  The arguments are the list
*/
char * findFirstPlateNum(Cars * theList);

/* Charge for $40 up to 100km and $0.15 per km after 100
* Take new KM - from rented list km and add to profit 
* The total profit is added up and printed at the end
*/
float calculateCost(Cars * theList, int mileage, float profit);