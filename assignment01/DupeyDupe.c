#include "DupeyDupe.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Jeffrey Callender
// COP 3502
// Spring 2019
// je410689


int main(int argc, char **argv)
{
	int i, j , counter, flag;
	counter = 0;
	flag = 0;

	// This for loop decrement reading the array of string backwards.
	for(i = argc - 1; i > 0; i--)
	{
		for(j = i - 1; j > 0; j--)
		{ // Statment checks to see is if the string has another that
			// is the same in the array.
			if(strcmp(argv[i],argv[j]) == 0)
			{
				counter++;
					if(counter == 1)
					{
						printf("%s\n",argv[j]);
							// Separate for loop to scan for instances of the string dupe dupe.
							for(i = argc - 1; i > 0; i--)
							{
								if((strcmp(argv[i],"dupe")) == 0 && (strcmp(argv[i - 1],"dupe") == 0))
								{	// Statment checks if the string dupe dupe occurs in the array.
									flag++;
									printf("dupe dupe!\n");
									// break statment to get out of for loop once we got dupe dupe.
									break;
								}
							}
						}
					}
				}
			}
	// Statment uses flag and counter to check if any repetition of strings occured.
	if(flag == 0 && counter == 0)
		printf("no dupey dupe :(\n");

	return 0;

}
double difficultyRating(void)
{
	return 2.0;
}

double hoursSpent(void)
{
	return 8.0;
}
