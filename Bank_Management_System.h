
#ifndef _BANK_MANAGEMENT_SYSTEM_
#define _BANK_MANAGEMENT_SYSTEM_
#include <stdio.h>
#include <stdlib.h>
#include "Platform_Types.h"

#define MAX_NAME_SIZE 30

// Create structure to Customer Data
typedef struct client
{
    uint8 name[MAX_NAME_SIZE];
    uint32 id;
    uint32 Phone_Number;
    uint32 age;
    float32 money;
}client_t;

struct Customer
{
    client_t CustomerData;
    struct Customer *CustomerLink;
};

// Function declarations
void Menu(void);
sint32 check_id(struct Customer *List,uint32 id);
void Create_New_Account(struct Customer **List);
void Print_Customer_Data(struct Customer *List);
void Display_All_Customer(struct Customer *List);
void Update_Customer_Account(struct Customer *List);
void Delete_Customer_Account(struct Customer **List);
void Transfer_Money(struct Customer *List);

#endif
