
#include <stdio.h>

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

/* Function declarations */
void addContact();
void displayContacts();
void searchContact();
void deleteContact();

int main() {
    int choice;

    do {
        printf("\n--- Contact Management System \n");
        printf("1. Add Contact\n");
        printf("2. Display All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}

/* Add a new contact */
void addContact() {
    struct Contact c;//contact variable
    FILE *fp = fopen("contacts.dat", "ab");//ab append binary mode

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter phone: ");
    scanf(" %[^\n]", c.phone);
    printf("Enter email: ");
    scanf(" %[^\n]", c.email);

    fwrite(&c, sizeof(c), 1, fp);//c struct ka address
    
    fclose(fp);

    printf("Contact added successfully!\n");
}

/* show all contacts */
void showContacts() {
    struct Contact c;
    FILE *fp = fopen("contacts.dat", "rb");

    if (fp == NULL) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (fread(&c, sizeof(c), 1, fp)) {
        printf("\nName  : %s", c.name);
        printf("\nPhone : %s", c.phone);
        printf("\nEmail : %s\n", c.email);
    }

    fclose(fp);
}

/* Search contact by name */
void searchContact() {
    struct Contact c;
    char searchName[50];
    int found = 0;

    FILE *fp = fopen("contacts.dat", "rb");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, searchName) == 0) {
            printf("\nContact Found!");
            printf("\nName  : %s", c.name);
            printf("\nPhone : %s", c.phone);
            printf("\nEmail : %s\n", c.email);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found.\n");

    fclose(fp);
}

/* Delete contact */
void deleteContact() {
    struct Contact c;
    char deleteName[50];
    int found = 0;

    FILE *fp = fopen("contacts.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter name to delete: ");
    scanf(" %[^\n]", deleteName);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, deleteName) != 0) {
            fwrite(&c, sizeof(c), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found)
        printf("Contact deleted successfully!\n");
    else
        printf("Contact not found.\n");
}
