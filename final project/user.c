#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "data.h"
#include "file_handler.h"

void user_mode(User *user);

void user_login() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    User *current = user_head;
    while (current) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            user_mode(current);
            return;
        }
        current = current->next;
    }
    printf("Invalid credentials\n");
}

void view_user_data(User *user) {
    printf("Username: %s\n", user->username);
    printf("User ID: %d\n", user->user_id);
    for (int i = 0; i < user->borrow_count; ++i) {
        printf("Borrowed Book ID: %d\n", user->borrowed_books[i]);
    }
   // printf("Library Card ID: %s\n", user->library_card_id);
//    printf("Balance: %.2f\n", user->balance);
}

void user_mode(User *user) {
    int choice;
    do {
        printf("User Mode:\n");
        printf("1. View User Data\n");
        printf("2. Change Password\n");
        printf("3. View All Books\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_user_data(user);
                break;
            case 2:
                // Implement password change functionality here
                break;
            case 3:
                // Implement view all books functionality here
                break;
            case 4:
                save_data();
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice\nPlease Try again.\n");
        }
    } while (choice != 4);
}

