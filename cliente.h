#ifndef EDA_CLIENTE_H
#define EDA_CLIENTE_H

#include "dlist.h"
#include "utils.h"
#include "string.h"
#include "meio.h"


typedef struct client {
    int id;
    int nif;
    char *name;
    char *address;
    float balance;
    Coords coordenadas;
} Client;

void AllocClient(Llist *l, int id, int nif, char *name, char *address, float balance, double latitude, double longitude);
void ReadClient(Llist *l);
void ShowClient(Llist* l);
void WriteClientToTextFile(Llist *l, const char *filename);
void ReadClientFromTextFile(Llist *l, const char *filename);
void write_to_binary_file_client(Llist *l, const char *filename);
void SetClient(Llist *l, int id , int new_nif, char *new_name, char *new_address, float new_balance, double new_latitude, double new_longitude);
void SetAndReadClient(Llist *l);
void RmClient(Llist *l, int id );
void RmClienAndReadId(Llist *l );
double calculate_distance(Coords coord1, Coords coord2);
void get_vehicles_within_radius(Llist *clients, Llist *vehicles, double radius);

#endif
