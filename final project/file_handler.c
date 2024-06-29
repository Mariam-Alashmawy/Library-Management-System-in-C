#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handler.h"


void load_books() {
    FILE *file = fopen("books.dat", "rb");
    if (file) {
        Book temp;
        while (fread(&temp, sizeof(Book), 1, file)) {
            Book *new_book = (Book *)malloc(sizeof(Book));
            *new_book = temp;
            new_book->next = book_head;
            book_head = new_book;
        }
        fclose(file);
    }
}

void save_books() {
    FILE *file = fopen("books.dat", "wb");
    if (file) {
        Book *current = book_head;
        while (current) {
            fwrite(current, sizeof(Book), 1, file);
            current = current->next;
        }
        fclose(file);
    }
}

void load_users() {
    FILE *file = fopen("users.dat", "rb");
    if (file) {
        User temp;
        while (fread(&temp, sizeof(User), 1, file)) {
            User *new_user = (User *)malloc(sizeof(User));
            *new_user = temp;
            new_user->next = user_head;
            user_head = new_user;
        }
        fclose(file);
    }
}

void save_users() {
    FILE *file = fopen("users.dat", "wb");
    if (file) {
        User *current = user_head;
        while (current) {
            fwrite(current, sizeof(User), 1, file);
            current = current->next;
        }
        fclose(file);
    }
}

void load_admins() {
    FILE *file = fopen("admins.dat", "rb");
    if (file) {
        Admin temp;
        while (fread(&temp, sizeof(Admin), 1, file)) {
            Admin *new_admin = (Admin *)malloc(sizeof(Admin));
            *new_admin = temp;
            new_admin->next = admin_head;
            admin_head = new_admin;
        }
        fclose(file);
    }
}

void save_admins() {
    FILE *file = fopen("admins.dat", "wb");
    if (file) {
        Admin *current = admin_head;
        while (current) {
            fwrite(current, sizeof(Admin), 1, file);
            current = current->next;
        }
        fclose(file);
    }
}

