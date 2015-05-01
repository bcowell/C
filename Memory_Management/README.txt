/* README.txt
 * Brayden Cowell - 0844864
 * Assignment 3 - CIS*3110
 * Monday, Mar. 23rd, 2015
 */
 
------------------------
		README
-----------------------
dine.c
----------
Compile: make phil
Run: ./dine (num_Philosophers) (numTimes_to_eat)
Output:

Algorithms:
In my program I used pthreading to simulate the philosophers. As done with Lock / unlocking while the philosophers eat(lock) or think(unlock).

----------
holes.c
----------

Compile: make hole
Run: ./holes test.txt
Output:
Each time a process is loaded into memory I print a line:
Pid:C loaded, #processes = 3, #Holes = 2, Memusage = 89, Cumulative Mem = 70

Along with a visual display of my memory with chars indicating which processes are where, and * to represent empty space.
EX:
Current Memory Allocation:
[*][*][*][E][E][E][E][E][E][E][E][E][E][E][E][E]
[E][E][E][E][E][E][E][E][E][E][E][E][E][E][E][E]
[E][E][E][E][E][E][E][E][E][E][E][E][F][F][F][F]
[F][F][F][F][F][F][F][F][F][F][F][F][F][F][F][F]
[F][F][F][F][F][F][F][F][F][F][F][F][G][G][H][H]
[H][H][H][H][H][H][H][*][*][*][*][*][*][*][*][*]
[*][*][*][C][C][D][D][*][*][*][*][*][*][*][*][*]
[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

Algorithms:

In the order:
	while (List of processes != NULL)
	{ 
		1. firstFit
		2. worstFit
		3. bestFit
		4. nextFit
	}
For data structures I used a bitMap, linked Lists, Queues, and structs.

In my program I used a modified bitmap.
The main difference was instead of bits I used chars to represent the process id's and * to represent empty memory blocks.
Simulates all allocation strategies until the parsed queue of processes is empty.

I used linked lists for the queues to store the list of processes waiting to be put in memory, and also the list of processes already in memory.

Examples of my structs for processes and lists:

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
