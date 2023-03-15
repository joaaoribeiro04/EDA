#ifndef EDA_CLIENTE_H
#define EDA_CLIENTE_H

#include "dlist.h"
#include "utils.h"
#include "string.h"


typedef struct client {
    int nif;
    char *name;
    char *address;
    float balance;
    struct client* next;
} Client;

void AllocClient(Llist *l, int nif, char *name, char *address, float balance);
void ReadClient(Llist *l);
void ShowClient(Llist* l);
void WriteClientToTextFile(Llist *l, const char *filename);
void ReadClientFromTextFile(Llist *l, const char *filename);
void write_to_binary_file_client(Llist *l, const char *filename);

#endif
