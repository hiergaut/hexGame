#include "list.h"
#include <malloc.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_node* node;
struct s_node {
    node next;
    node prev;
    void* el;
};

struct s_list {
    node sentinel;
    unsigned size;
    void (*printElement)(const void*);
};

list list_create() {
    list l =malloc(sizeof(struct s_list));

    l->sentinel =malloc(sizeof(struct s_node));
    l->sentinel->next =l->sentinel;
    l->sentinel->prev =l->sentinel;

    l->size =0;

    return l;
}

void list_pushBack(list l, void* el) {
    node new =malloc(sizeof(struct s_node));

    new->el =el;
    new->next =l->sentinel;
    new->prev =l->sentinel->prev;

    new->next->prev =new;
    new->prev->next =new;

    l->size++;
}

void list_pushFront(list l, void* el) {
    node new =malloc(sizeof(struct s_node));

    new->el =el;
    new->next =l->sentinel->next;
    new->prev =l->sentinel;

    new->next->prev =new;
    new->prev->next =new;

    l->size++;
}

void list_popBack(list l) {
    assert(l->size);

    node del =l->sentinel->prev;

    del->prev->next =del->next;
    del->next->prev =del->prev;
    l->size--;

    free(del);
}

void list_popFront(list l) {
    assert(l->size);

    node del =l->sentinel->next;

    del->prev->next =del->next;
    del->next->prev =del->prev;
    l->size--;

    free(del);
}

void list_insertAt(list l, unsigned level, void* el) {
    assert(level <=l->size);

    node cur=l->sentinel->next;

    while (level--) cur =cur->next;

    node new =malloc(sizeof(struct s_node));
    new->next =cur;
    new->prev =cur->prev;
    new->el =el;

    new->next->prev =new;
    new->prev->next =new;
    l->size++;
}

void list_removeAt(list l, unsigned level) {
    assert(level <l->size);

    node cur =l->sentinel->next;
    while(level--) cur =cur->next;

    cur->prev->next =cur->next;
    cur->next->prev =cur->prev;
    l->size--;

    free(cur);
}

void list_remove(list l, void* el) {
    assert(el);

    node cur =l->sentinel->next;
    while (cur !=l->sentinel) {
        if (cur->el ==el) {
            cur->prev->next =cur->next;
            cur->next->prev =cur->prev;
            l->size--;
            free(cur);
            return;
        }
        cur =cur->next;
    }
    assert(0);
}

void* list_ith(list l, unsigned level) {
    node cur =l->sentinel->next;
    while (level--) cur =cur->next;

    return cur->el;
}

void* list_front(list l) {
    return l->sentinel->next->el;
}

void* list_back(list l) {
    assert(! list_empty(l));
    return l->sentinel->prev->el;
}

unsigned list_size(list l) {
    return l->size;
}

bool list_empty(list l) {
    return ! l->size;
}

void list_map(list l, void (*process)(void*)) {
    node cur=l->sentinel->next;

    while (cur !=l->sentinel) {
	process(cur->el);
	cur =cur->next;
    }
}

void list_reduce(list l, void(*process)(void*, void*), void* user_data) {
    node cur=l->sentinel->next;

    while (cur !=l->sentinel) {
	process(cur->el, user_data);
	cur =cur->next;
    }
}

void list_reduce2(list l, void(*process)(void*, void*, void*), void* user_data, void* user_data2) {
    node cur=l->sentinel->next;

    while (cur !=l->sentinel) {
	process(cur->el, user_data, user_data2);
	cur =cur->next;
    }
}

void list_destroy(list* l) {
    list_clean(*l);
    /* node cur =(*l)->sentinel->next; */
    /* while (cur !=(*l)->sentinel) { */
    /* 	cur =cur->next; */
    /* 	free(cur->prev); */
    /* } */

    free((*l)->sentinel);
    free(*l);
    *l =NULL;
}

void list_clean(list l) {
    while (! list_empty(l)) {
        list_popBack(l);
    }
}

void list_translate(void* el, void* l2) {
    list_pushBack(l2, el);
}

void list_copy(list l, list l2) {
    list_clean(l2);
    list_reduce(l, list_translate, l2);
}



void list_testBench_print(const void* n) {
    printf("%d ", *(int*)(unsigned long)n);
}

void list_testBench_aff(list l) {
    list_map(l, (void (*)(void*))list_testBench_print);
    printf("\n");
}

void list_testBench() {
    printf("list_testBench :\n");

    list l =list_create(list_testBench_print);

    int tab[100];

    for (int i =0 ;i <30 ;i++) {
	tab[i] =rand() %100;
    }

    list_pushBack(l, &tab[0]);
    list_testBench_aff(l);
    list_pushBack(l, &tab[1]);
    list_testBench_aff(l);
    list_pushBack(l, &tab[2]);
    list_testBench_aff(l);
    list_popBack(l);
    list_testBench_aff(l);
    list_popFront(l);
    list_testBench_aff(l);
    list_popBack(l);
    list_testBench_aff(l);
    list_pushBack(l, &tab[3]);
    list_testBench_aff(l);
    list_pushBack(l, &tab[3]);
    list_testBench_aff(l);

    list_destroy(&l);
    printf("\n\n");
}


struct s_list_it {
    list l;
    node begin;
    node cur;
};

list_it list_it_create(list l) {
    list_it it =malloc(sizeof(struct s_list_it));

    it->l =l;
    it->begin =l->sentinel->next;
    it->cur =it->begin;

    return it;
}

void list_it_next(list_it it) {
    it->cur =it->cur->next;
}

bool list_it_end(list_it it) {
    return it->cur ==it->l->sentinel;
}

void* list_it_get(list_it it) {
    return it->cur->el;
}

void list_it_destroy(list_it* it) {
    free(*it);
    *it =NULL;
}

void list_it_restart(list_it it) {
    it->cur =it->begin;
}


unsigned list_getSize(list l) {
    return l->size;
}

int list_in(list l, const void* el) {
    list_it it =list_it_create(l);
    while (! list_it_end(it)) {
        void* cur =list_it_get(it);
        if (cur ==el)
            return 1;

        list_it_next(it);
    }
    return 0;
}



