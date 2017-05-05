#include "catalog.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct s_catalog {
    const char* name;
};

catalog catalog_create(const char* name) {
    catalog new =malloc(sizeof(struct s_catalog));

    new->name =name;

    FILE* f =fopen(name, "a");
    fclose(f);

    return new;
}

void catalog_destroy(catalog* c) {
    free(*c);
    *c =NULL;
}

int catalog_nbOccurrence(catalog c, const char* line) {
    FILE* f =fopen(c->name, "r");
    assert(f);

    char str[CATALOG_BUFFER_MAX +1];
    int cpt =0;
    while (fgets(str, CATALOG_BUFFER_MAX, f)) {
        str[strlen(str) -1] =0;
        if (! strcmp(str, line))
            cpt++;
    }

    fclose(f);
    return cpt;
}

int catalog_posIthOccurrence(catalog c, const char* line, int ith) {
    assert(ith <=catalog_nbOccurrence(c, line));

    FILE* f =fopen(c->name, "r");
    assert(f);

    char str[CATALOG_BUFFER_MAX +1];
    int cpt =0;
    int i =0;
    while (fgets(str, CATALOG_BUFFER_MAX, f) && cpt <ith) {
        str[strlen(str) -1] =0;
        if (! strcmp(str, line))
            cpt++;
        i++;
    }

    fclose(f);
    return i;
}

int catalog_nbLine(catalog c) {
    FILE* f =fopen(c->name, "r");
    assert(f);

    char str[CATALOG_BUFFER_MAX +1];
    int i =0;
    while (fgets(str, CATALOG_BUFFER_MAX, f)) i++;

    fclose(f);
    return i;
}

void catalog_insertAtLine(catalog c, int numLine, const char* sentence) {
    assert(1 <=numLine && numLine <=catalog_nbLine(c) +1);

    FILE* temp =fopen("temp.txt", "w");
    FILE* f =fopen(c->name, "r");
    assert(temp && f);

    int i =1;
    char str[CATALOG_BUFFER_MAX];
    while (fgets(str, CATALOG_BUFFER_MAX, f)) {
        if (numLine ==i) {
            fputs(sentence, temp);
            fputs("\n", temp);
        }
        fputs(str, temp);
        i++;
    }

    if (i ==numLine) {
        fputs(sentence, temp);
        fputs("\n", temp);
    }

    fclose(temp);
    fclose(f);

    rename("temp.txt", c->name);
}

void catalog_eraseLineBand(catalog c, int firstNumLine, int lastNumLine) {
    assert(firstNumLine <=lastNumLine);

    FILE* f =fopen(c->name, "r");
    FILE* temp =fopen("temp.txt", "w");

    char line[CATALOG_BUFFER_MAX];
    int i =1;
    while (fgets(line, CATALOG_BUFFER_MAX, f)) {
        if (i <firstNumLine || lastNumLine <i)
            fputs(line, temp);
        i++;
    }

    fclose(f);
    fclose(temp);

    rename("temp.txt", c->name);
}

void catalog_getLine(catalog c, int pos, char* str) {
    FILE* f =fopen(c->name, "r");

    while (fgets(str, CATALOG_BUFFER_MAX, f) && --pos);
    assert(! pos);

    str[strlen(str) -1] =0;

    fclose(f);
}
