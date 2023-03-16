#include "meio.h"

void AllocEletricVehicle(Llist *l,int id, char *type, int battery_lvl, float cph) {
    ElectricVehicle *v = (ElectricVehicle*) malloc(sizeof (ElectricVehicle));
    if(v == NULL)
        return;

    v->id = id;
    v->type = (char*) malloc(strlen(type) + 1); // Allocate space for a new string
    if(v->type == NULL) {
        free(v); // Clean up allocated memory
        printf("Failed to alloc");
        return;
    }
    strcpy(v->type, type); // Copy the contents of type into the new string
    v->battery_level = battery_lvl;
    v->cost_per_hour = cph;

    l->push_t(l,v);
}

void SetEletricVehicle(Llist *l, int id , char *new_type, int new_battery_lvl, float new_cph) {
    ElectricVehicle *v = NULL;
    size_t pos = 0;
    for (pos = 0; pos < l->len; pos++) {
           v = l->get(l,pos);
           if (v->id == id)
               break;
           if(pos == l->len -1)
               return;
    }
    if(v == NULL)
        return;

    if (v->type)
        free(v->type);
    v->type = (char*) malloc(strlen(new_type) + 1); // Allocate space for a new string
    if(v->type == NULL) {
        free(v); // Clean up allocated memory
        printf("Failed to alloc");
        return;
    }
    strcpy(v->type, new_type); // Copy the contents of type into the new string
    v->battery_level = new_battery_lvl;
    v->cost_per_hour = new_cph;
}

void RmEletricVehicle(Llist *l, int id ){
    ElectricVehicle *v = NULL;
    size_t pos = 0;
    for (pos = 0; pos < l->len; pos++) {
           v = l->get(l,pos);
           if (v->id == id)
               break;
           if(pos == l->len -1)
               return;
    }
    if (v->type)
        free(v->type);

    l->rm(l,pos);
    free(v);
}

void ShowEletricVehicles(Llist* l) {
    for (size_t i = 0; i < l->len ; i++) {
        ElectricVehicle *v = l->get(l,i);
        if (v == NULL)
            continue;
        printf("Id de veiculo -> %d\n", v->id);
        printf("Tipo de veiculo -> %s\n", v->type);
        printf("Bateria de veiculo -> %d\n", v->battery_level);
        printf("Custo por hora -> %f\n", v->cost_per_hour);
    }
}

void ReadElectricVehicleFromIo(Llist *l) {
    int id;
    char type[100];
    int battery_lvl;
    float cph;

    // Get input from user
    printf("Enter ID: ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input for ID\n");
        CleanStdin();
        return;
    }
    printf("Enter vehicle type: ");
    if(scanf("%99s", type) != 1) {
        printf("Invalid input for vehicle type\n");
        CleanStdin();
        return;
    }
    printf("Enter battery level: ");
    if(scanf("%d", &battery_lvl) != 1) {
        printf("Invalid input for battery level\n");
        CleanStdin();
        return;
    }
    printf("Enter cost per hour: ");
    if(scanf("%f", &cph) != 1) {
        printf("Invalid input for cost per hour\n");
        CleanStdin();
        return;
    }


    // Allocate new ElectricVehicle struct
    AllocEletricVehicle(l, id, type, battery_lvl, cph);
}

void WriteToTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (size_t i = 0; i < l->len; i++) {
        ElectricVehicle *v = l->get(l, i);
        if (v == NULL)
            continue;
        fprintf(file, "%d %s %d %f\n", v->id, v->type, v->battery_level, v->cost_per_hour);
    }

    fclose(file);
}

void ReadFromTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char type[100];
    int id, battery_lvl;
    float cph;

    while (fscanf(file, "%d %99s %d %f", &id, type, &battery_lvl, &cph) == 4) {
        ElectricVehicle *v = (ElectricVehicle*) malloc(sizeof(ElectricVehicle));
        v->id = id;
        v->type = (char*) malloc(strlen(type) + 1);
        strcpy(v->type, type);
        v->battery_level = battery_lvl;
        v->cost_per_hour = cph;
        l->push_t(l, v);
    }

    fclose(file);
}

void write_to_binary_file(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    for (size_t i = 0; i < l->len; i++) {
        ElectricVehicle *v = l->get(l, i);
        if (v == NULL) {
            continue;
        }
        fwrite(&v->id, sizeof(int), 1, file);
        fwrite(v->type, sizeof(char), strlen(v->type) + 1, file);
        fwrite(&v->battery_level, sizeof(int), 1, file);
        fwrite(&v->cost_per_hour, sizeof(float), 1, file);
    }
    fclose(file);
}