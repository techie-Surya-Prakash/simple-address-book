#include <stdio.h>
#include <string.h>


struct Contact {
    char name[50];
    char phone[20];
};

struct Contact contacts[100];
int contactCount = 0;

void addContact(void) {
    if (contactCount == 100) {
        printf("Address book is full.\n");
        return;
    }

    printf("Enter name: ");
    scanf(" %49[^\n]", contacts[contactCount].name);
    printf("Enter phone number: ");
    scanf(" %19s", contacts[contactCount].phone);

    contactCount++;
    printf("Contact added.\n");
}

void showContacts(void) {
    int i;

    if (contactCount == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("\nAddress Book\n");
    for (i = 0; i < contactCount; i++) {
        printf("%d. Name: %s, Phone: %s\n",
               i + 1, contacts[i].name, contacts[i].phone);
    }
}

void searchContact(void) {
    char searchName[50];
    int i;

    printf("Enter name to search: ");
    scanf(" %49[^\n]", searchName);

    for (i = 0; i < contactCount; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            printf("Name: %s, Phone: %s\n",
                   contacts[i].name, contacts[i].phone);
            return;
        }
    }

    printf("Contact not found.\n");
}

int main(void) {
    int choice;

    do {
        printf("\n1. Add contact\n");
        printf("2. Show contacts\n");
        printf("3. Search contact\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                showContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 4);

    return 0;
}

