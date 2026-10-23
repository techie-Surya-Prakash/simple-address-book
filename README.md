# Simple Address Book Application

A C console address book that lets you add contacts, list saved contacts, search names, and delete entries. Contacts are loaded from and saved to `contacts.csv` in the current working directory, so they remain available after restarting the program.

## Build and run

```sh
gcc address_book.c -o address-book
./address-book
```

On Windows, run `address-book.exe`.

Each contact stores a name, phone number, and email. The program keeps up to 100 contacts in memory. Names and phone numbers are required; email may be blank.
