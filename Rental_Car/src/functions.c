/*
	Brayden Cowell
	ID: 0844864
	Oct.11th, 2014
	CIS 2520
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************
 Functions operating on structs
 ***********************************/
 
/* -----------------------------------------------------------------------------------------*/
 
Cars * createAvailable(char * plateNum, int mileage, char repair)
{
	Cars * temp = malloc(sizeof(Cars));/* The function allocates memory for the struct */
	
	if(temp == NULL) /* Returns NULL on failure */
	{
		return(NULL);
	}

	temp->plateNum = malloc(sizeof(char)* 25);

	/* initializes the variables to the supplied values */ 
	strcpy(temp->plateNum, plateNum);
	temp->mileage = mileage;
	temp->repair = repair;

	temp->next = NULL; /* initializes the next pointer to null */

return(temp); /* returns a pointer to the allocated memory */
}
 
/* -----------------------------------------------------------------------------------------*/

Cars * createRented(char * plateNum, int mileage, int returnDate)
{
	Cars * temp = malloc(sizeof(Cars));/* The function allocates memory for the struct */
	
	if(temp == NULL) /* Returns NULL on failure */
	{
		return(NULL);
	}

	temp->plateNum = malloc(sizeof(char)* 25);

	/* initializes the variables to the supplied values */ 
	strcpy(temp->plateNum, plateNum);
	temp->mileage = mileage;
	temp->returnDate = returnDate;

	temp->next = NULL; /* initializes the next pointer to null */

return(temp); /* returns a pointer to the allocated memory */
}
 
/* -----------------------------------------------------------------------------------------*/
Cars * createRepair(char * plateNum, int mileage, char repair)
{
	Cars * temp = malloc(sizeof(Cars));/* The function allocates memory for the struct */
	
	if(temp == NULL) /* Returns NULL on failure */
	{
		return(NULL);
	}

	temp->plateNum = malloc(sizeof(char)* 25);

	/* initializes the variables to the supplied values */ 
	strcpy(temp->plateNum, plateNum);
	temp->mileage = mileage;
	temp->repair = repair;

	temp->next = NULL; /* initializes the next pointer to null */

return(temp); /* returns a pointer to the allocated memory */
}
 
/* ----------------------------------------------------------------------------------------*/

Cars * sortMileage(Cars *  theList, Cars * toBeAdded, int mileage)
{
	Cars * node;
	Cars * prev;
	
	node = malloc(sizeof(Cars));
	prev = malloc(sizeof(Cars));
	
	prev = theList;
	node = prev->next;;
	
	if (node == NULL) /* List is empty or there is one element - just Add to back */
	{
		if(mileage < prev->mileage) /* Add to front */
		{
				toBeAdded->next = theList;
				return(toBeAdded);
		}
		
		else /* Add to back */
		{
			prev->next = toBeAdded;
			return(theList);
		}
	}

	else
	{
		if(node->next == NULL) /* There are two elements in the list */
		{
			if(mileage < node->mileage)
			{
				prev->next = toBeAdded;
				toBeAdded->next = node;
			}
			
			else
			{
				node->next = toBeAdded;
			}
		}
		
		while(node != NULL)
		{
			/* if toBeAdded is < current node - inset toBeAdded between prev and node */
			if(mileage < node->mileage)
			{
				prev->next = toBeAdded;
				toBeAdded->next = node;
			}
			
			prev = node;
			node = node->next; /* Traverse the list */
		}
	}	
	

return(theList);
}

/* ----------------------------------------------------------------------------------------*/

Cars * sortReturn(Cars *  theList, Cars * toBeAdded, int mileage)
{
	Cars * node;
	Cars * prev;
	
	node = malloc(sizeof(Cars));
	prev = malloc(sizeof(Cars));
	
	prev = theList;
	node = prev->next;;
	
	if (node == NULL) /* List is empty or there is one element - just Add to back */
	{
		if(toBeAdded->returnDate < prev->returnDate) /* Add to front */
		{
				toBeAdded->next = theList;
				toBeAdded->mileage = mileage;
				return(toBeAdded);
		}
		
		else /* Add to back */
		{
			prev->next = toBeAdded;
			toBeAdded->mileage = mileage;
			return(theList);
		}
	}

	else
	{
		if(node->next == NULL) /* There are two elements in the list */
		{
			if(toBeAdded->returnDate < node->returnDate)
			{
				prev->next = toBeAdded;
				toBeAdded->next = node;
			}
			
			else
			{
				node->next = toBeAdded;
			}
		}
		
		while(node != NULL)
		{
			/* if toBeAdded is < current node - inset toBeAdded between prev and node */
			if(toBeAdded->returnDate < node->returnDate)
			{
				prev->next = toBeAdded;
				toBeAdded->next = node;
			}
			
			prev = node;
			node = node->next; /* Traverse the list */
		}
	}	
	
	toBeAdded->mileage = mileage;
return(theList);
}
 
/* -----------------------------------------------------------------------------------------*/

void print(Cars * availableList, Cars * rentedList, Cars * repairList)
 {
    Cars * temp1;
	Cars * temp2;
	Cars * temp3;
	
	temp1 = malloc(sizeof(Cars));
	temp2 = malloc(sizeof(Cars));
	temp3 = malloc(sizeof(Cars));
	
	temp1 = availableList;
	temp2 = rentedList;
	temp3 = repairList;
	
	printf("\nThis is the list of available cars.\n");
	
    while(temp1 != NULL)
    {
        printf("Plate: %s Mileage:%d\n", temp1->plateNum, temp1->mileage);
        temp1 = temp1->next;
    }
     
  
	printf("\nThis is the list of rented cars.\n");
	
    while(temp2 != NULL)
    {
        printf("Plate: %s Mileage:%d Return Date(YYMMDD):%d\n", temp2->plateNum, temp2->mileage, temp2->returnDate);
        temp2 = temp2->next;
    }  
	
	printf("\nThis is the list of cars being repaired.\n");
	
    while(temp3 != NULL)
    {
        printf("Plate: %s Mileage:%d\n", temp3->plateNum, temp3->mileage);
        temp3 = temp3->next;
    }
    printf("\n");
}

/* ----------------------------------------------------------------------------------------*/
Cars * addRepair(Cars * theList, Cars * toBeAdded, int mileage)
{
	Cars * node;
	
	node = malloc(sizeof(Cars));
	
	node = toBeAdded;

	node->next = theList;

return(node);
}

/* ----------------------------------------------------------------------------------------*/

int checkPlate(Cars * toBeSearched, char * checkPlate)
{
	Cars * node;
	
	node = malloc(sizeof(Cars));
	
	node = toBeSearched;

	
	while(node != NULL)
	{
		if(strcmp(node->plateNum, checkPlate) == 0) /* Plate number is in the list - return true */
		{
			return (1); 
		}
		
		node = node->next; /* Traverse the list */
	}

return(0); /* plate number is not in the list - return false */
}

/* ----------------------------------------------------------------------------------------*/

int checkMileage(Cars * theList, char * plateNum)
{
	Cars * node;
	
	node = malloc(sizeof(Cars));
	
	node = theList;

	
	while(node != NULL)
	{
		if(strcmp(node->plateNum, plateNum) == 0) /* Plate number is in the list - return true */
		{
			return(node->mileage);
		}
		
		node = node->next; /* Traverse the list */
	}


return(0);
}

/* ----------------------------------------------------------------------------------------*/

float calculateCost(Cars * theList, int mileage, float profit)
{
	int totalKm;

	totalKm = (mileage - theList->mileage);

	if(totalKm > 0 && totalKm <= 100)
	{
		profit = 40.0 + profit;
	}
	
	else if(totalKm > 100)
	{
		profit = 40.0 + (0.15 * (float)(totalKm - 100)) + profit;
	}

return (profit);
}

/* ----------------------------------------------------------------------------------------*/

void storeInFile(Cars * availableList, Cars * rentedList, Cars * repairList, FILE * myFile)
{
	Cars * temp1;
	Cars * temp2;
	Cars * temp3;
	
	temp1 = malloc(sizeof(Cars));
	temp2 = malloc(sizeof(Cars));
	temp3 = malloc(sizeof(Cars));
	
	temp1 = availableList;
	temp2 = rentedList;
	temp3 = repairList;
	
	char transaction;
	int returnDate;
	
    while(temp1 != NULL)
    {
		transaction = checkTransaction(temp1, temp1->plateNum);
		returnDate = checkReturnDate(temp1, temp1->plateNum);
        fprintf(myFile, "%s %d %c %d\n", temp1->plateNum, temp1->mileage, transaction, returnDate); /* Print values of item into file */
        temp1 = temp1->next;
    }
	
    while(temp2 != NULL)
    {
		transaction = checkTransaction(temp2, temp2->plateNum);
		returnDate = checkReturnDate(temp2, temp2->plateNum);
        fprintf(myFile, "%s %d %c %d\n", temp2->plateNum, temp2->mileage, transaction, returnDate); /* Print values of item into file */
        temp2 = temp2->next;
    }  
	
    while(temp3 != NULL)
    {
        fprintf(myFile, "%s %d %c %d\n", temp3->plateNum, temp3->mileage, temp3->transaction, temp3->returnDate); /* Print values of item into file */
        temp3 = temp3->next;
    }
    printf("\n");


	free(temp1);
	free(temp2);
	free(temp3);
}

/* -----------------------------------------------------------------------------------------*/
Cars * moveToList(Cars * oldList, Cars * newList, char * plateNum, int mileage, char transaction, int returnDate, char * destList)
{
	Cars * temp;
	Cars * node;
	
	temp = malloc(sizeof(Cars));
	node = malloc(sizeof(Cars));
	
	temp = oldList;

	
	
	while (temp->next != NULL)
	{
		if(strcmp(temp->plateNum, plateNum) == 0) /* When you are at the correct element you want to move */
		{
			if(strcmp(destList, "availableList") == 0) /* If you want to move to the availableList then you must sort by mileage after adding element */
			{
				temp->transaction = 'a';
				node = createAvailable(plateNum, mileage, 'a');
				/* newList = sortMileage(newList, node, mileage);  Add the element into the newList and sort */
				newList = addRepair(newList, node, mileage); /* Add to front of newList */
			}
			
			else if (strcmp(destList, "rentedList") == 0) /* If you want to move to the rentedList then you must sort by the return date after adding the element */
			{
				temp->transaction = 'r';
				node = createRented(plateNum, mileage, 'r');
				newList = sortReturn(newList, node, mileage); /* Add the element into the newList and sort */
			}
			
			else if (strcmp(destList, "repairList") == 0)
			{
				temp->transaction = 'f';
				node = createRepair(temp->plateNum, mileage, 'f'); /* node->transaction = 'f'; */
				newList = addRepair(newList, node, mileage);
			}
		}
		
		/* Traverse the list */
		temp = temp->next;
	}


return(newList);
}

/* -----------------------------------------------------------------------------------------*/

Cars * removeFromList(Cars * theList, char * plateNum)
{
	Cars * prev;
	Cars * curr;
	curr = theList;
	
	while(curr->next && strcmp(curr->plateNum, plateNum))
	{
		prev = curr;
		curr = curr->next;
	}
	
	if(strcmp(theList->plateNum, plateNum) == 0 )
	{
		theList = theList->next;
		free(curr);
		return(theList);
	}

	else
	{
		prev->next = curr->next;
		free(curr);
		return(theList);
	}

}

/* -----------------------------------------------------------------------------------------*/

Cars * rentFirstAvailable(Cars * oldList, Cars * newList, int returnDate)
{
	Cars * node;
	Cars * temp;
	
	node = malloc(sizeof(Cars));

	node = oldList;

	if(node == NULL)
	{
		printf("There are no cars available to rent!\nTransfer one from either the Repair list or the Rented List into the Available list!\n");
		return(NULL);
	}

	temp = createRented(node->plateNum, node->mileage, 'r');
	temp->returnDate = returnDate;
	/* newList = sortReturn(newList, temp, node->mileage);  Add the element into the newList and sort */
	newList = addRepair(newList, temp, node->mileage); /* Add to front of newList */


return(newList);
}

/* -----------------------------------------------------------------------------------------*/
char * findFirstPlateNum(Cars * theList)
{
	Cars * node;
	
	node = malloc(sizeof(Cars));
	
	node = theList;

	if(node == NULL)
	{
		printf("There are no cars in the list, add some!\n");
		return(NULL);
	}
	

return (node->plateNum);
}

/* -----------------------------------------------------------------------------------------*/
char checkTransaction(Cars * theList, char * plateNum)
{
	Cars * node;
	node = malloc(sizeof(Cars));
	
	node = theList;

	while(node != NULL)
	{
		if(strcmp(node->plateNum, plateNum) == 0) /* Plate number is in the list - return true */
		{
			return(node->transaction);
		}
		node = node->next; /* Traverse the list */
	}

return(0);
}
/* -----------------------------------------------------------------------------------------*/
int checkReturnDate(Cars * theList, char * plateNum)
{
	Cars * node;
	node = malloc(sizeof(Cars));
	
	node = theList;

	while(node != NULL)
	{
		if(strcmp(node->plateNum, plateNum) == 0) /* Plate number is in the list - return true */
		{
			return(node->returnDate);
		}
		node = node->next; /* Traverse the list */
	}

return(0);
}
/* -----------------------------------------------------------------------------------------*/