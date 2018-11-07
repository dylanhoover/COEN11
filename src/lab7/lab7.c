/***************************************************************************************************/
/*													  	Dylan Hoover COEN 11 Lab 7                                         */
/*																			1 November 2018		                                         */
/*	Stuct of linked lists that output to a file in binary, data can be read from a file aswell     */
/***************************************************************************************************/
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
  char name[20];
  int department;
  union extra additionalInfo;
  struct node *next;
};

struct things
{
	NODE *head;
	NODE *tail;
};

struct things departments[4];

//declare functions
void insert(char* tempName, int tempDep, union extra info);
int checkDuplicate();
void list();
void delRow();
void showDepartment();
void showInfo();
void readFile();
int saveFile();
void collectData();
void deleteAll();
void changeDepartment();
void recursion();

int main(int argc, char* argv[])
{
	int command;
	int i;
	if(argc == 1)
	{
		printf("The name of the file is missing!\n");
		exit(1);
	}
	readFile(argv[1]);
	do
	{
		printf("Welcome to waiting room program what would you like to do\n");
		printf("1: Enter your name and department\n2: Show current waiting list\n3: Delete oldest entry\n4: Check individual department\n5: Additional Info\n6: Change department\n0: Exit program\n");
		scanf("%d", &command);
		switch(command)
		{
			case 1:
				//name insert function
				collectData();
				break;
			case 2:
				//list names in array
				list();
				break;
			case 3:
				deleteAll();
			//	delRow();
				break;
			case 4:
				showDepartment();
				break;
			case 5:
				showInfo();
				break;
			case 6:
				changeDepartment();
				break;
			case 0:
				saveFile(argv[1]);
				deleteAll();
				printf("Goodbye\n");
				void exit();
				break;
			default:
				printf("Error, you have selected a non-existant option.\n");
		}
	}while(command !=0); //when 0 is pressed the do loop exits
	return 0;
}

void readFile(char *file)
{
	FILE *fp; //file pointer
	struct node duh;
	char tempName[20];
	int tempDep;
	union extra info;
	fp = fopen(file, "rb"); //set file pointer to open file
	if(fp == NULL) //if the file name does not exist
	{
		printf("File does not exist.\n");
		return;
	}
	while(fread(&duh, sizeof(NODE), 1, fp) == 1)
	{
		strcpy(tempName, duh.name);
		tempDep = duh.department;
		switch(duh.department)
		{
			case 1:
				info.fever = duh.additionalInfo.fever;
				break;
			case 2:
				strcpy(info.pain, duh.additionalInfo.pain);
				break;
			case 3:
			case 4:
				info.daySick = duh.additionalInfo.daySick;
				break;
		}
		insert(tempName, tempDep, info);

	}
	fclose(fp); //close the file
	return;
}

void collectData() //collects user input data
{
	char tempName[20];
	int tempDep;
	int x = 0;
	int y = 0;
	int check = 0;
	union extra info;
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
			switch(tempDep) //different departments require different information
			{
				case 1:
					printf("What temperature is your fever?\n");
					scanf("%f", &info.fever);
					y = 1;
					break;
				case 2:
					printf("What kind of pain are you experiencing?\n");
					scanf("%s",info.pain);
					y = 1;
					break;
				case 3:
					printf("How many days have you been sick?\n");
					scanf("%d", &info.daySick);
					y = 1;
					break;
				case 4:
					printf("How many days have you been sick?\n");
					scanf("%d", &info.daySick);
					y = 1;
					break;
				default:
					printf("Not a department.\n");
			}
		}
		insert(tempName, tempDep, info);
	}
	return;
}


void insert(char* tempName, int tempDep, union extra info)
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
					printf("%s	%d		%.2f degree fever\n", p->name,p->department, p->additionalInfo.fever);
				if(p->department == 2)
					printf("%s	%d		%s pain\n", p->name, p->department, p->additionalInfo.pain);
				if(p->department == 3)
					printf("%s	%d		%d days sick\n", p->name, p->department, p->additionalInfo.daySick);
				if(p->department == 4)
					printf("%s	%d		%d days sick\n", p->name, p->department, p->additionalInfo.daySick);
				p = p->next;
			}
		}
	printf("\n");
	return;
}

void delRow()
{
	int cmd;
	int x;
	NODE *p, *q;
	while(x != 1)
	{
		printf("Which department would you like to delete from?\n");
		scanf("%d", &cmd);
		if(cmd == 1 || cmd == 2 || cmd == 3 || cmd == 4)
		{
			int dep = cmd - 1;
			p = q = departments[dep].head; // p and q equal head
			if(p == NULL)
			{
				printf("No names in department\n\n");
				return;
			}
			if(p == departments[dep].head) //if p equal head
			{
				departments[dep].head = p->next; //set head to p next
				free(p); //remove p
			}
			//last or middle
			else
			{
				q->next = p->next; //set q next to p next to unlink p
				free(p);
			}
				x = 1;
		}
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
	union extra info;
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
								scanf("%f", &info.fever);;
								flag = 1;
								z = 1;
								break;
							case 2:
								printf("What kind of pain are you experiencing?\n");
								scanf("%s", info.pain);
								flag = 1;
								z = 1;
								break;
							case 3:
								printf("How many days have you been sick?\n");
								scanf("%d", &info.daySick);
								flag = 1;
								z = 1;
								break;
							case 4:
								printf("How many days have you been sick?\n");
								scanf("%d", &info.daySick);
								flag = 1;
								z = 1;
								break;
							default:
								printf("Not a department.\n");

						}
					}while(z != 1);
						insert(tempName, tempDep, info);;
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

void showInfo()
{
	int i;
	int flag = 0;
	int x = 0;
	int ctl;
	char tempName[20];
	NODE *p;

	 //temp name string to compare the name given with names in the list
	while(x == 0)
	{
		printf("What name would you like to see more information for?\n");
		scanf("%s", tempName); //get name
		for(i = 0; i < 4; i++)
		{
			p = departments[i].head;
			while(p != NULL) //loop through the array data
			{
				if(strcmp(tempName, p->name) == 0) //compare the name given to the names in the array
				{
					ctl = p->department;
				/*The name given is displayed and depending on keep the information is displayed*/
					switch(ctl)
					{
						case 1:
							printf("%s has a %.2f degree fever.\n", tempName, p->additionalInfo.fever);
							printf("\n");
							flag = 1;
							break;
						case 2:
							printf("%s has %s pain.\n", tempName, p->additionalInfo.pain);
							printf("\n");
							flag = 1;
							break;
						case 3:
							printf("%s has been sick for %i days.\n", tempName, p->additionalInfo.daySick);
							printf("\n");
							flag = 1;
							break;
						case 4:
							printf("%s has been sick for %i days.\n", tempName, p->additionalInfo.daySick);
							printf("\n");
							flag = 1;
							break;
					}
				}
				p = p->next;
			}
		}
		if(flag == 0)
		{
			printf("Name not in list\n");
			return;
		}
		else if(flag == 1)
			x = 1;
	}
	return;
}


int saveFile(char *file)
{
	NODE *p;
	FILE *ofp; //file pointer
	int i;
	ofp = fopen(file, "wb"); //set file pointer to file name specified
	for(i = 0; i < 4; i++) //iterate through the array
	{
		p = departments[i].head; //set p to head
		while(p != NULL)
		{
			fwrite(p, sizeof(NODE), 1, ofp);
			p = p->next;
		}
	}
	fclose(ofp); //close file
	return 0;
}

void deleteAll()
{
	int i;
	NODE *p, *q;
	for(i = 0; i < 4; i++) //iterate through array
	{
		p=departments[i].head; //set p to head
		recursion(p);
		departments[i].head = NULL; //NULL the whole array after

	}
	return;
}

void recursion(NODE *p)
{
	if(p == NULL)
		return;
	recursion(p->next);
	free(p);
	return;
}
