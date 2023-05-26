#ifndef EDA_MEIO_H
#define EDA_MEIO_H

#include "stdlib.h"
#include "dlist.h"
#include "utils.h"
#include "string.h"

typedef struct {
    double latitude;
    double longitude;
} Coords;

typedef struct electric_vehicle {
    int id;
    char *type;
    int battery_level;
    float cost_per_hour;
    int autonomia;
} ElectricVehicle;

void AllocEletricVehicle(Llist *l,int id, char *type, int battery_lvl, float cph, int autonomia);
void ReadElectricVehicleFromIo(Llist *l);
void ShowEletricVehicles(Llist* l);
void WriteToTextFile(Llist *l, const char *filename);
void ReadFromTextFile(Llist *l, const char *filename);
void write_to_binary_file(Llist *l, const char *filename);
void SetEletricVehicle(Llist *l, int id , char *new_type, int new_battery_lvl, float new_cph, int new_autonomia);
void SetAndReadEletricVehicle(Llist *l);
void RmEletricVehicle(Llist *l, int id );
void RmEletricVehicleAndReadId(Llist *l );


#endif