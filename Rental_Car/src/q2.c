/*
	Brayden Cowell
	ID: 0844864
	Oct. 4th, 2014
	CIS 2520
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int stack[25];
int place = -1;

int push(int item)/* Function for PUSH operation */
{                       
	return stack[++place] = item;
}
 
int pop()/* Function for POP operation */
{                      
	return(stack[place--]);
}

int main(int argc, char * argv[])
{        
	char ch;
	int i;
	int op1;
	int op2;
	i = 0;
	
	
	while((ch = argv[1][i++]) != '\0')
	{
		if(isdigit(ch))
		{  
			push(ch-'0'); /* Push the operand */
		}
		
		else
		{        /* Operator,pop two  operands */
			op2 = pop();
			op1 = pop();
		
			switch(ch)
			{
				case '+':
					push(op1 + op2);
				break;
			
				case '-':
					push(op1 - op2);
				break;
			
				case '*':
					push(op1 * op2);
				break;
			
				case '/':
					push(op1 / op2);
				break;
			}
		}
	}
	
	
	printf("\n Result after Evaluation: %d\n",stack[place]);
 
	return (0);
}