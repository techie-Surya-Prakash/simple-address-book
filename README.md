# Simple Address Book Application

A menu-driven C program for managing a small address book from the terminal.

## Features

- Add a contact with a name, phone number, and optional email address.
- List all saved contacts.
- Search names by a case-sensitive substring.
- Delete a contact by its number in the displayed list.
- Load and save contacts in `contacts.csv` so they persist between runs.

The program supports up to 100 contacts in memory. The CSV file is created in the program's current working directory. Contact fields are comma-separated, so commas in names, phone numbers, or email addresses are not supported.

## Build and run

With GCC:

```sh
gcc address_book.c -o address-book
./address-book
```

On Windows, run `address-book.exe` from the directory where you want `contacts.csv` stored.

## Menu

1. Add contact
2. List contacts
3. Search by name
4. Delete contact
5. Exit
