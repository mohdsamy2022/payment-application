#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

//#define test             //define first to test
//#define getCardHolderNametest      //define only the function you want to test
//#define getCardExpiryDatetest
//#define getCardPANtest
//#define setMaxAmounttest
//#define getTransactionDatetest
//#define isCardExpiredtest
//#define getTransactionAmounttest
//#define isBelowMaxAmounttest
//#define recieveTransactionDatatest
//#define saveTransactiontest
//#define listSavedTransactionstest
void appStart(void)
{
 #ifndef test
    ST_cardData_t Card;
   //card holder name
    EN_cardError_t CardHolderName_ErrorState =getCardHolderName(&Card);

   if( (WRONG_NAME == CardHolderName_ErrorState) )
    {
        printf("\n WRONG_NAME \n");
        return;
    }
    else {;printf("\n CARD_OK\n");}


//cardexpiry
    EN_cardError_t CardExpDate_ErrorState = getCardExpiryDate(&Card);

    if( (WRONG_EXP_DATE == CardExpDate_ErrorState) )
    {
        printf("\n WRONG_EXP_DATE\n");
        return;
    }else {;printf("\n CARD_OK\n");}

//cardpan
    EN_cardError_t CardPAN_ErrorState = getCardPAN(&Card);

    if( (WRONG_PAN == CardPAN_ErrorState) )
    {
        printf("\n WRONG_PAN \n");
        return;
    }else {;printf("\n CARD_OK\n");}

    ST_terminalData_t Terminal;
//setmaxamount
EN_terminalError_t setMaxAmount_ErrorState = setMaxAmount(&Terminal);


    if((INVALID_MAX_AMOUNT == setMaxAmount_ErrorState ))
    {
        printf("\n INVALID_MAX_AMOUNT \n");
        return;
    }
    else {;printf("\n setMaxAmount_TERMINAL_OK\n");}


//transdate
    EN_terminalError_t GetTransDate_ErrorState = getTransactionDate(&Terminal);

    if( (WRONG_DATE == GetTransDate_ErrorState) )
    {
        printf(" \n WRONG_DATE \n");
        return;
    }else {;printf("\n TransDate_TERMINAL_OK\n");}

//card expiration
    EN_terminalError_t ExpiredCard_ErrorState = isCardExpired(Card, Terminal);

    if( (EXPIRED_CARD == ExpiredCard_ErrorState) )
    {
        printf("\n EXPIRED_CARD \n");
        return;
    }else {;printf("\n notExpiredCard_TERMINAL_OK\n");}



//transamount
    EN_terminalError_t TransAmount_ErrorState = getTransactionAmount(&Terminal);

    if( (INVALID_AMOUNT == TransAmount_ErrorState) )
    {
        printf("\n INVALID_AMOUNT\n");
        return;
    }else {;printf("\n TransAmount_TERMINAL_OK\n");}

//transamountlimit
    EN_terminalError_t TransAmountLimit_ErrorState = isBelowMaxAmount(&Terminal);

    if( (EXCEED_MAX_AMOUNT == TransAmountLimit_ErrorState) )
    {
       printf("\n EXCEED_MAX_AMOUNT\n");
       return;
    }else {;printf("\n TransAmountLimit_TERMINAL_OK\n");}

//acount validity
    ST_transaction_t Transaction = {.cardHolderData = Card, .terminalData = Terminal};
    EN_transState_t Transaction_ErrorState = recieveTransactionData(&Transaction);

    if( (FRAUD_CARD == Transaction_ErrorState) )
    {
        printf("\n FRAUD_CARD\n");
        return;
    }
    else if( (DECLINED_INSUFFECIENT_FUND ==  Transaction_ErrorState) )
    {
        printf("\n DECLINED_INSUFFECIENT_FUND\n");
        return;
    }
      else if( (DECLINED_STOLEN_CARD ==  Transaction_ErrorState) )
    {
        printf("\n DECLINED_STOLEN_CARD\n");
        printf("\n BLOCKED_ACCOUNT\n");
        return;
    }
    else if( (INTERNAL_SERVER_ERROR == Transaction_ErrorState) )
    {
        printf("\n INTERNAL_SERVER_ERROR \n");
        return;
    }
    else {;printf("\n Transaction_APPROVED\n");}




    //savetransaction
    EN_serverError_t saveTransaction_ErrorState =saveTransaction(&Transaction);

    if ((SAVING_FAILED == saveTransaction_ErrorState ))
    {
        printf("\n SAVING_FAILED\n");
        return;
    }
    else {;printf("\n your transaction saved seccessfully\n");}


  listSavedTransactions(&Transaction);
#endif //test
#ifdef getCardHolderNametest
    ST_cardData_t Card;

   //card holder name
    EN_cardError_t CardHolderName_ErrorState =getCardHolderName(&Card);

   if( (WRONG_NAME == CardHolderName_ErrorState) )
    {
        printf("\n WRONG_NAME\n");
        return;
    }
    else {;printf("\n CARD_OK\n");}
        return;
#endif // cardnameerror
#ifdef getCardExpiryDatetest
    ST_cardData_t Card;
    EN_cardError_t CardExpDate_ErrorState = getCardExpiryDate(&Card);

    if( (WRONG_EXP_DATE == CardExpDate_ErrorState) )
    {
        printf("\n WRONG_EXP_DATE\n");
        return;
    }else {;printf("\n CARD_OK\n");}
 #endif // cardexpiryerror

#ifdef getCardPANtest
//cardpan
    ST_cardData_t Card;
    EN_cardError_t CardPAN_ErrorState = getCardPAN(&Card);

    if( (WRONG_PAN == CardPAN_ErrorState) )
    {
        printf("\n WRONG_PAN \n");
        return;
    }else {;printf("\n CARD_OK\n");}
 #endif //cardpanerror
#ifdef setMaxAmounttest
    ST_cardData_t Card;
    ST_terminalData_t Terminal;
//setmaxamount
EN_terminalError_t setMaxAmount_ErrorState = setMaxAmount(&Terminal);


    if((INVALID_MAX_AMOUNT == setMaxAmount_ErrorState ))
    {
        printf("\n INVALID_MAX_AMOUNT \n");
        return;
    }
    else {;printf("\n setMaxAmount_TERMINAL_OK\n");}
 #endif //setmaxerror
#ifdef getTransactionDatetest
//transdate
   ST_cardData_t Card;
    ST_terminalData_t Terminal;
    EN_terminalError_t GetTransDate_ErrorState = getTransactionDate(&Terminal);

    if( (WRONG_DATE == GetTransDate_ErrorState) )
    {
        printf(" \n WRONG_DATE \n");
        return;
    }else {;printf("\n TransDate_TERMINAL_OK\n");}
#endif //getTransactionDatetest
#ifdef isCardExpiredtest
//card expiration
  ST_cardData_t Card;
   ST_terminalData_t Terminal;
    EN_terminalError_t ExpiredCard_ErrorState = isCardExpired(Card, Terminal);

    if( (EXPIRED_CARD == ExpiredCard_ErrorState) )
    {
        printf("\n EXPIRED_CARD \n");
        return;
    }else {;printf("\n notExpiredCard_TERMINAL_OK\n");}
#endif //isCardExpiredtestr

#ifdef getTransactionAmounttest
//transamount
   ST_cardData_t Card;
    ST_terminalData_t Terminal;
    EN_terminalError_t TransAmount_ErrorState = getTransactionAmount(&Terminal);

    if( (INVALID_AMOUNT == TransAmount_ErrorState) )
    {
        printf("\n INVALID_AMOUNT\n");
        return;
    }else {;printf("\n TransAmount_TERMINAL_OK\n");}
#endif //getTransactionAmounttest
#ifdef isBelowMaxAmounttest

//transamountlimit
    ST_cardData_t Card;
    ST_terminalData_t Terminal;
    EN_terminalError_t TransAmountLimit_ErrorState = isBelowMaxAmount(&Terminal);

    if( (EXCEED_MAX_AMOUNT == TransAmountLimit_ErrorState) )
    {
       printf("\n EXCEED_MAX_AMOUNT\n");
       return;
    }else {;printf("\n TransAmountLimit_TERMINAL_OK\n");}
#endif //isBelowMaxAmounttest
#ifdef  recieveTransactionDatatest
//acount validity
   ST_cardData_t Card;
   ST_terminalData_t Terminal;
    ST_transaction_t Transaction = {.cardHolderData = Card, .terminalData = Terminal};
    EN_transState_t Transaction_ErrorState = recieveTransactionData(&Transaction);

    if( (FRAUD_CARD == Transaction_ErrorState) )
    {
        printf("\n FRAUD_CARD\n");
        return;
    }
    else if( (DECLINED_INSUFFECIENT_FUND ==  Transaction_ErrorState) )
    {
        printf("\n DECLINED_INSUFFECIENT_FUND\n");
        return;
    }
      else if( (DECLINED_STOLEN_CARD ==  Transaction_ErrorState) )
    {
        printf("\n DECLINED_STOLEN_CARD\n");
        return;
    }
    else if( (INTERNAL_SERVER_ERROR == Transaction_ErrorState) )
    {
        printf("\n INTERNAL_SERVER_ERROR \n");
        return;
    }
    else {;printf("\n Transaction_APPROVED\n");}

#endif //recieveTransactionDatatest

 #ifdef saveTransactiontest
    //savetransaction
   ST_cardData_t Card;
    ST_terminalData_t Terminal;
    ST_transaction_t Transaction = {.cardHolderData = Card, .terminalData = Terminal};
    EN_serverError_t saveTransaction_ErrorState =saveTransaction(&Transaction);

    if ((SAVING_FAILED == saveTransaction_ErrorState ))
    {
        printf("\n SAVING_FAILED\n");
        return;
    }
    else {;printf("\n your transaction saved seccessfully\n");}

#endif //saveTransactiontest
   #ifdef listSavedTransactionstest
      ST_cardData_t Card;
    ST_terminalData_t Terminal;
    ST_transaction_t Transaction = {.cardHolderData = Card, .terminalData = Terminal};
    EN_serverError_t saveTransaction_ErrorState =saveTransaction(&Transaction);
  listSavedTransactions(&Transaction);
 #endif //listSavedTransactionstest
}


