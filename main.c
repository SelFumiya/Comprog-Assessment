#include <stdio.h>
#include <string.h>

#define MB 100
#define TL 50
#define AL 50

struct Book {
    int id;
    char title[TL];
    char author[AL];
    int isIssued;
    char issuedTo[AL];
};

void addBook(struct Book books[], int *bookCount);
void listBooks(struct Book books[], int bookCount);
void searchBook(struct Book books[], int bookCount);
void issueBook(struct Book books[], int bookCount);
void deleteBook(struct Book books[], int *bookCount);

int main() {
    struct Book books[MB];
    int bookCount = 0;
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. List Books\n");
        printf("3. Search Book by Title\n");
        printf("4. Issue Book\n");
        printf("5. Delete Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &bookCount);
                break;
            case 2:
                listBooks(books, bookCount);
                break;
            case 3:
                searchBook(books, bookCount);
                break;
            case 4:
                issueBook(books, bookCount);
                break;
            case 5:
                deleteBook(books, &bookCount);
                break;
            case 6:
                printf("Exiting the system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void addBook(struct Book books[], int *bookCount) {
    if (*bookCount >= MB) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    newBook.id = *bookCount + 1;
    printf("Enter book title: ");
    scanf(" %[^\n]", newBook.title);
    printf("Enter author name: ");
    scanf(" %[^\n]", newBook.author);
    newBook.isIssued = 0;
    strcpy(newBook.issuedTo, "");

    books[*bookCount] = newBook;
    (*bookCount)++;
    printf("Book added successfully with ID: %d\n", newBook.id);
}

void listBooks(struct Book books[], int bookCount) {
    if (bookCount == 0) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\n%-5s %-30s %-30s %-10s %-30s\n", "ID", "Title", "Author", "Status", "Issued To");
    for (int i = 0; i < bookCount; i++) {
        printf("%-5d %-30s %-30s %-10s %-30s\n", 
               books[i].id, 
               books[i].title, 
               books[i].author, 
               books[i].isIssued ? "Issued" : "Available",
               books[i].isIssued ? books[i].issuedTo : "N/A");
    }
}

void searchBook(struct Book books[], int bookCount) {
    char searchTitle[TL];
    printf("Enter book title to search: ");
    scanf(" %[^\n]", searchTitle);

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, searchTitle) == 0) {
            printf("Book found! ID: %d, Title: %s, Author: %s, Status: %s\n",
                   books[i].id, 
                   books[i].title, 
                   books[i].author, 
                   books[i].isIssued ? "Issued" : "Available");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void issueBook(struct Book books[], int bookCount) {
    int bookID;
    printf("Enter the book ID to issue: ");
    scanf("%d", &bookID);

    if (bookID < 1 || bookID > bookCount || books[bookID - 1].isIssued) {
        printf("Invalid ID or book already issued.\n");
        return;
    }

    printf("Enter the name of the person to whom the book is issued: ");
    scanf(" %[^\n]", books[bookID - 1].issuedTo);
    books[bookID - 1].isIssued = 1;
    printf("Book ID %d has been issued to: %s.\n", bookID, books[bookID - 1].issuedTo);
}

void deleteBook(struct Book books[], int *bookCount) {
    int bookID;
    printf("Enter the book ID to delete: ");
    scanf("%d", &bookID);

    if (bookID < 1 || bookID > *bookCount) {
        printf("Invalid ID. Cannot delete book.\n");
        return;
    }

    for (int i = bookID - 1; i < *bookCount - 1; i++) {
        books[i] = books[i + 1];
    }

    (*bookCount)--;
    printf("Book with ID %d has been deleted.\n", bookID);
}
