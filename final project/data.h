#ifndef DATA_H
#define DATA_H

#define MAX_NAME_LEN 100

typedef struct Book {
    char name[MAX_NAME_LEN];
    char author[MAX_NAME_LEN];
    int id;
    int available;
    float price;
    struct Book *next;
} Book;

typedef struct User {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int user_id;
    int borrowed_books[2]; // IDs of borrowed books
    int borrow_count;
    char library_card_id[MAX_NAME_LEN];
    float balance;
    struct User *next;
} User;

typedef struct Admin {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];
    int can_add_remove_member;
    int can_add_remove_book;
    int can_reserve_book;
    struct Admin *next;
} Admin;

extern Book *book_head;
extern User *user_head;
extern Admin *admin_head;

void init_data();
void load_data();
void save_data();

#endif // DATA_H
