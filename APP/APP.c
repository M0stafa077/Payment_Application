/**
 *	app.c
 *	Jan 24th 2024
 *	@auther : Mostafa Asaad
**/
/* --------------- Section : Includes --------------- */
#include "APP.h"
/*---------------  Section: Main Function --------------- */
int main()
{
	while (true)
	{	
		fflush(stdin);
		STD_ReturnType ret;

		Account_t tempAccount =
		{
			.accountCard.Card_holder_name = { 0 },
			.accountCard.Card_expiry_date = { 0 },
			.accountCard.Card_PAN = { 0 },
			.balance = 0,
			.transaction.transactionAmount = 0,
			.validAccount = 0
		};

		header_message();

		/* First we get the card data */
		ret = card_get_holder_name(&(tempAccount.accountCard));
		if (CARD_WRONG_NAME == ret)
			{ continue; }
		else
			{ /* Nothing */ }
		
		ret = card_get_expiry_date(&(tempAccount.accountCard));
		if (CARD_WRONG_EXP_DATE == ret)
			{ continue; }
		else
			{ /* Nothing */ }

		ret = card_get_PAN(&(tempAccount.accountCard));
		if (CARD_WRONG_PAN == ret)
			{ continue; }
		else
			{ /* Nothing */ }

		/* Second we get the amount of money */
		ret = is_card_expired(&(tempAccount.accountCard));
		if (CARD_EXPIRED == ret)
			{ continue; }
		else
			{ /* Nothing */ }

		ret = get_tranaction_amount(&(tempAccount.transaction));
		if (TRANSACTION_AMOUNT_EXCEEDED == ret)
			{ continue; }
		else
			{ /* Nothing */ }

		ret = account_exist(&tempAccount);
		if (ACCOUNT_NOT_EXIST == ret)
			{ continue; }
		else
			{ /* Nothing */ }

		ret = account_valid(&tempAccount);
		if (ACCOUNT_NOT_VALID == ret)
			{ continue; }
		else
			{ /* Nothing */ }

		ret = is_amount_available(&tempAccount);
		if (AMOUNT_NOT_AVAILABLE == ret)
			{ continue; }
		else
			{ /* Nothing */ }

		ret = update_account_balance(&tempAccount);

		clear_screen();
		display("Successfull Operation..");
		Sleep(2000);
		delete("Successfull Operation..");
		ret = getchar();
		fflush(stdin);
	}
}