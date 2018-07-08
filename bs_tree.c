#include "bs_tree.h"

// dump all key in binary search tree structure
void bs_dump_tree(tree_node_t *t)
{
	tree_node_t *q = (tree_node_t *)t;

	if (q != NULL) {
		bs_dump_tree(q->left);
		MSG_OUT("%d ", BST_GET_NODE(q));
		bs_dump_tree(q->right);
	}
}

// search for a specific given key on binary search tree
// structure
tree_node_t *bs_tree_search(tree_node_t *t, int32_t data)
{
	tree_node_t *q = (tree_node_t *)t;

	if (q == NULL)
		return NULL;

	if (BST_EQ(data, BST_GET_NODE(q)))
		return q;

	if (BST_LT(data, BST_GET_NODE(q)))
		return bs_tree_search(q->left, data);

	return bs_tree_search(q->right, data);
}

// find the most minimum key in binary search tree
tree_node_t *bs_tree_minimum_key(tree_node_t *t)
{
	tree_node_t *q = (tree_node_t *)t;

	while (q->left != NULL)
		q = q->left;

	return q;
}

// find the most maximum key in binary search tree
tree_node_t *bs_tree_maximum_key(tree_node_t *t)
{
	tree_node_t *q = (tree_node_t *)t;

	while (q->right != NULL)
		q = q->right;

	return q;
}

// insert a new node on binary search tree
tree_node_t *bs_insert(tree_node_t *t, int32_t data)
{
	if (t == NULL) {
		t = TREE_NODE_ALLOC();
		t->data = data;
		INIT_LEAF_AS_NULL(t->left);
		INIT_LEAF_AS_NULL(t->right);
	}

	if (BST_LT(data, BST_GET_NODE(t)))
		t->left = bs_insert(t->left, data);
	else if (BST_GT(data, BST_GET_NODE(t)))
		t->right = bs_insert(t->right, data);

	return t;
}

// free memory which allocated for the binary search tree
void bs_destruct_tree(tree_node_t *t)
{
	if (t == NULL)
		return;

	bs_destruct_tree(t->left);
	bs_destruct_tree(t->right);
	free(t);
}
