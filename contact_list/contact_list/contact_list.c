// Use Everything search newc++file.cpp
#define _CRT_SECURE_NO_WARNINGS 1
#include "contact_list.h"

// Load file information to contacts
void load_contacts(contacts* pc) {
	FILE* pf = fopen("contacts.txt", "rb");

	if (pf == NULL)
	{
		perror("load_contacts::fopen");
	}
	else
	{
		people temp = { 0 };
		int i = 0;
		while (fread(&temp, sizeof(people), 1, pf))
		{
			check_capacity(pc);
			pc->data[i] = temp;
			pc->sz++;
			i++;
		}
	}

	fclose(pf);
	pf = NULL;
}

void init_contact(contacts* pc) {
	assert(pc);

	pc->sz = 0;
	people* p = (people*)calloc(DEFAULT_SIZE, sizeof(people));
	if (p == NULL)
	{
		perror("init_contact::calloc");
		return;
	}

	pc->data = p;
	pc->capacity = DEFAULT_SIZE;

	// Load file info
	load_contacts(pc);
}

void check_capacity(contacts* pc) {
	if (pc->sz == pc->capacity)
	{
		people* p = (people*)realloc(pc->data, (pc->capacity + INC_SIZE) * sizeof(people));
		if (p == NULL)
		{
			perror("check_capacity::realloc");
			return;
		}

		pc->data = p;
		pc->capacity += INC_SIZE;

		printf("The capacity increase was successful.\n");
	}
}

void add_contact(contacts* pc) {
	assert(pc);

	check_capacity(pc);

	// Add one people
	printf("Please enter the name: ");
	scanf("%s", pc->data[pc->sz].name);

	printf("Please enter the age: ");
	scanf("%d", &(pc->data[pc->sz].age));

	printf("Please enter the gender: ");
	scanf("%s", pc->data[pc->sz].gender);

	printf("Please enter the address: ");
	scanf("%s", pc->data[pc->sz].addr);

	printf("Please enter the telephone number: ");
	scanf("%s", pc->data[pc->sz].tele);

	// Added one people, make size add too
	pc->sz++;
}

// Find a specific name in the directory
// return the index of this person in the contacts if found
// -1 if not
int find_by_name(contacts* pc, char* name) {
	for (int i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
		{
			return i;
		}
	}

	return -1;
}

void delete_contact(contacts* pc) {
	if (pc->sz == 0)
	{
		printf("Directory is empty, cannot delete");
		return;
	}

	printf("Please enter the name you want to delete: ");
	char name[NAME_MAX];
	scanf("%s", name);

	int del = find_by_name(pc, name);
	if (del == -1)
	{
		printf("Cannot find this person.\n");
		return;
	}

	memmove(&(pc->data[del]), &(pc->data[del + 1]), (pc->sz - del - 1) * sizeof(pc->data[0]));

	pc->sz--;

	printf("Deleted.\n");
}


void search_contact(const contacts* pc) {
	assert(pc);

	printf("Please enter the name you want to search: ");
	char name[NAME_MAX];
	scanf("%s", name);

	int ret = find_by_name(pc, name);
	if (ret == -1)
	{
		printf("Cannot find this person.\n");
		return;
	}

	printf("%-20s%-10s%-20s%-20s%-12s\n", "Name", "Age", "Sex", "Address", "Telephone number");
	printf("%-20s%-10d%-20s%-20s%-12s\n", pc->data[ret].name, pc->data[ret].age, pc->data[ret].gender, pc->data[ret].addr, pc->data[ret].tele);
}

void modify_contact(contacts* pc) {
	assert(pc);

	printf("Please enter the name you want to modify: ");
	char name[NAME_MAX];
	scanf("%s", name);

	int ret = find_by_name(pc, name);
	if (ret == -1)
	{
		printf("Cannot find this person.\n");
		return;
	}

	printf("Please enter the name: ");
	scanf("%s", pc->data[ret].name);

	printf("Please enter the age: ");
	scanf("%d", &(pc->data[ret].age));

	printf("Please enter the gender: ");
	scanf("%s", pc->data[ret].gender);

	printf("Please enter the address: ");
	scanf("%s", pc->data[ret].addr);

	printf("Please enter the telephone number: ");
	scanf("%s", pc->data[ret].tele);

	printf("Modified.\n");
}

void show_directory(const contacts* pc) {
	printf("%-20s%-10s%-20s%-20s%-12s\n", "Name", "Age", "Sex", "Address", "Telephone number");

	for (int i = 0; i < pc->sz; i++)
	{
		printf("%-20s%-10d%-20s%-20s%-12s\n", pc->data[i].name, pc->data[i].age, pc->data[i].gender, pc->data[i].addr, pc->data[i].tele);
	}
}


// Compare by people's name
int compare_by_name(const void* p1, const void* p2) {
	contacts* a = (contacts*)p1;
	contacts* b = (contacts*)p2;

	return strcmp(a->data->name, b->data->name);
}

// Compare by people's age
int compare_by_age(const void* p1, const void* p2) {
	contacts* a = (contacts*)p1;
	contacts* b = (contacts*)p2;

	return a->data->age - b->data->age;
}

// Compare by people's gender
int compare_by_gender(const void* p1, const void* p2) {
	contacts* a = (contacts*)p1;
	contacts* b = (contacts*)p2;

	return strcmp(a->data->gender, b->data->gender);
}

void sort_directory(contacts* pc) {
	printf("Please specify how you would like to sort: \n");
	printf("1.Name\n");
	printf("2.Age\n");
	printf("3.Gender\n");

	int input = 0;
	scanf("%d", &input);

	size_t sz = sizeof(pc->data[0]);

	switch (input)
	{
	case 1:
		qsort(pc->data, pc->sz, sz, compare_by_name);
		break;
	case 2:
		qsort(pc->data, pc->sz, sz, compare_by_age);
		break;
	case 3:
		qsort(pc->data, pc->sz, sz, compare_by_gender);
		break;
	default:
		printf("Invalid selection.\n");
		break;
	}
}

void destroy_directory(contacts* pc) {
	free(pc->data);
	pc->data = NULL;
	pc->capacity = 0;
	pc->sz = 0;
	pc = NULL;
}

void save_contact(contacts* pc) {
	FILE* pf = fopen("contacts.txt", "wb");

	if (pf == NULL)
	{
		perror("save_contact");
	}
	else
	{
		for (int i = 0; i < pc->sz; i++)
		{
			fwrite(pc->data + i, sizeof(people), 1, pf);
		}

		fclose(pf);
		pf = NULL;
		printf("Save successuful.\n");
	}
}