#ifndef EDA_GESTOR_H
#define EDA_GESTOR_H

#include "dlist.h"
#include "utils.h"
#include "string.h"

typedef struct gestor {
    int id;
    char *username;
    char *password;
    struct gestor* next;
} Gestor;

void AllocManager(Llist *l, int id, char *username, char *password);
void ReadManager(Llist *l);
void ShowManager(Llist* l);
void WriteManagerToTextFile(Llist *l, const char *filename);
void ReadManagerFromTextFile(Llist *l, const char *filename);
void write_to_binary_file_manager(Llist *l, const char *filename);


#endif
