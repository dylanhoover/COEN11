/************************************************************/
/*           Dylan Hoover	COEN 11 Lab #2                  */						 
/*                24 September 2018                         */
/* Creates a list that holds a name and a department number */                           
/************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int department[10], i, counter;
char names[10][20];
char temp[20];

//delcare functions
int insert(); 
int list();

int main (void)
{
	int command;

	do
	{
		printf("Welcome to waiting room program what would you like to do\n");
		printf("1: Enter your name and department      2: Show current waiting list   0: Exit program\n");
		scanf("%d", &command);
		switch(command)
		{
			case 1:
				//name insert function
				insert();
				break;
			case 2:
				//list names in array
				list();
				break;
			case 0:
				printf("Goodbye\n");
				break;
			default:
				printf("Error, you have selected a non-existant option.\n");
			
		}
	}while(command !=0); //when 0 is pressed the do loop exits
	return 0;
}

int insert()
{
		if(counter > 9) //if the counter is at 9 the array is full so the insert function exits
		{
			printf("The waiting list is full\n");
		}
		else
		{
			printf("What is your name?\n");		
			scanf("%s",temp); //pulls user input into temp array
			int c = 0; //declare control int to continue code
			for(i = 0; i < 10; i++) //loops i to 10 to run through entire array
			{
				if(strcmp(temp,names[i]) == 0) //compares the user input in temp to the names in the array, strcmp gives '0' when the names are the same
				{
					printf("Name already in use choose a new one\n");
					c = 1;
					break;
					
				}
				else
				{
					c = 2; //when names aren't the same set the control int to 2
				}
			}
			if(c == 2) //control int is 2 run code
			{
				strcpy(names[counter],temp); //copy the name in temp to the next space in the array		
				printf("What Department are you in? 1, 2, 3 or 4?\n");
				scanf("%d", &department[counter]); //scan for department number and put into next space in array
				counter++; //increase the counter to insure names are inserted into the next space
			}			
		} 
return 0;
}


int list()
{
	printf("Names  Department\n");
	for(i = 0; i < 10; i++) //run through the array
	{
		printf("%s	%d\n", names[i], department[i]); //list the names and department numbers in the array
	}	
return 0;
}




