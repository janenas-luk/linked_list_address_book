#include "main.h"

static int run_loop = 1;

static void signal_handler(int signo)
{
    printf("CTRL+C was pressed. Stopping program\n");
    run_loop = 0;
}

int main(void)
{
    struct Address *list = NULL;
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    print_usage();

    load_addresses(&list);

    while(run_loop) {
        switch (get_user_option()) {
        case 1:
            print_list(list);
            break;
        case 2:
            add_address(&list);
            break;
        case 3:
            add_address_at_position(&list);
            break;
        case 4:
            find_by_keyword(list);
            break;
        case 5:
            delete_address_at_position(&list);
            break;
        case 6:
            printf("List size %d\n", get_list_size(list));
            break;
        case 7:
            delete_list(&list);
            break;
        case 8:
            run_loop = 0;
            break;
        default:
            printf("Your selected option doesn't exist\n");
            break;
        }
    }
    delete_list(&list);
    return 0;
}
