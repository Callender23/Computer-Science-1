// Jeffrey Callender
// COP 3502C
// je410689
// Spring 2019

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

int isReflection(node *a, node *b)
{
	// Conditional statment checking for an empty tree.
	if(a == NULL && b == NULL)
		return 1;
	// checks if tree a is non empty and tree b is empty
	else if(a != NULL && b == NULL)
		return 0;
	// checks if tree b is non empty and tree a is empty
	else if(b != NULL && a == NULL)
		return 0;

	if(a->data == b->data)
	{
		// Statment that checks if the content at tree a is the same as the content in tree b.
		if(isReflection(a->left, b->right) && isReflection(a->left, b->right))
		{
			return 1;
		}
	}
	return 0;
}

node *makeReflection(node *root)
{
	node *n;
	if(root == NULL)
		return root;

	// Allocate the size for the new tree we are going to have
	n = malloc(sizeof(node));

	n->data = root->data;
	n->left = makeReflection(root->right);
	n->right = makeReflection(root->left);

	return n;
}

// Helper function to count the number of nodes in both tree a and b.
int nodeCount(node *a)
{
	int count = 1;
	// return 0 if a is NULL
	if( a == NULL)
		return 0;

	if(a->left != NULL)
	{
		// Count is going to be equal to the recursive call nodeCount and whatever is left of the tree
		count += nodeCount(a->left);
	}
	if(a->right != NULL)
	{
		// Count is going to be equal to the recursive call nodeCount and whatever is right of the tree
		count += nodeCount(a->right);
	}
	return count;
}

// Helper function that is going to populate our array with the preOrderTraversal of node a
// This function takes parameter of a node and a array return pointer to an array.
int *fillArrayPreOrder(node *root, int *array)
{
	int nodes, index = 0;
	if(root == NULL)
		return array;

	// We set a variable called node and set it equal to the nodeCount.
	nodes = nodeCount(root);

	// Allocate the memory for the array holding the values. We use our previous node variable
	// to malloc the size for the array.
	array = malloc(sizeof(nodes));

	// We increase the index to keep getting the data
	array[index++] = root->data;

	// Recursive call to get the left and right of the tree in preorder order for the array.
	fillArrayPreOrder(root->left,array);
	fillArrayPreOrder(root->right,array);

	// Return the array
	return array;
}

// Helper function that is going to populate our array with the postOrderTraversal of node b
// function takes parameter of a node and a array return pointer to an array.
int *fillArrayPostOrder(node *root, int *array)
{
	int nodes,index = 0;
	if(root == NULL)
		return array;

	nodes = nodeCount(root);
	array = malloc(sizeof(nodes));

	// Doing the same thing here but for the postOrderTraversal for to be place in our array.
	fillArrayPostOrder(root->left,array);
	fillArrayPostOrder(root->right,array);
	array[index++] = root->data;

	return array;
}
int kindredSpirits(node *a, node *b)
{
	int *arrayA, *arrayB, i, j, nodesA, nodesB;

	if(a == NULL && b == NULL)
		return 1;
	else if(a != NULL && b == NULL)
		return 0;
	else if(b != NULL && a == NULL)
		return 0;
	else
	{
		// number of nodes in a && b
		nodesA = nodeCount(a);
		nodesB = nodeCount(b);

		if(nodesA != nodesB)
			return 0;

		// We set our variable arrayA and arrayB to be filled with our preorder and postorder.
		arrayA = fillArrayPreOrder(a,arrayA);
		arrayB = fillArrayPostOrder(b,arrayB);

		// for loop checking the values of arrayA and arrayB and seeing if they are all equal to each
		// other. If we see a vaule that is not the same then we return zero and know they
		// are not kindredSpirits.
		for( j = 0; j < nodesA; j++)
		{
			if(arrayA[i] != arrayB[i])
				return 0;
		}

		// return 1 if Successfully exit the for loop.
		return 1;
	}
}

double difficultyRating(void)
{
	return 2.0;
}

double hoursSpent(void)
{
	return 15.0;
}
