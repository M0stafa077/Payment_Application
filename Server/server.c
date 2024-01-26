/**
 *	server.c
 *	Jan 25th 2024
 *	@auther : Mostafa Asaad
**/
/* --------------- Section : Includes --------------- */
#include "server.h"
/* --------------- Section: Helper Functions Declarations --------------- */
static bool check_name(const Account_t *account, const uint8_t *buffer);
static bool check_exp_date(const Account_t* account, const uint8_t* buffer);
static bool check_PAN(const Account_t* account, const uint8_t* buffer);
static bool compare_name(const uint8_t* str1, const uint8_t* str2);
static STD_ReturnType store_balance(Account_t *account, const uint8_t* buffer);
static STD_ReturnType store_validation(Account_t *account, const uint8_t* buffer);
/* --------------- Section: Opening the database --------------- */
FILE* database = NULL;
/*---------------  Section: Functions Definition --------------- */
bool account_exist(Account_t* account)
{
	database = fopen("Server/Database.txt", "r");
	uint8_t buffer[66] = { 0 };
	uint8_t existFlag = false;

	Account_t readAccount = {
		.accountCard.Card_expiry_date = { 0 },
		.accountCard.Card_holder_name = { 0 },
		.accountCard.Card_PAN = { 0 },
		.balance = 0,
		.transaction.transactionAmount = 0,
		.validAccount = 0
	};
	if (NULL != database)
	{
		for (uint8_t l_counter = 0; l_counter < NUMBER_OF_LINES; ++l_counter)
		{
			fgets(buffer, LINE_SIZE, database);
			if (check_name(account, buffer))
			{
				printf("NAME IS RIGHT\n");
				Sleep(2000);
				if (check_exp_date(account, buffer))
				{
					printf("EXP Date IS RIGHT\n");
					Sleep(2000);
					if (check_PAN(account, buffer))
					{
						printf("PAN IS RIGHT\n");
						Sleep(2000);
						store_balance(account, buffer);
						store_validation(account, buffer);
						if (account->validAccount)
						{
							printf("Account is Valid\n");
							Sleep(2000);
						}
						else
						{
							printf("Account is NOT Valid!!!\n");
							Sleep(2000);
						}
						existFlag = true;
						break;
					}
					else
					{
						existFlag = false;
						continue;
					}
				}
				else
				{
					existFlag = false;
					continue;
				}
			}
			else
			{
				existFlag = false;
				continue;
			}
		}
		fclose(database);
	}
	else
	{ /* Nothing */ }
	if (existFlag)
	{
		return ACCOUNT_EXISTS;
	}
	else
	{
		clear_screen();
		display("Account does not exist..");
		Sleep(2000);
		delete("Account does not exist..");
		return ACCOUNT_NOT_EXIST;
	}
}

bool account_valid(Account_t* account)
{
	if (account->validAccount)
	{
		return ACCOUNT_VALID;
	}
	else
	{
		return ACCOUNT_NOT_VALID;
	}
}

bool is_amount_available(Account_t* account)
{
	if (account->transaction.transactionAmount <= account->balance)
	{
		return AMOUNT_AVAILABLE;
	}
	else
	{
		clear_screen();
		display("Sorry, your balance doesn't cover the specified transaction amount..");
		Sleep(2000);
		delete("Sorry, your balance doesn't cover the specified transaction amount..");
		return AMOUNT_NOT_AVAILABLE;
	}
}

STD_ReturnType update_account_balance(Account_t* account)
{
	STD_ReturnType ret = E_OK;
	if (NULL == account)
	{
		ret = E_NOT_OK;
	}
	else
	{
		account->balance -= (uint32_t)account->transaction.transactionAmount;
	}
	
	return ret;
}

/* --------------- Section: Helper Functions Definition --------------- */
static bool check_name(const Account_t* account, const uint8_t* buffer)
{
	bool ret = true;
	if (NULL == account || NULL == buffer)
	{
		ret = false;
	}
	else
	{
		uint8_t name[NAME_SIZE] = { 0 };
		uint8_t i = 0;
		while (true)
		{
			if (',' == buffer[i])
			{
				break;
			}
			else
			{
				name[i] = buffer[i];
			}
			++i;
		}

		ret = compare_name(account->accountCard.Card_holder_name, name);
	}
	return ret;
}

static bool check_exp_date(const Account_t* account, const uint8_t* buffer)
{
	bool ret = true;
	if (NULL == account || NULL == buffer)
	{
		ret = false;
	}
	else
	{
		uint8_t expDate[EXP_DATE_SIZE+1] = { 0 };
		uint8_t cnt = 0;
		uint8_t start = strlen(account->accountCard.Card_holder_name) + 2;
		uint8_t end = strlen(account->accountCard.Card_holder_name) + 2 + 8;
		for (uint8_t i = start; i < end; ++i)
		{
			expDate[cnt++] = buffer[i];
		}
		for (uint8_t i = 0; i < EXP_DATE_SIZE; ++i)
		{
			if (expDate[i] != account->accountCard.Card_expiry_date[i])
			{
				ret = false;
				break;
			}
		}
	}
	return ret;
}

static bool check_PAN(const Account_t* account, const uint8_t* buffer)
{
	bool ret = true;
	if (NULL == account || NULL == buffer)
	{
		ret = false;
	}
	else
	{
		uint8_t PAN[PAN_SIZE + 1] = { 0 };
		uint8_t cnt = 0;
		uint8_t start = strlen(account->accountCard.Card_holder_name) + EXP_DATE_SIZE + 3;
		uint8_t end = start + PAN_SIZE;
		for (uint8_t i = start; i < end; ++i)
		{
			PAN[cnt++] = buffer[i];
		}
		for (uint8_t i = 0; i < EXP_DATE_SIZE; ++i)
		{
			if (PAN[i] != account->accountCard.Card_PAN[i])
			{
				ret = false;
				break;
			}
		}
		
	}
	return ret;
}

static bool compare_name(const uint8_t* str1, const uint8_t* str2)
{
	for (uint8_t i = 0; i < strlen(str1); ++i)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}
	return true;
}

static STD_ReturnType store_balance(Account_t *account, const uint8_t* buffer)
{
	STD_ReturnType ret = E_OK;
	if (NULL == account || NULL == buffer)
	{
		ret = E_NOT_OK;
	}
	else
	{
		uint8_t balance[6] = { 0 }, cnt = 0;
		uint8_t start = strlen(account->accountCard.Card_holder_name) 
						+ EXP_DATE_SIZE + PAN_SIZE + 5;
		uint8_t end = start + 5;
		for (uint8_t i = start; i < end; ++i)
		{
			balance[cnt++] = buffer[i];
		}
		uint16_t savedBalance = (uint16_t)atoi(balance);
		account->balance = savedBalance;
	}
	return ret;
}

static STD_ReturnType store_validation(Account_t *account, const uint8_t* buffer)
{
	STD_ReturnType ret = E_OK;
	if (NULL == account || NULL == buffer)
	{
		ret = E_NOT_OK;
	}
	else
	{
		bool validationState = 0;
		uint8_t pos = strlen(account->accountCard.Card_holder_name)
			+ EXP_DATE_SIZE + PAN_SIZE + 10;
		validationState = (bool) buffer[pos];
		account->validAccount = validationState;
	}
}