#include "gestor.h"

void AllocManager(Llist *l,int id, char *username, char *password) {
    Gestor *v = (Gestor *) malloc(sizeof (Gestor));
    if(v == NULL)
        return;

    v->id = id;
    v->username = (char*) malloc(strlen(username) + 1); /// Alocar espaço para uma nova string
    if(v->username == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->username, username);
    v->password = (char*) malloc(strlen(password) + 1); /// Alocar espaço para uma nova string
    if(v->password == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->password, password);

    l->push_t(l,v);
}

/// Função que altera os dados de um gestor
void SetManager(Llist *l, int id , char *new_username, char *new_password) {
    Gestor *v = NULL;
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

    if (v->username)
        free(v->username);
    v->username = (char*) malloc(strlen(new_username) + 1); /// Alocar espaço para uma nova string
    if(v->username == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->username, new_username); /// Copia o conteudo para uma nova string
    if (v->password)
        free(v->password);
    v->password = (char*) malloc(strlen(new_password) + 1); /// Alocar espaço para uma nova string
    if(v->password == NULL) {
        free(v); /// Limpa a memoria alocada
        printf("Failed to alloc");
        return;
    }
    strcpy(v->password, new_password); /// Copia o conteudo para uma nova string
}

/// Função que remove um gestor
void RmManager(Llist *l, int id ){
    Gestor *v = NULL;
    size_t pos = 0;
    for (pos = 0; pos < l->len; pos++) {
        v = l->get(l,pos);
        if (v->id == id)
            break;
        if(pos == l->len -1)
            return;
    }
    if (v->username)
        free(v->username);

    l->rm(l,pos);
    free(v);
}

/// Função que lista gestores
void ShowManager(Llist* l) {
    for (size_t i = 0; i < l->len ; i++) {
        Gestor *v = l->get(l,i);
        if (v == NULL)
            continue;
        printf("ID do gestor -> %d\n", v->id);
        printf("UserName do gestor -> %s\n", v->username);
        printf("Password do gestor -> %s\n", v->password);
    }
}

/// Função que insere novos gestores
void ReadManager(Llist *l) {
    int id;
    char username[100];
    char password[100];

    /// Obter entrada do usuário
    printf("Enter manager ID: ");
    if(scanf("%d", &id) != 1) {
        printf("Invalid input for manager ID\n");
        CleanStdin();
        return;
    }
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

    // Aloca a nova struct Manager
    AllocManager(l, id, username, password);
}

/// Função que guarda os dados de um gestor em ficheiro de texto (.txt)
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
        fprintf(file, "%d %s %s\n",v->id, v->username, v->password);
    }

    fclose(file);
}

/// Função de leitura do ficheiro de texto
void ReadManagerFromTextFile(Llist *l, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int id;
    char username[100];
    char password[100];


    while (fscanf(file, "%d %s %s",&id, username, password) == 2) {
        Gestor *v = (Gestor *) malloc(sizeof(Gestor));
        v->id = id;
        v->username = (char*) malloc(strlen(username) + 1);
        strcpy(v->username, username);
        v->password = (char*) malloc(strlen(password) + 1);
        strcpy(v->password, password);
        l->push_t(l, v);
    }

    fclose(file);
}

///Função que guarda os dados de um gestor em binário (.bin)
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
        fwrite(&v->id, sizeof(int), 1, file);
        fwrite(v->username, sizeof(char), strlen(v->username) + 1, file);
        fwrite(v->password, sizeof(char), strlen(v->password) + 1, file);
    }
    fclose(file);
}
