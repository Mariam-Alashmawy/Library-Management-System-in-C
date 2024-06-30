#include <stddef.h>
#include "data.h"
#include "file_handler.h"

Book *book_head = NULL;
User *user_head = NULL;
Admin *admin_head = NULL;

void init_data() {
    load_books();
    load_users();
    load_admins();
}

void save_data() {
    save_books();
    save_users();
    save_admins();
}
