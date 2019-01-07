#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "list.c"
#include "files.c"
#include "proj.h"

struct things departments[4] = {NULL};
pthread_mutex_t mutex;


int main(int argc, char* argv[])
{
	int command;
	int i;
	pthread_t thread_id;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&thread_id, NULL, autoSave, argv[2]);
	if(argc == 1)
	{
		printf("The name of the file is missing!\n");
		exit(1);
	}
	int key = atoi(argv[3]);
	readFile(argv[1], key);
	do
	{
		
		printf("Welcome to waiting room program what would you like to do\n");
		printf("1: Enter your name and department\n2: Show current waiting list\n3: Delete oldest entry\n4: Check individual department\n5: Additional Info\n6: Change department\n7: Show save file\n0: Exit program\n");
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
				delRow();
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
			case 7:
				displaySave(argv[2]);
				break;
			case 0:
                pthread_mutex_lock(&mutex);
				pthread_cancel(thread_id);
                pthread_mutex_unlock(&mutex);
				saveFile(argv[1], key);
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