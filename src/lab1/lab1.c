/******************************************************************************/
/*                         Dylan Hoover COEN 11 Lab #1                        */
/*                               19 May 2018                                  */
/* This program creates a random number and uses it as a math test for 10 #'s */
/******************************************************************************/


#include <stdio.h> 
#include <stdlib.h>
#include <time.h>


int main (void)
{
	int divisor, quotient, dividend, i, amountCorrect; //delcare variables
	srand ((int) time (NULL)); //initialize srand to setup rand	
	amountCorrect = 0; //initialize amountCorrect
	for(i = 0; i < 10; i++) //start for loop to go for 10 rounds
	{
		divisor = rand () % 12 + 1; //setup divsior random generator 1-12
		quotient = rand () % 13; //setup quotient random generator 0-12
		dividend = divisor * quotient; //define dividend
		printf("What is %i divided by %i\n", dividend, divisor); //print the question 
		int answer; //define new int for user input
		scanf("%i", &answer); //scan for user input and set answer int to user input
		if(answer == quotient) //if statement to see fi user input is the same as random quotient
		{
			printf("\033[0;34m"); //this is random color stuff to make text blue
			printf("You are correct \n"); //print correct
			printf("\033[0m"); //this is random color stuff to reset the text to normal
			amountCorrect++; //increment amount correct every time user gets answer right
		}
		else 
		{
			printf("\033[0;31m"); //random color stuff to make text red
			printf("You are incorrect, the answer is %i \n", quotient); //print out if user is wrong and display correct answer
			printf("\033[0m"); //random coor stuff to reset text
		}
	}		
	printf("You got %i answers correct \n", amountCorrect); //print the amount correct
	return 0;
}
		
