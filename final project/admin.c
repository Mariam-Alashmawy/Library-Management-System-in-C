#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "data.h"
#include "file_handler.h"

int count_borrowed_books(User *user) {
    return user->borrow_count;
}

User *find_user_by_id(int user_id) {
    User *current_user = user_head;

    while (current_user != NULL) {
        if (current_user->user_id == user_id) {
            return current_user; // User found, return pointer to user
        }
        current_user = current_user->next;
    }

    return NULL; // User not found
}

void search_books_by_name(const char *name) {
    Book *current = book_head;
    int found = 0;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Book Name: %s\n", current->name);
            printf("Author: %s\n", current->author);
            printf("Book ID: %d\n", current->id);
            printf("Available: %s\n", current->available ? "Yes" : "No");
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No books found matching the name '%s'.\n", name);
    }
}

void search_books_by_id(int id) {
    Book *current = book_head;
    int found = 0;

    while (current) {
        if (current->id == id) {
            printf("Book Name: %s\n", current->name);
            printf("Author: %s\n", current->author);
            printf("Book ID: %d\n", current->id);
            printf("Available: %s\n", current->available ? "Yes" : "No");
            found = 1;
            break; // Stop searching after finding the book
        }
        current = current->next;
    }

    if (!found) {
        printf("Book with ID %d not found.\n", id);
    }
}

void search_books_by_author(const char *author) {
    Book *current = book_head;
    int found = 0;

    while (current) {
        if (strcmp(current->author, author) == 0) {
            printf("Book Name: %s\n", current->name);
            printf("Author: %s\n", current->author);
            printf("Book ID: %d\n", current->id);
            printf("Available: %s\n", current->available ? "Yes" : "No");
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No books found by author '%s'.\n", author);
    }
}

void admin_login() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    Admin *current = admin_head;
    while (current) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            admin_mode(current);
            return;
        }
        current = current->next;
    }
    printf("Invalid credentials\n");
}

void view_all_users() {
    User *current = user_head;
    while (current) {
        printf("User: %s, ID: %d\n", current->username, current->user_id);
        current = current->next;
    }
}

void view_all_books() {
    Book *current = book_head;
    while (current) {
        printf("Book: %s, Author: %s, ID: %d, Available: %d\n", current->name, current->author, current->id, current->available);
        current = current->next;
    }
}

void add_book() {
    Book *new_book = (Book *)malloc(sizeof(Book));
    printf("Enter book name: ");
    scanf(" %[^\n]", new_book->name);
    printf("Enter book author: ");
    scanf(" %[^\n]", new_book->author);
    new_book->id = (book_head ? book_head->id + 1 : 1);
    new_book->available = 1;
    new_book->next = book_head;
    book_head = new_book;
    save_books();
}

void remove_book() {
    int book_id;
    printf("Enter book ID to remove: ");
    scanf("%d", &book_id);

    Book *current = book_head;
    Book *prev = NULL;
    while (current) {
        if (current->id == book_id) {
            if (prev) {
                prev->next = current->next;
            } else {
                book_head = current->next;
            }
            free(current);
            save_books();
            printf("Book removed.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Book not found.\n");
}

void add_user() {
    User *new_user = (User *)malloc(sizeof(User));
    printf("Enter username: ");
    scanf("%s", new_user->username);
    printf("Enter password: ");
    scanf("%s", new_user->password);
    new_user->user_id = (user_head ? user_head->user_id + 1 : 1);
    new_user->borrow_count = 0;
    new_user->next = user_head;
    user_head = new_user;
    save_users();
}

void remove_user() {
    int user_id;
    printf("Enter user ID to remove: ");
    scanf("%d", &user_id);

    User *current = user_head;
    User *prev = NULL;
    while (current) {
        if (current->user_id == user_id) {
            if (prev) {
                prev->next = current->next;
            } else {
                user_head = current->next;
            }
            free(current);
            save_users();
            printf("User removed.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("User not found.\n");
}

void edit_user_id() {
    int old_id, new_id;

    printf("Enter the old user ID: ");
    scanf("%d", &old_id);
    printf("Enter the new user ID: ");
    scanf("%d", &new_id);

    edit_user_id(old_id, new_id);
}

void search_books() {
    int search_choice;
    char search_term[MAX_NAME_LEN];

    printf("Search books by:\n");
    printf("1. Book Name\n");
    printf("2. Book ID\n");
    printf("3. Book Author\n");
    printf("Enter your choice: ");
    scanf("%d", &search_choice);

    getchar(); // Consume newline character left by scanf

    printf("Enter search term: ");
    fgets(search_term, sizeof(search_term), stdin);
    search_term[strcspn(search_term, "\n")] = '\0'; // Remove newline character from fgets result

    switch (search_choice) {
        case 1:
            search_books_by_name(search_term);
            break;
        case 2:
            search_books_by_id(atoi(search_term));
            break;
        case 3:
            search_books_by_author(search_term);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

void make_reservation() {
    // Display users and prompt admin to choose a user
    User *current_user = user_head;
    int user_choice, user_found = 0;

    printf("Select a user to make a reservation:\n");
    while (current_user) {
        printf("%d. %s\n", current_user->user_id, current_user->username);
        current_user = current_user->next;
    }

    printf("Enter user ID: ");
    scanf("%d", &user_choice);

    // Find the chosen user
    current_user = find_user_by_id(user_choice);
    if (current_user) {
        // Display all books and prompt admin to choose book(s)
        int book_choice;
        char reserve_more;

        do {
            // Display all books
            Book *current_book = book_head;
            printf("Available Books:\n");
            while (current_book) {
                if (current_book->available) {
                    printf("Book ID: %d, Name: %s, Author: %s\n", current_book->id, current_book->name, current_book->author);
                }
                current_book = current_book->next;
            }

            printf("Enter book ID to reserve: ");
            scanf("%d", &book_choice);

            // Find the selected book
            Book *book_to_reserve = NULL;
            current_book = book_head;
            while (current_book) {
                if (current_book->id == book_choice) {
                    book_to_reserve = current_book;
                    break;
                }
                current_book = current_book->next;
            }

            if (book_to_reserve) {
                if (book_to_reserve->available && count_borrowed_books(current_user) < 2) {
                    reserve_book(current_user, book_to_reserve);
                    printf("Book '%s' reserved for user '%s'.\n", book_to_reserve->name, current_user->username);
                } else {
                    printf("Book '%s' cannot be reserved.\n", book_to_reserve->name);
                }
            } else {
                printf("Book with ID %d not found.\n", book_choice);
            }

            printf("Do you want to reserve more books? (y/n): ");
            scanf(" %c", &reserve_more);
        } while (reserve_more == 'y' || reserve_more == 'Y');
    } else {
        printf("User with ID %d not found.\n", user_choice);
    }
}

void admin_mode(Admin *admin) {
    int choice;
    do {
        printf("Admin Mode:\n");
        printf("1. View All Users\n");
        printf("2. View All Books\n");
        printf("3. Add Book\n");
        printf("4. Remove Book\n");
        printf("5. Add User\n");
        printf("6. Remove User\n");
        printf("7. Edit User ID\n");
        printf("8. Search Books\n");
        printf("9. Make Reservation\n");
        printf("10. Make Reserved Book Available\n");
        printf("11. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_all_users();
                break;
            case 2:
                view_all_books();
                break;
            case 3:
                if (admin->can_add_remove_book) {
                    add_book();
                } else {
                    printf("Permission denied.\n");
                }
                break;
            case 4:
                if (admin->can_add_remove_book) {
                    remove_book();
                } else {
                    printf("Permission denied.\n");
                }
                break;
            case 5:
                if (admin->can_add_remove_member) {
                    add_user();
                } else {
                    printf("Permission denied.\n");
                }
                break;
            case 6:
                if (admin->can_add_remove_member) {
                    remove_user();
                } else {
                    printf("Permission denied.\n");
                }
                break;
            case 7:
                edit_user_id();
                break;
            case 8:
                search_books();
                break;
            case 9:
                if (admin->can_reserve_book) {
                    make_reservation();
                } else {
                    printf("Permission denied.\n");
                }
                break;
            case 10:
                if (admin->can_reserve_book) {
                    make_book_available();
                } else {
                    printf("Permission denied.\n");
                }
                break;
            case 11:
                save_data();
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 11);
}
