int *preOrderTraversal(node *root, int *array)
{
		*array++ = root->data;
		if(root->left)
			array = preOrderTraversal(root->left,array);
		if(root->right)
			array = preOrderTraversal(root->right,array);
		return array;
}

int *preOrder_NULL_Check(node *root)
{
	int *array,nodeA_count;
	nodeA_count = nodeCount(root);

	if(root == NULL)
		return NULL;
	if(array != NULL)
	{
		array = malloc(sizeof(int) * nodeA_count);
		preOrderTraversal(root,array);
		return array;
	}
}

int *postOrderTraversal(node *root, int *array)
{
	*array++ = root->data;
	if(root->left)
		array = postOrderTraversal(root->left,array);
	if(root->right)
		array = postOrderTraversal(root->right,array);
	return array;
}

int *postOrder_NULL_Check(node *root)
{
	int *array,nodeA_count;
	nodeA_count = nodeCount(root);

	if(root == NULL)
		return NULL;
	if(array != NULL)
	{
		array = malloc(sizeof(int) * nodeA_count);
		postOrderTraversal(root,array);
		return array;
	}
}
