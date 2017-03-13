#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_menu() {
	printf("[1] Show passwords\n");
	printf("[2] Add new password\n");
	printf("[3] Delete existing password\n");
	printf("[4] Quit\n");
}

void show_passwords() {
	// show file contents
	printf("----- credentials -----\n");

	int c;
	FILE *file;
	file = fopen("/home/crimson/hsf/storesafe/creds", "r");
	if (file) {
		while ((c = getc(file)) != EOF)
			putchar(c);
		fclose(file);
	}

	printf("-----------------------\n");
}

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);

	printf("--=[ Welcome to StoreSafe v1.0 ]=--\n");
	printf("\n");
	printf("There's no safer place to store your passwords, definitely.\n");
	printf("\n");

	char* username = "anonynooseAdmin";
	char* password = "thisisthesupersecretpasswordyouwillandcouldneverguess";

	char input_username[256];
	char input_password[256];

	printf("Please enter your credentials...\n");

	printf("Username: ");
	fgets(input_username, 256, stdin);

	char* pos;
	if ((pos = strchr(input_username, '\n')) != NULL)
		*pos = '\0';

	printf("Password: ");
	fgets(input_password, 256, stdin);

	if ((pos = strchr(input_password, '\n')) != NULL)
		*pos = '\0';

	if (strncmp(input_username, username, 256) == 0 &&
		strncmp(input_password, password, 256) == 0) {

		printf("\n*** Authenticated ***\n");

		while (1) {
			display_menu();

			int option;
			printf("Option> ");
			scanf("%d", &option);

			if (option == 1) {
				show_passwords();
			} else if (option == 2) {
				printf("Not yet implemented.\n");
			} else if (option == 3) {
				printf("Not yet implemented.\n");
			} else if (option == 4) {
				printf("Have a nice day. Goodbye.\n");
				return 0;
			} else {
				printf("That's not a valid option. Try again.\n");
			}

		}

	} else {
		printf(input_username);
		printf("/");
		printf(input_password);
		printf(" are invalid credentials. Goodbye.\n");
	}

	return 0;
}
