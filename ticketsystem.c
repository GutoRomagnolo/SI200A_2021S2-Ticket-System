#include <stdio.h>
#include <stdlib.h>

#define FILE_DATA "./file_data.txt"

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
            option = 0;
        } else if (option == 2) {
            list_menu(FILE_DATA);
            option = 0;
        } else if (option == 3) {
            search_menu(FILE_DATA, 0);
            option = 0;
        } else if (option == 4) {
            edit_menu(FILE_DATA, 0);
            option = 0;
        } else if (option == 5) {
            remove_menu(FILE_DATA, 0);
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

void create_menu(char *file_data) {
    char name[100], description[300];
    float price;
    int status;

    FILE *p;
    
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Cadastrar ticket\n");
    
    printf("Título do ingresso:\t");
    scanf("%s", name);
    
    printf("Descrição do ingresso: \t");
    scanf("%s", description);
    
    printf("Valor do ingresso:\t");
    scanf("%f", &price);
    
    printf("Situação do ingresso:\t");
    scanf("%d", &status);
    
    p = fopen("file_data.txt", "a");
    
    fprintf(p, "Título: %s\n", name);
    fprintf(p, "Descrição: %s\n", description);
    fprintf(p, "Preço: %.2f\n", price);
    fprintf(p, "Status: %d\n", status);
    
    if(status == 1){
        fprintf(p, "Status: Disponível\n");
        fprintf(p, "\n");
    }
    
    else{
        fprintf(p, "Status: Indisponível\n");
        fprintf(p, "\n");
    }
    
    fclose(p);
}

void list_menu(char *file_data) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Lista de tickets\n");
}

void search_menu(char *file_data, int id) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Busca de tickets\n");
}

void edit_menu(char *file_data, int id) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Editar ticket\n");
}

void remove_menu(char *file_data, int id) {
    printf("SEJA BEM-VINDO AO TICKETSYSTEM\n\n");
    printf("Remover ticket\n");
}
