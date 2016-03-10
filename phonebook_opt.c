#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
#define Hash_size 0x7FFFF


entry* Hash_table[Hash_size];

entry *findName(char lastname[], entry *pHead)
{
    entry* e=Hash_table[Hash(lastname)];
    while (e->pNext != NULL) {
        if (strcasecmp(lastname, e->lastName) == 0)
            return e;
        e = e->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e = (entry *) malloc(sizeof(entry));
    e->pNext = NULL;
    strcpy(e->lastName, lastName);
    int key = Hash(lastName);
    if(Hash_table[key]!=NULL) {
        e->pNext=Hash_table[key];
        Hash_table[key]=e;
    } else {
        Hash_table[key]=e;
    }

    return e;
}

unsigned int BKDRHash(char *str)
{
    unsigned int seed=131;
    unsigned int hash=0;

    while(*str)
        hash = hash * seed +(*str++);

    return (hash & Hash_size);
}

unsigned int Hash(char *str)
{
    return BKDRHash(str);
}
