#include <stdio.h>
#include <stdlib.h> 
#include "tree.h"
#include <assert.h>
/* #include "list.h" */
#include "math.h"


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

int tree_height(Node node) {
    if (! node)
        return -1;
    int level =0;
    while (node->parent) {
        level++;
        node =node->parent;
    }
    return level;
}


void tree_widthBrowse(Node node, action_node action) {
    Node list[1000000000];
    int cursorRight =0;
    int cursorLeft =0;
    int level =-1;

    list[cursorRight++] =node;
    while (cursorLeft !=cursorRight) {
        Node pullNode =list[cursorLeft++];
        if (pullNode) {
            if (tree_height(pullNode) !=level) {
                printf("\n");
                for (int i =5; i >level; i--) {
                    printf("    ");
                }
                level =tree_height(pullNode);
            }

            /* print(pullNode); */
            action(pullNode);


            if (pullNode->first_child) {
                list[cursorRight++] =pullNode->first_child;

                Node brother =pullNode->first_child->sibling;
                while (brother) {
                    list[cursorRight++] =brother;
                    brother =brother->sibling;
                }
            }
            else
                list[cursorRight++] =NULL;

            if (pullNode->parent && pullNode ==last_sibling(pullNode)) {
                printf("    ");
                list[cursorRight++] =NULL;
            }
        }
        else
            printf("    ");
    }
    printf("\n");
}

void* tree_getData(Node n) {
    assert(n);
    return n->data;
}

void* tree_parent(Node n) {
    return n->parent;
}

int tree_firstChild(Node n) {
    assert(n);
    if (n->parent)
        return n ==n->parent->first_child;
    else
        return 0;
}

int tree_lastChild(Node n) {
    return ! n->sibling;
}

int tree_isLeaf(Node n) {
    return ! n->first_child;
}

Node tree_getChild(Node n) {
    assert(n);
    return n->first_child;
}

Node tree_getBrother(Node n) {
    assert(n);
    return n->sibling;
}

void tree_mapInfix(Node n, action_node action) {
    if (n->first_child)
        tree_mapInfix(n->first_child, action);
    action(n);
    if (n->sibling)
        tree_mapInfix(n->sibling, action);
}





