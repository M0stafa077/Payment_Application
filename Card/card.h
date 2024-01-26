/**
 *	card.h
 *	Jan 24th 2024
 *	@auther : Mostafa Asaad
**/
#ifndef CARD_H
#define CARD_H	

/* --------------- Section : Includes --------------- */
#include "../Utilities/utilities.h"
/* --------------- Section: Macro Declarations --------------- */
#define CARD_OK					E_OK
#define	CARD_NOT_OK				E_NOT_OK

#define	CARD_WRONG_NAME			CARD_NOT_OK
#define	CARD_WRONG_EXP_DATE		CARD_NOT_OK	
#define	CARD_WRONG_PAN			CARD_NOT_OK	

#define	NAME_SIZE				25
#define	EXP_DATE_SIZE			9
#define PAN_SIZE				16
/* --------------- Section: Data Type Declarations --------------- */
typedef struct {
	uint8_t Card_holder_name[NAME_SIZE];
	uint8_t Card_expiry_date[EXP_DATE_SIZE];
	uint8_t Card_PAN[PAN_SIZE];
} Card_t;
/*---------------  Section: Function Declarations --------------- */
STD_ReturnType card_get_holder_name(Card_t *card);
STD_ReturnType card_get_expiry_date(Card_t *card);
STD_ReturnType card_get_PAN(Card_t *card);

#endif // CARD_H
