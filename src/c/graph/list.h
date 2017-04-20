#ifndef __LIST__
#define __LIST__

#include <stdbool.h>

typedef struct s_list* list;

list list_create();
void list_pushBack(list l ,void* el);


void list_pushFront(list l ,void* el);
void list_popBack(list l);
void list_popFront(list l);
void list_insertAt(list l ,unsigned level ,void* el);
void list_removeAt(list l ,unsigned level);
void* list_ith(list l ,unsigned level);
void* list_front(list l);
void* list_back(list l);
bool list_empty(list l);

unsigned list_size(list l);
void list_map(list l ,void (*process)(void*));
void list_reduce(list l ,void(*process)(void* ,void*) ,void* user_data);
void list_reduce2(list l ,void(*process)(void* ,void* ,void*) ,void* user_data ,void* user_data2);
void list_copy(list l ,list l2);


void list_destroy(list* l);
void list_clean(list l);

void list_testBench();



typedef struct s_list_it* list_it;
list_it list_it_create(list l);
void list_it_next(list_it it);
bool list_it_end(list_it it);
void* list_it_get(list_it it);
void list_it_destroy(list_it* it);

#endif
