#ifndef __MENU_H__
#define __MENU_H__

#include "stdio.h"

#define C_VERM "\033[91m"
#define C_VERDE "\033[92m"
#define C_AMAR "\033[93m"
#define C_RESET "\033[0m"

/// Função para dar print ao menu principal
void print_main_menu() {
    printf("\nMain menu options:\n");
    printf(C_VERM "1. Veiculos eletricos\n" C_RESET);
    printf(C_AMAR "2. Clientes\n" C_RESET);
    printf(C_VERDE "3. Gestores\n" C_RESET);
    printf("0. Sair\n");
    printf("Por favor, insira a sua escolha: ");
}

/// Função para dar print no menu de veiculos eletricos
void print_electric_vehicle_menu() {
    printf(C_VERM "\nMenu de opções dos veiculos eletricos:\n");
    printf("1. Adicionar veiculo eletrico\n");
    printf("2. Mostra veiculo eletrico\n");
    printf("3. Alterar dados de um veiculo eletrico\n");
    printf("4. Remover veiculo eletrico\n");
    printf("5. Armazenar os dados de veiculos eletricos em ficheiro de texto\n");
    printf("6. Armazenar os dados de veiculos eletricos em binario \n");
    printf("0. Voltar ao menu de opcoes\n");
    printf("Por favor, insira a sua escolha: " C_RESET);
}

/// Função para dar print ao menu de cliente
void print_client_menu() {
    printf(C_AMAR "\nMenu de opções dos clientes:\n");
    printf("1. Adicionar clientes\n");
    printf("2. Mostra clientes\n");
    printf("3. Alterar dados de um cliente\n");
    printf("4. Remover cliente\n");
    printf("5. Armazenar os dados de clientes em ficheiro de texto\n");
    printf("6. Armazenar os dados de clientes em binario \n");
    printf("0. Voltar ao menu de opcoes\n");
    printf("Por favor, insira a sua escolha: " C_RESET);
}

/// Função para dar print ao menu de gestores
void print_manager_menu() {
    printf(C_VERDE "\nMenu de opções dos gestores:\n");
    printf("1. Adicionar gestor\n");
    printf("2. Mostra gestores\n");
    printf("3. Alterar dados de um gestor\n");
    printf("4. Remover gestor\n");
    printf("5. Armazenar os dados de gestores em ficheiro de texto\n");
    printf("6. Armazenar os dados de gestores em binario \n");
    printf("0. Voltar ao menu de opcoes\n");
    printf("Por favor, insira a sua escolha: " C_RESET);
}

#endif