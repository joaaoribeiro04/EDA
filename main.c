// includes

#include "meio.h"
#include "stdio.h"
#include "cliente.h"
#include "gestor.h"

int main() {

    Llist *listaveiculos = lst_init();

    if (listaveiculos == NULL)
        return 1;

    for (int i = 0; i < 2; i++){
       ReadElectricVehicleFromIo(listaveiculos);
    }
    ShowEletricVehicles(listaveiculos);
    /*ReadClientFromTextFile(listaveiculos,"Meios.txt");

    ShowEletricVehicles(listaveiculos);

    WriteToTextFile(listaveiculos,"Meios.txt");
*/
  /*  Llist *listaclientes = lst_init();

    if (listaclientes == NULL)
        return 1;

    for (int i = 0; i < 2; i++){
        ReadClient(listaclientes);
    }

    ShowClient(listaclientes);


   puts();
    write_to_binary_file_client(listaclientes, "Clientes.bin");*/
    puts(""
            );
    puts("");

    SetEletricVehicle(listaveiculos, 69, "bicicleta33333", 1,1);

    ShowEletricVehicles(listaveiculos);

    RmEletricVehicle(listaveiculos, 69);

    // RmEletricVehicle(listaveiculos, 65);
    puts(""
    );
    puts("");

    ShowEletricVehicles(listaveiculos);

 /* Llist *listagestor = lst_init();

    if (listagestor == NULL)
        return 1;

    for (int i = 0; i < 2; i++){
        ReadManager(listagestor);
    }

    ShowManager(listagestor);


    write_to_binary_file_manager(listagestor, "Gestor.bin");
*/
}
