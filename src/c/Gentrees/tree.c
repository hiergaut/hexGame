#include <stdio.h>
#include <stdlib.h> 
#include "tree.h"


struct _node {
    void* data;
    Node parent;
    Node sibling;
    Node first_child;
};

Root create_tree() {
    return NULL;
}

Node last_sibling(Node child) {
    Node last = child;

    while (last->sibling) {
	last = last->sibling;
    }
    return last;
}
Node add_child(Root root, Node parent, void *data) {

    Node new = (Node)malloc(sizeof(struct _node));
    if (new == NULL) {
	return NULL;
    }

    if (root == NULL) { // aka first child
	new->data = data;
	new->sibling = NULL;
	new->first_child = NULL;
	new->parent = NULL;
	root = new;
    }
    else {
	new->data = data;
	new->sibling = NULL;
	new->first_child = NULL;
	new->parent = parent;
	if (parent->first_child) {
	    last_sibling(parent->first_child)->sibling = new;
	}
	else {
	    parent->first_child = new;
	}
    }
    return new;
}

void print(Node node) {
    printf("%p ", node->data);
}

void destroy_tree(Node node) {
    if (node == NULL) {
	return;
    }
    if (node->first_child) {
	destroy_tree(node->first_child);
    }
    else {
	if (node->sibling) {
	    destroy_tree(node->sibling);
	}
	else {
	    if (node->parent) {
		if (node->parent->sibling) {
		    destroy_tree(node->parent->sibling);
		}
	    }
	}
    }
    free(node);
}

void print_tree(Node node) {
    traverse_tree(node,print);
}

int traverse_tree(Node node, action_node action) {

    if (node == NULL) {
	return -1;
    }
    if (node->first_child) {
	traverse_tree(node->first_child, action);
    }
    else {
	action(node);
	if (node->sibling) {
	    traverse_tree(node->sibling, action);
	}
	else {
	    if (node->parent) {
		action(node->parent);
		if (node->parent->sibling) {
		    traverse_tree(node->parent->sibling, action);
		}
	    }
	    return 0;
	}
    }
    if (node->parent == NULL) {
	action(node);
    }
    return 0;
}

int main(void) {
    Root root = create_tree();

    root = add_child(root,NULL,(void *)5);
    Node a = add_child(root,root,(void *)3);
    Node b = add_child(root,root,(void *)2);
    Node c = add_child(root,root,(void *)1);
    Node d = add_child(root,a,(void *)6);
    Node e = add_child(root,a,(void *)7);
    Node f = add_child(root,b,(void *)4);
    Node g = add_child(root,b,(void *)20);
    Node h = add_child(root,b,(void *)8);
    Node i = add_child(root,c,(void *)6);
    Node j = add_child(root,c,(void *)5);
    Node k = add_child(root,c,(void *)4);
    Node l = add_child(root,c,(void *)1);
    Node m = add_child(root,g,(void *)16);

    print_tree(root);
    destroy_tree(root);
    printf("\n");

    return 0;
}
