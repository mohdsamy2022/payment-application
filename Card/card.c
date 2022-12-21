#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> //to define uint8_t...
#include <ctype.h>
#include "card.h"
//card name function
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
  uint8_t CardHolderName[25];
  printf("\n please enter your card holder's name: ");
  //scanf ("%s",&CardHolderName);
  gets(CardHolderName);
  uint8_t namelength= strlen(CardHolderName);
  printf("\n name length=%d",namelength);
  EN_cardError_t State = CARD_OK;
  int condition=0;
  for (int i=0;i<namelength;++i)
  {
       //result=isdigit(CardHolderName[i]);
      if(CardHolderName[i] < 'A' || CardHolderName[i] > 'Z' && CardHolderName[i] <'a' || CardHolderName[i] > 'z')
      {
          condition=1;

      }

  }
  if(condition)
  {
    //printf("result is %d",result);
    State = WRONG_NAME;
  }

  else if (namelength<20 || namelength>24 || CardHolderName== NULL)
  {
      State = WRONG_NAME;

  }





  else
  {
     //EN_cardError_t State = CARD_OK;
     strcpy(cardData->cardHolderName, CardHolderName);
  }
  return State;
}
//card date function
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
 uint8_t cardExpirationDate[6]={0};
 EN_cardError_t State = CARD_OK;
 printf ("\n please enter your card expiration data MM/YY: ");
 //scanf("%s",&cardExpirationDate);
 gets(cardExpirationDate);
 uint8_t expdatelength= strlen(cardExpirationDate);
 if (expdatelength<5 || expdatelength>5 || cardExpirationDate[2] !='/' || expdatelength== NULL
     || ((((cardExpirationDate[0] - '0') * 10) + (cardExpirationDate[1] - '0'))> 12)
     || isdigit(cardExpirationDate[0])==0 ||isdigit(cardExpirationDate[1])==0||isdigit(cardExpirationDate[3]==0)|| isdigit(cardExpirationDate[4])==0 )
 {
     State = WRONG_EXP_DATE;
 }
 else
 {
    strcpy(cardData->cardExpirationDate, cardExpirationDate);
 }
 return State;
}
//card pan function
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
 uint8_t primaryAccountNumber[20]={0};
 EN_cardError_t State = CARD_OK;
 printf ("\n please enter your card primary account number: ");
 //scanf("%s",&primaryAccountNumber);
 gets(primaryAccountNumber);
 uint8_t PANlength= strlen(primaryAccountNumber);
  int condition=0;
   for (int i=0;i<PANlength;++i)
  {
       //result=isdigit(CardHolderName[i]);
      if(primaryAccountNumber[i] < '0' || primaryAccountNumber[i] > '9')
      {
          condition=1;

      }
  }
  if(condition)
  {
    //printf("result is %d",result);
    State = WRONG_PAN;
  }




 else if (PANlength<16 || PANlength>20 || PANlength== NULL)
 {
     State = WRONG_PAN;
 }
 else
 {
    strcpy(cardData->primaryAccountNumber, primaryAccountNumber);
 }
 return State;
}

