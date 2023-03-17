#include "meio.h"
#include "stdio.h"
#include "cliente.h"
#include "gestor.h"

#include "utils.h"

#define C_VERM "\033[91m"
#define C_VERDE "\033[92m"
#define C_AMAR "\033[93m"
#define C_RESET "\033[0m"


void print_main_menu() {
    printf("\nMain menu options:\n");
    printf(C_VERM "1. Veiculos eletricos\n" C_RESET);
    printf(C_AMAR "2. Clientes\n" C_RESET);
    printf(C_VERDE "3. Gestores\n" C_RESET);
    printf("0. Sair\n");
    printf("Por favor, insira a sua escolha: ");
}

void print_electric_vehicle_menu() {
    printf(C_VERM "\nMenu de opções dos veiculos eletricos:\n");
    printf("1. Adicionar veiculo eletrico\n");
    printf("2. Mostra veiculo eletrico\n");
    printf("3. Editar veiculo eletrico\n");
    printf("4. Remover veiculo eletrico\n");
    printf("5. Armazenar os dados de veiculos eletricos em ficheiro de texto\n");
    printf("6. Armazenar os dados de veiculos eletricos em binario \n");
    printf("0. Voltar ao menu de opcoes\n");
    printf("Por favor, insira a sua escolha: " C_RESET);
}

void print_client_menu() {
    printf(C_AMAR "\nMenu de opções dos clientes:\n");
    printf("1. Adicionar clientes\n");
    printf("2. Mostra clientes\n");
    printf("3. Editar cliente\n");
    printf("4. Remover cliente\n");
    printf("5. Armazenar os dados de clientes em ficheiro de texto\n");
    printf("6. Armazenar os dados de clientes em binario \n");
    printf("0. Voltar ao menu de opcoes\n");
    printf("Por favor, insira a sua escolha: " C_RESET);
}

void print_manager_menu() {
        printf(C_VERDE "\nMenu de opções dos gestores:\n");
        printf("1. Adicionar gestor\n");
        printf("2. Mostra gestores\n");
        printf("3. Editar gestor\n");
        printf("4. Remover gestor\n");
        printf("5. Armazenar os dados de gestores em ficheiro de texto\n");
        printf("6. Armazenar os dados de gestores em binario \n");
        printf("0. Voltar ao menu de opcoes\n");
        printf("Por favor, insira a sua escolha: " C_RESET);
}

int main() {

    // Listas duplamente ligadas genericas
    Llist *listagestor= lst_init();
    Llist *listaveiculos= lst_init();
    Llist *listacliete = lst_init();

    ReadFromTextFile(listaveiculos,"Meios.txt");
    ReadClientFromTextFile(listacliete, "Clientes.txt");
    ReadManagerFromTextFile(listagestor,"Gestor.txt" );

    int choice = -1;
    while (choice != 0) {
        print_main_menu();
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
            {
                int ev_choice = -1;
                while (ev_choice != 0) {
                    print_electric_vehicle_menu();
                    if (scanf("%d", &ev_choice)!=1) {
                        CleanStdin();
                        ev_choice = -1;
                    }

                    // Call functions related to Electric Vehicles
                    switch (ev_choice) {
                        // Add your code for each case to call the corresponding functions
                        // and handle user inputs
                        case 1:
                            ReadElectricVehicleFromIo(listaveiculos);
                            break;
                        case 2:
                            ShowEletricVehicles(listaveiculos);
                            break;
                        case 3:
                            // ler dados para alterar
                            // altera()
                            break;
                        case 4:
                            // ler id
                            RmEletricVehicle(listaveiculos,1);
                            break;
                        case 5:
                            WriteToTextFile(listaveiculos, "Meio.txt");
                            break;
                        case 6:
                            write_to_binary_file(listaveiculos, "Meio.bin");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Escolha inválida. Por favor, tente novamente!\n");
                    }
                }
            }
                break;
            case 2:

            {
                int client_choice = -1;
                while (client_choice != 0) {
                    print_client_menu();
                    if (scanf("%d", &client_choice)!=1) {
                        CleanStdin();
                        client_choice = -1;
                    }

                    // Call functions related to Clients
                    switch (client_choice) {
                        // Add your code for each case to call the corresponding functions
                        // and handle user inputs
                        case 1:
                            ReadClient(listacliete);
                            break;
                        case 2:
                            ShowClient(listacliete);
                            break;
                        case 3:
                            ///
                            break;
                        case 4:
                            ///
                            break;
                        case 5:
                            WriteClientToTextFile(listacliete, "Clientes.txt");
                            break;
                        case 6:
                            write_to_binary_file_client(listacliete, "Clientes.bin");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Escolha inválida. Por favor, tente novamente!\n");
                    }
                }
            }
                break;
            case 3:
            {
                int manager_choice = -1;
                while (manager_choice != 0) {
                    print_manager_menu();
                    if (scanf("%d", &manager_choice)!=1) {
                        CleanStdin();
                        manager_choice = -1;
                    }

                    // Call functions related to Managers
                    switch (manager_choice) {
                        // Add your code for each case to call the corresponding functions
                        // and handle user inputs
                        case 1:
                            ReadManager(listagestor);
                            break;
                        case 2:
                            ShowManager(listagestor);
                            break;
                        case 3:
                            ///
                            break;
                        case 4:
                            ///
                            break;
                        case 5:
                            WriteManagerToTextFile(listagestor, "Gestor.txt");
                            break;
                        case 6:
                            write_to_binary_file_manager(listagestor, "Gestor.bin");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Escolha inválida. Por favor, tente novamente!\n");
                    }
                }
            }
                break;
            case 0:
                printf("A sair...\n");
                break;
            default:
                printf("Escolha inválida. Por favor, tente novamente!\n");
        }
    }


    return 0;
}





//   if (listagestor == NULL)
//        return 1;
//
//    for (int i = 0; i < 2; i++){
//       ReadManager(listagestor);
//    }
//    ShowManager(listagestor);
//
//    SetManager(listagestor, 20, "joao", "lalalala");
//
//    ShowManager(listagestor);
//
//    RmManager(listagestor, 21);
//
//    puts(""
//    );
//    puts("");
//
//    ShowManager(listagestor);
//
//    WriteManagerToTextFile(listagestor,"Gestor.txt");


