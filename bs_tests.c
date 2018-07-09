#include "bs_tree.h"

#define UNUSED(x)	((void)(x))

static void insert_then_dump_tree(void)
{
	INIT_ROOT_AS_NULL();

	srand(time(0));

	root = bs_insert(root, rand());
	root = bs_insert(root, rand());
	root = bs_insert(root, rand());
	root = bs_insert(root, rand());
	root = bs_insert(root, rand());
	root = bs_insert(root, rand());

	MSG_OUT("[*] Overall key in tree: ");
	bs_dump_tree(root);
	MSG_OUT("\n");

	bs_destruct_tree(root);
}

static void insert_then_search(void)
{
	tree_node_t *q;

	INIT_ROOT_AS_NULL();

	root = bs_insert(root, 2);
	root = bs_insert(root, 5);
	root = bs_insert(root, 10);
	root = bs_insert(root, -2);
	root = bs_insert(root, -10);
	root = bs_insert(root, 100);

	MSG_OUT("[*] Overall key in tree: ");
	bs_dump_tree(root);
	MSG_OUT("\n");

	if ((q = bs_tree_search(root, 5)) == NULL)
		MSG_OUT("\t[*] %d didn't exist in tree.\n", 5);
	else
		MSG_OUT("\t[*] %d did exist in tree.\n", BST_GET_NODE(q));

	if ((q = bs_tree_search(root, 200)) == NULL)
		MSG_OUT("\t[*] %d didn't exist in tree.\n", 200);
	else
		MSG_OUT("\t[*] %d did exist in tree.\n", BST_GET_NODE(q));

	bs_destruct_tree(root);
}

static void insert_then_find_minimum_key(void)
{
	tree_node_t *q;

	INIT_ROOT_AS_NULL();

	root = bs_insert(root, 2);
	root = bs_insert(root, 5);
	root = bs_insert(root, 10);
	root = bs_insert(root, -100);
	root = bs_insert(root, 3);
	root = bs_insert(root, -1);

	q = bs_tree_minimum_key(root);

	MSG_OUT("[*] Minimum key: %d\n", BST_GET_NODE(q));

	bs_destruct_tree(root);
}

static void insert_then_find_maximum_key(void)
{
	tree_node_t *q;

	INIT_ROOT_AS_NULL();

	root = bs_insert(root, 2);
	root = bs_insert(root, 5);
	root = bs_insert(root, 10);
	root = bs_insert(root, -100);
	root = bs_insert(root, 3);
	root = bs_insert(root, -1);

	q = bs_tree_maximum_key(root);

	MSG_OUT("[*] Maximum key: %d\n", BST_GET_NODE(q));

	bs_destruct_tree(root);
}

static void insert_then_find_its_successor(void)
{
	tree_node_t *q, *s;

	INIT_ROOT_AS_NULL();

	root = bs_insert(root, 2);
	root = bs_insert(root, 5);
	root = bs_insert(root, 10);
	root = bs_insert(root, -100);
	root = bs_insert(root, 3);
	root = bs_insert(root, -1);

	if ((q = bs_tree_search(root, 5)) == NULL)
		MSG_OUT("[*] %d didn't exists in tree.\n", 5);
	else {
		s = bs_tree_successor(q);
		MSG_OUT("[*] q: %d, successor(q): %d\n", BST_GET_NODE(q), BST_GET_NODE(s));
	}

	bs_destruct_tree(root);
}

static void insert_then_delete(void)
{
	INIT_ROOT_AS_NULL();

	root = bs_insert(root, 2);
	root = bs_insert(root, 5);
	root = bs_insert(root, 10);
	root = bs_insert(root, -100);
	root = bs_insert(root, 3);
	root = bs_insert(root, -1);

	MSG_OUT("[*] Before: ");
	bs_dump_tree(root);
	MSG_OUT("\n");

	bs_delete(root, -100);

	MSG_OUT("[*] After: ");
	bs_dump_tree(root);
	MSG_OUT("\n");

	bs_destruct_tree(root);
}

int main(int argc, char **argv, char **envp)
{
	UNUSED(argc);
	UNUSED(argv);
	UNUSED(envp);

	insert_then_dump_tree();
	insert_then_search();
	insert_then_find_minimum_key();
	insert_then_find_maximum_key();
	insert_then_find_its_successor();
	insert_then_delete();

	return 0;
}
