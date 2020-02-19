//	Jeffrey Callender
//	COP3502
//	Spring 2019
//	je410689

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"



int processInputFile(char *filename)
{
	// created new listy that will read and open file to check for the string manipulation.
	ListyString *crazyListy;
	char str[1024], temp;
	FILE *f;
	if(f = fopen(filename,"r"))
	{
		fscanf(f,"%s",str);
		crazyListy = createListyString(str);

		while(fscanf(f,"%c",&temp) != EOF)
	 	{
			// does string replace.
			if(str[0] == '@')
			{
				fscanf(f," %s",str);
				fscanf(f," %c",&temp);
				replaceChar(crazyListy,temp,str);
			}
			// does string cacatnate.
			if(str[0] == '+')
			{
				fscanf(f," %s",str);
				listyCat(crazyListy,str);
			}
			// does string deletion.
			if(str[0] == '-')
			{
				fscanf(f," %s",str);
				replaceChar(crazyListy,str[0],"");
			}
			// reverse the string.
			if(str[0] == '~')
			{
				reverseListyString(crazyListy);
			}
			// print the numbers of characters.
			if(str[0] == '?')
			{
				printf("%d\n",listyLength(crazyListy));
			}
			// print the working string.
			if(str[0] == '!')
			{
				printListyString(crazyListy);
			}
		}
		crazyListy = destroyListyString(crazyListy);
		fclose(f);
		return 0;
	}
	else
		return 1;
}

 // create a new listyString.
ListyString *createListyString(char *str)
{
	// make a current node and prev node. make sure to allocate space for the new listy.
	ListyString *listy = malloc(sizeof(ListyString));
	ListyNode *current;
	ListyNode *prev;
	int length;
  listy->head = NULL;
	listy->length = 1;


	// Checks for null string
	if(str == NULL)
	{
		listy->length = 0;
		listy->head = NULL;
		return listy;
	}

	// Checks for empty
	if(str[0] == '\0')
	{
		listy->length = 0;
		listy->head = NULL;
		return listy;
	}

	// Set up for fill
  listy->head = malloc(sizeof(ListyNode));
  prev = listy->head;
	length = strlen(str);
	listy->head->data = str[0];

	// Filling the thing with the stuff
	for(int i = 1; i < length; i++)
	{
		current = malloc(sizeof(ListyNode));
		current->data = str[i];
		current->next = NULL;
		prev->next = current;
		prev = prev->next;
		listy->length++;
	}
	return listy;
}

	// destroy and free the listy string.
ListyString *destroyListyString(ListyString *listy)
{
	int length;
	ListyNode *destroyerOfNodes, *current;

	//check if head is NULL.
	if(listy == NULL)
		return NULL;
	if(listy->head == NULL)
	{
		free(listy);
	}
	length = listy->length;
	current = listy->head;

	// traverse the listy.
	while(current)
	{
		destroyerOfNodes = current;
		current = current->next;
		free(destroyerOfNodes);
		destroyerOfNodes = NULL;
	}

	// free the listy.
	free(listy);
	listy = NULL;
	return NULL;

}
	// clone listyString that does same thing as above create fucntion.
ListyString *cloneListyString(ListyString *listy)
{
	ListyString *cloneListy = malloc(sizeof(ListyString));
	ListyNode *prev, *current, *originalCurrent;
	int length;
	if(listy == NULL)
	{
		free(cloneListy);
		return NULL;
	}

	if(listy->head == NULL)
	{
		cloneListy->head = NULL;
		cloneListy->length = 0;
		return cloneListy;
	}

	length = cloneListy->length;
	// Set up for fill
  cloneListy->head = malloc(sizeof(ListyNode));
  prev = cloneListy->head;
	cloneListy->head->data = listy->head->data;
	originalCurrent = listy->head;
	// Filling the thing with the stuff
	for(int i = 1; i < length; i++)
	{
		originalCurrent = originalCurrent->next;
		current = malloc(sizeof(ListyNode));
		current->data = originalCurrent->data;
		current->next = NULL;
		prev->next = current;
		prev = prev->next;
		listy->length++;
	}
}
void replaceChar(ListyString *listy, char key, char *str)
{
		// code is commented out as it does not work properly.
// 	ListyNode *temp;
// 	ListyNode *right;
// 	ListyNode *left;
// 	ListyString *newListy_String;
//
// 	if(listy == NULL || listy->head == NULL)
// 		return;
//
// 	listy->head = malloc(sizeof(ListyString));
//
// 	if(str == NULL || str[0] == '\0')
// 	{
// 		if(listy->head-> == key)
// 		{
// 			temp = listy->head;
// 	 		listy->head = listy->next;
// 	 		free(temp);
// 		}
// 		else
// 			temp = listy->head;
// 	 		while(temp->next != NULL)
// 			{
// 				if(listy->data == key)
// 				prePTR = temp;
// 				temp->next = NULL;
//
// 			}
// 			prePTR->next = NULL;
// 			free(temp);
// 		if(listy
// 	}
//
//
// 	if(listy->head->data == key)
// 	{
// 		newListy_String = createListyString(str);
// 		temp = listy->head;
// 		listy->head = listy->head->next;
// 		free(temp);
// 		temp = NULL;
// 		temp = newListy_String->head;
// 		while(temp->next != NULL)
// 			{
// 				temp = temp->next;
// 				temp->next = listy->head;
// 				listy->head = newListy_String->head;
// 			}
// 	}
// 	else
// 	{
// 		temp = listy->head;
// 		while(temp->next != NULL)
// 		{
// 			left = temp;
// 			temp = temp->next;
// 			right = temp->next;
// 			if(temp->data == key)
// 			{
// 				newListy_String =createListyString(str);
// 				left->next = newListy_String->head;
// 				free(temp);
// 				temp = listy->head;
// 				while(temp->next != NULL)
// 					{
// 						temp = temp->next;
// 						temp->next = right;
// 						continue;
// 					}
// 					temp = temp->next;
// 					if(temp->data == key)
// 					{
// 						newListy_String =createListyString(str);
// 						temp = listy->head;
// 						listy->head = listy->head->next;
// 						free(temp);
// 						temp = NULL;
// 						temp = newListy_String->head;
// 						while(temp->next != NULL)
// 						{
// 							temp = temp->next;
// 							temp->next = listy->head;
// 							listy->head = newListy_String->head;
// 						}
// 					}
// 				}
// 			}
// 		}
 }

void reverseListyString(ListyString *listy)
{
	ListyNode *temp;
	char *str;

	// checks if listy is null and head is null.
	if(listy == NULL || listy->head == NULL)
		return;
	str = malloc(sizeof(char) * listy->length);

	// makes temp that capture listy->head.
	temp = listy->head;

	// for loop to tranvers the listy that was converted to string.
	for(int i = 0; i < listy->length; i++)
	{
		str[i] = temp->data;
		temp = temp->next;
	}

	temp = listy->head;
	// transverse the new string backwards.
	for(int i = listy->length - 1; i >= 0; i--)
	{
		temp->data = str[i];
		temp = temp->next;
	}
}
// this functions cocantenate a string tp the end of the working string.
ListyString *listyCat(ListyString *listy, char *str)
{
	ListyNode *temp;
	ListyString *newListy;

	// check if listy is null and str is not the empty string.
	if(listy == NULL && str[0] != '\0')
	{
		// create a new listystring and set it to a node called listy.
		listy = createListyString(str);
		return listy;
	}

	// check is listy is null and str is null. We return null
	if(listy == NULL && str == NULL)
		return NULL;

	// if listy is null and str is the empty string.
	if(listy == NULL && str[0] == '\0')
	{
		// set listy length to 0 and listy head to null.
		listy->length = 0;
		listy->head = NULL;
		return listy;
	}
	// listy head is check to see if it is.
	if(listy->head == NULL)
	{
		// set newListy to create a new listystring.
		// set listy to be the new listyLength and listy head to newListyhead.
		newListy = createListyString(str);
		listy->length = newListy->length;
		listy->head = newListy->head;
		free(newListy);
		return listy;
	}

	if(listy->head != NULL)
	{
		temp = listy->head;
		while(temp->next)
			temp = temp->next;

		newListy = createListyString(str);
		listy->length+= newListy->length;
		temp->next = newListy->head;
		free(newListy);
		return listy;
	}
}
int listyCmp(ListyString *listy1, ListyString *listy2)
{
	ListyNode *node1;
	ListyNode *node2;
	if(listy1 == NULL && listy2 == NULL)
		return 0;
	else if(listy1 == NULL && listy2 != NULL)
		return 1;
	else if (listy1 != NULL &&  listy2 == NULL)
		return 1;
	else
	{
		if(listy1->length != listy2->length)
			return 1;
		node1 = listy1->head;
		node2 = listy2->head;
		while(node1 != NULL && node2 != NULL)
		{
			if(node1->data == node2->data)
			{
				node1 = node1->next;
				node2 = node2->next;
				continue;
			}
			else
			{
				return 1;
			}
			if(node1 == NULL && node2 == NULL)
				return 0;
			else
				return 1;
		}
	}
}
// returns the length of listy->length;
int listyLength(ListyString *listy)
{
	if(listy != NULL && listy->head != NULL)
		return listy->length;
	else if (listy == NULL)
		return -1;
	else
		return 0;

}
// prints a the listystring.
void printListyString(ListyString *listy)
{
	ListyNode *temp;
	// if listy is null and listy head is null print out the empty string.
	if(listy == NULL || listy->head == NULL)
		printf("(empty string)");
	else
	{
		temp = listy->head;
		while(temp)
		{
			printf("%c", temp->data);
			temp = temp->next;
		}
	}
	printf("\n");

}
double difficultyRating(void)
{
	return 4.0;

}
double hoursSpent(void)
{
	return 50;

}
int main(int argc, char **argv)
{
	processInputFile(argv[1]);
}
