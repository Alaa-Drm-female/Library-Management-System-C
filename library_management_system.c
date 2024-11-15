#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define max_books 50

struct book {
   char title[40];
   char author[40];
   int id;
   int year_of_version;
   char category[20]; 
};

struct book library[max_books];
int bookcounter = 0;

void saveToFile() {
    FILE *file = fopen("library_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < bookcounter; i++) {
        fprintf(file, "%d|%s|%s|%d|%s\n", library[i].id, library[i].title, library[i].author, library[i].year_of_version, library[i].category);
    }
    fclose(file);
    printf("Library data saved successfully!\n");
}

void loadFromFile() {
    FILE *file = fopen("library_data.txt", "r");
    if (file == NULL) {
        printf("No previous data found. Starting fresh!\n");
        return;
    }
    while (fscanf(file, "%d|%[^|]|%[^|]|%d|%[^\n]\n", 
                  &library[bookcounter].id, 
                  library[bookcounter].title, 
                  library[bookcounter].author, 
                  &library[bookcounter].year_of_version, 
                  library[bookcounter].category) != EOF) {
        bookcounter++;
    }
    fclose(file);
    printf("Library data loaded successfully!\n");
}

void addbook() {
    if (bookcounter < max_books) {
        printf("Enter the title of the book:\n");
        scanf(" %[^\n]%*c", library[bookcounter].title);

        printf("Enter the author's name:\n");
        scanf(" %[^\n]%*c", library[bookcounter].author);

        printf("Enter the ID of the book:\n");
        scanf("%d", &library[bookcounter].id);
        getchar();

        printf("Enter the year of version:\n");
        scanf("%d", &library[bookcounter].year_of_version);
        getchar();

        int category_choice;
        printf("Choose a category:\n");
        printf("1. Arabic Literature and Novels\n");
        printf("2. Arabic Poetry\n");
        printf("3. Languages\n");
        printf("4. History\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &category_choice);
        getchar();

        switch (category_choice) {
            case 1:
                strcpy(library[bookcounter].category, "Arabic Literature");
                break;
            case 2:
                strcpy(library[bookcounter].category, "Arabic Poetry");
                break;
            case 3:
                strcpy(library[bookcounter].category, "Languages");
                break;
            case 4:
                strcpy(library[bookcounter].category, "History");
                break;
            default:
                printf("Invalid choice! Defaulting to 'Uncategorized'.\n");
                strcpy(library[bookcounter].category, "Uncategorized");
        }

        bookcounter++;
        printf("The book has been added successfully!\n");
    } else {
        printf("The library is full, can't add more books.\n");
    }
}

void displaybooks() {
    if (bookcounter == 0) {
        printf("The library is empty.\n");
    } else {
        for (int i = 0; i < bookcounter; i++) {
            printf("\nBook #%d\n", i + 1);
            printf("ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Year of Version: %d\n", library[i].year_of_version);
            printf("Category: %s\n", library[i].category);
        }
    }
}

void deletebook() {
    if (bookcounter == 0) {
        printf("The library is empty, no books to delete.\n");
        return;
    }

    int id, found = 0;
    printf("Enter the ID of the book to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookcounter; i++) {
        if (library[i].id == id) {
            found = 1;

            for (int j = i; j < bookcounter - 1; j++) {
                library[j] = library[j + 1];
            }

            bookcounter--;
            printf("The book with ID %d has been deleted.\n", id);
            break;
        }
    }

    if (!found) {
        printf("No book found with ID %d.\n", id);
    }
}

void searchbook() {
    if (bookcounter == 0) {
        printf("The library is empty.\n");
        return;
    }

    int id, found = 0;
    printf("Enter the ID of the book to search for: ");
    scanf("%d", &id);

    for (int i = 0; i < bookcounter; i++) {
        if (library[i].id == id) {
            found = 1;
            printf("\nBook Found!\n");
            printf("ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Year of Version: %d\n", library[i].year_of_version);
            printf("Category: %s\n", library[i].category);
            break;
        }
    }

    if (!found) {
        printf("No book found with ID %d.\n", id);
    }
}

int main() {
    loadFromFile();
    int choice;

    do {
        printf("\nWelcome to Library Management System\n");
        printf("1. Add a Book\n");
        printf("2. Display Books\n");
        printf("3. Delete a Book\n");
        printf("4. Search for a Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addbook();
                break;
            case 2:
                displaybooks();
                break;
            case 3:
                deletebook();
                break;
            case 4:
                searchbook();
                break;
            case 5:
                saveToFile();
                printf("Exiting... Thank you for using the Library Management System!\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
