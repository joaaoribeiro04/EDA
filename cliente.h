#ifndef EDA_CLIENTE_H
#define EDA_CLIENTE_H

#include "dlist.h"
#include "utils.h"
#include "string.h"


typedef struct client {
    int id;
    int nif;
    char *name;
    char *address;
    float balance;
} Client;

void AllocClient(Llist *l, int id, int nif, char *name, char *address, float balance);
void ReadClient(Llist *l);
void ShowClient(Llist* l);
void WriteClientToTextFile(Llist *l, const char *filename);
void ReadClientFromTextFile(Llist *l, const char *filename);
void write_to_binary_file_client(Llist *l, const char *filename);
void SetClient(Llist *l, int id , int new_nif, char *new_name, char *new_address, float new_balance);
void SetAndReadClient(Llist *l);
void RmClient(Llist *l, int id );
void RmClienAndReadId(Llist *l );

#endif
