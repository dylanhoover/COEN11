#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "proj.h"


void readFile(char *file, int key)
{
	FILE *fp; //file pointer
	char tempName[20];
	int tempDep;
	char temp[60];
	int i;
	union Extra *info;
	fp = fopen(file, "r"); //set file pointer to open file
	if(fp == NULL) //if the file name does not exist
	{
		printf("File does not exist.\n");
		return;
	}

   while(fgets(temp, 60, fp) != NULL) //while the data inputed into temp is not null
   {
	    for(i = 0; temp[i] != '\n'; i++)
	    {
		   temp[i] = ((temp[i]) ^ (key)); //cycles through all the characters and decrypts them
	    }
		sscanf(temp, "%s\t%d\t", tempName, &tempDep); //gets the info
		switch(tempDep)
		{
			case 1:
				sscanf(temp, "%s\t%d\t%f\n", tempName, &tempDep, &info->fever);
				insert(tempName, tempDep, info);
				break;
			case 2:
				sscanf(temp, "%s\t%d\t%s\n", tempName, &tempDep, info->pain);
				insert(tempName, tempDep, info);
				break;
			case 3:
			case 4:
				sscanf(temp, "%s\t%d\t%d\n", tempName, &tempDep, &info->daySick);
				insert(tempName, tempDep, info);
				break;
		}
   }

	fclose(fp); //close the file
	return;
}

void *autoSave(char *file)
{
	NODE *p;
	FILE *ofp; //file pointer
	int i;
	while(1) //infinite while loop so the thread function is always running
	{
		pthread_mutex_lock(&mutex); //always lock when editing the list and reading from the list
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
		pthread_mutex_unlock(&mutex);
    //    printf("Sleeping\n");
		sleep(15);
     //   printf("waking up\n");
	}

}

int saveFile(char *file, int key)
{
	NODE *p;
	FILE *ofp; //file pointer
	int i;
	int j;
	char buffer[70];
	ofp = fopen(file, "w"); //set file pointer to file name specified
	//fprintf(ofp, "Names		Department	Issue\n");
	for(i = 0; i < 4; i++) //iterate through the array
	{
		p = departments[i].head; //set p to head
		while(p != NULL)
		{
			
			/*Prints the indiviual departments because they have different information they need to be split up, encrypts the data aswell using ^ */
			if(p->department == 1)
			{
				sprintf(buffer, "%s	%d	%.02f\n", p->name, p->department,p->additionalInfo->fever);
				for(j = 0; buffer[j] != '\n'; j++)
				{
					buffer[j] = ((buffer[j]) ^ (key));
				}	
				fprintf(ofp, "%s", buffer);
			}
			else if(p->department == 2)
			{
				sprintf(buffer, "%s	%d	%s\n", p->name, p->department,p->additionalInfo->pain);
				for(j = 0; buffer[j] != '\n'; j++)
				{
					buffer[j] = ((buffer[j]) ^ (key));
				}	
				fprintf(ofp, "%s", buffer);
			}
			else if(p->department == 3 || p->department == 4)
			{
				sprintf(buffer, "%s	%d	%.d\n", p->name, p->department,p->additionalInfo->daySick);
				for(j = 0; buffer[j] != '\n'; j++)
				{
					buffer[j] = ((buffer[j]) ^ (key));
				}	
				fprintf(ofp, "%s", buffer);
			}
			p = p->next;
		}
	}
	fclose(ofp); //close file
	return 0;
}