#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

struct Address* create_node(char *name, char *surname, char *email, char *number)
{
    struct Address *node = NULL;
    node = (struct Address*) malloc(sizeof(struct Address));
    if(node == NULL) {
        return NULL;
    }
    strcpy(node->name, name);
    strcpy(node->surname, surname);
    strcpy(node->email, email);
    strcpy(node->number, number);
    node->next = NULL;
    return node;
}

void add_to_list(struct Address **list, struct Address *node)
{
    struct Address* temp = *list;
    if(temp == NULL) {
        *list = node;
        return; 
    }

    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

int add_to_list_at_pos(struct Address **list, struct Address *node, int position)
{
    struct Address *temp = *list;
    int i = 1;
    if(temp == NULL) {
        *list = node;
        return 2; 
    }

    if(position == 1) {
        node->next = temp;
        *list = node;
        return 0;
    }

    while(temp != NULL) {
        if(temp->next == NULL) {
            temp->next = node;
            return 3;
        } else if((position - 1) == i) {
            node->next = temp->next;
            temp->next = node;
            break;
        }
        temp = temp->next;
        i++;
    }
    return 0;
}

int delete_addr_at_pos(struct Address **list, int position)
{
    struct Address *prev = *list;
    struct Address *temp = *list;
    int i = 1;
    if(*list == NULL) {
        return 1;
    }
    while(temp != NULL) {
        if(position == i) {
            prev->next = temp->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
        i++;
    }
    return 0;
}

void print_list(struct Address *list)
{
    struct Address *temp = list;
    int i = 1;
    if(temp == NULL) {
        printf("List is empty\n");
        return;
    }
    while (temp != NULL) {
        printf("Entry %d -> ", i);
        print_node(temp);
        temp = temp->next;
        i++;
    }
    printf("\n\n");
}

void print_node(struct Address *node)
{
    printf("Name - %s --- ", node->name);
    printf("Surname - %s --- ", node->surname);
    printf("Email - %s --- ", node->email);
    printf("Number - %s\n", node->number);
}

void delete_list(struct Address **list)
{
    struct Address *to_delete = *list;
    while (*list != NULL) {
        *list = (*(list))->next;
        free(to_delete);
        to_delete = *list;
    }
}

int get_list_size(struct Address *list)
{
    int size = 0;
    struct Address *temp = list;
    while(temp != NULL) {
        temp = temp->next;
        size++;
    }
    return size;
}

static struct Address *copy_node(struct Address *src)
{
    struct Address *copy = NULL;
    copy = (struct Address *) malloc(sizeof(struct Address));
    if (copy == NULL) {
        return NULL;
    }
    strcpy(copy->name, src->name);
    strcpy(copy->surname, src->surname);
    strcpy(copy->email, src->email);
    strcpy(copy->number, src->number);
    copy->next = NULL;
    return copy;
}

/* 
This functions returns a list of founded addresses
After use, you need to clean the list
*/
struct Address *find_addr_by_keyword(struct Address *list, char *keyword)
{
    struct Address *temp_list = NULL;
    struct Address *node = NULL;
    struct Address *temp = list;
    int found = 0;
    while(temp != NULL) {
        if(strcmp(temp->name, keyword) == 0) {
            found = 1;
        } else if(strcmp(temp->surname, keyword) == 0) {
            found = 1;
        } else if(strcmp(temp->email, keyword) == 0) {
            found = 1;
        } else if(strcmp(temp->number, keyword) == 0) {
            found = 1;
        }
        if(found) {
            found = 0;
            node = copy_node(temp);
            add_to_list(&temp_list, node);
        }
        temp = temp->next;
    }
    return temp_list;
}