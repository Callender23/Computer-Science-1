
int *preOrderTraversal(node *root, int *array)
{
	int *arrayA,nodesACount;
	if(root == NULL)
		return root;

	nodesACount = nodeCount(root);
	arrayA = malloc(sizeof(int) * nodesACount);

	*arrayA++ = root->data;
	if(root->left)
		arrayA = postOrderTraversal(root->left,array);
	if(root->right)
		arrayA = postOrderTraversal(root->right,array);
	return arrayA;
}

int *postOrderTraversal(node *root, int *array)
{
	int *arrayB,nodesBCount;
	if(root == NULL)
		return root;

	nodesBCount = nodeCount(root);
	arrayB = malloc(sizeof(int) * nodesBCount);

	*arrayB++ = root->data;
	if(root->left)
		arrayB = postOrderTraversal(root->left,array);
	if(root->right)
		arrayB = postOrderTraversal(root->right,array);
	return arrayB;
}
