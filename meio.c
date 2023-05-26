#include "meio.h"

void AllocEletricVehicle(Llist *l,int id, char *type, int battery_lvl, float cph, int autonomia) {
    ElectricVehicle *v = (ElectricVehicle*) malloc(sizeof (ElectricVehicle));
    if(v == NULL)
        return;

    v->id = id;
    v->type = (char*) malloc(strlen(type) + 1); /// Alocar espaço para uma nova string
    if(v->type == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    /// Copia o conteudo para uma nova string
    strcpy(v->type, type);
    v->battery_level = battery_lvl;
    v->cost_per_hour = cph;
    v->autonomia = autonomia;

    l->push_t(l,v);
}

/// Função que altera os dados de um veiculo eletrico
void SetEletricVehicle(Llist *l, int id , char *new_type, int new_battery_lvl, float new_cph, int new_autonomia) {
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
    v->type = (char*) malloc(strlen(new_type) + 1); /// Alocar espaço para uma nova string
    if(v->type == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->type, new_type); /// Copia o conteudo para uma nova string
    v->battery_level = new_battery_lvl;
    v->cost_per_hour = new_cph;
    v->autonomia = new_autonomia;
}

/// Função que altera os dados de um veiculo eletrico
void SetAndReadEletricVehicle(Llist *l) {
    int id;
    char type[100];
    int battery_lvl;
    float cph;
    int autonomia;

    /// Obter entrada do usuário
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
    printf("Enter autonomy: ");
    if(scanf("%d", &autonomia) != 1) {
        printf("Invalid input for autonomy\n");
        CleanStdin();
        return;
    }
    SetEletricVehicle(l, id, type, battery_lvl, cph,autonomia);
}

/// Função que remove um veiculo eletrico
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
/// Função que remove um veiculo eletrico e le o id do teclado
void RmEletricVehicleAndReadId(Llist *l ){
    int id;

    printf("Insira o ID do veiculo eletrico que quer remover ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input \n");
        CleanStdin();
        return;
    }

    RmEletricVehicle(l, id);
}


/// Função que lista veiculos eletricos
void ShowEletricVehicles(Llist* l) {
    for (size_t i = 0; i < l->len ; i++) {
        ElectricVehicle *v = l->get(l,i);
        if (v == NULL)
            continue;
        printf("Id de veiculo -> %d\n", v->id);
        printf("Tipo de veiculo -> %s\n", v->type);
        printf("Bateria de veiculo -> %d\n", v->battery_level);
        printf("Custo por hora -> %f\n", v->cost_per_hour);
        printf("Autonomia do veiculo\n", v->autonomia);
    }
}

/// Função que insere novos veiculos eletricos
void ReadElectricVehicleFromIo(Llist *l) {
    int id;
    char type[100];
    int battery_lvl;
    float cph;
    int autonomia;

    /// Obter entrada do usuário
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
    printf("Enter autonomy: ");
    if(scanf("%d", &autonomia) != 1) {
        printf("Invalid input for autonomy\n");
        CleanStdin();
        return;
    }


    // Aloca a nova struct ElectricVehicle
    AllocEletricVehicle(l, id, type, battery_lvl, cph, autonomia);
}

/// Função que guarda os dados de um veiculo eletrico em ficheiro de texto (.txt)
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
        fprintf(file, "%d %s %d %f %d\n", v->id, v->type, v->battery_level, v->cost_per_hour, v->autonomia);
    }

    fclose(file);
}

/// Função de leitura do ficheiro de texto
void ReadFromTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char type[100];
    int id, battery_lvl;
    float cph;
    int autonomia;

    while (fscanf(file, "%d %99s %d %f %d", &id, type, &battery_lvl, &cph, &autonomia) == 5) {
        ElectricVehicle *v = (ElectricVehicle*) malloc(sizeof(ElectricVehicle));
        v->id = id;
        v->type = (char*) malloc(strlen(type) + 1);
        strcpy(v->type, type);
        v->battery_level = battery_lvl;
        v->cost_per_hour = cph;
        v->autonomia = autonomia;
        l->push_t(l, v);
    }

    fclose(file);
}

///Função que guarda os dados de um veiculo eletrico em binário (.bin)
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
        fwrite(&v->autonomia, sizeof(int), 1, file);
    }
    fclose(file);
}
