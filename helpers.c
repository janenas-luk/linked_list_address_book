#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "helpers.h"

void add_address(struct Address **list)
{
    struct Address *address = NULL;
    char name[30], surname[30], number[25], email[50];

    parse_user_input(name, surname, email, number);
    address = create_node(name, surname, email, number);
    if (address == NULL) {
            printf("Unable to create new address\n\n");
            return;
    }
    add_to_list(list, address);
    printf("Address successfully was added to the list\n\n");
}

void add_address_at_position(struct Address **list)
{
    int position;
    int rc;
    struct Address *address = NULL;
    char name[30], surname[30], number[25], email[50];

    position = get_user_pos();
    if(position <= 0) {
        printf("Invalid position\n\n");
        return;
    }
    parse_user_input(name, surname, email, number);
    address = create_node(name, surname, email, number);
    if (address == NULL) {
            printf("Unable to create new address\n");
            return;
    }
    rc = add_to_list_at_pos(list, address, position);
    switch (rc) {
        case 0:
            printf("Address added at position -> %d\n\n", position);
            break;
        case 2:
            printf("List was empty. Address added to the top\n\n");
            break;
        case 3:
            printf("Address was added to the end of the list. Too few entries in the list\n\n");
            break;
        default:
            break;
    }
}

void delete_address_at_position(struct Address **list)
{
    int position;
    position = get_user_pos();
    if(position < 1 || position > get_list_size(*list)) {
        printf("Invalid position\n\n");
        return;
    }
    delete_addr_at_pos(list, position);
}

void find_by_keyword(struct Address *list)
{
    char *keyword;
    struct Address *address = NULL;
    keyword = get_user_keyword();
    address = find_addr_by_keyword(list, keyword);
    if(address != NULL) {
        print_node(address);
    } else {
        printf("No address was found by the keyword - %s\n\n", keyword);
    }
    if(keyword != NULL) {
        free(keyword);
    }
    
}

int get_user_option() {
    int c;
    printf("Enter your choice: ");
    scanf("%d", &c);
    while (getchar() != '\n' && c != EOF);
    return c;
}

void print_usage()
{
    printf("1: Print address book\n");
    printf("2: Add to address book\n");
    printf("3: Add address at position\n");
    printf("4: Find address by keyword\n");
    printf("5: Delete address at position\n");
    printf("6: Get address book size\n");
    printf("7: Delete address book\n");
    printf("8: Exit\n\n");
}

void parse_user_input(char *name, char *surname, char *email, char *number)
{
    printf("\nEnter First name: ");
    fscanf(stdin, "%29s", name);

    printf("Enter Last name: ");
    fscanf(stdin, "%29s", surname);

    printf("Enter email: ");
    fscanf(stdin, "%49s", email);

    printf("Enter number: ");
    fscanf(stdin, "%24s", number);
}

int get_user_pos()
{
    int position;
    printf("Enter position: ");
    scanf("%d", &position);
    while (getchar() != '\n' && position != EOF);
    return position;
}

char *get_user_keyword()
{
    char *keyword = (char *) malloc(sizeof(char) * 50);
    printf("Enter search keyword: ");
    scanf("%49s", keyword);
    return keyword;
}

void load_addresses(struct Address **list)
{
    char line[128];
    char *name, *surname, *number, *email;
    FILE *data_file = NULL;
    struct Address *address = NULL;

    data_file = fopen("./data.csv", "r");
    if(data_file == NULL){
        fprintf(stderr, "Unable to open addresses file\n");
        return;
    }

    while (fgets(line, sizeof(line), data_file)) {
        int len = strlen(line);
        if(len > 0 && line[len - 1] == '\n'){
            line[len - 1] = '\0';
        }
        name = strtok(line, DELIMETER);
        surname = strtok(NULL, DELIMETER);
        email = strtok(NULL, DELIMETER);
        number = strtok(NULL, DELIMETER);
        address = create_node(name, surname, email, number);
        if (address != NULL) {
            add_to_list(list, address);
        }
    }
    fclose(data_file);
}