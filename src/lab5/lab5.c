/*********************************************/
/*         Dylan Hoover COEN 11 Lab 5        */
/*              18 October 2018              */
/* Creates a wating list using a linked list */
/*********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NODE struct node
union extra
{
	float fever;
	char pain[30];
	int daySick;
};
struct node
{
	char names[20];
	int department;
	int keep;
	union extra additionalInfo;
	struct node *next;
};
int counter = 0;
NODE *head = NULL;
NODE *tail = NULL;

//delcare functions
void insert();
void list();
void delRow();
int checkDuplicate();
void showDepartment();
void showInfo();

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

void insert()
{
	NODE *p, *q;
	NODE *temp;
	temp = (NODE *)malloc(sizeof(NODE));
	p = q = head;
	int z; //control variable
	int tempi; //temporary interger holder
	char tempName[20]; //temporary name holder
	int x,y;
		do //this loop is to make sure when the names are the same the code doesn't continue to run
		{
			printf("What is your name?\n");
			scanf("%s",tempName); //pulls user input into temp array
			int c = 0; //declare control int to continue code
			z = checkDuplicate(tempName); //z control is set to the return of checkDuplicate
			if(z == 0)
				x = 0; //will keep the do while loop going
			else
				x = 1;
		}while(x == 0);
		if(z == 1) //z is returned from the checkDuplicate
		{
			strcpy(temp->names,tempName); //copy the name in temp
			do
			{
				printf("What Department are you in? 1, 2, 3 or 4?\n");
				scanf("%d", &tempi); //scan for department number
				if(tempi == 1 || tempi == 2 || tempi == 3 || tempi == 4) //makes sure the department number is only one of these numbers
				{
					y = 1; //y control vairable defintion
					temp->department = tempi; //sets department equal to the given department
					temp->keep = tempi; //sets int keep for the union equal to the given department
					/* These if statements depend on what department is being choosen */
					if(temp->keep == 1)
					{
						printf("What temperature is your fever?\n");
						scanf("%f", &temp->additionalInfo.fever);
					}
					else if(temp->keep == 2)
					{
						printf("What kind of pain are you experiencing?\n");
						scanf("%s", temp->additionalInfo.pain);
					}
					else if(temp->keep == 3)
					{
						printf("How many days have you been sick?\n");
						scanf("%d", &temp->additionalInfo.daySick);
					}
					else if(temp->keep == 4)
					{
						printf("How many days have you been sick?\n");
						scanf("%d", &temp->additionalInfo.daySick);
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
		//empty list
		if(p == NULL)
		{
			temp->next = NULL;
			tail = head = temp;
		}
		//list not empty, adds to the end
		else
		{
			temp->next = NULL; //temp arry next pointer goes to null
			tail->next = temp;
			tail = temp;
		}
return;
}

int checkDuplicate(char temp[20])
{
	NODE *p;
	p = head;
	while(p != NULL)
	{
		if(strcmp(temp, p->names) == 0) //check temp against all the names in data
		{
			printf("Name already in use choose a new one\n");
			return 0; //when 0 is returned the insert function will ask for a new name
		}
		p = p->next;
	}
	return 1; //retruning 1 lets the insert function continue
}


void list()
{
	NODE *p;
	int i;
	p = head;
	printf("Names	Department	Issue\n");
	while(p != NULL)
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
		p = p->next;
	}
	printf("\n");
return;
}

void delRow()
{
	int x = 0;
	int cmd;
	NODE *p, *q;
	p = q = head;
	do
	{
		printf("Which department:  ");
		scanf("%d",&cmd);
		if(cmd == 1 || cmd == 2 || cmd == 3 || cmd == 4) //the cmd is the same as the department selection
		{
			while( p != NULL)
			{
				if(p->department == cmd) //if the department exists then the next for loop will run
				{
					x = 1;
					break;
				}

				q = p;
				p = p->next;
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

	if(p == NULL)
	{
		printf("No names in department\n\n");
		return;
	}
	//First node
	if(p == head)
	{
		head = p->next;
		free(p);
	}
	//last or middle
	else
	{
		q->next = p->next;
		free(p);
	}
	return;
}

void showDepartment()
{
	int dep;
	int i;
	int j = 0;
	int x = 0;
	NODE *p;
	p = head; //decalre p
	do
	{
		printf("What department would you like to view?\n");
		scanf("%d", &dep);
		if(dep == 1 || dep == 2 || dep == 3 || dep == 4) //makes sure only the correct departments can be inserted
		{
			printf("The names in the department are:\n");
			while(p != NULL)
			{
				if(p->department == dep) //if the department is equal to the choosen department then the code will run
				{
					printf("%s\n", p->names); //prints the names in the department
					x = 1; //makes sure the do while loop exits;
					j = 1;
				}
				p = p->next;

			}
				if( j == 0)//if j is not set equal to 1 by the previous loop then there are no names in the department
				{
					printf("\n");
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
	return;
}

void showInfo()
{
int i;
int flag = 0;
int x = 0;
int ctl;
char tempName[20];
NODE *p;

 //temp name string to compare the name given with names in the list
do
{
	p = head;
	printf("What name would you like to see more information for?\n");
	scanf("%s", tempName); //get name
	//flag = test(tempName);
	while(p != NULL) //loop through the array data
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
		p = p->next;
	}
	if(flag == 0)
		printf("Name not in list\n");
	else if(flag == 1)
		x = 1;
}while(x == 0);
return;
}
