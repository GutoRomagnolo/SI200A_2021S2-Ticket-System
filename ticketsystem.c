#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define FILE_DATA "./file_data.txt"

typedef struct {
    char id[15];
    char description[62];
    float price;
    int status;
} Ticket;

void start_menu();
void create_menu(char *file_data);
void list_menu(char *file_data);
void search_menu(char *file_data);
void edit_menu(char *file_data);
void remove_menu(char *file_data, int id);
void ticketsystem();
char *get_id(char *pointer_date);

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
            search_menu(FILE_DATA);
            option = 0;
        } else if (option == 4) {
            edit_menu(FILE_DATA);
            option = 0;
        } else if (option == 5) {
            remove_menu(FILE_DATA, 0);
            option = 0;
        } else if (option == 6) {
            printf("Deseja realmente sair (S/N)? ");
            getchar();
            scanf("%c", &confirm);
            confirm = toupper(confirm);

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
    Ticket ticket;

    FILE *fp = fopen("file_data.txt", "a");
    
    ticketsystem();
    printf("Cadastrar ticket\n\n");
        
    char* id = get_id(ticket.id);

    printf("Descrição do ingresso: ");
    getchar();
    fgets(ticket.description, 60, stdin);
    ticket.description[strlen(ticket.description) - 1] = '\0';
    
    printf("Valor do ingresso: ");
    scanf("%f", &ticket.price);
    
    printf("Situação do ingresso (0 = Indisponível ou 1 = Disponível): ");
    scanf("%d", &ticket.status);
    
    fprintf(fp, "%s;%s;%f;%d\n", id, ticket.description, ticket.price, ticket.status);

    fclose(fp);
}

void list_menu(char *file_data) {
    Ticket ticket;

    int option = 0;
    char line[256];

    FILE *fp = fopen(file_data, "r");

    ticketsystem();
    printf("Lista de tickets\n\n");

    printf("%-14s %-60s %-10s %-9s\n", "ID", "DESCRIÇÃO", "PREÇO", "SITUAÇÃO");

    while (fgets(line, 256, fp) != NULL) {
        sscanf(line, "%[^;];%[^;];%f;%d", ticket.id, ticket.description, &ticket.price, &ticket.status);
        printf("%-14s %-58s %-9.2f %-8d\n", ticket.id, ticket.description, ticket.price, ticket.status);
    }
    
    fclose(fp);

    printf("\nDigite 0 para retornar ao menu principal: ");
    scanf("%d", &option);

    if (option == 0){
        return;
    }

    while (option != 0) {
        printf("Opa! Você digitou uma opção que não existe. Digite 0 para retornar ao menu principal.\n");
        scanf("%d", &option);
    }
}

void search_menu(char *file_data) {
    Ticket ticket;

    int option = 0;
    char line[256];
    char ticket_id[15];

    ticketsystem();
    printf("Busca de tickets\n\n");

    printf("Digite o identificador do ingresso: ");
    scanf("%s", ticket_id);
    getchar();

    FILE *fp = fopen(file_data, "r+");

    while (fgets(line, 256, fp) != NULL) {
        sscanf(line, "%[^;];%[^;];%f;%d", ticket.id, ticket.description, &ticket.price, &ticket.status);

        if (strcmp(ticket.id, ticket_id) == 0) {
            printf("Você deseja cancelar a venda do ingresso (0 = Cancelar ou 1 = Disponibilizar)? ");
            scanf("%d", &option);
            getchar();

            int position = ftell(fp);
            fseek(fp, position - 2, SEEK_SET);
            fputc(option, fp);
        }
    }
    
    fclose(fp);
}

void edit_menu(char *file_data) {
    ticketsystem();
    printf("Editar ticket\n\n");
}

void remove_menu(char *file_data, int id) {
    char ticket_id[15];
    char line[256];
    Ticket ticket;
    #define NULO '0'

    ticketsystem();
    FILE *fp = fopen(file_data, "r+");
    printf("Remover ticket\n\n");

    printf("Digite o identificador do ingresso: ");
    scanf("%s", ticket_id);

        while (fgets(line, 256, fp) != NULL) {
        sscanf(line, "%[^;];%[^;];%f;%d", ticket.id, ticket.description, &ticket.price, &ticket.status);
        getchar();
        
        if (strcmp(ticket.id, ticket_id) == 0 || strcmp(ticket.description, ticket_id) == 0) {
            memset(ticket.id, 0, sizeof(char) * 50);
            memset(ticket.description, 0, sizeof(char) * 50);
            memset(&ticket.price, 0, sizeof(char) * 50);
            memset(&ticket.status, 0, sizeof(char) * 50);

            printf("Cadastro removido com sucesso!\n\n");
        }
    }
    

    //FILE *fp = fopen(file_data, "w+");

    fclose(fp);
}

void ticketsystem() {
    printf("**** TICKETSYSTEM ****\n\n");
}

char *get_id(char *pointer_date) {
    time_t t = time(NULL);
    struct tm* pointer_localtime = localtime(&t);
    strftime(pointer_date, 15, "%Y%m%d%H%M%S", pointer_localtime);
    return pointer_date;
}
