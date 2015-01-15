struct Members{
	/*Biographic details of the member*/
	char memberID[25];										// Member ID
	char memberNameF[35];										// First name
	char memberNameL[15];										// Last name
	char memberAddress[100];									// Street address
	char memberEmail[30];										// Email
	int memberPhone;										// Phone number
	int memberDateJ;										// Joining date
	int memberDateE;										// Membership expiry date

	/*One member can issue only 3 books at any given time*/
	char *bookIssued_1 = NULL;									// Issued book #1
	char *bookIssued_2 = NULL;									// Issued book #2
	char *bookIssued_3 = NULL;									// Issued book #3

	/*Emergency contact number in case member cannot be contacted*/
	char memberEmerName[30];									// Emergency contact name
	char memberEmerRelation[10];								// Relation with emergency contact
	int memberEmerPhone;										// Emergency contact number	

	struct Members *next;										// For connecting members in a list
};

void addMember(struct Members *node);
void deleteMember(int ask);
void modifyMember(struct Members *edit);
void searchMember(struct Members *node);
void printMember(void);
void print(struct Members *member);


int total_members = 0;											// Total number of members in the list
struct Members *first_member;									// Pointer to the first node in the list


void addMember(struct Members *node){
ADD_MEMBER:
	// Create new member space in memory
	struct Members *new_member;
	new_member = (struct Members*) malloc(sizeof(struct Members));

	// Enter new member data
	printf("%30s", "Member ID: ");					fflush(stdin);	gets_s(new_member->memberID);
	printf("%30s", "First name: ");					fflush(stdin);	gets_s(new_member->memberNameF);
	printf("%30s", "Last name: ");					fflush(stdin);	gets_s(new_member->memberNameL);
	printf("%30s", "Address: ");					fflush(stdin);	gets_s(new_member->memberAddress);
	printf("%30s", "Email address: ");				fflush(stdin);	gets_s(new_member->memberEmail);
	printf("%30s", "Contact number: ");				scanf_s("%d", &new_member->memberPhone);
	printf("%30s", "Date of joining: ");			scanf_s("%d", &new_member->memberDateJ);
	printf("%30s", "Expiry date: ");				scanf_s("%d", &new_member->memberDateE);
	printf("%30s", "Emergency contact name: ");		fflush(stdin);	gets_s(new_member->memberEmerName);
	printf("%30s", "Emergency contact relation: ");	fflush(stdin);	gets_s(new_member->memberEmerRelation);
	printf("%30s", "Emergency contact number: ");	scanf_s("%d", &new_member->memberEmerPhone);
	puts("");
	puts("--------------------------------------------------------------------------------");

	// Add new member to start of the list
	new_member->next = first_member;
	first_member = new_member;
	total_members++;

	// Add another member
	puts("Data of the new member has been successfully added.");
	printf_s("Do you want to add another member? (Y/N)  ");
	char add_new_member;
	fflush(stdin);
	scanf_s("%c", &add_new_member);
	puts("");
	switch (add_new_member){
	case 'y':
	case 'Y':
		goto ADD_MEMBER;
		break;
	default:
		break;
	}
}

void searchMember(struct Members *node){
	char names[30];
	int found = 0;
	node = first_member;
	if (node == NULL){
		puts("No data has been added yet.");
	}
	else{
		puts("Enter a name to search in the list.");
		fflush(stdin);
		gets_s(names);

		// searching in the list
		printf_s("Searching");
		for (int i = 1; i <= 3; i++){
			Sleep(800);
			printf_s(" .");
		}
		puts("");

		while (node != NULL){
			char str[50];
			sprintf_s(str, "%s %s", node->memberNameF, node->memberNameL);
			if (strcmp(node->memberNameF, names) == 0 || strcmp(node->memberNameL, names) == 0 || strcmp(str, names) == 0){
				found = 1;
				break;
			}
			else{
				puts("Not found");
			}
			node = node->next;
		}

		// print member data if found in list
		if (found == 1){
			print(node);
		}
	}
}

void deleteMember(int ask){
	struct Members *prev_ptr, *cur_ptr;
	prev_ptr = (struct Members*)malloc(sizeof(struct Members));
	cur_ptr = (struct Members*)malloc(sizeof(struct Members));
	int i;

	cur_ptr = first_member;

	// If the location is starting of the list  
	if (ask == 1)
	{
		first_member = cur_ptr->next;
		free(cur_ptr);
		cur_ptr = NULL;
	}
	else
	{
		for (i = 1; i<ask; i++)
		{
			prev_ptr = cur_ptr;					// Looping to reach the one point less than desired deletion point
			cur_ptr = cur_ptr->next;
		}

		prev_ptr->next = cur_ptr->next;			// Data Access of Next Node is Being Stored in Node Previous to One Being Deleted
		free(cur_ptr);
		cur_ptr = NULL;
	}
}

void modifyMember(struct Members *edit){
	int iterate = 1;
	char mod;
	edit = first_member;
	int position;
	if (edit == NULL){
		puts("No data has been added yet.");
	}
	else
	{
		printMember();
		puts("Complete list of members is displayed above. Select one to modify.");
		printf_s("%s", "Serial # ");
		scanf_s("%d", &position);

		while (iterate != position){
			iterate++;
			edit = edit->next;      //getting to place where data is to be modified
		}

		if (iterate == position){
			puts("What do you want to modify?");
			puts("\t1 - Fist name");
			puts("\t2 - Last name");
			puts("\t3 - Address");
			puts("\t4 - Email");
			puts("\t5 - Phone");
			puts("\t6 - Emergency contact name");
			puts("\t7 - Emergency contact relation");
			puts("\t8 - Emergency contact number");
			puts("\t0 - Stop Editing");
			fflush(stdin);
			scanf_s("%c", &mod);
			while (mod != '0'){
				switch (mod){
				case'1':
					printf("%37s", "First name                  |   ");
					fflush(stdin);
					gets_s(edit->memberNameF);
					break;
				case'2':
					printf("%37s", "Last name                   |   ");
					fflush(stdin);
					gets_s(edit->memberNameL);
					break;
				case'3':
					printf("%37s", "Address                     |   ");
					fflush(stdin);
					gets_s(edit->memberAddress);
					break;
				case'4':
					printf("%37s", "Email address               |   ");
					fflush(stdin);
					gets_s(edit->memberEmail);
					break;
				case'5':
					printf("%37s", "Contact number              |   ");
					fflush(stdin);
					scanf_s("%d", &edit->memberPhone);
					break;
				case'6':
					printf("%37s", "Emergency contact name      |   ");
					fflush(stdin);
					gets_s(edit->memberEmerName);
					break;
				case '7':
					printf("%37s", "Emergency contact relation  |   ");
					fflush(stdin);
					gets_s(edit->memberEmerRelation);
					break;
				case '8':
					printf("%37s", "Emergency contact number    |   ");
					fflush(stdin);
					scanf_s("%d", &edit->memberEmerPhone);
					break;
				default:
					break;
				}
				puts("\nSuccessfully modified.");
				puts("What else do you want to modify?");
				fflush(stdin);
				scanf_s("%c", &mod);
			}
		}
		puts("Successfully modified.");
	}
}

void printMember(void){
	struct Members *temp;
	temp = first_member;
	if (temp == NULL){
		puts("No data has been added yet.");
	}
	else{
		int position = 1;
		puts("--------------------------------------------------------------------------------");
		while (temp != NULL){
			printf("%70s%d\n", "Serial # ", position);
			print(temp);
			temp = temp->next;
			position++;
		}
	}
}

void print(struct Members *member){
	printf("%37s", "Member ID                   |   ");	puts(member->memberID);
	printf("%37s", "First name                  |   ");	puts(member->memberNameF);
	printf("%37s", "Last name                   |   ");	puts(member->memberNameL);
	printf("%37s", "Address                     |   ");	puts(member->memberAddress);
	printf("%37s", "Email address               |   ");	puts(member->memberEmail);
	printf("%37s", "Contact number              |   ");	printf_s("%d\n", member->memberPhone);
	printf("%37s", "Date of joining             |   ");	printf_s("%d\n", member->memberDateJ);
	printf("%37s", "Membership expires on       |   ");	printf_s("%d\n", member->memberDateE);
	printf("%37s", "Emergency contact name      |   ");	puts(member->memberEmerName);
	printf("%37s", "Emergency contact relation  |   ");	puts(member->memberEmerRelation);
	printf("%37s", "Emergency contact number    |   ");	printf_s("%d\n", member->memberEmerPhone);
	puts("");
	puts("--------------------------------------------------------------------------------");
}
