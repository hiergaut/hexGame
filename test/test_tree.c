#include "tree.h"
#include <stdio.h>

void print_node(Node n) {
    printf("%p ", tree_nodeGetData(n));
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
    (void)d;
    (void)e;
    (void)f;
    (void)g;
    (void)h;
    (void)i;
    (void)j;
    (void)k;
    (void)l;
    (void)m;

    print_tree(root);
    printf("\n");
    tree_widthBrowse(root, print_node);
    destroy_tree(root);
    printf("\n");

    return 0;
}
