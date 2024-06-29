#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "owner.h"
#include "data.h"
#include "file_handler.h"

void owner_mode();

void owner_login() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, "owner") == 0 && strcmp(password, "1234") == 0) {
        owner_mode();
    } else {
        printf("Invalid Data\n");
    }
}

void add_admin() {
    Admin *new_admin = (Admin *)malloc(sizeof(Admin));
    printf("Enter admin username: ");
    scanf("%s", new_admin->username);
    printf("Enter admin password: ");
    scanf("%s", new_admin->password);
    new_admin->can_add_remove_member = 1;
    new_admin->can_add_remove_book = 1;
    new_admin->can_reserve_book = 1;
    new_admin->next = admin_head;
    admin_head = new_admin;
    save_admins();
    printf("Admin added\n");
}

void remove_admin() {
    char username[MAX_NAME_LEN];
    printf("Enter admin username to remove: ");
    scanf("%s", username);

    Admin *current = admin_head;
    Admin *prev = NULL;
    while (current) {
        if (strcmp(current->username, username) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                admin_head = current->next;
            }
            free(current);
            save_admins();
            printf("Admin removed\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Admin not found\n");
}

void set_admin_permissions() {
    char username[MAX_NAME_LEN];
    printf("Enter admin username to set permissions: ");
    scanf("%s", username);

    Admin *current = admin_head;
    while (current) {
        if (strcmp(current->username, username) == 0) {
            printf("Set permissions for %s:\n", username);
            printf("Can add/remove member (Press 1 for Yes and 0 for No): ");
            scanf("%d", &current->can_add_remove_member);
            printf("Can add/remove book (Press 1 for Yes and 0 for No): ");
            scanf("%d", &current->can_add_remove_book);
            printf("Can reserve book (Press 1 for Yes and 0 for No): ");
            scanf("%d", &current->can_reserve_book);
            save_admins();
            printf("Permissions updated\n");
            return;
        }
        current = current->next;
    }
    printf("Admin not found\n");
}

void owner_mode() {
    int choice;
    do {
        printf("Owner Mode:\n");
        printf("1- Add Admin\n");
        printf("2- Remove Admin\n");
        printf("3- Set Admin Permissions\n");
        printf("4- Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_admin();
                break;
            case 2:
                remove_admin();
                break;
            case 3:
                set_admin_permissions();
                break;
            case 4:
                save_data();
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice\nPlease Try again\n");
        }
    } while (choice != 4);
}

