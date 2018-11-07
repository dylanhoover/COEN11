/*******************************************************************************/
/*                       Dylan Hoover COEN 11 Lab #4                           */
/*                             11 October 2018                                 */
/* Creates a waitng list using a struct with extra information kept in a union */
/*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
union extra
{
	float fever;
	char pain[30];
	int daySick;
};
struct info
{
	char names[20];
	int department;
	int keep;
	union extra additionalInfo;
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
int showInfo();

int main (void)
{
	int command;
	do
	{
		printf("Welcome to waiting room program what would you like to do\n");
		printf("1: Enter your name and department\n2: Show current waiting list\n3: Delete oldest entry\n4: Check individual department\n5: Additional Info\n0: Exit program\n");
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
			case 5:
				showInfo();
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
	int z; //control variable
	int tempi; //temporary interger holder
	char temp[20]; //temporary name holder
	if(counter > 9) //if the counter is at 9 the array is full so the insert function exits
	{
		printf("The waiting list is full\n");
	}
	else
	{	int x,y;
		do //this loop is to make sure when the names are the same the code doesn't continue to run
		{
			printf("What is your name?\n");		
			scanf("%s",temp); //pulls user input into temp array
			int c = 0; //declare control int to continue code
			z = checkDuplicate(temp); //z control is set to the return of checkDuplicate
			if(z == 0)
				x = 0; //will keep the do while loop going
			else
				x = 1;
		}while(x == 0);
		if(z == 1) //z is returned from the checkDuplicate
		{
			strcpy(data[counter].names,temp); //copy the name in temp	
			do
			{
				printf("What Department are you in? 1, 2, 3 or 4?\n");
				scanf("%d", &tempi); //scan for department number
				if(tempi == 1 || tempi == 2 || tempi == 3 || tempi == 4) //makes sure the department number is only one of these numbers
				{
					y = 1;
					data[counter].department = tempi; //sets department equal to the given department
					data[counter].keep = tempi; //sets int keep for the union equal to the given department
					/* These if statements depend on what department is being choosen */
					if(data[counter].keep == 1) 
					{
						printf("What temperature is your fever?\n");
						scanf("%f", &data[counter].additionalInfo.fever);
					}
					else if(data[counter].keep == 2)
					{
						printf("What kind of pain are you experiencing?\n");
						scanf("%s", data[counter].additionalInfo.pain);
					}
					else if(data[counter].keep == 3)
					{
						printf("How many days have you been sick?\n");
						scanf("%d", &data[counter].additionalInfo.daySick);
					}
					else if(data[counter].keep == 4)
					{
						printf("How many days have you been sick?\n");
						scanf("%d", &data[counter].additionalInfo.daySick);
					}
					counter++; //increase the counter to insure names are inserted into the next space
					printf("\n");
				}
				else //if the correct deparment number is not given the do while loop will not exit
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
	for(i=0; i < 10; i++, p++)
	{
		if(strcmp(temp, p->names) == 0) //check temp against all the names in data
		{
			printf("Name already in use choose a new one\n");
			return 0; //when 0 is returned the insert function will ask for a new name
		}
		else
		{
			return 1; //retruning 1 lets the insert function continue
		}
	}	
}


int list()
{
	struct info *p;
	p = data;
	int i;
	printf("Names	Department	Issue\n");
	for(i = 0; i < 10; i++, p++) //run through the array
	{
		/*depending on keep a different printf has to be used because of the union*/
		if(p->keep == 1)
			printf("%s	%d		%.2f degree fever\n", p->names,p->department, p->additionalInfo.fever);
		if(p->keep == 2)
			printf("%s	%d		%s pain\n", p->names, p->department, p->additionalInfo.pain);
		if(p->keep == 3)
			printf("%s	%d		%d days sick\n", p->names, p->department, p->additionalInfo.daySick);
		if(p->keep == 4)
			printf("%s	%d		%d days sick\n", p->names, p->department, p->additionalInfo.daySick);
	}	
	printf("\n");
return 0;
}



int delRow()
{
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
		if(cmd == 1 || cmd == 2 || cmd == 3 || cmd == 4) //the cmd is the same as the department selection
		{

			for(i = 0; i < 10; i++, p++, d++)
			{
				if(p->department == cmd) //if the department exists then the next for loop will run
				{
					for(i = 0; i < 10; i++, p++, d++)
					{
						strcpy(p->names, d->names); //copies the names up the list
						p->department = d->department; //copies the departments up the list
						//The keep int is coppied so that the data in the union can be copied as well which is what is happening in the if statements, they only run through the correct department
						if(cmd == 1)
						{
							p->keep = d->keep; 
							p->additionalInfo.fever = d->additionalInfo.fever;
						}
						if(cmd == 2)
						{
							p->keep = d->keep;
							strcpy(p->additionalInfo.pain, d->additionalInfo.pain);
						}
						if(cmd == 3)
						{
							p->keep = d->keep;
							p->additionalInfo.daySick = d->additionalInfo.daySick;
						}
						if(cmd == 4)
						{
							p->keep = d->keep;
							p->additionalInfo.daySick = d->additionalInfo.daySick;
						}
					}
					counter --; //brings the counter back down so the list gets inserted into correctly
				}
			}
			x = 1; //allows for the do while loop to exit
		}
		else //if the correct department is not inserted
		{
			printf("Not a department\n");
			printf("\n");
			x = 0; //reruns the do while loop
		}
	}while(x == 0);
	return 0;
}

int showDepartment()
{
	int dep;
	int i;
	int j = 0;
	int x = 0;
	struct info *p;
	p = data;
	struct info *d;
	d = &p[i]; //allows for incrementing through names
	do
	{
		printf("What department would you like to view?\n");
		scanf("%d", &dep);
		if(dep == 1 || dep == 2 || dep == 3 || dep == 4) //makes sure only the correct departments can be inserted
		{
			printf("The names in the department are:\n");
			for(i = 0; i < 10; i++, d++)
			{
				if(d->department == dep) //if the department is equal to the choosen department then the code will run
				{
					printf("%s\n", d->names); //prints the names in the department
					x = 1; //makes sure the do while loop exits;
					j = 1;
				}
			}
				if( j == 0)//if j is not set equal to 1 by the previous loop then there are no names in the department
				{
					printf("There are no names in the department\n");
					break;
					x = 1; //will allow the do while loop to exit
				}
			printf("\n");
		}
		else //if a number is choosen that is not a department
		{
			printf("Not a department\n");
			printf("\n");
		}
	}while(x == 0);
}	

int showInfo()
{
int i;
int flag = 0;
int x = 0;
int ctl;
char tempName[20];
struct info *p;
 //temp name string to compare the name given with names in the list
do
{	
	p = data;
	printf("What name would you like to see more information for?\n");
	scanf("%s", tempName); //get name
	//flag = test(tempName);
	for(i = 0; i < 10; i++, p++) //loop through the array data
	{
		if(strcmp(tempName, p->names) == 0) //compare the name given to the names in the array
		{
			ctl = p->keep;
		/*keep is the same as the department*/
		/*The name given is displayed and depending on keep the information is displayed*/
			switch(ctl)
			{
				case 1:
					printf("%s has a %.2f degree fever.\n", tempName, p->additionalInfo.fever); 
					printf("\n");
					//return 0;
					flag = 1;
					break;
				case 2:
					printf("%s has %s pain.\n", tempName, p->additionalInfo.pain);
					printf("\n");
					//return 0;
					flag = 1;
					break;
				case 3:
					printf("%s has been sick for %i days.\n", tempName, p->additionalInfo.daySick);
					printf("\n");
					//return 0;
					flag = 1;
					break;
				case 4:
					printf("%s has been sick for %i days.\n", tempName, p->additionalInfo.daySick);
					printf("\n");
					//return 0;
					flag = 1;
					break;

				}	
		}
	}			
	if(flag == 0)
		printf("Name not in list\n");
	else if(flag == 1)
		x = 1;
}while(x == 0);
return 0;
}
