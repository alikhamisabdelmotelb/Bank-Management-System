#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bank_Management_System.h"
#define Zero 0
#define Password 13579

uint32 Pass = Zero;
int main()
{
    printf("->Hello ... \n");

    label: printf("=>Enter the Password : ");
    scanf("%i",&Pass);
    if(Password == Pass)
    {
        printf("->Password is True \n\n");
        sleep(1);
        menu();
    }
    else{
        printf("->Password is Wrong !! \n");
        uint16 PassWrong = Zero;
        printf("=>Enter 1 to try again and any Number to exit : ");
        scanf("%i",&PassWrong);
        if(1==PassWrong){
          goto label;
        }
        else{
            exit(1);
        }

    }
    return 0;
}
