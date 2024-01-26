/**
 *	teminal.c
 *	Jan 24th 2024
 *	@auther : Mostafa Asaad
**/
/* --------------- Section : Includes --------------- */
#include "terminal.h"
/*---------------  Section: Helper Function Declarations --------------- */
static uint8_t check_date(uint8_t* card_date);
/*---------------  Section: Global Variables --------------- */
static volatile uint16_t max_amount = 20000;
/*---------------  Section: Function Definitions --------------- */
STD_ReturnType is_card_expired(Card_t* card)
{
	STD_ReturnType ret = E_OK;
	if (NULL == card)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = check_date(card->Card_expiry_date);
		if (CARD_EXPIRED == ret)
		{
			clear_screen();
			display("Sorry, Your card seems to be expired...");
			Sleep(1500);
			delete("Sorry, Your card seems to be expired...");
			display("Please Contact your bank..");
			Sleep(2000);
			delete("Please Contact your bank..");
		}
		else
		{ /* Nothing */ }
	}
	return ret;
}

STD_ReturnType get_tranaction_amount(Transaction_t* transaction)
{
	STD_ReturnType ret = E_OK;
	if (NULL == transaction)
	{
		ret = E_NOT_OK;
	}
	else
	{
		clear_screen();
		display("Enter the amount of money..");
		printf("\n");
		uint16_t tempAmount;
		scanf_s("%hd", &tempAmount);
		loading_message();
		clear_screen();
		if (is_below_max_amount(&tempAmount))
		{
			transaction->transactionAmount = tempAmount;
			ret = TRANSACTION_BELOW_MAX_AMOUNT;
		}
		else
		{
			clear_screen();
			display("Sorry, Amount Exceeding Limit..");
			Sleep(2000);
			delete("Sorry, Amount Exceeding Limit..");
			ret = TRANSACTION_AMOUNT_EXCEEDED;
		}
	}
	return ret;
}

bool is_below_max_amount(const uint16_t* amount)
{
	return (*amount <= max_amount);
}
STD_ReturnType set_max_amount(uint8_t new_max_amount)
{
	max_amount = new_max_amount;
}
/*---------------  Section: Helper Function Declarations --------------- */
static uint8_t check_date(uint8_t* card_date)
{
	time_t t;
	struct tm* now;
	char current_date[9]; 
	time(&t);
	now = localtime(&t);
	strftime(current_date, sizeof(current_date), "%d/%m/%y", now);

	uint8_t d[3] = { card_date[0] , card_date[1] , '\0' };	
	uint8_t m[3] = { card_date[3] , card_date[4] , '\0' };
	uint8_t y[3] = { card_date[6] , card_date[7] , '\0' };
	
	uint8_t card_day   = atoi(d);
	uint8_t card_month = atoi(m);
	uint8_t card_year  = atoi(y);


	uint8_t d2[3] = { current_date[0] , current_date[1] , '\0' };
	uint8_t m2[3] = { current_date[3] , current_date[4] , '\0' };
	uint8_t y2[3] = { current_date[6] , current_date[7] , '\0' };

	uint8_t current_day   = atoi(d2);
	uint8_t current_month = atoi(m2);
	uint8_t current_year  = atoi(y2);

	if (card_year < current_year)
	{
		return CARD_EXPIRED;
	}
	else if (card_year == current_year)
	{
		if (card_month < current_month)
		{
			return CARD_EXPIRED;
		}
		else if (card_month == current_month)
		{
			if (card_day < current_day)
			{
				return CARD_EXPIRED;
			}
			else
			{ /* Nothing */ }
		}
		else
		{ /* Nothing */ }
	}
	else
	{ /* Nothing */ }

	return CARD_NOT_EXPIRED;
}