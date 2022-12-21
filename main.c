//„Õ„œ ”«„Ì ”⁄œ
//mohdsamy2022@gmail.com

#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include "Application/app.h"

int main(void)
{
printf ("welcome to payment application \n");
    uint8_t state = 0;

    while(1)
    {
        printf("\n 1. Make your transaction.");
        printf("\n 2. Exit program.");

        state = getch();

        switch(state)
        {
            case '1':
                    fflush(stdin);
                    appStart();
                    break;
            case '2':

                return 1;
            default:

            printf("\n Invalid input.");
                break;
        }
    }


    return 0;
}
