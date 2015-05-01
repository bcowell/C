/* holes.c
 * Brayden Cowell - 0844864
 * Assignment 3 - CIS*3110
 * Monday, Mar. 23rd, 2015
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct process_s
{
	char id;
	int size;
	int swap;
	int pos;
}process;

typedef struct list_s
{
	process * p;
	struct list_s * next;
}list;

char memory[128];
int holes[128][1];
int numHoles = 0;
int totalLoads = 0;
int numProcesses = 0;
float memUsage = 0.0;
int memCount = 0;
float cumulativeMem = 0.0;

/* Function declarations */
void display();
void parse(char * fileName, list ** head);
void addToQueue(process * p, list ** head);
void addToFront(process * p, list ** head);
void displayQueue(list * head);
process * removeFromQueue(list ** head);
int countHoles();
void firstFit(list ** head, list ** load);
void worstFit(list ** head, list ** load);
void bestFit(list ** head, list ** load);
void nextFit(list ** head, list ** load, int pos);


int main(int argc, char * argv[])
{
	list * head = NULL;
	list * load = NULL;
	int i;
	int pos = 0;
	
	if (argc != 2) /* Check for command-line args */
	{
		printf("Usage: ./holes fileName\n");
	}

	for (i = 0; i < 128; i++) /* Initalize memory as empty */
	{
		memory[i] = '*';
	}
	
	for (i = 0; i < 128; i++) /* Initalize holes to have space */
	{
		holes[i][0] = 0;
	}
	
	parse(argv[1], &head); /* Parse the input file */
	display();
	
	printf("Parsed Queue:\n");
	displayQueue(head);
	printf("\n");
	
	while (head != NULL)
	{ 
		firstFit(&head, &load); /* First Fit */
		worstFit(&head, &load); /* Worst Fit */
		bestFit(&head, &load); /* Best Fit */
		nextFit(&head, &load, pos); /* Next Fit */
	}

	printf("Total Loads = %d, Avg.#Processes = %.f, Avg.#Holes = %.f, Cumulative_Mem = %.f\n", totalLoads, (float)numProcesses, (float)numHoles, (cumulativeMem/memCount));
	
	return (0);
 }

void display()
{
	int i, j, h = 0;
	
	printf("Current Memory Allocation:\n");
	
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 16; j++)
		{
			if (memory[h] == '*')
			{
				printf("[*]" );
			}
			
			else
			{
				printf("[%c]", memory[h]);
			}
			h++;
		}
		printf("\n");
	}
	printf("\n");
}

void parse(char * fileName, list ** head)
{
	FILE * fp;
	char * string = (char *)malloc(sizeof(char *)*30);
	char * token;
	char id;
	int size = 0;
	
	fp = fopen(fileName, "r"); /* Read the file */
	if (fp == NULL)
	{
		printf("Error: Opening file.\n");
		exit(1);
	}
	
	while ((fgets(string, 20, fp)) != NULL)
	{
		token = strtok(string, " ");
		id = token[0];
		
		token = strtok(NULL, " ");
		size = atoi(token);
		
		process * p; 
		p = malloc(sizeof(process));
		p->id = id;
		p->size = size;
		p->swap = 3;
		p->pos = size-1;
		
		addToQueue(p, head);
	}
	fclose(fp);
	free(string);
}

void addToQueue(process * p, list ** head)
{
	list * temp = malloc(sizeof(list));
	temp->p = p;
	temp->next = NULL;
	
	if (*head == NULL)  /* If there is no head - create a new one */
	{
		*head = temp;
	}
	
	else /* Insert at end of list */
	{
		list * current;
		for (current = *head; current->next != NULL; current = current->next)
		{
		}
		current->next = temp;
	}
}

void addToFront(process * p, list ** head)
{
	list * temp = malloc(sizeof(list));
	temp->p = p;
	
	if (*head == NULL) /* If there is no head - create a new one */
	{
		temp->next = NULL;
		*head = temp;
	}
	
	else /* Insert at beginning of list */
	{
		temp->next = *head;
		*head = temp;
	}
}

void displayQueue(list * head)
{
	while (head != NULL) /* navigate to end of queue */
	{
		printf("pid: %c, psize: %d, pswap: %d\n", head->p->id, head->p->size, head->p->swap);
		head = head->next;
	}
}

process * removeFromQueue(list ** head)
{
	process * temp;
	
	temp = (*head)->p;
	if ((*head)->next != NULL)
	{
		(*head) = (*head)->next;
	}
	else
	{
		(*head) = NULL;
	}
	return (temp);
}

int countHoles()
{
	int i, pos, count, j;
	
	for (i = 0; i < 128; i++) /* Reset holes */
	{
		holes[i][0] = 0;
	}
	
	for (i = 0; i < 128; i++)
	{
		count = 0;
		if (!isalpha(memory[i])) /* When memory is empty */
		{
			pos = i;
			j = i;
			while ((!isalpha(memory[j])) && (j != 128)) /* Keep counting until you hit a char or end of memory */
			{
				count++;
				j++;
			}
			
			/* When we encounter a char */
			holes[pos][0] = count;
			i = j;
		}
	}
	count = 0;
	/* Count the number of Holes */
	for (i = 0; i < 128; i++)
	{
		
		if (holes[i][0] != 0)
		{
			/* printf("i: %d size: %d\n", i, holes[i][0]); */
			count += 1;
			numHoles += 1;
		}
	}
	return (count);
}

void firstFit(list ** head, list ** load)
{
	int i, h, inserted = 0;
	
	
	if (*head == NULL)
	{
		printf("Queue is empty.\n");
		exit(1);
	}
	
	process * p = removeFromQueue(head);
	
	
	/* Go through memory and find the first hole large enough to store process */
	numHoles = countHoles();
		
	for (i = 0; i < 128; i++)
	{
		if (((holes[i][0] >= p->size)) && (inserted == 0)) /* Find first hole that will fit */
		{
			/* Insert the process into memory space */
			p->pos = i;
			memUsage += p->size;
			cumulativeMem += (memUsage/128)*100;
			memCount += 1;
			for (h = i; h < (p->size + p->pos); h++)
			{
				memory[h] = p->id;
			}
			numProcesses += 1;
			totalLoads += 1;
			inserted = 1;	
			addToQueue(p, load); /* Load process into the memory list */
			/* Print statement for loading process into memory */
			printf("Pid:%c loaded, #processes = %d, #Holes = %d, Memusage = %.f, Cumulative Mem = %.f\n", (p->id), numProcesses, numHoles, (memUsage/128)*100, (cumulativeMem/memCount));
			display();
			break;
		}
	}
	
	if (inserted == 0) /* If no holes large enough are found */
	{
		/* Swap oldest process out and re-call first fit */
		process * q = removeFromQueue(load);
		numProcesses -= 1;
		q->swap -= 1;
		memUsage -= q->size;
		/* Remove from memory */
		for (i = q->pos; i < (q->size + q->pos); i++)
		{
			memory[i] = '*';
		}
		
		if (q->swap > 0)
		{
			/* Re-insert into the process queue */
			addToQueue(q, head);
		}
		
		addToFront(p, head); /* Re Add the cut process to the process queue */
		/* Process has completed (Do not requeue) */
		firstFit(head, load); /* Call recursively */
	}
	
}

void worstFit(list ** head, list ** load)
{
	int i, h, inserted = 0;
	int greatest = 0;
	int pos = 0;
	int found = 0;
	
	if (*head == NULL)
	{
		printf("Queue is empty.\n");
		exit(1);
	}
	
	process * p = removeFromQueue(head);
	
	
	/* Go through memory and find the first hole large enough to store process */
	numHoles = countHoles();
	
	for (i = 0; i < 128; i++) /* Calculate the largest hole that will fit the process */
	{
		if ((holes[i][0] >= p->size) && (holes[i][0] > greatest))
		{
			greatest = holes[i][0];
			pos = i;
			found = 1;
		}
	}
			
	if (found == 1) /* Find first hole that will fit */
	{
		/* Insert the process into memory space */
		p->pos = pos;
		memUsage += p->size;
		cumulativeMem += (memUsage/128)*100;
		memCount += 1;
		for (h = pos; h < (p->size + p->pos); h++)
		{
			memory[h] = p->id;
		}
		numProcesses += 1;
		totalLoads += 1;
		inserted = 1;	
		addToQueue(p, load); /* Load process into the memory list */
		/* Print statement for loading process into memory */
		printf("Pid:%c loaded, #processes = %d, #Holes = %d, Memusage = %.f , Cumulative Mem = %.f \n", (p->id), numProcesses, numHoles, (memUsage/128)*100, (cumulativeMem/memCount));
		display();
	}
	
	
	if (inserted == 0) /* If no holes large enough are found */
	{
		/* Swap oldest process out and re-call first fit */
		process * q = removeFromQueue(load);
		numProcesses -= 1;
		q->swap -= 1;
		memUsage -= q->size;
		/* Remove from memory */
		for (i = q->pos; i < (q->size + q->pos); i++)
		{
			memory[i] = '*';
		}
		
		if (q->swap > 0)
		{
			/* Re-insert into the process queue */
			addToQueue(q, head);
		}
		
		addToFront(p, head); /* Re Add the cut process to the process queue */
		/* Process has completed (Do not requeue) */
		worstFit(head, load); /* Call recursively */
	}
	
}

void bestFit(list ** head, list ** load)
{
	int i, h, inserted = 0;
	int smallest = 128;
	int pos = 0;
	int found = 0;
	
	if (*head == NULL)
	{
		printf("Queue is empty.\n");
		exit(1);
	}
	
	process * p = removeFromQueue(head);
	
	
	/* Go through memory and find the first hole large enough to store process */
	numHoles = countHoles();
	
	for (i = 0; i < 128; i++) /* Calculate the largest hole that will fit the process */
	{
		if ((holes[i][0] >= p->size) && (holes[i][0] < smallest))
		{
			smallest = holes[i][0];
			pos = i;
			found = 1;
		}
	}
			
	if (found == 1) /* Find first hole that will fit */
	{
		/* Insert the process into memory space */
		p->pos = pos;
		memUsage += p->size;
		cumulativeMem += (memUsage/128)*100;
		memCount += 1;
		for (h = pos; h < (p->size + p->pos); h++)
		{
			memory[h] = p->id;
		}
		numProcesses += 1;
		totalLoads += 1;
		inserted = 1;	
		addToQueue(p, load); /* Load process into the memory list */
		/* Print statement for loading process into memory */
		printf("Pid:%c loaded, #processes = %d, #Holes = %d, Memusage = %.f, Cumulative Mem = %.f\n", (p->id), numProcesses, numHoles, (memUsage/128)*100, (cumulativeMem/memCount));
		display();
	}
	
	
	if (inserted == 0) /* If no holes large enough are found */
	{
		/* Swap oldest process out and re-call first fit */
		process * q = removeFromQueue(load);
		numProcesses -= 1;
		q->swap -= 1;
		memUsage -= q->size;
		/* Remove from memory */
		for (i = q->pos; i < (q->size + q->pos); i++)
		{
			memory[i] = '*';
		}
		
		if (q->swap > 0)
		{
			/* Re-insert into the process queue */
			addToQueue(q, head);
		}
		
		addToFront(p, head); /* Re Add the cut process to the process queue */
		/* Process has completed (Do not requeue) */
		bestFit(head, load); /* Call recursively */
	}
	
}

void nextFit(list ** head, list ** load, int pos)
{
	int i, h, inserted = 0;
	
	
	if (*head == NULL)
	{
		printf("Queue is empty.\n");
		exit(1);
	}
	
	process * p = removeFromQueue(head);
	
	
	/* Go through memory and find the first hole large enough to store process */
	numHoles = countHoles();
		
	for (i = pos; i < 128; i++)
	{
		if (((holes[i][0] >= p->size)) && (inserted == 0)) /* Find first hole that will fit */
		{
			if (pos >= 128)
			{
				pos = 0;
			}
				
			/* Insert the process into memory space */
			p->pos = i;
			memUsage += p->size;
			cumulativeMem += (memUsage/128)*100;
			memCount += 1;
			for (h = i; h < (p->size + p->pos); h++)
			{
				memory[h] = p->id;
			}
			numProcesses += 1;
			totalLoads += 1;
			inserted = 1;	
			addToQueue(p, load); /* Load process into the memory list */
			/* Print statement for loading process into memory */
			printf("Pid:%c loaded, #processes = %d, #Holes = %d, Memusage = %.f, Cumulative Mem = %.f\n", (p->id), numProcesses, numHoles, (memUsage/128)*100, (cumulativeMem/memCount));
			display();
			pos = h;
			break;
		}
	}
	
	if (inserted == 0) /* If no holes large enough are found */
	{
		/* Swap oldest process out and re-call first fit */
		process * q = removeFromQueue(load);
		numProcesses -= 1;
		q->swap -= 1;
		memUsage -= q->size;
		/* Remove from memory */
		for (i = q->pos; i < (q->size + q->pos); i++)
		{
			memory[i] = '*';
		}
		
		if (q->swap > 0)
		{
			/* Re-insert into the process queue */
			addToQueue(q, head);
		}
		
		addToFront(p, head); /* Re Add the cut process to the process queue */
		/* Process has completed (Do not requeue) */
		nextFit(head, load, pos); /* Call recursively */
	}
	
}
