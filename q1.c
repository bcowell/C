/*
	Brayden Cowell
	ID: 0844864
	Oct.11th, 2014
	CIS 2520
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedLists.h"
#include "functions.c"

/*--------------------------------------------------------------------------------------------------------*/


int main(int argc, char * argv[])
{
	Cars * availableCreate;
	Cars * availableHead;
	
	Cars * rentedCreate;
	Cars * rentedHead;
	
	Cars * repairCreate;
	Cars * repairHead;
	
	FILE * file;
	
	char * string;
	char * plateNum;
	char * temp;
	char * text;
	
	int mileage;
	int newMileage;
	int km;
	int returnDate;
	int input;
	int check;
	char transaction;
	float profit;
	
	if(argc != 2)
	{
		printf("Please load the initial text file\nAfter compiling type: ./q1 cars.txt\n");
		exit(0);
	}
	
	else
	{
		string = malloc(sizeof(char) * 200);
		temp = malloc(sizeof(char) * 20);
		plateNum = malloc(sizeof(char) * 20);
		text = malloc(sizeof(char) * 20);
		
		profit = 0;
		
		strcpy(text, argv[1]);
		
		file = fopen(text, "r"); /* Open text file called cars in read mode */
		
		if (file == NULL)
		{
			printf("There was an error opening the file.\n");
			exit(0);
		}
		
		availableHead = NULL;
		rentedHead = NULL;
		repairHead = NULL;

		while((fgets(string, 200, file)) != '\0') /* While there are lines of strings still in the file */
		{
			strcpy(plateNum, strtok(string, " ")); /* Cut the License plate number from file */
			
			mileage = atoi(strtok(NULL, " ")); /* Get mileage from file */
			
			temp = (strtok(NULL, " ")); /* Get transaction from file */
			
			returnDate = atoi(strtok(NULL, " ")); /* Get return date in yymmdd from file */
			
			transaction = temp[0]; /* Transaction is a char */
			
			/* Add to repair or available list depending on what we read in from the txt file */
			if (transaction == 'f') /* Car is in repair */
			{
				if (repairHead == NULL) /* If there are no other elements in the list - make a head */
				{
					repairHead = createRepair(plateNum, mileage, transaction);
				}
				
				else if (repairHead != NULL) /* There are other elements in the list, so we must add it  */
				{
					repairCreate = createRepair(plateNum, mileage, transaction);
					/* Does not need sorting - so just add it to the front of the repair list */
					repairHead = addRepair(repairHead, repairCreate, mileage);
				}
			}
			
			else if (transaction == 'a') /* Car is available for rent */
			{
				if (availableHead == NULL) /* If there are no other elements in the list - make a head */
				{
					availableHead = createAvailable(plateNum, mileage, transaction);
				}
				
				else if (availableHead != NULL) /* There are other elements in the list - so we must add it sorted */
				{
					
					availableCreate = createAvailable(plateNum, mileage, transaction);
					/* Sort depending on - MILEAGE */
					availableHead = sortMileage(availableHead, availableCreate, mileage);
				}
				
			}
			
			else if (transaction == 'r') /* Car is being rented */
			{
				if (rentedHead == NULL) /* If there are no other elements in the list - make a head */
				{
					rentedHead = createRented(plateNum, mileage, returnDate);
				}
				
				else if (rentedHead != NULL) /* There are other elements in the list - so we must add it sorted */
				{
					rentedCreate = createRented(plateNum, mileage, returnDate);
					/* Sort depending on - Return Date */
					rentedHead = sortReturn(rentedHead, rentedCreate, mileage);
				}
				
			}
		
		}	
		
		fclose(file);
		
		input = 0;
		
		while (input != 7) /* While user doesn't want to quit */
		{
			printf("\n"
			"1. Add a new car to the available-for-rent list.\n"
			"2. Add a returned car to the available-for-rent list\n"
			"3. Add a returned car to the repair list\n"
			"4. Transfer a car from the repair list to the available-for-rent list\n"
			"5. Rent the first available car\n"
			"6. Print all the lists\n"
			"7. quit.\n"); 
			

			scanf("%d", &input);
		
			switch(input)
			{
				case 1: /* Add a new car to the available-for-rent list. */
					printf("Please enter a License Plate number of the new car (Ex. ABCD-123):\n");
					scanf("%s", plateNum);
					printf("Please enter the car's mileage (Ex. 18000):\n");
					scanf("%d", &mileage);
					transaction = 'a'; /* Put new car under available */
					/* Create a new element and sort it by lowest mileage */
					availableCreate = createAvailable(plateNum, mileage, transaction);
					availableHead = sortMileage(availableHead, availableCreate, mileage);
					printf("New car with plate:%s and %d KM added to available-for-rent List.\n", plateNum, mileage);
				break;
				
				
				case 2: /* Add a returned car to the available-for-rent list */
					check = 0;
					/* Check for plate number in list of cars being rented */
					while(check != 1)/* If not found - print an error message and let user retry*/
					{
						printf("Please enter the License Plate number of the car you want to return (Ex. ABCD-123):\n");
						scanf("%s", plateNum);
						check = checkPlate(rentedHead, plateNum);
						
						if(check == 0) /* If check comes back negative */
						{
							printf("That car is not in the rented list! Make sure the plate number you enter is being rented.\n");
						}
					}
					/* If check comes back positive - charge price */

					printf("Please enter the car's new mileage (Ex. 18990):\n");
					scanf("%d", &mileage);
					newMileage = checkMileage(rentedHead, plateNum);
					profit = calculateCost(rentedHead, mileage, profit);
					/* Calculate cost of the trip - based on inital km and returned km */
					km = 0;
					
					km = (mileage - newMileage);

					if(km > 0 && km <= 100)
					{
						printf("The cost of your trip was: $40.0\n");
					}
					
					else if(km > 100)
					{
						printf("The cost of your trip was $%.2f\n", 40.0 + (0.15 * (float)(km - 100)));
					}
					else
					{
						printf("You must have entered a new mileage less than the old mileage. - Please re-enter.\n");
						break;
					}
					
					availableHead = moveToList(rentedHead, availableHead, plateNum, mileage, transaction, returnDate, "availableList");
					/* Send rentedList, availableList, plateNum and destination list to function - moveToList */
					/* Function will take find item matching plateNum in rentedList and add it into availableList */
					/* Then it will sort new availableList and return availableList */
					
					/* Then we remove the element from rentedList with plateNum */
					rentedHead = removeFromList(rentedHead, plateNum);
					printf("The car with plates:%s has been returned and has been put into the available List.\n", plateNum);
				break;
				
				
				case 3: /* Add a returned car to the repair list */
					check = 0;
					/* Check for plate number in list of cars being rented */
					while(check != 1)/* If not found print error */
					{
						printf("Please enter the License Plate number of the car you want to return and repair (Ex. ABCD-123):\n");
						scanf("%s", plateNum);
						check = checkPlate(rentedHead, plateNum);
						
						if(check == 0)
						{
							printf("That car is not in the rented list! Make sure the plate number you enter is being rented.\n");
						}
					}
					/* Charge for $40 up to 100km and $0.15 per km after 100 */
					/* Take new KM - from rented list km and add to profit */ 
					printf("Please enter the car's new mileage (Ex. 18990):\n");
					scanf("%d", &mileage);
					
					profit = calculateCost(rentedHead, mileage, profit);
					/* Calculate cost of the trip - based on inital km and returned km */
					km = 0;
					newMileage = checkMileage(rentedHead, plateNum);
					km = (mileage - newMileage);
					if(km > 0 && km <= 100)
					{
						printf("The cost of your trip was: $40.0\n");
					}
					else if(km > 100)
					{
						printf("The cost of your trip was $%.2f\n", 40.0 + (0.15 * (float)(km - 100)));
					}
					else
					{
						printf("You must have entered a new mileage less than the old mileage. - Please re-enter.\n");
						break;
					}
					repairHead = moveToList(rentedHead, repairHead, plateNum, mileage, transaction, returnDate, "repairList");
					/* Then we remove the element from rentedList with plateNum */
					rentedHead = removeFromList(rentedHead, plateNum);
					printf("The car with plates:%s has been returned, but needed repairs.\n", plateNum);
				break;
				
				
				case 4: /* Transfer a car from the repair list to the available-for-rent list */
					check = 0;
					/* Check for plate number in list of cars being rented */
					while(check != 1)/* If not found print error */
					{
						printf("Please enter the License Plate number of the car in repair (Ex. ABCD-123):\n");
						scanf("%s", plateNum);
						check = checkPlate(repairHead, plateNum);
						
						if(check == 0)
						{
							printf("That car is not in the repair list! Make sure the plate number you enter is being rented.\n");
						}
					}
					
					availableHead = moveToList(repairHead, availableHead, plateNum, mileage, transaction, returnDate, "availableList");
					/* Then we remove the element from rentedList with plateNum */
					repairHead = removeFromList(repairHead, plateNum);/* Then remove from repair list */
					
					printf("The car with plates:%s has finished being repaired and has been put into the available List.\n", plateNum);
					
				break;
				
				
				case 5: /* Rent the first available car (Move from AvailableList -> rentedList) */
				
					/* Take expected return date (int: yymmdd) */
					printf("Please enter your car's expected return date (Ex. yymmdd / 141230):\n");
					scanf("%d", &returnDate);
					
					rentedHead = rentFirstAvailable(availableHead, rentedHead, returnDate);
					
					if(rentedHead != NULL)
					{
						plateNum = findFirstPlateNum(availableHead);/* Then we remove the element from availableList with plateNum */
						availableHead = removeFromList(availableHead, plateNum); /* Remove first car from available list */
						printf("The car with plates:%s and %d KM has been moved from the available list into the rented List.\n", plateNum, mileage);
					}
					
				break;
				
				
				case 6: /* Print all the lists */
					print(availableHead, rentedHead, repairHead);
				break;
				
				
				case 7: /* Quit */
				
					/* Print total income from all the rented cars */
					printf("Total income for all the rented cars: $%.2f.\n", profit);
					
					/* Store list data to file */
					file = fopen("disk.txt", "w"); /* W opens the file in write mode - and rewrites the file from a blank */
		
					if (file == NULL)
					{
						printf("There was an error opening the file.\n");
						exit(0);
					}
					
					storeInFile(availableHead, rentedHead, repairHead, file); /* Store Lists into file */

					fclose(file);
					
					printf("Now quitting ...\n");
					exit(0);
				break;
				
				
				default:
					printf("Please enter a valid transaction code.\n");
				break;
			}
		}
		
		free(string);
		free(temp);
		free(plateNum);
	}
		
return (0);
}

