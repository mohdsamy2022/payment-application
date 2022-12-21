#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> //to define uint8_t...


#include "../Card/card.h"
#include "terminal.h"
//transdate
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t State = TERMINAL_OK;

    uint8_t transactionDate[11] = {0};

    printf("\n please enter the transaction date DD/MM/YYYY: ");
    scanf("%s",transactionDate);
     //gets(transactionDate);
    uint8_t TransactionDateLength = strlen(transactionDate);
     //printf("length=%d",TransactionDateLength);
    if( (TransactionDateLength < 10) || (TransactionDateLength > 10) || (transactionDate[2] != '/') || (transactionDate[5] != '/')||( TransactionDateLength==NULL)|| (isdigit(transactionDate[0])==0) || (isdigit(transactionDate[1])==0) ||
       (isdigit(transactionDate[3])==0) || (isdigit(transactionDate[4])==0)
             ||(isdigit(transactionDate[6])==0)|| (isdigit(transactionDate[7])==0)|| (isdigit(transactionDate[8])==0)|| (isdigit(transactionDate[9])==0)
             || ((((transactionDate[3] - '0') * 10) + (transactionDate[4] - '0'))> 12) || ((((transactionDate[0] - '0') * 10) + (transactionDate[1] - '0'))> 31))
    {
        State = WRONG_DATE;
    }


    else
    {
        strcpy(termData->transactionDate, transactionDate);
    }

    return State;
}
//ISCARD EXPIRED
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)//add*
{
    EN_terminalError_t State = TERMINAL_OK;
    //MM/YY DD/MM/YYYY
    //01234 0123456789
    uint8_t CardExpiryMonth = ((cardData.cardExpirationDate[0] - '0') * 10) + (cardData.cardExpirationDate[1] - '0');
    uint8_t CardExpiryYear  = ((cardData.cardExpirationDate[3] - '0') * 10) + (cardData.cardExpirationDate[4] - '0');

    uint8_t TransactionMonth = ((termData.transactionDate[3] - '0') * 10) + (termData.transactionDate[4] - '0');
    uint8_t TransactionYear  = ((termData.transactionDate[8] - '0') * 10) + (termData.transactionDate[9] - '0');

    if( (CardExpiryYear < TransactionYear) )
    {
        State = EXPIRED_CARD;
    }
    else if( (CardExpiryYear == TransactionYear) )
    {
        if( (CardExpiryMonth < TransactionMonth) ||(CardExpiryMonth == TransactionMonth) )
        {
            State = EXPIRED_CARD;
        }
        else {State = TERMINAL_OK;}
    }
    else {State = TERMINAL_OK;}

    return State;
}
//transamount
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t State = TERMINAL_OK;

    float transAmount = 0;
    printf("\n please enter  your transaction amount: ");
    scanf("%f", &transAmount);

    if( ( transAmount<=0) )
    {
        State = INVALID_AMOUNT;
    }
    else
    {
        termData->transAmount = transAmount;
    }
    return State;
}
//isbelow max
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t State = TERMINAL_OK;

    if( (termData->transAmount > termData->maxTransAmount) )
    {
        State = EXCEED_MAX_AMOUNT;
    }
    else{State = TERMINAL_OK;}

    return State;
}
//maxamount
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t State = TERMINAL_OK;

    float maxTransAmount = 0;

    printf("\n please enter maximum transaction amount: ");
    scanf("%f", &maxTransAmount);

    if( (maxTransAmount<=0) )
    {
        State = INVALID_MAX_AMOUNT;
    }
    else
    {
        termData->maxTransAmount = maxTransAmount;
    }

    return State;
}
