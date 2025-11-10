#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
    int quantity;
};

void addBook();
void displayBooks();
void searchBook();
void deleteBook();

int main() {
    int choice;
    while (1) {
        printf("\n====== Library Management System ======\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: 
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addBook() {
    struct Book b;
    FILE *fp = fopen("library.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    getchar();  // clear newline
    printf("Enter Book Title: ");
    gets(b.title);
    printf("Enter Author Name: ");
    gets(b.author);
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("Book added successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("\n%-10s %-30s %-30s %-10s\n", "Book ID", "Title", "Author", "Qty");
    printf("--------------------------------------------------------------------------\n");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-10d %-30s %-30s %-10d\n", b.id, b.title, b.author, b.quantity);
    }
    fclose(fp);
}

void searchBook() {
    struct Book b;
    int id, found = 0;
    FILE *fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == id) {
            printf("\nBook Found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n", b.id, b.title, b.author, b.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

void deleteBook() {
    struct Book b;
    int id, found = 0;
    FILE *fp = fopen("library.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id != id)
            fwrite(&b, sizeof(b), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found!\n");
}
