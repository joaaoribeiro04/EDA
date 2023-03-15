#include "gestor.h"

void AllocManager(Llist *l, char *username, char *password) {
    Gestor *v = (Gestor *) malloc(sizeof (Gestor));
    if(v == NULL)
        return;

    v->username = (char*) malloc(strlen(username) + 1); // Allocate space for a new string
    if(v->username == NULL) {
        free(v); // Clean up allocated memory
        printf("Failed to alloc");
        return;
    }
    strcpy(v->username, username);
    v->password = (char*) malloc(strlen(password) + 1); // Allocate space for a new string
    if(v->password == NULL) {
        free(v); // Clean up allocated memory
        printf("Failed to alloc");
        return;
    }
    strcpy(v->password, password);

    l->push_t(l,v);
}


void ShowManager(Llist* l) {
    for (size_t i = 0; i < l->len ; i++) {
        Gestor *v = l->get(l,i);
        if (v == NULL)
            continue;
        printf("UserName do gestor -> %s\n", v->username);
        printf("Password do gestor -> %s\n", v->password);
    }
}


void ReadManager(Llist *l) {
    char username[100];
    char password[100];

    // Get input from user
    printf("Enter manager username: ");
    if(scanf("%s", username) != 1) {
        printf("Invalid input for manager username\n");
        CleanStdin();
        return;
    }
    printf("Enter manager password: ");
    if(scanf("%s", password) != 1) {
        printf("Invalid input for client's address\n");
        CleanStdin();
        return;
    }

    // Allocate new ElectricVehicle struct
    AllocManager(l, username, password);
}
void WriteManagerToTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (size_t i = 0; i < l->len; i++) {
        Gestor *v = l->get(l, i);
        if (v == NULL)
            continue;
        fprintf(file, "%s %s\n",v->username, v->password);
    }

    fclose(file);
}

void ReadManagerFromTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    char username[100];
    char password[100];


    while (fscanf(file, "%s %s",username, password) == 2) {
        Gestor *v = (Gestor *) malloc(sizeof(Gestor));
        v->username = (char*) malloc(strlen(username) + 1);
        strcpy(v->username, username);
        v->password = (char*) malloc(strlen(password) + 1);
        strcpy(v->password, password);
        l->push_t(l, v);
    }

    fclose(file);
}

void write_to_binary_file_manager(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    for (size_t i = 0; i < l->len; i++) {
        Gestor *v = l->get(l, i);
        if (v == NULL) {
            continue;
        }
        fwrite(v->username, sizeof(char), strlen(v->username) + 1, file);
        fwrite(v->password, sizeof(char), strlen(v->password) + 1, file);
    }
    fclose(file);
}
