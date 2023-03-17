#include "cliente.h"

void AllocClient(Llist *l, int id, int nif, char *name, char *address, float balance) {
    Client *v = (Client*) malloc(sizeof (Client));
    if(v == NULL)
        return;

    v->id = id;
    v->nif = nif;
    v->name = (char*) malloc(strlen(name) + 1); /// Alocar espaço para uma nova string
    if(v->name == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->name, name);
    v->address = (char*) malloc(strlen(address) + 1); /// Alocar espaço para uma nova string
    if(v->address == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->address, address);
    v->balance = balance;

    l->push_t(l,v);
}

/// Função que altera os dados de um cliente
void SetClient(Llist *l, int id , int new_nif, char *new_name, char *new_address, float new_balance) {
    Client *v = NULL;
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

    v->nif = new_nif;
    if (v->name)
        free(v->name);
    v->name = (char*) malloc(strlen(new_name) + 1); /// Alocar espaço para uma nova string
    if(v->name == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->name, new_name); /// Copia o conteudo para uma nova string
    if (v->address)
        free(v->address);
    v->address = (char*) malloc(strlen(new_address) + 1); /// Alocar espaço para uma nova string
    if(v->address == NULL) {
        free(v);  /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->address, new_address); /// Copia o conteudo para uma nova string
    v->balance = new_balance;
}

void SetAndReadClient(Llist *l) {
    int id;
    int nif;
    char *name;
    char *address;
    float balance;


    /// Obter entrada do usuário
    printf("Enter client's ID: ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input for client's ID\n");
        CleanStdin();
        return;
    }
    printf("Enter client's NIF: ");
    if(scanf("%d", &nif) != 1) {
        printf("Invalid input for client's NIF\n");
        CleanStdin();
        return;
    }
    printf("Enter client's name: ");
    if(scanf("%s", name) != 1) {
        printf("Invalid input for client's name\n");
        CleanStdin();
        return;
    }
    printf("Enter client's address: ");
    if(scanf("%s", address) != 1) {
        printf("Invalid input for client's address\n");
        CleanStdin();
        return;
    }
    printf("Enter client's balance: ");
    if(scanf("%f", &balance) != 1) {
        printf("Invalid input for client's balance\n");
        CleanStdin();
        return;
    }
    SetClient(l, id, nif, name, address, balance);
}
/// Função que remove um cliente
void RmClient(Llist *l, int id ) {
    Client *v = NULL;
    size_t pos = 0;
    for (pos = 0; pos < l->len; pos++) {
        v = l->get(l,pos);
        if (v->id == id)
            break;
        if(pos == l->len -1)
            return;
    }
    if (v->name)
        free(v->name);

    l->rm(l,pos);
    free(v);
}

/// Função que remove um cliente e le o id do teclado
void RmClienAndReadId(Llist *l ){
    int id;

    printf("Insira o ID do cliente que quer remover ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input \n");
        CleanStdin();
        return;
    }

    RmClient(l, id);
}

/// Função que lista clientes
void ShowClient(Llist* l) {
    for (size_t i = 0; i < l->len ; i++) {
        Client *v = l->get(l,i);
        if (v == NULL)
            continue;
        printf("ID do cliente -> %d\n", v->id);
        printf("NIF do cliente -> %d\n", v->nif);
        printf("Nome do cliente -> %s\n", v->name);
        printf("Morada do cliente -> %s\n", v->address);
        printf("Saldo do cliente -> %f\n", v->balance);
    }
}

/// Função que insere novos clientes
void ReadClient(Llist *l) {
    int id;
    int nif;
    char name[100];
    char address[100];
    float balance;

    /// Obter entrada do usuário
    printf("Enter client's ID: ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input for client's ID\n");
        CleanStdin();
        return;
    }
    printf("Enter client's NIF: ");
    if(scanf("%d", &nif) != 1) {
        printf("Invalid input for client's NIF\n");
        CleanStdin();
        return;
    }
    printf("Enter client's name: ");
    if(scanf("%s", name) != 1) {
        printf("Invalid input for client's name\n");
        CleanStdin();
        return;
    }
    printf("Enter client's address: ");
    if(scanf("%s", address) != 1) {
        printf("Invalid input for client's address\n");
        CleanStdin();
        return;
    }
    printf("Enter client's balance: ");
    if(scanf("%f", &balance) != 1) {
        printf("Invalid input for client's balance\n");
        CleanStdin();
        return;
    }

    // Aloca uma nova struct ElectricVehicle
    AllocClient(l, id, nif, name, address, balance);
}
/// Função que guarda os dados de um cliente em ficheiro de texto (.txt)
void WriteClientToTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (size_t i = 0; i < l->len; i++) {
        Client *v = l->get(l, i);
        if (v == NULL)
            continue;
        fprintf(file, "%d %d %s %s %f\n", v-> id, v->nif, v->name, v->address, v->balance);
    }

    fclose(file);
}

/// Função de leitura do ficheiro de texto
void ReadClientFromTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int id;
    int nif;
    char name[100];
    char address[100];
    float balance;


    while (fscanf(file, "%d %d %s %s %f", &id, &nif, name, address, &balance) == 4) {
        Client *v = (Client *) malloc(sizeof(Client));
        v->id = id;
        v->nif = nif;
        v->name = (char*) malloc(strlen(name) + 1);
        strcpy(v->name, name);
        v->address = (char*) malloc(strlen(address) + 1);
        strcpy(v->address, address);
        v->balance = balance;
        l->push_t(l, v);
    }

    fclose(file);
}

///Função que guarda os dados de um cliente em binário (.bin)
void write_to_binary_file_client(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    for (size_t i = 0; i < l->len; i++) {
        Client *v = l->get(l, i);
        if (v == NULL) {
            continue;
        }
        fwrite(&v->id, sizeof(int), 1, file);
        fwrite(&v->nif, sizeof(int), 1, file);
        fwrite(v->name, sizeof(char), strlen(v->name) + 1, file);
        fwrite(v->address, sizeof(char), strlen(v->address) + 1, file);
        fwrite(&v->balance, sizeof(float), 1, file);
    }
    fclose(file);
}
