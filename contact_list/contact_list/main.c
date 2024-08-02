// Use Everything search newc++file.cpp
#define _CRT_SECURE_NO_WARNINGS 1
#include "contact_list.h"

void menu() {
	printf("********************************\n");
	printf("****** 1.add     2.del    ******\n");
	printf("****** 3.search  4.modify ******\n");
	printf("****** 5.show    6.sort   ******\n");
	printf("****** 0.exit             ******\n");
	printf("********************************\n");
}

enum selection
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

int main() {
	int input;

	// Create directory of contact
	contacts con;

	// Initialization
	init_contact(&con);

	do
	{
		menu();
		printf("Please make your selection: ");
		scanf("%d", &input);

		switch (input)
		{
		case ADD:
			add_contact(&con);
			break;
		case DEL:
			delete_contact(&con);
			break;
		case SEARCH:
			search_contact(&con);
			break;
		case MODIFY:
			modify_contact(&con);
			break;
		case SHOW:
			show_directory(&con);
			break;
		case SORT:
			sort_directory(&con);
			break;
		case EXIT:
			// Save Information to file
			save_contact(&con);

			destroy_directory(&con);
			printf("Exit the directory of contact.\n");
			break;
		default:
			printf("Invalid selection.\n");
			break;
		}

	} while (input);


	return 0;
}