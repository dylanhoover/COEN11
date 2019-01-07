#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "proj.h"
#include <pthread.h>
#define DEPCHECK(x) ((((x) < 5) && ((x) != 0)) ? 1:0)



void insert(char* tempName, int tempDep, union Extra *info)
{
	/* All data is passed to insert, both from read file and collect data functions*/
	int y;
	NODE *p, *q;
	NODE *temp;
	temp = (NODE*)malloc(sizeof(NODE));
	strcpy(temp->name, tempName);
	temp->department = tempDep; //copies department to temp node
	temp->additionalInfo = info; //copies additional info to temp node
	p = departments[tempDep-1].head; //set p to the first array
	q = departments[tempDep-1].tail; //set q to the first array
	pthread_mutex_lock(&mutex);
	if(p == NULL) //if the linked list is empty
	{
		temp->next = NULL; //temp next is null
		departments[tempDep-1].tail = departments[tempDep-1].head  = temp; //tail is head and head is temp
	}
	else //list has information
	{
		temp->next = NULL;
		q->next = temp; //tail next points to temp
		q = temp; //tail is equal to temp				
	}
	pthread_mutex_unlock(&mutex);
	return;
}

int checkDuplicate(char name[20])
{
	NODE *p;
	int i;
	for(i = 0; i < 4; i++) //iterate through the array
	{
		p = departments[i].head; //sets p to head
		while(p != NULL) //while p doesn't reach the end of the linked list
		{
			if(strcmp(name, p->name) == 0)
			{
				printf("Name already in use, please choose a new one.\n");
				return 0;
			}
			p = p->next;
		}
	}
	return 1;
}

void list()
{
	NODE *p;
	int i;
	printf("Names	Department	Issue\n");
		for(i = 0; i < 4; i++)
		{
			p = departments[i].head;
		/*depending on keep a different printf has to be used because of the union*/
			while(p != NULL)
			{
				if(p->department == 1)
					printf("%s	%d		%.2f degree fever\n", p->name,p->department, p->additionalInfo->fever);
				if(p->department == 2)
					printf("%s	%d		%s pain\n", p->name, p->department, p->additionalInfo->pain);
				if(p->department == 3)
					printf("%s	%d		%d days sick\n", p->name, p->department, p->additionalInfo->daySick);
				if(p->department == 4)
					printf("%s	%d		%d days sick\n", p->name, p->department, p->additionalInfo->daySick);
				p = p->next;
			}
		}
	printf("\n");
	return;
}

void collectData() //collects user input data
{
	char tempName[20];
	int tempDep;
	int x = 0;
	int y = 0;
	int check = 0;
	union Extra *info;
	while(x != 1)
	{
		printf("What is your name?\n");
		scanf("%s", tempName);
		check = checkDuplicate(tempName);
		if(check == 1)
		{
			x = 1;
		}
	}
	if(check == 1)
	{
		while(y != 1)
		{
			printf("What department are you in?\n");
			scanf("%d", &tempDep);
			int w = DEPCHECK(tempDep);
			if(w == 1)
			{
				switch(tempDep) //different departments require different information
				{
					case 1:
						printf("What temperature is your fever?\n");
						scanf("%f", &info->fever);
						y = 1;
						break;
					case 2:
						printf("What kind of pain are you experiencing?\n");
						scanf("%s",info->pain);
						y = 1;
						break;
					case 3:
						printf("How many days have you been sick?\n");
						scanf("%d", &info->daySick);
						y = 1;
						break;
					case 4:
						printf("How many days have you been sick?\n");
						scanf("%d", &info->daySick);
						y = 1;
						break;
				}
			}
			else
				printf("Not a department\n");
		}
		insert(tempName, tempDep, info);
	}
	return;
}

void showDepartment()
{
	int dep;
	int x = 0;
	NODE *p;
	while(x != 1)
	{
		printf("What department would you like to view?\n");
		scanf("%d", &dep);
		if(dep == 1 || dep == 2 || dep == 3 || dep == 4) //makes sure only the correct departments can be inserted
		{
			int ctl = dep - 1;
			printf("The names in the department are:\n");
			p = departments[ctl].head;
			while(p != NULL)
			{
				printf("%s\n", p->name); //prints the names in the department
				x = 1; //makes sure the while loop exits;
				p = p->next;
			}
			if(p == NULL)//if j is not set equal to 1 by the previous loop then there are no names in the department
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
	}
	return;
}

void changeDepartment()
{
	int i;
	char tempName[20];
	int tempDep;
	int x = 0, z = 0;
	int flag = 0;
	NODE *p, *q;
	union Extra *info;
	while(x == 0)
	{
		printf("What is your name?\n");
		scanf("%s", tempName);
		for(i = 0; i < 4; i++)
		{
			p = q = departments[i].head;
			while(p != NULL)
			{
				if(strcmp(tempName, p->name) == 0)
				{
					if(p == departments[i].head) //basically the remove function
					{
						departments[i].head = p->next;
						free(p);
					}
					//last or middle
					else
					{
						q->next = p->next;
						free(p);
					}
					do
					{
						printf("What department do you want to swtich to?\n");
						scanf("%d", &tempDep);
						switch(tempDep) //this gets back the additional information
						{
							case 1:
								printf("What temperature is your fever?\n");
								scanf("%f", &info->fever);
								flag = 1;
								z = 1;
								break;
							case 2:
								printf("What kind of pain are you experiencing?\n");
								scanf("%s", info->pain);
								flag = 1;
								z = 1;
								break;
							case 3:
								printf("How many days have you been sick?\n");
								scanf("%d", &info->daySick);
								flag = 1;
								z = 1;
								break;
							case 4:
								printf("How many days have you been sick?\n");
								scanf("%d", &info->daySick);
								flag = 1;
								z = 1;
								break;
							default:
								printf("Not a department.\n");

						}
					}while(z != 1);
						insert(tempName, tempDep, info);
						return;
				}

				else
				{
					p = p->next;
				}
			}
		}
		if(flag == 0)
		{
			printf("Name not in list.\n");
		}
	}
	return;
}

void deleteAll()
{
	int i;
	NODE *p, *q;
	for(i = 0; i < 4; i++) //iterate through array
	{
		p=departments[i].head; //set p to head
		recursion(p); //pass pointer to recursion
		departments[i].head = NULL; //NULL the whole array after

	}
	return;
}

void recursion(NODE *p)
{
	if(p == NULL) //if the pointer is null
		return;
	recursion(p->next); //pass the arrow to the next node
	free(p); //free the node
	return;
}