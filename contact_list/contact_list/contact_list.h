#pragma once
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define NAME_MAX 20
#define SEX_MAX 5
#define ADDR_MAX 20
#define TELE_MAX 12

#define DEFAULT_SIZE 3
#define INC_SIZE 2

// Structure of People
typedef struct people
{
	char name[NAME_MAX];
	int age;
	char gender[SEX_MAX];
	char addr[ADDR_MAX];
	char tele[TELE_MAX];
} people;

// Structure of contacts
typedef struct contacts
{
	people* data; // Point to the space that store people's information
	int sz; // Current number of people
	int capacity; // Max capacity of the current contact list
} contacts;

// Initialization of contact list
void init_contact(contacts* pc);

// Add a contact to contact list
void add_contact(contacts* pc);

// Delete a contact in contact list
void delete_contact(contacts* pc);

// Search a contact in contact list
void search_contact(const contacts* pc);

// Modify a contact in contact list
void modify_contact(contacts* pc);

// Print the contact list
void show_directory(const contacts* pc);

// Sort the contact list
void sort_directory(contacts* pc);

// Destroy the contact list
void destroy_directory(contacts* pc);
