// includes

#include "meio.h"
#include "stdio.h"
#include "cliente.h"

int main() {

   /* Llist *listaveiculos = lst_init();

    if (listaveiculos == NULL)
        return 1;

    for (int i = 0; i < 2; i++){
       ReadElectricVehicleFromIo(listaveiculos);
    }

    ReadClientFromTextFile(listaveiculos,"Meios.txt");

    ShowEletricVehicles(listaveiculos);

    WriteToTextFile(listaveiculos,"Meios.txt");

    write_to_binary_file(listaveiculos, "Meio.bin");
*/


    Llist *listaclientes = lst_init();

    if (listaclientes == NULL)
        return 1;

    for (int i = 0; i < 2; i++){
        ReadClient(listaclientes);
    }

    ///ShowClient(listaclientes);

    write_to_binary_file_client(listaclientes, "Clientes.bin");



}
