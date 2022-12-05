
struct Address{
    char name[30];
    char surname[30];
    char email[50];
    char number[25];
    struct Address *next;
};

void print_list(struct Address *list);
void print_node(struct Address *node);
struct Address* create_node(char *name, char *surname, char *email, char *number);
void add_to_list(struct Address **list, struct Address *node);
int add_to_list_at_pos(struct Address **list, struct Address *node, int position);
void delete_list(struct Address **list);
int get_list_size(struct Address *list);
struct Address *find_addr_by_keyword(struct Address *list, char *keyword);
int delete_addr_at_pos(struct Address **list, int position);