#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
#define Hash_size 0x7FFF


entry* Hash_table[Hash_size+1];

entry *findName(char lastname[], entry *pHead)
{
    entry* e=Hash_table[Hash(lastname)];
    while (e!=NULL) {
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

unsigned int APHash(char *str)
{
    unsigned int hash=0;
    int i;

    for(i=0; *str; i++) {
        if((i & 1)==0) {
            hash ^=((hash << 7)^(*str++)^(hash>>3));
        } else {
            hash^=(~((hash<<11)^(*str++)^(hash>>5)));
        }
    }

    return (hash & Hash_size);
}

unsigned int ELFHash(char *str)
{
    unsigned int hash=0;
    unsigned int x=0;

    while(*str) {
        hash=(hash<<4)+(*str++);
        if((x=hash & 0xF0000000L)!=0) {
            hash ^= (x>>24);
            hash &= ~x;
        }
    }

    return (hash & Hash_size);
}

unsigned int Hash(char *str)
{
    //return BKDRHash(str);
    //return APHash(str);
    return ELFHash(str);
}
