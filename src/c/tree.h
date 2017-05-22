#ifndef __TREE__
#define __TREE__

typedef struct _node *Node;
typedef struct _node *Root;
typedef void(*action_node)(Node);

/** 
 * Create a new tree
 */
Root create_tree();

/**
 * Add a child to the node of the tree
 * Root, the root of the tree
 * Node parent, the parent of the new child
 * void * data, the data in the node
 */
Node add_child(Root root, Node parent, void * data);

/**
 * Depth first tree traversal
 * Root, the root of the tree
 * action_node, a functor to make an action on a node
 */
int traverse_tree(Root, action_node);

/**
 * Print the elements of the tree
 */
void print_tree(Node);

/**
 * Free the memory allocated to the nodes
 */
void destroy_tree(Node);

void tree_widthBrowse(Node node, action_node);
void* tree_getData(Node n);
void* tree_parent(Node n);
int tree_firstChild(Node n);
int tree_lastChild(Node n);
int tree_isLeaf(Node n);
Node tree_getChild(Node n);
Node tree_getBrother(Node n);
void tree_mapInfix(Node n, action_node action);
void tree_mapLeaf(Node n, action_node action);
Node tree_getFather(Node n);
void* tree_nodeGetData(Node n);

#endif
