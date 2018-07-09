#ifndef _BS_TREE_H_
#define _BS_TREE_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct tree_node {
	int32_t data;
	struct tree_node *parent;
	struct tree_node *left;
	struct tree_node *right;
};

typedef struct tree_node tree_node_t;

tree_node_t *root;

#define MSG_OUT(...)	fprintf(stdout, __VA_ARGS__)
#define MSG_ERR(...)	fprintf(stderr, __VA_ARGS__)

#define FATAL(m, ...) do { \
	MSG_ERR(m, ...); \
	exit(errno); \
} while (0)

#ifndef TREE_NODE_ALLOC
#define TREE_NODE_ALLOC() \
({ \
	tree_node_t *tq; \
	(tq) = malloc(sizeof(tree_node_t)); \
	if ((tq) == NULL) { \
		MSG_ERR("%s\n", strerror((errno))); \
		(tq) = NULL; \
	} \
\
	(tq); \
})
#endif

#ifndef TREE_NODE_DESTRUCT
#define TREE_NODE_DESTRUCT(q) do { \
	free(q); \
} while (0)
#endif

// initialize root of the binary search tree as null
#define INIT_ROOT_AS_NULL()	((root) = NULL)

// initialize leaf (either left or right) of the binary search tree as null
#define INIT_LEAF_AS_NULL(q)	((q) = NULL)

// equal
#define BST_EQ(a, b)	((a) == (b))

// less-than
#define BST_LT(a, b)	((a) < (b))

// less-than or equal
#define BST_LTE(a, b)	((a) <= (b))

// greater-than
#define BST_GT(a, b)	((a) > (b))

// greater-than or equal
#define BST_GTE(a, b)	((a) >= (b))

// get node or leaf value
#define BST_GET_NODE(a)	((a)->data)

// set node value
#define BST_SET_NODE(a, b)	((a)->data = (b))

// set parent of current node
#define BST_SET_PARENT(a, b)	((a)->parent = (b))

void bs_dump_tree(tree_node_t *t);
tree_node_t *bs_tree_search(tree_node_t *t, int32_t data);
tree_node_t *bs_tree_minimum_key(tree_node_t *t);
tree_node_t *bs_tree_maximum_key(tree_node_t *t);
tree_node_t *bs_tree_successor(tree_node_t *t);
tree_node_t *bs_insert(tree_node_t *t, int32_t data);
void bs_delete(tree_node_t *t, int32_t data);
void bs_destruct_tree(tree_node_t *t);

#endif /* _BS_TREE_H_ */
