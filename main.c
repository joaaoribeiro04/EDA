// includes

#include "meio.h"
#include "stdio.h"
#include "cliente.h"
#include "gestor.h"

int main() {


    Llist *listagestor= lst_init();

   if (listagestor == NULL)
        return 1;

    for (int i = 0; i < 2; i++){
       ReadManager(listagestor);
    }
    ShowManager(listagestor);

    SetManager(listagestor, 20, "joao", "lalalala");

    ShowManager(listagestor);

    RmManager(listagestor, 21);

    puts(""
    );
    puts("");

    ShowManager(listagestor);

    WriteManagerToTextFile(listagestor,"Gestor.txt");

}
