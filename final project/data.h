#ifndef DATA_H
#define DATA_H

#define MAX_NAME_LEN 100

typedef struct ReservedBook {
    struct Book *book; 
    struct ReservedBook *next; 
} ReservedBook;

typedef struct BorrowedBook {
    struct Book *book; 
    struct BorrowedBook *next; 
} BorrowedBook;

typedef struct Book {
    char name[MAX_NAME_LEN];
    char author[MAX_NAME_LEN];
    int id;
    int available;
    float price;
    struct Book *next;
} Book;

typedef struct User {
    int user_id;
    char username[50];
    char password[50];
    int isAdmin;
    int library_card_id[10];
    int borrowed_count; 
    struct BorrowedBook *borrowed_books;
    struct ReservedBook *reserved_books; 
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

typedef struct BorrowRequest {
    User *user;    
    Book *book;     
    int status;    
    struct BorrowRequest *next; 
} BorrowRequest;

typedef struct NewBookRequest {
    char book_name[MAX_NAME_LEN];
    char book_author[MAX_NAME_LEN];
    struct NewBookRequest *next;
} NewBookRequest;

extern Book *book_head;
extern User *user_head;
extern Admin *admin_head;

void init_data();
void load_data();
void save_data();

#endif 
