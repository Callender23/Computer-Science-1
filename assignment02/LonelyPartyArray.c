//	Jeffrey Callender
//	COP3502
//	Spring 2019
//	je410689

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"


// We are creating are LonelyPartyArray here and passing num_fragments and fragment_length.
LonelyPartyArray *createLonelyPartyArray( int num_fragments, int fragment_length)
{
	int i;

	// Allocate the space of the LPA.
	LonelyPartyArray *LPA = malloc(sizeof(LonelyPartyArray));

	// Check to see if LPA is NULL and return NULL if it is.
	if(LPA == NULL)
		return NULL;

	// We are setting up are LPA members here.
	// Size is se to zero as well as num_active_fragments.
	// We make both num_fragments and fragment_length equal to our pass by value in this function.
	LPA->size = 0;
	LPA-> num_active_fragments = 0;
	LPA->num_fragments = num_fragments;
	LPA->fragment_length = fragment_length;

	// We allocate space for fragments since it is a 2d array.
	LPA->fragments = (malloc(sizeof(int*) * num_fragments));

	// We check again to make sure are fragments arent being passed NULL;
	if(LPA->fragments == NULL)
	{
	// We free our framents if are call to malloc fails.
		free(LPA->fragments);
		free(LPA);
		return NULL;
	}

	// We initialize are framents[i] to be all NULL.
	for(i = 0; i < LPA->num_fragments; i++)
	{
		LPA->fragments[i] = NULL;
	}

	// We allocate space for our fragment_sizes array.
	LPA->fragment_sizes = (malloc(sizeof(int) * num_fragments));

	// Check if call to malloc is is successfull if not free all members associated with struct.
		if(LPA->fragment_sizes == NULL)
		{
			free(LPA->fragment_sizes);
			free(LPA->fragments);
			free(LPA);
			return NULL;
		}
	// Set all fragment_sizes to zero.
		for(i = 0; i < LPA->num_fragments; i++)
		{
			LPA->fragment_sizes[i] = 0;
		}

	// We print out that we created a new LonelyPartyArray and the capacity of said array.
	// We then return the LPA.
		printf("-> A new LonelyPartyArray has emerged from the void. (capacity: ");
		printf("%d, fragments: %d)\n", (LPA->num_fragments * LPA->fragment_length), LPA->num_fragments);
		return LPA;
}

// This function will free up whatever members we allocated space for.
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i;

	// Check to see is party is NULL.
	if(party == NULL)
		return NULL;

	// Free each inividual components of the fragments array.
	// Then we free the whole framents and party.
	free(party->fragment_sizes);
	for(i = 0; i < party->num_fragments; i++)
	{
		free(party->fragments[i]);
	}
	free(party->fragments);
	free(party);

	printf("-> The LonelyPartyArray has returned to the void.\n");
	return NULL;

}
// This function set our array up and passes an index and key.
// We consitenly check our index to be valid and party to be not NULL.
// We update our members if we successfully insert are key into the correct index given.
// We return LPA_FAILURE if our call to malloc fail or if are index is invalid.
int set(LonelyPartyArray *party, int index, int key)
{
	int i,p,j,k;

	// Check to see if party is NULL.
	if(party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}

	// k and j are our index value for the framents array.
	// We divide by the fragment_length to get our postion.
	k = index / party->fragment_length;
	j = index % party->fragment_length;

	// Check to see  if our index is valid if not we print the invalid index and offset.
	// We also return LPA_FAILURE.
	if((index > (party->num_fragments * party->fragment_length - 1) || index < 0))
	{
		printf("-> Bloop! Invalid access in set(). ");
		printf("(index: %d, fragment: %d, offset: %d)\n",index, k, j);
		return LPA_FAILURE;
	}

	// If framents array is not NULL and is UNUSED then we insert key with our
	// key value and index.
	if(party->fragments[k] !=  NULL)
	{
		if(party->fragments[k][j] == UNUSED)
			{
				// We increase and update the value of the fragment_sizes and size
				// We return LPA_SUCCESS if successfull.
				party->fragments[k][j] = key;
				party->fragment_sizes[k]++;
				party->size++;
				return LPA_SUCCESS;
		}
		else
			// We insert key as we if framents[k][j] is not UNUSED.
			party->fragments[k][j] = key;
	}

	// If framents is NULL then we allocated space for it here.
	else if(party->fragments[k] == NULL)
	{
		// malloc space for framents array.
		party->fragments[k] = malloc(sizeof(int) * party->fragment_length);
		printf("-> Spawned fragment %d. ", k);
		printf("(capacity: %d, indices: %d", party->fragment_length, index - j);
		printf("..%d)\n", party->fragment_length + (index - j - 1));

		// Check to see if call to malloc failed.
		if(party->fragments[k] == NULL)
		{
			// We free framents here and return LPA_FAILURE.
			free(party->fragments[k]);
			return LPA_FAILURE;
		}
		else
			// If call is successfull we initialize framents to UNUSED.
			for(i = 0; i < party->fragment_length; i++)
			{
				party->fragments[k][i] = UNUSED;
			}
		// We update the members if we insert the key into the frament array.
		// We aslo return LPA_SUCCESS.
		party->fragments[k][j] = key;
		party->fragment_sizes[k]++;
		party->size++;
		party->num_active_fragments++;
	}
	return LPA_SUCCESS;
}

// This function get() retrives the value stored at the index of the LonelyPartyArray.
// As with the set() function we consitenly check our index and party to make sure
// we dont segfault or go out of bound with our index.
// We aslo print if our index is invalid and print the offset of that index.
int get(LonelyPartyArray *party, int index)
{

	int k;
	int j;

	// Check to see if party is NULL.
	if(party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}

	// Our postion for our framents array.
	k = index / party->fragment_length;
	j = index % party->fragment_length;

	// Check to see if our index is within valid range if not return LPA_FAILURE.
	if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
	{
		printf("-> Bloop! Invalid access in get(). ");
		printf("(index: %d, fragment: %d, offset: %d)\n",index, k, j);
		return LPA_FAILURE;
	}

	// If are index is technically valid and are framents[k] is not NULL.
	if(((index <= (party->num_fragments * party->fragment_length - 1)) && (index >= 0)))
	{
	// We return the value at framents[k][j].
		if(party->fragments[k] != NULL)
			return party->fragments[k][j];

	// If not we return UNUSED.
		else if(party->fragments[k] == NULL)
			return UNUSED;
	}
}

// This function delete() check to see what we are getting ride of is not being used.
int delete (LonelyPartyArray *party, int index)
{
	int k;
	int j;

	// Check to see if party is NULL.
	if(party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}

	// Our value for our framents array.
	k = index / party->fragment_length;
	j = index % party->fragment_length;

	// Check to see if index is valid .
	if(((index <= (party->num_fragments * party->fragment_length - 1)) && (index >= 0)))
	{
		// If either framents[k] is NULL or framents[k][j] return LPA_FAILURE.
		if(party->fragments[k] == NULL || party->fragments[k][j] == UNUSED)
			return LPA_FAILURE;

		// If our framents[k][j] is not UNUSED  we set it to UNUSED.
		else if(party->fragments[k][j] != UNUSED)
		{
			// We set framents[k][j] to UNUSED and update the members by decrementing
			// the size and fragment_sizes.
			party->fragments[k][j] = UNUSED;
			party->size--;
			party->fragment_sizes[k]--;
			// If fragment_sizes becomes zero then we deallocted the members
			// to be used again.
			if(party->fragment_sizes[k] == 0)
			{
				// We print that we have successfully deallocted our framents array and set it to NULL.
				// We return LPA_SUCCESS once we are done.
				printf("-> Deallocated fragment %d. ",k);
				printf("(capacity: %d, ",party->fragment_length);
				printf("indices: %d",index - j);
				printf("..%d)\n", party->fragment_length + (index - j - 1));
				free(party->fragments[k]);
				party->fragments[k] = NULL;
				party->num_active_fragments--;
			}
			return LPA_SUCCESS;
		}
	}
	// If our index is invalid we print out that we got an invalid access in delete.
	// and return LPA_FAILURE.
	if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
	{
		printf("-> Bloop! Invalid access in delete(). ");
		printf("(index: %d, fragment: %d, offset: %d)\n",index, k, j);
		return LPA_FAILURE;
	}

	return LPA_SUCCESS;
}
// linear search that goes through and finds our key.
int containsKey(LonelyPartyArray *party, int key)
{
	int i,j;
	// This is the range of our index.
	int index_range = (party->num_fragments * party->fragment_length - 1);

	// Check to see if party is NULL.
	if(party == NULL)
		return 0;

	// If index is invalid we return 0.
	if(index_range > (party->num_fragments * party->fragment_length - 1) || index_range < 0)
		return 0;
	else
	{
		// If index is valid we peform a linear search to search for the key
		for(i = 0; i < party->num_fragments; i++)
		{
			// If framents[i] is not NULL then we continue to search for the key
			if(party->fragments[i] != NULL)
			{
				for(j = 0; j < party->fragment_length; j++)
				{ // If we find our key we return 1.
					if(party->fragments[i][j] == key)
						return 1;
				}
			}
			else
				// If key is not found at all we return 0.
				return 0;
		}
		return 0;
	}
}

int isSet(LonelyPartyArray *party, int key)
{
	int index, k, j;

	// Check to see if party is NULL.
	if(party == NULL)
		return 0;

	// Our value for our framents array.
	k = index / party->fragment_length;
	j = index % party->fragment_length;
	index = (party->num_fragments * party->fragment_length - 1);

	// If index is not valid we simply return 0.
	if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
		return 0;
	// If framents is not allocated or framents is UNUSED we aslo return 0.
	if(party->fragments[k] == NULL || party->fragments[k][j] == UNUSED)
		return 0;
	// If fragments is not UNUSED or not NULL we return 1.
	else if(party->fragments[k][j] != UNUSED)
		return 1;
}

int printIfValid(LonelyPartyArray *party, int index)
{
	int k, j;

	// Check to see if party is NULL.
	if(party == NULL)
		return LPA_FAILURE;

	// Our value for framents array position.
	k = index / party->fragment_length;
	j = index % party->fragment_length;

	// If our index is invalid we return LPA_FAILURE.
	if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
		return LPA_FAILURE;
	// If framents is not allocated or is equal to UNUSED then return LPA_FAILURE.
	if(party->fragments[k] == NULL || party->fragments[k][j] == UNUSED)
		return LPA_FAILURE;

	// If our index is valid and framents is not NULL or UNUSED the we print out
	// the framents value at the index position and return LPA_SUCCESS.
	printf("%d\n",party->fragments[k][j]);
	return LPA_SUCCESS;

}
// Function reset the LonelyPartyArray to how it was when we created it
// in createLonelyPartyArray.
// We reset the members expect the fragment_length and num_fragments.
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	// We have a variable max_index which contains the maximum capacity of array.
	int index, k, j, i, max_index;

	// Check to see if party is NULL.
	if(party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
		return party;
	}

	// We initialize are index and max_index here.
	max_index = (party->num_fragments * party->fragment_length);
	index = (party->num_fragments * party->fragment_length - 1);
	k = index / party->fragment_length;
	j = index % party->fragment_length;

	// If index is invalid we return party.
	if(index > (party->num_fragments * party->fragment_length - 1) || index < 0)
		return party;

	// We print that the LonelyPartyArray has reset properly to the state
	// it was in when we created it in createLonelyPartyArray.
	printf("-> The LonelyPartyArray has returned to its nascent state. ");
	printf("(capacity: %d, fragments: %d)\n",max_index,party->num_fragments);
	// We aslo free the fragment_sizes.
	free(party->fragment_sizes);

	// We free framents by individually setting each framents to NULL.
	for(i = 0; i < party->num_fragments; i++)
	{
		free(party->fragments[i]);
		party->fragments[i] = NULL;
	}
	// We free the whole of framents and reset the size and num_active_fragments to zero.
	free(party->fragments);
	party->size = 0;
	party->num_active_fragments = 0;

	// return party when successfull.
	return party;
}
int getSize(LonelyPartyArray *party)
{
	// Check to see if party is NULL and return -1.
	if(party == NULL)
		return -1;
	// If party is not NULL we return the size.
	return party->size;

}
int getCapacity(LonelyPartyArray *party)
{
	int index;

	// Check to see if party is NULL.
	if(party == NULL)
		return -1;
	// initialize index here to definition of valid index.
	index = (party->num_fragments * party->fragment_length);

	// We return the index if successfull.
	return index;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	// delcare variable called max_elements that will hold the max number of integers.
	int max_elements;

	// return -1 if party is NULL.
	if(party == NULL)
		return -1;

	// Initialize max_elements to the maximum number of intergers.
	max_elements = party->num_active_fragments * party->fragment_length;

	// We return the max_elements.
	return max_elements;
}
long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	// Check to see if party is NUll and return 0.
	if(party == NULL)
		return 0;

	// Declare long long unsigned int called array.
	long long unsigned int array;
	// Initialize array to the size of bytes for the traditional array size.
	array = sizeof(int) * (party->num_fragments * party->fragment_length);

	// We return array.
	return array;
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	// Check to see if party is NULL and return 0.
	if(party == NULL)
		return 0;

	// Declare a series of variable type long long unsigned int that will hold
	// the size of our structs members inorder to get the size of these members in bytes.
	// We use sizeof inorder to get the size of these varibles in bytes.
	long long unsigned int LPA_pointer	= sizeof(LPA*);
	long long unsigned int LPA_struct	= sizeof(LPA);

	// I called these varibles Nu, Nu1, Nu2 to reduce the length of the lines to keep it at 100 lines.
	long long unsigned int Nu = sizeof(int) * (party->num_active_fragments * party->fragment_length);
	long long unsigned int Nu1 = sizeof(int*) * party->num_fragments;
	long long unsigned int Nu2 = sizeof(int) * party->num_fragments;

	// We declare and initialize a variable called total to hold the values of all these members.
	long long unsigned int total = 0;
	// We add all the members up inorder to get the total size of this LonelyPartyArray.
	total += Nu + Nu1 + Nu2 + LPA_pointer + LPA_struct;
	// We return the total.
	return total ;
}

double difficultyRating(void)
{
	return 4.0;
}

double hoursSpent(void)
{
	// I wrote down 40 hours because if I wrote down more than that I lose ny will to live.
	// 99.999% of those hours went to set(), debugging get() and that dreadfull last function.
	return 40.0;
}
