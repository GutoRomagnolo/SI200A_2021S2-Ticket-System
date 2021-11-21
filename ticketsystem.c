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
void remove_menu(char *file_data);
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
            remove_menu(FILE_DATA);
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

    printf("Descricao do ingresso: ");
    getchar();
    fgets(ticket.description, 62, stdin);
    ticket.description[strlen(ticket.description) - 1] = '\0';
    
    printf("Valor do ingresso: ");
    scanf("%f", &ticket.price);
    
    printf("Situacao do ingresso (0 = Indisponivel ou 1 = Disponivel): ");
    scanf("%d", &ticket.status);
    
    fprintf(fp, "%s;%s;%f;%d\n", id, ticket.description, ticket.price, ticket.status);

    fclose(fp);
}

void list_menu(char *file_data) {
    Ticket ticket;

    int option = 0, 
        line = 0;

    FILE *fp = fopen(file_data, "r");

    ticketsystem();
    printf("Lista de tickets\n\n");

    printf("%-15s %-62s %-10s %-9s\n", "ID", "DESCRICAO", "PRECO", "SITUACAO");

    do {
        line = fscanf(fp, "%[^;];%[^;];%f;%d ", ticket.id, ticket.description, &ticket.price, &ticket.status);
        if (line == 0) break;
        printf("%-15s %-62s %-10.2f %-9d\n", ticket.id, ticket.description, ticket.price, ticket.status);

    } while (!feof(fp));
    
    fclose(fp);

    printf("\nDigite 0 para retornar ao menu principal: ");
    scanf("%d", &option);

    if (option == 0){
        return;
    }

    while (option != 0) {
        printf("Opa! Você digitou uma opcao que nao existe. Digite 0 para retornar ao menu principal.\n");
        scanf("%d", &option);
    }
}

void search_menu(char *file_data) {
    Ticket ticket;

    int option = 0, 
        line = 0;
    char ticket_id[15];

    ticketsystem();
    printf("Busca de tickets\n\n");

    printf("Digite o identificador do ingresso: ");
    scanf("%s", ticket_id);
    getchar();

    FILE *fp = fopen(file_data, "r+");

    do {
        line = fscanf(fp, "%[^;];%[^;];%f;%d ", ticket.id, ticket.description, &ticket.price, &ticket.status);
        if (line == 0) break;

        if (strcmp(ticket.id, ticket_id) == 0) {
            printf("Você deseja cancelar a venda do ingresso (0 = Cancelar ou 1 = Disponibilizar)? ");
            scanf("%d", &option);
            getchar();
            
            fseek(fp, -2, SEEK_CUR);
            fprintf(fp, "%d", option);
        }
    } while (!feof(fp));
    
    fclose(fp);
}

void edit_menu(char *file_data) {
    int line = 0, 
        count_lines = 0,
        loop_lines = 0;
    char break_line;
    char ticket_id[15];

    Ticket ticket;
    Ticket* tickets;
    
    ticketsystem();
    printf("Editar ticket\n\n");

    FILE *fp_read = fopen(file_data, "r");

    printf("Digite o identificador do ingresso: ");
    scanf("%s", ticket_id);
    getchar();
    
    while (!feof(fp_read)) {
        break_line = fgetc(fp_read);
        if (break_line == '\n') {
            count_lines++;
        }
    }

    rewind(fp_read);

    tickets = (Ticket*) malloc(sizeof(Ticket) * count_lines);

    while (!feof(fp_read)) {
        line = fscanf(fp_read, "%[^;];%[^;];%f;%d ", ticket.id, ticket.description, &ticket.price, &ticket.status);

        if (line == 0) {
            break;
        } else {
            strcpy(tickets[loop_lines].id, ticket.id);
            strcpy(tickets[loop_lines].description, ticket.description);
            tickets[loop_lines].price = ticket.price;
            tickets[loop_lines].status = ticket.status;
            loop_lines++;
        }
    }

    FILE *fp_write = fopen(file_data, "w");

    loop_lines = 0;

    while (loop_lines < count_lines) {
        if (strcmp(tickets[loop_lines].id, ticket_id) == 0) {
            printf("Descrição do ingresso: ");

            char temp_description[62];

            fgets(temp_description, sizeof temp_description, stdin);
            temp_description[strlen(temp_description) - 1] = '\0';

            strcpy(tickets[loop_lines].description, temp_description);

            printf("%s", tickets[loop_lines].description);

            printf("Valor do ingresso: ");
            scanf("%f", &tickets[loop_lines].price);

            printf("Situação do ingresso (0 = Indisponível ou 1 = Disponível): ");
            scanf("%d", &ticket.status);

            tickets[loop_lines].status = ticket.status;
        }

        fprintf(
            fp_write, 
            "%s;%s;%f;%d\n", 
            tickets[loop_lines].id, 
            tickets[loop_lines].description, 
            tickets[loop_lines].price, 
            tickets[loop_lines].status
        );

        loop_lines++;
    }

    fclose(fp_read);
    fclose(fp_write);
}

void remove_menu(char *file_data) {
    int line = 0, 
        count_lines = 0,
        loop_lines = 0;
    char break_line;
    char ticket_id[15];

    Ticket ticket;
    Ticket* tickets;

    ticketsystem();
    printf("Remover ticket\n\n");

    FILE *fp_read = fopen(file_data, "r");

    printf("Digite o identificador do ingresso: ");
    scanf("%s", ticket_id);
    getchar();
    
    while (!feof(fp_read)) {
        break_line = fgetc(fp_read);
        if (break_line == '\n') {
            count_lines++;
        }
    }

    rewind(fp_read);

    tickets = (Ticket*) malloc(sizeof(Ticket) * count_lines);

    while (!feof(fp_read)) {
        line = fscanf(fp_read, "%[^;];%[^;];%f;%d ", ticket.id, ticket.description, &ticket.price, &ticket.status);

        if (line == 0) {
            break;
        } else {
            strcpy(tickets[loop_lines].id, ticket.id);
            strcpy(tickets[loop_lines].description, ticket.description);
            tickets[loop_lines].price = ticket.price;
            tickets[loop_lines].status = ticket.status;
            loop_lines++;
        }
    }

    FILE *fp_write = fopen(file_data, "w");

    loop_lines = 0;

    while (loop_lines < count_lines) {
        if (strcmp(tickets[loop_lines].id, ticket_id) != 0) {
            fprintf(
                fp_write, 
                "%s;%s;%f;%d\n", 
                tickets[loop_lines].id, 
                tickets[loop_lines].description, 
                tickets[loop_lines].price, 
                tickets[loop_lines].status
            );
        }

        loop_lines++;
    }

    fclose(fp_read);
    fclose(fp_write);
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
