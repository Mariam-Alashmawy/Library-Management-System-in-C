# Library Management System

## Overview


This Library Management System is a C-based console application that allows users and administrators to manage books and library operations. Users can borrow, buy, and request books, while administrators can manage users, books, and reservations.

## Features

### User Mode

1- View User Data

* Display username
* Display user ID
* Display borrowed books (if any)
* Display library card ID (if available)
  
2- Change User Password

* User can change their password
* Requires a new login after the change
  
3- View All Books

* Display all books with their availability status
  
4- Search for a Book

* Search by book name, book ID, or book author
* In case of search by author, list all books by that author
* Display book information and its availability status
  
5- Request to Borrow a Book

* User can request to borrow an available book
* Requests must be approved by an admin

6- Buy a Book

* Display available books with prices
* User can buy one or more books
* Display total price and allow payment by cash or library card
* Check user's library card balance before approving the transaction

7- Request a New Book

* User can request for a new book to be added to the library in the future

8- Show Current Borrow Requests

* Display the status of user's borrow requests (approved, waiting, denied)

9- Logout

### Admin Mode

1- View All Users

* Display all users with their details

2- View All Books

* Display all books with their details

3- Add Book

* Add a new book to the library

4- Remove Book

* Remove an existing book from the library

5- Add User

* Add a new user to the library system

6-  Remove User

* Remove an existing user from the library system

7- Edit User ID

* Change the ID of an existing user

8- Search Books

* Search books in the library by name, ID, or author

9- Make Reservation

* Admin can reserve a book for a user

10- Make Reserved Book Available

* Admin can mark a reserved book as available

11- Logout

### Owner Mode

1- Add/Remove Admins
* Allows adding or removing administrators who have access to the system

2- Manage Admin Permissions:
*Grant or revoke specific permissions to admins. Permissions include:
  * Add/remove member
  * Add/remove book
  * Make a book reservation
