#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

ST_accountsDB_t *DBreference;
static ST_accountsDB_t accountsDB[255] =
{      {5000, RUNNING, "123456789123456789"},
       {2000, RUNNING, "526814352185456824"},
       {3000, RUNNING, "154265295741628542"},
       {4000, RUNNING, "542192352012548704"},
       {5000, BLOCKED, "123456789123456787"},
       {6000, RUNNING, "502306250128142014"},
       {7000, BLOCKED, "501245032592410528"},
       {8000, BLOCKED, "501203205148245023"},
       {9000, RUNNING, "501206254013085425"},

};

static ST_transaction_t TransactionsDB[255] =
{
    {0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}
};
static uint32_t AccountDBIndex = 0;
//recieve transactiondata function
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_serverError_t State = APPROVED;
   if (isValidAccount(&(transData->cardHolderData),&DBreference))
    {
        State = FRAUD_CARD;
        transData->transState = FRAUD_CARD;
    }

    else if( (isBlockedAccount(DBreference)))
    {
        State = DECLINED_STOLEN_CARD;
        transData->transState = DECLINED_STOLEN_CARD;
    }

        else if( (isAmountAvailable(&(transData->terminalData))== LOW_BALANCE) )
    {
        State = DECLINED_INSUFFECIENT_FUND;
        transData->transState = DECLINED_INSUFFECIENT_FUND;
    }


    else
    {
        if( (saveTransaction(transData)==SAVING_FAILED ) )
        {
            State = INTERNAL_SERVER_ERROR;
        }
        else
        {
            DBreference->balance -= transData->terminalData.transAmount;
        }
    }

    return State;
}
//isValidAccount function
EN_serverError_t isValidAccount(ST_cardData_t *cardData,ST_accountsDB_t **accountRefrence)
{
    EN_serverError_t State = SERVER_OK;

    uint8_t condition = 0;
    uint8_t i = 0;
    for(i = 0; (i < 10); ++i)
    {
        if( (strcmp(cardData->primaryAccountNumber,accountsDB[i].primaryAccountNumber) == 0) )
        {
            AccountDBIndex = i;
            *accountRefrence=&accountsDB[i];
            condition=1;

        }
    }
    if(condition)
        {
            State= SERVER_OK;
        }
    else
        {
        printf("\n account not found\n");
        State= ACCOUNT_NOT_FOUND;

        }



    return State;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t State = SERVER_OK;

    uint8_t condition = 0;
    uint8_t i = 0;
    for(i = 0; (i < 10); ++i)
    {
        if( BLOCKED==(DBreference->state))
        {

            condition=1;

        }
    }
    if(condition)
        {
            State= BLOCKED_ACCOUNT;
        }
    else
        {
        printf("\n RUNNING ACCOUNT\n");
        State= SERVER_OK;

        }



    return State;
}


//isAmountAvailable
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    EN_serverError_t State = SERVER_OK;

    if( (termData->transAmount > accountsDB[AccountDBIndex].balance) )
    {
        State = LOW_BALANCE;
    }
    else {;}

    return State;
}

//saveTransaction function
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t State = SERVER_OK;
    //unsigned int uint32_t
    static uint32_t TransactionsSequenceNumber = 0;

    if( (TransactionsSequenceNumber > 255) )
    {
        State = SAVING_FAILED;
    }
    else
    {
        TransactionsDB[TransactionsSequenceNumber].cardHolderData = transData->cardHolderData;
        TransactionsDB[TransactionsSequenceNumber].terminalData = transData->terminalData;
        TransactionsDB[TransactionsSequenceNumber].transState = transData->transState;
        TransactionsDB[TransactionsSequenceNumber].transState = TransactionsSequenceNumber;
        transData->transactionSequenceNumber = TransactionsSequenceNumber;

        ++TransactionsSequenceNumber;
    }

    return State;


}


     listSavedTransactions(ST_transaction_t *transData)
    {
        printf("transaction info\n");
        printf("TransactionsSequenceNumber=%d\n",transData->transactionSequenceNumber);
        printf("transaction date is =%s\n",transData->terminalData.transactionDate);
        printf("transaction amount is =%f\n",transData->terminalData.transAmount);
        printf("terminal maximmum amount is =%f\n",transData->terminalData.maxTransAmount);
        printf("account balance =%f\n",DBreference->balance);
        printf("card holder name is =%s\n",transData->cardHolderData.cardHolderName);
        printf("pan is =%s\n",transData->cardHolderData.primaryAccountNumber);
    }

