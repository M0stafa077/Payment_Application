/**
 *	teminal.h
 *	Jan 24th 2024
 *	@auther : Mostafa Asaad
**/
#ifndef TERMINAL_H
#define	TERMINAL_H

/* --------------- Section : Includes --------------- */
#include "../Card/card.h"
/* --------------- Section: Macro Declarations --------------- */
#define CARD_EXPIRED					1	
#define CARD_NOT_EXPIRED				0	
#define TRANSACTION_AMOUNT_EXCEEDED		1
#define TRANSACTION_BELOW_MAX_AMOUNT	0
/* --------------- Section: Data Type Declarations --------------- */
typedef struct
{
	uint16_t transactionAmount;
} Transaction_t;
/*---------------  Section: Function Declarations --------------- */
STD_ReturnType is_card_expired(Card_t* card);
STD_ReturnType get_tranaction_amount(Transaction_t* transaction);
bool is_below_max_amount(const uint16_t* amount);
STD_ReturnType set_max_amount(uint8_t new_max_amount);

#endif // !TERMINAL_H