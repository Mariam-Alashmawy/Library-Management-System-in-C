#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "user.h"
#include "data.h"
#include "file_handler.h"

void user_mode(User *user);
NewBookRequest *new_book_request_head = NULL;

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
    printf("\nUser Data:\n");
    printf("Username: %s\n", user->username);
    printf("User ID: %d\n", user->user_id);

    // Display borrowed books if any
    if (user->borrowed_count > 0) {
        printf("Borrowed Books:\n");
        BorrowedBook *current = user->borrowed_books;
        while (current != NULL) {
            printf("- %s\n", current->book->name);
            current = current->next;
        }
    } else {
        printf("No books currently borrowed.\n");
    }
    printf("Library Card ID: %d\n", user->library_card_id);
}

void change_password(User *user) {
    char new_password[MAX_NAME_LEN];
    char confirm_password[MAX_NAME_LEN];

    printf("Enter new password: ");
    scanf("%s", new_password);

    printf("Confirm new password: ");
    scanf("%s", confirm_password);

    if (strcmp(new_password, confirm_password) != 0) {
        printf("Passwords do not match. Password change failed.\n");
        return;
    }

    // Update user's password
    strcpy(user->password, new_password);
    printf("Password changed successfully.\n");

    // Request new login after password change
    printf("Please log in again with your new password.\n");
    user_login(); 
}


BorrowRequest* create_borrow_request(User *user, Book *book) {
    BorrowRequest *new_request = (BorrowRequest *)malloc(sizeof(BorrowRequest));
    if (new_request == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    new_request->user = user;
    new_request->book = book;
    new_request->status = 0; 
    new_request->next = NULL;

    // Add the new request to the global list of borrow requests
    if (new_book_request_head == NULL) {
        new_book_request_head = new_request;
    } else {
        BorrowRequest *current_request = new_book_request_head;
        while (current_request->next) {
            current_request = current_request->next;
        }
        current_request->next = new_request;
    }

    return new_request;
}

Book* find_book_by_id(int id) {
    Book *current_book = book_head;
    while (current_book) {
        if (current_book->id == id) {
            return current_book;
        }
        current_book = current_book->next;
    }
    return NULL;
}

void request_borrow_book(User *user) {
    int book_id;
    char confirm;

    // Display available books
    printf("Available books:\n");
    Book *current_book = book_head;
    while (current_book) {
        if (current_book->available) {
            printf("- Book ID: %d, Name: %s\n", current_book->id, current_book->name);
        }
        current_book = current_book->next;
    }

    printf("Enter the ID of the book you want to borrow: ");
    scanf("%d", &book_id);

    // Find the selected book
    current_book = find_book_by_id(book_id);
    if (current_book == NULL) {
        printf("Book with ID %d not found.\n", book_id);
        return;
    }

    // Confirm the book selection
    printf("Do you want to borrow '%s'? (y/n): ", current_book->name);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
            BorrowRequest *request = create_borrow_request(user, current_book);
            if (request) {
                printf("Your request to borrow '%s' has been submitted for admin approval.\n", current_book->name);
            } else {
                printf("Failed to create borrow request. Please try again.\n");
            }
        }
}


void buy_book(User *user) {
    int book_id;
    char confirm;
    float total_price = 0.0;

    // Display available books
    printf("Available books:\n");
    Book *current_book = book_head;
    while (current_book) {
        if (current_book->available) {
            printf("- Book ID: %d, Name: %s, Price: %.2f\n", current_book->id, current_book->name, current_book->price);
        }
        current_book = current_book->next;
    }

    // Prompt user to choose a book
    printf("Enter the ID of the book you want to buy: ");
    scanf("%d", &book_id);

    // Find the selected book
    current_book = find_book_by_id(book_id);
    if (current_book == NULL) {
        printf("Book with ID %d not found.\n", book_id);
        return;
    }

    // Confirm the book selection
    printf("Do you want to buy '%s' for %.2f? (y/n): ", current_book->name, current_book->price);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        total_price += current_book->price;
        printf("Total price: %.2f\n", total_price);
        printf("How would you like to pay? (1 for cash, 2 for library card): ");
        int payment_method;
        scanf("%d", &payment_method);

        if (payment_method == 1) {
            printf("Paid %.2f in cash.\n", total_price);
            current_book->available = 0; // Mark the book as sold
        } else if (payment_method == 2) {
            char card_id[50];
            char card_password[50];
            float card_balance = 100.0; // Assume some balance for the library card

            printf("Enter your library card ID: ");
            scanf("%s", card_id);
            printf("Enter your library card password: ");
            scanf("%s", card_password);
            
            if (card_balance >= total_price) {
                card_balance -= total_price;
                printf("Paid %.2f with library card. Remaining balance: %.2f\n", total_price, card_balance);
                current_book->available = 0; // Mark the book as sold
            } else {
                printf("Insufficient balance on your library card.\n");
            }
        } else {
            printf("Invalid payment method.\n");
        }
    } else {
        printf("Purchase cancelled.\n");
    }
}

void request_new_book() {
    char book_name[MAX_NAME_LEN];
    char book_author[MAX_NAME_LEN];

    printf("Enter the name of the book you want to request: ");
    scanf(" %[^\n]", book_name);
    printf("Enter the author of the book: ");
    scanf(" %[^\n]", book_author);

    // Create a new book request
    NewBookRequest *new_request = (NewBookRequest *)malloc(sizeof(NewBookRequest));
    if (new_request == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strncpy(new_request->book_name, book_name, MAX_NAME_LEN);
    strncpy(new_request->book_author, book_author, MAX_NAME_LEN);
    new_request->next = NULL;

    // Add the new request to the end of the linked list
    if (new_book_request_head == NULL) {
        new_book_request_head = new_request;
    } else {
        NewBookRequest *current = new_book_request_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_request;
    }

    printf("New book request for '%s' by '%s' has been submitted.\n", book_name, book_author);
}

BorrowRequest *borrow_request_head;



void show_borrow_requests(User *user) {
    BorrowRequest *current_request = borrow_request_head;
    int request_found = 0;

    printf("\nCurrent Borrow Requests for User: %s\n", user->username);
    while (current_request) {
        if (current_request->user->user_id == user->user_id) { // Compare user IDs
            printf("Book Name: %s, Status: %s\n",
                   current_request->book->name,
                   current_request->status == 0 ? "waiting" :
                   current_request->status == 1 ? "approved" : "denied");
            request_found = 1;
        }
        current_request = current_request->next;
    }

    if (!request_found) {
        printf("No borrow requests found for this user.\n");
    }
}

void user_mode(User *user) {
    int choice;
    do {
        printf("\nUser Menu\n");
        printf("1. View user data\n");
        printf("2. Change password\n");
        printf("3. View all books\n");
        printf("4. Search for a book\n");
        printf("5. Request to borrow a book\n");
        printf("6. Buy a book\n");
        printf("7. Request a new book\n");
        printf("8. Show current borrow requests\n");
        printf("9. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                view_user_data(user);
                break;
            case 2:
                change_password(user);
                break;
            case 3:
                view_all_books();
                break;
            case 4:
                search_books();
                break;
            case 5:
                request_borrow_book(user);
                break;
            case 6:
                buy_book(user);
                break;
            case 7:
                request_new_book();
                break;
            case 8:
                show_borrow_requests(user);
                break;
            case 9:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please enter a number from 1 to 9.\n");
        }
    } while (choice != 9);
}
