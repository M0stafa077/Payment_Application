/**
 * Utilities.c
 * Jan 24th 2024
 * @auther : Mostafa Asaad
*/
/* --------------- Section : Includes --------------- */
#include "utilities.h"

/*---------------  Section: Function Definitions --------------- */
void header_message()
{
	system("cls");
	printf("|---------------------------------------------|\n");
	printf("|------------ Payment Application ------------|\n");
	printf("|---------------------------------------------|\n");
}

void loading_message()
{
	printf("Loading");
	for (int dots = 0; dots < 10; dots++) {
		printf(".");
		fflush(stdout);
		Sleep(80);
	}

	for (int dots = 0; dots < 10; dots++) {
		printf("\b \b");
		fflush(stdout);
		Sleep(80);
	}
	for (int l_counter = 0; l_counter < 8; ++l_counter)
	{
		printf("\b \b");
	}
	printf("\n");
}

void clear_screen() 
{
	system("cls");
	header_message();
}

void display(uint8_t* mes)
{
	for (uint8_t i = 0; i < strlen(mes); ++i)
	{
		printf("%c", mes[i]);
		fflush(stdout);
		Sleep(20);
	}
}

void delete(uint8_t* mes)
{
	for (uint8_t i = 0; i < strlen(mes); ++i)
	{
		printf("\b \b");
		fflush(stdout);
		Sleep(20);
	}
}