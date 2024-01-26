/**
 *	server.h
 *	Jan 25th 2024
 *	@auther : Mostafa Asaad
**/
#ifndef SERVER_H
#define SERVER_H

/* --------------- Section : Includes --------------- */
#include "../Terminal/terminal.h"
/* --------------- Section: Macro Declarations --------------- */
#define	NUMBER_OF_LINES			4
#define LINE_SIZE				68
#define ACCOUNT_EXISTS			1
#define ACCOUNT_NOT_EXIST		0

#define ACCOUNT_VALID			1
#define ACCOUNT_NOT_VALID		0

#define AMOUNT_AVAILABLE		1
#define AMOUNT_NOT_AVAILABLE	0
/* --------------- Section: Data Type Declarations --------------- */
typedef struct
{
	Card_t accountCard;
	uint32_t balance;
	bool validAccount;
	Transaction_t transaction;
} Account_t;
/*---------------  Section: Functions Declarations --------------- */
bool account_exist(Account_t* account);
bool account_valid(Account_t* account);
bool is_amount_available(Account_t* account);
STD_ReturnType update_account_balance(Account_t* account);

#endif // !SERVER_H