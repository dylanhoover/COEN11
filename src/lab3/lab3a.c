/*******************************************/
/*     Dylan Hoover COEN 11 Lab#3          */
/*          4 October 2018                 */
/*  Creates a waiting list using structs   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct info
{
	char names[20];
	int department;
};
struct info data[10];
struct info *p;
int counter = 0;

//delcare functions
int insert(); 
int list();
int delRow();
int checkDuplicate();
int showDepartment();

int main (void)
{
	int command;
	do
	{
		printf("Welcome to waiting room program what would you like to do\n");
		printf("1: Enter your name and department\n2: Show current waiting list\n3: Delete oldest entry\n4: Check individual department\n0: Exit program\n");
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
			case 3:
				delRow();
				break;
			case 4:
				showDepartment();
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
	int z;
	int tempi;
	char temp[20];
	if(counter > 9) //if the counter is at 9 the array is full so the insert function exits
	{
		printf("The waiting list is full\n");
	}
	else
	{	int x,y;
		do
		{
			printf("What is your name?\n");		
			scanf("%s",temp); //pulls user input into temp array
			int c = 0; //declare control int to continue code
			z = checkDuplicate(temp);
			if(z == 0)
				x = 0;
			else
				x = 1;
		}while(x == 0);
		if(z == 1) //control int is 2 run code
		{
			strcpy(data[counter].names,temp); //copy the name in temp	
			do
			{
				printf("What Department are you in? 1, 2, 3 or 4?\n");
				scanf("%d", &tempi); //scan for department number
				if(tempi == 1 || tempi == 2 || tempi == 3 || tempi == 4)
				{
					y = 1;
					data[counter].department = tempi;
					counter++; //increase the counter to insure names are inserted into the next space
					printf("\n");
				}
				else
				{
					printf("Not a department number\n");
					y = 0;
				}
			}while(y == 0);
		}	
	} 
return 0;
}

int checkDuplicate(char temp[20])
{
	struct info *p; //declare pointer
	p = data;
	int i;
	int flag = 0; //used to make sure the function runs correctly
	for(i=0; i < 10; i++, p++)
	{
		if(strcmp(temp, p->names) == 0) //check temp against all the names in data
		{
			printf("Name already in use choose a new one\n");
			return 0;
			flag = 0; 
			break;
		}
		else
		{
			flag = 1;
		}
	}	
	if(flag == 1)
	{
		return 1;
	}
}


int list()
{
	struct info *p;
	p = data;
	int i;
	printf("Names  Department\n");
	for(i = 0; i < 10; i++, p++) //run through the array
	{
		printf("%s	%d\n", p->names, p->department); //list the names and department numbers in the array
	}	
return 0;
}



int delRow()
{
	char nullStr[20] = {'\0'};
	int i;
	int x = 0;
	int cmd;
	struct info *p;
	p = data;
	struct info *d;
	d = p+1; //create pointer that is one spot pased p pointer ie data[i+1]
	do
	{
		printf("Which department:  ");	
		scanf("%d",&cmd);
		if(cmd == 1 || cmd == 2 || cmd == 3 || cmd == 4)
		{

			for(i = 0; i < 10; i++, p++, d++)
			{
				if(p->department == cmd)
				{
					for(i = 0; i < 10; i++, p++, d++)
					{
					strcpy(p->names, d->names);
					p->department = d->department;
					}
					counter --;
				}
			}
			x = 1;
		}
		else
		{
			printf("Not a department\n");
			printf("\n");
			x = 0;
		}
	}while(x == 0);
	return 0;
}

int showDepartment()
{
	int dep;
	int i;
	int j = 0;
	struct info *p;
	p = data;
	struct info *d;
	d = &p[i]; //allows for incrementing through names
	printf("What department would you like to view?\n");
	scanf("%d", &dep);
	switch(dep)
	{
		case 1:

			printf("The names in the department are:\n");
			for(i = 0; i < 10; i++, d++)
			{
				if(d->department == 1)
				{
					printf("%s\n", d->names);
					j = 1;
				}
			}
				if( j == 0)
				{
					printf("There are no names in the department\n");
					break;
				}
			printf("\n");
			break;
		case 2:
			
			printf("The names in the department are:\n");
			for(i = 0; i < 10; i++, d++)
			{
				if(d->department == 2)
				{
					printf("%s\n", d->names);
					j = 1;
				}
			}
				if(j == 0)
				{
					printf("There are no names in the department\n");
					break;
				}
			printf("\n");
			break;
		case 3:

			printf("The names in the department are:\n");
			for(i = 0; i < 10; i++, d++)
			{
				if(d->department == 3)
				{
					printf("%s\n", d->names);
					j = 1;
				}
			}
				if( j == 0)
				{
					printf("There are no names in the department\n");
					break;
				}
			printf("\n");
			break;
		case 4:	

			printf("The names in the department are:\n");
			for(i = 0; i < 10; i++, d++)
			{
				if(d->department == 4)
				{
					printf("%s\n", d->names);
					j = 1;
				}
			}
				if( j == 0)
				{
					printf("There are no names in the department\n");
					break;
				}
			printf("\n");
			break;
		default:
			printf("Error, you have selected a department that does not exist\n");
			printf("\n");
	}
return 0;
}		
