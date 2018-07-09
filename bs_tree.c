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

// find the successor from a given node in binary search tree
tree_node_t *bs_tree_successor(tree_node_t *t)
{
	tree_node_t *q;

	if (t->right != NULL)
		return bs_tree_minimum_key(t->right);

	q = t->parent;

	while (q != NULL && t == q->right) {
		t = q;
		q = q->parent;
	}

	return q;
}

// insert a new node on binary search tree
tree_node_t *bs_insert(tree_node_t *t, int32_t data)
{
	if (t == NULL) {
		t = TREE_NODE_ALLOC();
		BST_SET_NODE(t, data);
		BST_SET_PARENT(t, NULL);
		INIT_LEAF_AS_NULL(t->left);
		INIT_LEAF_AS_NULL(t->right);
	}

	tree_node_t *tmp;

	if (BST_LT(data, BST_GET_NODE(t))) {
		tmp = bs_insert(t->left, data);
		t->left = tmp;
		tmp->parent = t;
	} else if (BST_GT(data, BST_GET_NODE(t))) {
		tmp = bs_insert(t->right, data);
		t->right = tmp;
		tmp->parent = t;
	}

	return t;
}

// replace specific node with one node or another (depends on key comparison)
static void ___bs_transplant_node(tree_node_t *t, tree_node_t *x, tree_node_t *y)
{
	if (BST_EQ(x->parent, NULL))
		t = y;
	else if (BST_EQ(x, x->parent->left))
		x->parent->left = y;
	else
		x->parent->right = y;

	if (!BST_EQ(y, NULL))
		x->parent = y->parent;
}

// free memory which allocated for a single node/leaf
static void ___bs_destruct_single_leaf(tree_node_t *t)
{
	free(t);
}

// delete node/leaf from binary search tree
void bs_delete(tree_node_t *t, int32_t data)
{
	tree_node_t *q, *x;

	if ((q = bs_tree_search(t, data)) == NULL)
		return;

	if (BST_EQ(q->left, NULL))
		___bs_transplant_node(t, q, q->right);
	else if (BST_EQ(q->right, NULL))
		___bs_transplant_node(t, q, q->left);
	else {
		x = bs_tree_minimum_key(q->right);
		if (!BST_EQ(x->parent, q)) {
			___bs_transplant_node(t, x, x->right);
			x->right = q->right;
			x->right->parent = x;
		}
		___bs_transplant_node(t, q, x);
		x->left = q->left;
		x->left->parent = x;
	}

	___bs_destruct_single_leaf(q);
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
