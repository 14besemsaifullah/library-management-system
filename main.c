//----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------H-E-A-D-E-R---F-I-L-E-S--------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <malloc.h>
#include "manageMembers.h"
#include "manageBooks.h"


//----------------------------------------------------------------------------------------------------------------//
//----------------------------------------F-U-N-C-T-I-O-N---P-R-O-T-O-T-Y-P-E-S-----------------------------------//
//----------------------------------------------------------------------------------------------------------------//

int librarianMenu(void);
int memberMenu(void);
int guestMenu(void);
void printHeader(void);


//----------------------------------------------------------------------------------------------------------------//
//--------------------------------------------D-A-T-A---S-T-R-U-C-T-U-R-E-S---------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

typedef struct {
	bool info;								// Librarian data available? TRUE/FALSE
	char libNameF[30];						// Librarian's first name
	char libNameL[20];						// Librarian's last name
	char libStreet[150];					// Librarrian's street address
	char libCity[20];						// Libraririan's city of residence
	char libEmail[75];						// Librarian's email address
	unsigned long libPhone;					// Librarian's phone number
	char libID[11];							// Auto-generated ID to access librarian menu 
} Librarian;


//----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------G-L-O-B-A-L---V-A-R-I-A-B-L-E-S------------------------------------//
//----------------------------------------------------------------------------------------------------------------//




//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------P-R-O-G-R-A-M---E-N-T-R-Y---P-O-I-N-T---------------------------------//
//----------------------------------------------------------------------------------------------------------------//

int main()
{
MAIN_MENU:
	// Prints main menu
	printHeader();
	printf_s("%s\n",	"                                                                                ");
	printf_s("%s\n\n",	"--------------------------------------------------------------------------------");
	printf_s("%s\n",	"                Librarian menu                       1                          ");
	printf_s("%s\n",	"                Members menu                         2                          ");
	printf_s("%s\n",	"                Guest menu                           3                          ");
	printf_s("%s",		"------------------------------------------------------------------------------");
	
	// Main menu selection
	char choice;
	scanf_s("%d", &choice);
	while (choice != 0){
		switch (choice){
		case 1:
			librarianMenu();
			puts("Press enter to return to main menu");
			fflush(stdin);
			getchar();
			goto MAIN_MENU;
			break;
		case 2:
			memberMenu();
			puts("Press enter to return to main menu");
			fflush(stdin);
			getchar();
			goto MAIN_MENU;
			break;
		case 3:
			guestMenu();
			puts("Press enter to return to main menu");
			fflush(stdin);
			getchar();
			goto MAIN_MENU;
			break;
		default:
			break;
		}
		scanf_s("%c", &choice);
	}
	return 0;
}


//----------------------------------------------------------------------------------------------------------------//
//----------------------------------------------F-U-N-C-T-I-O-N---B-O-D-I-E-S-------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

int librarianMenu(void){

	FILE *libPtr; /* librarian.dat file pointer */
	Librarian primary_lib = { FALSE, "", "", "", "", "", 0, "" };

	/* fopen opens file. Exit program if unable to create file */
	if ((libPtr = fopen("librarian.dat", "w")) == NULL) {
		printf("Librarian data could not be loaded\n");
	} /* end if */
	else {
		if (primary_lib.info == FALSE){
			system("cls");
			printHeader();

			/* get librarian data */
			fflush(stdin);
			puts("HELLO LIBRARIAN");
			puts("Enter your details.");
			printf_s("%-20s", "First name: ");
			fgets(primary_lib.libNameF, 30, stdin);
			printf_s("%-20s", "Last name: ");
			fgets(primary_lib.libNameL, 20, stdin);
			printf_s("%-20s", "Street address: ");
			fgets(primary_lib.libStreet, 150, stdin);
			printf_s("%-20s", "City: ");
			fgets(primary_lib.libCity, 20, stdin);
			printf_s("%-20s", "Email: ");
			fgets(primary_lib.libEmail, 75, stdin);
			printf_s("%-20s", "Phone: ");
			scanf_s("%lu", &primary_lib.libPhone); fflush(stdin);
			sprintf(primary_lib.libID, "LB%c%c%c%4luSK", primary_lib.libNameL[0], primary_lib.libCity[0],
				primary_lib.libNameF[0], primary_lib.libPhone / 5);
			printf_s("Your auto-generated librarian ID is %s\n"
				"Store it in a safe place\n"
				"You'll need this to access the Librarian menu in future"
				, primary_lib.libID);
			fflush(stdin); getchar();
			primary_lib.info = TRUE;

			/* write librarian info to file */
			fprintf(libPtr, "%-20s %s\n", "First name: ", primary_lib.libNameF);
			fprintf(libPtr, "%-20s %s\n", "Last name: ", primary_lib.libNameL);
			fprintf(libPtr, "%-20s %s\n", "Street address: ", primary_lib.libStreet);
			fprintf(libPtr, "%-20s %s\n", "City: ", primary_lib.libCity);
			fprintf(libPtr, "%-20s %s\n", "Email: ", primary_lib.libEmail);
			fprintf(libPtr, "%-20s %lu\n", "Phone: ", primary_lib.libPhone);
			fprintf(libPtr, "%-20s %s\n", "UserID", primary_lib.libID);
			fprintf(libPtr, "%-20s %i\n", "Availability: ", primary_lib.info);
		}
	} /* end else */

	if (primary_lib.info == TRUE){
		system("cls");
		printHeader();
		printf_s("Hello, %s\n", primary_lib.libNameF);
		printf_s("Enter your Librarian ID to continue\n");
		char checkID[11];
		fflush(stdin); fgets(checkID, 11, stdin);
		if ((strcmp(checkID, primary_lib.libID)) != 0){
			puts("You entered wrong ID. Access denied.\nPress enter to return to main menu");
			getchar();
		}
		else {
		LIBRARIAN_MENU:
			// prints main menu
			printHeader();
			printf_s("%s\n", "                                 LIBRARIAN MENU                                 ");
			printf_s("%s\n\n", "--------------------------------------------------------------------------------");
			printf_s("%s\n", "                Add member                           1                          ");
			printf_s("%s\n", "                Search member by name                2                          ");
			printf_s("%s\n", "                Remove member                        3                          ");
			printf_s("%s\n", "                Modify member details                4                          ");
			printf_s("%s\n", "                Display all members                  5                          ");
			printf_s("%s\n", "                Add book                             6                          ");
			printf_s("%s\n", "                Search book by title                 7                          ");
			printf_s("%s\n", "                Remove book                          8                          ");
			printf_s("%s\n", "                Modify book details                  9                          ");
			printf_s("%s\n", "                Display all books                   10                          ");
			printf_s("%s", "------------------------------------------------------------------------------");

			// initialisinng the first_member pointer 
			first_member = (struct Members*)malloc(sizeof(struct Members));
			first_member = NULL;

			// main menu selection
			char choice;
			scanf_s("%c", &choice);
			while (choice != 'q'){
				switch (choice){
				case'1':
					printHeader();
					printf_s("%s\n", "                          LIBRARIAN MENU - ADD MEMBERR                          ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					addMember(first_member);
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				case'2':
					printHeader();
					printf_s("%s\n", "                        LIBRARIAN MENU - SEARCH BY NAME                         ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					searchMember(first_member);
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				case'3':
					printHeader();
					printf_s("%s\n", "                        LIBRARIAN MENU - REMOVE MEMBER                          ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					int loc_member;
					printf_s("Enter the location of member you want to delete ");
					scanf_s("%d", &loc_member);
					if (loc_member <= total_members){
						deleteMember(loc_member);
						total_members--;
					}
					else
						printf("Invalid location entered. Total number of members is %d\n", total_members);
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				case'4':
					printHeader();
					printf_s("%s\n", "                    LIBRARIAN MENU - MODIFY MEMEBR DETAILS                      ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					modifyMember(first_member);
					goto LIBRARIAN_MENU;
					break;
				case'5':
					printHeader();
					printf_s("%s\n", "                     LIBRARIAN MENU - DISPLAY ALL MEMBERS                       ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					printMember();
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				case'6':
					printHeader();
					printf_s("%s\n", "                           LIBRARIAN MENU - ADD BOOK                            ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					addBook(first_book);
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				case'7':
					printHeader();
					printf_s("%s\n", "                        LIBRARIAN MENU - SEARCH BY NAME                         ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					searchBook(first_book);
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				case'8':
					printHeader();
					printf_s("%s\n", "                         LIBRARIAN MENU - REMOVE BOOK                           ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					int loc_book;
					printf_s("Enter the location of member you want to delete ");
					scanf_s("%d", &loc_book);
					if (loc_book <= total_books){
						deleteBook(loc_book);
						total_books--;
					}
					else
						printf("Invalid location entered. Total number of members is %d\n", total_books);
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				case'9':
					printHeader();
					printf_s("%s\n", "                     LIBRARIAN MENU - MODIFY BOOK DETAILS                       ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					modifyMember(first_member);
					goto LIBRARIAN_MENU;
					break;
				case'10':
					printHeader();
					printf_s("%s\n", "                      LIBRARIAN MENU - DISPLAY ALL BOOKS                        ");
					printf_s("%s\n\n", "--------------------------------------------------------------------------------");
					printMember();
					puts("Press enter to return to librarian menu");
					fflush(stdin);
					getchar();
					goto LIBRARIAN_MENU;
					break;
				} /*end switch*/
				scanf_s("%c", &choice);
			} /*end while*/
		} /*end else*/
		return 0; /*program terminated successfully*/
	} /*end if*/
} /*end main function*/

int memberMenu(void){
	return 0;
}

int guestMenu(void){
	return 0;
}

void printHeader(void){
	system("cls");
	printf_s("%s\n\n",	"--------------------------------------------------------------------------------");
	printf_s("%s\n\n",	"                    T H E   P E R S O N A L   L I B R A R Y                     ");
	printf_s("%s\n\n",	"                                      O F                                       ");
	printf_s("%s\n\n",	"                M U H A M M A D   S A I F U L L A H   K H A N                   ");
	printf_s("%s\n",	"--------------------------------------------------------------------------------");
}
