struct books{
	/*Details of the book*/
	char *bookID;										// Book ID
	long bookISBN;										// ISBN
	char *bookTitle;									// Title
	char *bookAuthor;									// Author
	char *bookGenre;									// Genre
	char *bookCategory;									// Category
	char *bookPublisher;								// Publisher
	short bookYear;										// Publishing year
	short bookEdition;									// Eidition

	/*One book can issue only 1 books at any given time*/
	char *bookIssuedTo = NULL;							// Points to Member who has issued the book

	struct books *next;									// For connecting books in a list
};

void addBook(struct books *node);
void deleteBook(int ask);
void modifyBook(struct books *edit);
void searchBook(struct books *node);
void printBook(void);
void print(struct books *book);


int total_books = 0;									// Total number of books in the list
struct books *first_book;								// Pointer to the first node in the list


void addBook(struct books *node){
ADD_BOOK:
	// Create new book space in memory
	struct books *new_book;
	new_book = (struct books*) malloc(sizeof(struct books));

	// Enter new book data
	printf("%30s", "Book ID: ");					fflush(stdin);	gets(new_book->bookID);
	printf("%30s", "Title: ");						fflush(stdin);	gets(new_book->bookTitle);
	printf("%30s", "ISBN: ");						scanf_s("%d", &new_book->bookISBN);
	printf("%30s", "Author: ");						fflush(stdin);	gets(new_book->bookAuthor);
	printf("%30s", "Genre: ");						fflush(stdin);	gets(new_book->bookGenre);
	printf("%30s", "Category: ");					fflush(stdin);	gets(new_book->bookCategory);
	printf("%30s", "Publisher: ");					fflush(stdin);	gets(new_book->bookPublisher);
	printf("%30s", "Publishing Year: ");			scanf_s("%d", &new_book->bookYear);
	printf("%30s", "Edition: ");					scanf_s("%d", &new_book->bookEdition);
	puts("");
	puts("--------------------------------------------------------------------------------");

	// Add new book to start of the list
	new_book->next = first_book;
	first_book = new_book;
	total_books++;

	// Add another book
	puts("Data of the new book has been successfully added.");
	printf_s("Do you want to add another book? (Y/N)  ");
	char add_new_book;
	fflush(stdin);
	scanf_s("%c", &add_new_book);
	puts("");
	switch (add_new_book){
	case 'y':
	case 'Y':
		goto ADD_BOOK;
		break;
	default:
		break;
	}
}

void searchBook(struct books *node){
	char names[30];
	int found = 0;
	node = first_book;
	if (node == NULL){
		puts("The library has no books!");
	}
	else{
		puts("Enter book title to search in the list.");
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
			sprintf_s(str, "%s %s", node->bookTitle, node->bookAuthor);
			if (strcmp(node->bookTitle, names) == 0 || strcmp(node->bookAuthor, names) == 0 || strcmp(str, names) == 0){
				found = 1;
				break;
			}
			else{
				puts("Sorry, we do not have this book.");
			}
			node = node->next;
		}

		// print book data if found in list
		if (found == 1){
			print(node);
		}
	}
}

void deleteBook(int ask){
	struct books *prev_ptr, *cur_ptr;
	prev_ptr = (struct books*)malloc(sizeof(struct books));
	cur_ptr = (struct books*)malloc(sizeof(struct books));
	int i;

	cur_ptr = first_book;

	// If the location is starting of the list  
	if (ask == 1)
	{
		first_book = cur_ptr->next;
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

void modifyBook(struct books *edit){
	int iterate = 1;
	char mod;
	edit = first_book;
	int position;
	if (edit == NULL){
		puts("The library has no books!");
	}
	else
	{
		printBook();
		puts("Complete list of books is displayed above. Select one to modify.");
		printf_s("%s", "Serial # ");
		scanf_s("%d", &position);

		while (iterate != position){
			iterate++;
			edit = edit->next;      //getting to place where data is to be modified
		}

		if (iterate == position){
			puts("What do you want to modify?");
			puts("\t1 - Title");
			puts("\t2 - ISBN");
			puts("\t3 - Author");
			puts("\t4 - Publisher");
			puts("\t5 - Genre");
			puts("\t6 - Category");
			puts("\t7 - Publishing year");
			puts("\t8 - Edition number");
			puts("\t0 - Stop Editing");
			fflush(stdin);
			scanf_s("%c", &mod);
			while (mod != '0'){
				switch (mod){
				case'1':
					printf("%37s", "Title                       |   ");
					fflush(stdin);
					gets(edit->bookTitle);
					break;
				case'2':
					printf("%37s", "ISBN                        |   ");
					fflush(stdin);
					scanf_s("%d", &edit->bookISBN);
					break;
				case'3':
					printf("%37s", "Author                      |   ");
					fflush(stdin);
					gets(edit->bookAuthor);
					break;
				case'4':
					printf("%37s", "Publisher                   |   ");
					fflush(stdin);
					gets(edit->bookPublisher);
					break;
				case'5':
					printf("%37s", "Genre                       |   ");
					fflush(stdin);
					gets(edit->bookGenre);
					break;
				case'6':
					printf("%37s", "Categoy                     |   ");
					fflush(stdin);
					gets(edit->bookCategory);
					break;
				case '7':
					printf("%37s", "Publishing Year             |   ");
					fflush(stdin);
					scanf_s("%d", &edit->bookYear);
					break;
				case '8':
					printf("%37s", "Edition                     |   ");
					fflush(stdin);
					scanf_s("%d", &edit->bookEdition);
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

void printBook(void){
	struct books *temp;
	temp = first_book;
	if (temp == NULL){
		puts("The library has no books!");
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

void print(struct books *book){
	printf("%37s", "Book ID                     |   ");	puts(book->bookID);
	printf("%37s", "Title                       |   ");	puts(book->bookTitle);
	printf("%37s", "ISBN                        |   ");	printf_s("%ld\n", book->bookISBN);
	printf("%37s", "Author                      |   ");	puts(book->bookAuthor);
	printf("%37s", "Publisher                   |   ");	puts(book->bookPublisher);
	printf("%37s", "Genre                       |   ");	puts(book->bookGenre);
	printf("%37s", "Category                    |   ");	puts(book->bookCategory);
	printf("%37s", "Publishing Year             |   ");	printf_s("%d\n", book->bookYear);
	printf("%37s", "Edition                     |   ");	printf_s("%d\n", book->bookEdition);
	puts("--------------------------------------------------------------------------------");
}
