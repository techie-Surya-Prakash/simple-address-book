#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LENGTH 80
#define PHONE_LENGTH 32
#define EMAIL_LENGTH 100
#define DATA_FILE "contacts.csv"

typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
} Contact;

static Contact contacts[MAX_CONTACTS];
static int contact_count = 0;

static void trim_newline(char *text) {
    text[strcspn(text, "\r\n")] = '\0';
}

static int read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) return 0;
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
    }
    trim_newline(buffer);
    return 1;
}

static void load_contacts(void) {
    FILE *file = fopen(DATA_FILE, "r");
    char line[NAME_LENGTH + PHONE_LENGTH + EMAIL_LENGTH + 4];
    if (file == NULL) return;

    while (contact_count < MAX_CONTACTS && fgets(line, sizeof line, file) != NULL) {
        Contact c;
        trim_newline(line);
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        if (name == NULL || phone == NULL || email == NULL) continue;
        snprintf(c.name, sizeof c.name, "%s", name);
        snprintf(c.phone, sizeof c.phone, "%s", phone);
        snprintf(c.email, sizeof c.email, "%s", email);
        contacts[contact_count++] = c;
    }
    fclose(file);
}

static int save_contacts(void) {
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL) {
        perror("Could not save contacts");
        return 0;
    }
    for (int i = 0; i < contact_count; i++) {
        if (fprintf(file, "%s,%s,%s\n", contacts[i].name,
                    contacts[i].phone, contacts[i].email) < 0) {
            perror("Could not write contacts");
            fclose(file);
            return 0;
        }
    }
    if (fclose(file) != 0) {
        perror("Could not close contacts file");
        return 0;
    }
    return 1;
}

static void add_contact(void) {
    if (contact_count == MAX_CONTACTS) {
        puts("Address book is full.");
        return;
    }
    Contact c;
    if (!read_line("Name: ", c.name, sizeof c.name) || c.name[0] == '\0' ||
        !read_line("Phone: ", c.phone, sizeof c.phone) || c.phone[0] == '\0' ||
        !read_line("Email: ", c.email, sizeof c.email)) {
        puts("Contact was not added; name and phone are required.");
        return;
    }
    contacts[contact_count++] = c;
    if (save_contacts()) puts("Contact added.");
}

static void list_contacts(void) {
    if (contact_count == 0) {
        puts("No contacts saved.");
        return;
    }
    printf("\n%-4s %-30s %-20s %s\n", "No.", "Name", "Phone", "Email");
    for (int i = 0; i < contact_count; i++)
        printf("%-4d %-30s %-20s %s\n", i + 1, contacts[i].name,
               contacts[i].phone, contacts[i].email);
}

static void search_contacts(void) {
    char query[NAME_LENGTH];
    if (!read_line("Search name: ", query, sizeof query)) return;
    int found = 0;
    for (int i = 0; i < contact_count; i++) {
        if (strstr(contacts[i].name, query) != NULL) {
            printf("%s | %s | %s\n", contacts[i].name,
                   contacts[i].phone, contacts[i].email);
            found = 1;
        }
    }
    if (!found) puts("No matching contacts.");
}

static void delete_contact(void) {
    char input[16];
    if (contact_count == 0) {
        puts("No contacts to delete.");
        return;
    }
    list_contacts();
    if (!read_line("Contact number to delete: ", input, sizeof input)) return;
    char *end;
    long number = strtol(input, &end, 10);
    if (*input == '\0' || *end != '\0' || number < 1 || number > contact_count) {
        puts("Invalid contact number.");
        return;
    }
    for (int i = (int)number - 1; i < contact_count - 1; i++)
        contacts[i] = contacts[i + 1];
    contact_count--;
    if (save_contacts()) puts("Contact deleted.");
}

int main(void) {
    char input[16];
    load_contacts();
    for (;;) {
        puts("\nAddress Book\n1. Add contact\n2. List contacts\n3. Search by name\n4. Delete contact\n5. Exit");
        if (!read_line("Choose an option: ", input, sizeof input)) break;
        if (strcmp(input, "1") == 0) add_contact();
        else if (strcmp(input, "2") == 0) list_contacts();
        else if (strcmp(input, "3") == 0) search_contacts();
        else if (strcmp(input, "4") == 0) delete_contact();
        else if (strcmp(input, "5") == 0) break;
        else puts("Invalid option.");
    }
    return 0;
}
