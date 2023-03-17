// includes

#include "meio.h"
#include "stdio.h"
#include "cliente.h"
#include "gestor.h"

int main() {

    Llist *listaclientes = lst_init();

    if (listaclientes == NULL)
        return 1;

    for (int i = 0; i < 2; i++){
       ReadClient(listaclientes);
    }
    ShowClient(listaclientes);

    WriteClientToTextFile(listaclientes,"Clientes.txt");


    SetClient(listaclientes, 20, 11111, "joao", "igreja nº13", 124);

    ShowClient(listaclientes);

    RmClient(listaclientes, 21);

    puts(""
    );
    puts("");

    ShowClient(listaclientes);


}
