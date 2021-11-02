#include <stdio.h>
#include <stdlib.h>

#define FILE_DATA "./file_data.txt"

typedef struct {
    int id;
    char description[256];
    float price;
    int status;
} Ticket;

void start_menu();
void create_menu(char *file_data);
void list_menu(char *file_data);
void search_menu(char *file_data, int id);
void edit_menu(char *file_data, int id);
void remove_menu(char *file_data, int id);

int main() {

    /*
    0 = Return menu;
    1 = Create menu;
    2 = List menu;
    3 = Search menu;
    4 = Edit menu;
    5 = Remove menu;
    6 = Exit menu;
    */

    char confirm = 'N';
    int option = 0;
    int exit = 0;

    do {
        if (option == 0) {
            start_menu();
            scanf("%d", &option);
        } else if (option == 1) {
            create_menu(FILE_DATA);
            Ticket ticket;
            option = 0;
        } else if (option == 2) {
            list_menu(FILE_DATA);
            Ticket ticket;
            option = 0;
        } else if (option == 3) {
            search_menu(FILE_DATA, 0);
            Ticket ticket;
            option = 0;
        } else if (option == 4) {
            edit_menu(FILE_DATA, 0);
            Ticket ticket;
            option = 0;
        } else if (option == 5) {
            remove_menu(FILE_DATA, 0);
            Ticket ticket;
            option = 0;
        } else if (option == 6) {
            printf("Deseja realmente sair (S/N)? ");
            getchar();
            scanf("%c", &confirm);

            if (confirm == 'N') {
                option = 0;
            } else {
                exit = 1;
            }
        }
        
        system("clear");

    } while (exit == 0);

    return 0;
}

void start_menu() {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("1 - Cadastro\n");
    printf("2 - Listar\n");
    printf("3 - Buscar\n");
    printf("4 - Editar\n");
    printf("5 - Remover\n");
    printf("6 - Sair\n\n");
    printf("Qual menu deseja acessar? ");
}

void create_menu(char *file_path) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Cadastrar ticket\n");
}

void list_menu(char *file_path) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Lista de tickets\n");
}

void search_menu(char *file_path, int id) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Busca de tickets\n");
}

void edit_menu(char *file_path, int id) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Editar ticket\n");
}

void remove_menu(char *file_path, int id) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Remover ticket\n");
}
