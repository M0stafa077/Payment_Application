/**
 * card.c
 * Jan 24th 2024
 * @auther : Mostafa Asaad
*/
/* --------------- Section : Includes --------------- */
#include "card.h"
/* --------------- Section : Helper Functions Declaration --------------- */
static STD_ReturnType check_card_holder_name(const uint8_t* name);
static STD_ReturnType check_card_expiry_date(const uint8_t* date);
static STD_ReturnType check_date_syntax(uint8_t* date);
static STD_ReturnType check_date_logic(uint8_t* date);
static STD_ReturnType check_card_PAN(uint8_t* pan);
static STD_ReturnType store_name(Card_t* card, const uint8_t* name);
static STD_ReturnType card_store_exp_date(Card_t* card, uint8_t* date);
static STD_ReturnType card_store_PAN(Card_t* card, uint8_t* pan);
static void display_get_name_message();
static void process_name(uint8_t* name);
static void invalid_name();
static void invalid_exp_date();
static uint8_t leap_year(uint8_t year);
/*---------------  Section: Function Definitions --------------- */
STD_ReturnType card_get_holder_name(Card_t* card)
{
	STD_ReturnType ret = E_OK;
	if (NULL == card)
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint8_t* tempName = (uint8_t*) malloc(20 * sizeof(uint8_t));
		display("Enter the card holder name..");
		printf("\n");
		gets(tempName);
		
		loading_message();

		ret = check_card_holder_name(tempName);

		if (CARD_WRONG_NAME != ret)
		{
			clear_screen();
			process_name(tempName);
			ret = store_name(card, tempName);
		}
		else
		{
			invalid_name();
			ret = CARD_WRONG_NAME;
		}
		free(tempName);
	}
	return ret;
}

STD_ReturnType card_get_expiry_date(Card_t* card)
{
	STD_ReturnType ret = E_OK;
	if (NULL == card)
	{
		ret = E_NOT_OK;
	}
	else
	{		
		display("Enter the expiry date in the form dd/mm/yy..");
		printf("\n");
		uint8_t* tempExpDate = (uint8_t*) malloc(7 * sizeof(uint8_t));
		fflush(stdin);
		gets(tempExpDate);
		
		loading_message();

		ret = check_card_expiry_date(tempExpDate);

		if (CARD_WRONG_EXP_DATE == ret)
		{
			invalid_exp_date();
		}
		else
		{
			ret = card_store_exp_date(card, tempExpDate);
			clear_screen();
		}
	}

	return ret;
}

STD_ReturnType card_get_PAN(Card_t* card)
{
	STD_ReturnType ret = E_OK;
	if (NULL == card)
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint8_t* tempPAN = (uint8_t*)malloc(17 * sizeof(uint8_t));
		display("Enter your 16 digit Primary Account Number (PAN)...");
		printf("\n");
		gets(tempPAN);
		loading_message();
		clear_screen();
		ret = check_card_PAN(tempPAN);
		if (CARD_WRONG_PAN == ret)
		{
			display("Invalid PAN..");
			Sleep(2000);
			delete("Invalid PAN..");
			display("Please try again..");
			Sleep(2000);
			delete("Please try again..");
		}
		else
		{
			ret = card_store_PAN(card, tempPAN);
		}
	}
	return ret;
}

/*---------------  Section: Helper Functions Definitions --------------- */
static void display_get_name_message()
{
	uint8_t mes[] = "Enter card holder name..";
	display(mes);
	Sleep(2000);
	delete(mes);
	
}

static STD_ReturnType check_card_holder_name(const uint8_t* name)
{
	STD_ReturnType ret = E_OK;
	if (NULL == name)
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint8_t size = strlen(name);
		if (size < 5)
		{
			ret = CARD_WRONG_NAME;
		}
		else
		{
			for (int l_counter = 0; l_counter < size; ++l_counter)
			{
				if (('a' < name[l_counter] && 'z' > name[l_counter])
					|| ('A' < name[l_counter] && 'Z' > name[l_counter])
					|| (' ' == name[l_counter]))
				{
					ret = CARD_OK;
				}
				else
				{
					ret = CARD_WRONG_NAME;
				}
			}
		}
	}

	return ret;
}

static STD_ReturnType store_name(Card_t* card, const uint8_t* name)
{
	STD_ReturnType ret = E_OK;
	if (NULL == card || NULL == name)
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint8_t l_counter = 0;
		for (; l_counter < (uint8_t) strlen(name); ++l_counter)
		{
			card->Card_holder_name[l_counter] = name[l_counter];
		}
		card->Card_holder_name[l_counter] = '\0';
	}
	return ret;
}

/* Function Capitalizes the first character of each name */
static void process_name(uint8_t* name)
{
	// First : make all the characters lower case.
	for (int i = 0; i < strlen(name); ++i)
	{
		if (' ' == name[i])
		{
			continue;
		}
		else
		{ /* Nothing */ }
		
		if (('A' <= name[i]) && ('Z' >= name[i]))
		{
			name[i] += 32;
		}
		else
		{ /* Nothing */ }
	}
	
	// Second : Capitalize the first character.
	if (('a' <= name[0]) && ('z' >= name[0]) && (' ' != name[0]))
	{
		name[0] -= 32;
	}

	// Third : Capitalize the first character of laset name.
	for (int i = 0; i < strlen(name); ++i)
	{
		if (' ' == name[i])
		{
			if (('a' <= name[i + 1]) && ('z' >= name[i + 1]) && (' ' != name[i + 1]))
			{
				name[i+1] -= 32;
			}
		}
	}
	

}

static void invalid_name()
{
	clear_screen();
	uint8_t mes[] = "Sorry, Invalid Name";

	display(mes);
	Sleep(2000);
	delete(mes);

	display("Please try again..");
	Sleep(2000);
	delete("Please try again..");
}

static STD_ReturnType check_card_expiry_date(const uint8_t* date)
{
	STD_ReturnType ret = E_OK;
	ret = check_date_syntax(date);
	if (E_NOT_OK == ret)
	{
		return ret;
	}
	else
	{ /* Nothing */ }

	ret = check_date_logic(date);
	if (E_NOT_OK == ret)
	{
		return ret;
	}
	else
	{ /* Nothing */ }

	return ret;
}

static void invalid_exp_date()
{
	clear_screen();

	uint8_t mes[] = "Invalid Expiration date..";
	uint8_t try_again_mes[] = "Please try again..";
	
	display(mes);
	Sleep(2000);
	delete(mes);
	
	display(try_again_mes);
	Sleep(2000);
	delete(try_again_mes);
}

static uint8_t leap_year(uint8_t year)
{
	year += 2000;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		return 1; // Leap year
	}
	else {
		return 0; // Not a leap year
	}
}

static STD_ReturnType check_date_syntax(uint8_t* date)
{
	STD_ReturnType ret = E_OK;
	for (uint8_t l_counter = 0; l_counter < strlen(date); ++l_counter)
	{
		if (2 == l_counter || 5 == l_counter)
		{
			if ('/' == date[l_counter])
			{
				ret = E_OK;
			}
			else
			{
				ret = CARD_WRONG_EXP_DATE;
				break;
			}
		}
		else
		{
			if (('0' <= date[l_counter]) && ('9' >= date[l_counter]))
			{
				ret = E_OK;
			}
			else
			{
				ret = CARD_WRONG_EXP_DATE;
				break;
			}
		}
	}
}

static STD_ReturnType check_date_logic(uint8_t* date)
{
	STD_ReturnType ret = E_OK;

	uint8_t d[3];
	d[0] = date[0];
	d[1] = date[1];
	d[2] = '\0';
	uint8_t day = atoi(d);

	uint8_t m[3];
	m[0] = date[3];
	m[1] = date[4];
	m[2] = '\0';
	uint8_t month = atoi(m);

	uint8_t y[3];
	y[0] = date[6];
	y[1] = date[7];
	y[2] = '\0';
	uint8_t year = atoi(y);

	if (day > (uint8_t)32)
	{
		ret = CARD_WRONG_EXP_DATE;
		return ret;
	}

	if (month > (uint8_t)12)
	{
		ret = CARD_WRONG_EXP_DATE;
		return ret;
	}

	if (year > (uint8_t)30)
	{
		ret = CARD_WRONG_EXP_DATE;
		return ret;
	}

	if (!(leap_year(year)) && (2 == month) && (day > 28))
	{
		ret = CARD_WRONG_EXP_DATE;
		return ret;
	}
	else if ((leap_year(year)) && (2 == month) && (day > 29))
	{
		ret = CARD_WRONG_EXP_DATE;
		return ret;
	}
	
	return ret;
}

static STD_ReturnType card_store_exp_date(Card_t* card, uint8_t *date)
{
	STD_ReturnType ret = E_OK;
	if (NULL == card)
	{
		ret = E_NOT_OK;
	}
	else
	{
		for (uint8_t l_counter = 0; l_counter < 9; ++l_counter)
		{
			card->Card_expiry_date[l_counter] = date[l_counter];
		}
	}
}

static STD_ReturnType check_card_PAN(uint8_t* pan)
{
	STD_ReturnType ret = E_OK;
	
	if (16 < strlen(pan))
	{
		ret = CARD_WRONG_PAN;
		return ret;
	}
	else
	{
		for (uint8_t l_counter = 0; l_counter < strlen(pan); ++l_counter)
		{
			if ('0' > pan[l_counter] || '9' < pan[l_counter])
			{
				return CARD_WRONG_PAN;
			}
			else
			{ /* Nothing */ }
		}
	}
	return ret;
}

static STD_ReturnType card_store_PAN(Card_t* card, uint8_t* pan)
{
	STD_ReturnType ret = E_OK;
	if (NULL == card || NULL == pan)
	{
		ret = E_NOT_OK;
	}
	else
	{
		for (uint8_t l_counter = 0; l_counter < 16; ++l_counter)
		{
			card->Card_PAN[l_counter] = pan[l_counter];
		}
	}
	return ret;
}