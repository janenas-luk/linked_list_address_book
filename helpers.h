#define DELIMETER ","

int get_user_option();
int get_user_pos();
char *get_user_keyword();
void print_usage();
void add_address();
void add_address_at_position(struct Address **list);
void parse_user_input(char *name, char *surname, char *email, char *number);
void find_by_keyword(struct Address *list);
void delete_address_at_position(struct Address **list);
void load_addresses(struct Address **list);