#include <stdio.h>
#include "owner.h"
#include "admin.h"
#include "user.h"
#include "data.h"

void display_menu() {
    printf("Library Management System\n");
    printf("1- Owner Login\n");
    printf("2- Admin Login\n");
    printf("3- User Login\n");
    printf("4- Exit\n");
    printf("Enter your choice: ");
}

int main() {
    init_data();

    int choice;
    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                owner_login();
                break;
            case 2:
                admin_login();
                break;
            case 3:
                user_login();
                break;
            case 4:
                save_data();
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\nPlease Try again\n");
        }
    } while (choice != 4);

    return 0;
}
