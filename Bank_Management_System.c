
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bank_Management_System.h"   //Including the header file for declarations and structure
#define Zero 0

struct Customer *ListHead = NULL;


/**
  *@brief  Display the main menu
  *@param  void
  *@retval void
  */
void menu(void)
{
    uint8 UserChoice = Zero;  //User Choice
    while(1)
    {
        //Displaying the main menu options for the user
        printf("======================= Main Menu ========================\n");
        printf("(1) -> Create New Account \n");
        printf("(2) -> Update Customer Account \n");
        printf("(3) -> Print Customer Data \n");
        printf("(4) -> Transfer Money \n");
        printf("(5) -> Delete Account \n");
        printf("(6) -> Display All Account \n");
        printf("(7) -> Quit From Application \n");
        printf("==========================================================\n");

        label_:printf("please select one of the Previous options (1, 2, 3, 4, 5, 6, 7) : ");
        scanf("%i",&UserChoice);
        printf("\n");
        switch(UserChoice)
        {
            case 1:
                Create_New_Account(&ListHead);
                sleep(1);
            break ;

            case 2:
                Update_Customer_Account(ListHead);
                sleep(1);
            break ;

            case 3:
                Print_Customer_Data(ListHead);
                sleep(1);
            break ;
            case 4:
                Transfer_Money(ListHead);
                sleep(1);
            break ;
            case 5:
                Delete_Customer_Account(&ListHead);
                printf("\nAccount Successfully Deleted \n");
                printf("---------------------------------------------------------\n\n");
                sleep(1);
            break ;

            case 6:
                Display_All_Customer(ListHead);
                sleep(1);
            break ;
            case 7:
                printf("------------------------ \n");
                printf("=> Quit From Application \n");
                printf("------------------------ \n");
                exit(1);
            break ;
            default:
                printf("---------------------- \n");
                printf("=> Error!,Out of Range \n");
                printf("---------------------- \n");
                sleep(1);
                goto label_;
        }

    }
}

/**
  *@brief  check ID Exist or Not
  *@param  list pointer to the client
  *@param  id
  *@retval Status of the ID
  */
sint32 check_id(struct Customer *List,uint32 id)
{
   uint32 check=-1 ;
   if(List==NULL)
   {
    check=1 ;
   }
    while(List!=NULL)
    {
        if(List->CustomerData.id==id)
        {
            check=2 ;
            break ;
        }
        List=List->CustomerLink ;
    }
    return check ;
}

/**
  *@brief  Create New Account
  *@param  List pointer to the client
  *@retval void
  */
void Create_New_Account(struct Customer **List)
{
    struct Customer *Temp_New_Account = NULL;
    struct Customer *Current_Check_Id = *List;
    sint32 check_1 = Zero ;

    Temp_New_Account = (struct Customer *)malloc(sizeof(struct Customer));
    if(NULL!=Temp_New_Account)
    {
        printf("=>Please Enter the Following Data : \n\n");
        sleep(1);

        getchar();
        printf("->Name         : ");
        gets(&(Temp_New_Account->CustomerData.name));

        label_1: printf("->ID           : ");
        fflush(stdout);
        scanf("%d",&(Temp_New_Account->CustomerData.id));
        //if the id is exist
        while(Current_Check_Id!=NULL){
            if(Current_Check_Id->CustomerData.id == Temp_New_Account->CustomerData.id){
                printf("Id Already exist \n");
                goto label_1;
            }
            Current_Check_Id = Current_Check_Id->CustomerLink;
        }

        printf("->Phone Number : ");
        fflush(stdout);
        scanf("%d",&(Temp_New_Account->CustomerData.Phone_Number));

        printf("->Age          : ");
        fflush(stdout);
        scanf("%d",&(Temp_New_Account->CustomerData.age));

        label_2: printf("->Money        : ");
        fflush(stdout);
        scanf("%f",&(Temp_New_Account->CustomerData.money));
        //if money less then Zero
        if(Temp_New_Account->CustomerData.money < 0)
        {
            printf("the money should be positive number \n");
            goto label_2;
        }
        printf("\nAccount Successfully Created \n");
        printf("----------------------------------------------------------\n\n");

        //list is Empty
        if(NULL == *List)
        {
            Temp_New_Account->CustomerLink = NULL;
            *List = Temp_New_Account;
        }
        //list is Not Empty
        else
        {
            Temp_New_Account->CustomerLink =*List;
            *List = Temp_New_Account;
        }
    }
    else
    {
        printf("Error, Not allocate \n");
    }
}

/**
  *@brief  Print Customer Data
  *@param  List pointer to the client
  *@retval void
  */
void Print_Customer_Data(struct Customer *List){
    struct Customer *Current_All_Data = List;
    uint32 id_customer = Zero;
    uint32 check = Zero;

    if(List == NULL){
        printf("=>List is Empty !! \n");
        return;
    }
    else
    {
        label_1: printf("=>Please Enter the Customer ID you want to Print : ");
        scanf("%i",&id_customer);
        check=check_id(List,id_customer);
        if (check==-1)
        {
            printf("Invalid id \n");
            goto label_1 ;
        }
        else
        {
            /* Nothing */
        }
    }
    while(Current_All_Data->CustomerData.id != id_customer)
    {
        Current_All_Data = Current_All_Data->CustomerLink;
    }
    printf("===============================\n");
    printf("=>Customer Data:  \n\n");
    printf("->Name         : %s \n",Current_All_Data->CustomerData.name);
    printf("->ID           : %i \n",Current_All_Data->CustomerData.id);
    printf("->Phone Number : +20%d \n",Current_All_Data->CustomerData.Phone_Number);
    printf("->Age          : %i \n",Current_All_Data->CustomerData.age);
    printf("->Money        : %f \n",Current_All_Data->CustomerData.money);
    printf("------------------------------\n");
}

/**
  *@brief  Transfer Money
  *@param  List pointer to the client
  *@retval void
  */
void Transfer_Money(struct Customer *List){
    struct Customer *Current_Send = List;
    struct Customer *Current_Receive = List;
    uint32 id_Customer_Send = 0;
    uint32 id_Customer_Receive = 0;
    uint32 Money_send = 0;
    uint32 check_1 = 0;
    uint32 check_2 = 0;

    //if the list is Empty
    if(List == NULL){
        printf("List is Empty \n");
        return;
    }
    // if the list contains one element
    if(List->CustomerLink==NULL)
    {
        printf("The Transfer Money it must be at least two Elements \n\n");
        return ;
    }

    //Customer ID that Sender
    label_5: printf("Enter the Customer ID that Sender  : ");
    scanf("%i",&id_Customer_Send);
    check_1=check_id(List,id_Customer_Send);
    if (check_1==-1)
    {
        printf("Invalid id \n");
        goto label_5 ;
    }
    while(Current_Send->CustomerLink != NULL){
        if(Current_Send->CustomerData.id == id_Customer_Send){
            break;
        }
        Current_Send = Current_Send->CustomerLink;
    }

    // Money ?
    label_6: printf("How much Money you want to send ?  : ");
    scanf("%i",&Money_send);
    if(Money_send < 0)
    {
        printf("the money should be positive number \n");
        goto label_6;
    }
    if(Current_Send->CustomerData.money <= Money_send){
        printf("The Money Not Enough \n");
        goto label_6;
    }

    //Customer ID that Receive
    label_7: printf("Enter the Customer ID that Receive : ");
    scanf("%i",&id_Customer_Receive);
    check_2=check_id(List,id_Customer_Receive);
    if (check_2==-1)
    {
        printf("Invalid id \n");
        goto label_7 ;
    }
    // if id Customer Sender equal to id Customer Receive
    if(id_Customer_Send == id_Customer_Receive){
        printf("=>Customer ID that Sender equal to Customer ID that Receive \n");
        goto label_5;
    }

    while(Current_Receive->CustomerLink!= NULL)
    {
        if(Current_Receive->CustomerData.id==id_Customer_Receive){
            break;
        }
        Current_Receive = Current_Receive->CustomerLink;
    }

    Current_Send->CustomerData.money -= Money_send;
    Current_Receive->CustomerData.money +=Money_send;

    printf("\nDone Successfully \n");
    printf("----------------------------------------------------------\n\n");

}

/**
  *@brief  Update information of Customer Account
  *@param  List pointer to the client
  *@retval void
  */
void Update_Customer_Account(struct Customer *List){
    struct Customer *Temp_Update = List;
    struct Customer *check_ID = List;
    uint32 id_customer = Zero;
    sint32 check = Zero;
    uint32 Num_of_data = Zero;

    // if list is empty
    if(List == NULL){
        printf("=>List is Empty !! \n");
    }
    // list not empty
    else
    {
        label_1: printf("=>Please Enter the Customer ID you want to Update : ");
        scanf("%i",&id_customer);
        check=check_id(List,id_customer);
        if (check==-1)
        {
            printf("Invalid id \n");
            goto label_1 ;
        }

        while(Temp_Update->CustomerData.id != id_customer)
        {
            Temp_Update = Temp_Update->CustomerLink;
        }

        printf("=>Please Enter the Number of Data you want to Update :\n(1->Name   2->ID   3->Phone Number   4->Age   5->Money) : ");
        scanf("%i",&Num_of_data);
        sleep(1);
        if(1==Num_of_data)
        {
            getchar();
            printf("->Name : ");
            gets(&(Temp_Update->CustomerData.name));
        }
        else if(2==Num_of_data)
        {
            printf("sorry,if you want update the id create New account \n");
            printf("---------------------------------------------------------\n\n");
            return;
        }
        else if(3==Num_of_data)
        {
            printf("->Phone Number : ");
            fflush(stdout);
            scanf("%d",&(Temp_Update->CustomerData.Phone_Number));
        }
        else if(4==Num_of_data)
        {
            printf("->Age : ");
            fflush(stdout);
            scanf("%d",&(Temp_Update->CustomerData.age));
        }
        else if(5==Num_of_data)
        {
            label_2: printf("->Money : ");
            fflush(stdout);
            scanf("%f",&(Temp_Update->CustomerData.money));
            if(Temp_Update->CustomerData.money < 0)
            {
                printf("the money should be positive number \n");
                goto label_2;
            }
        }
        else
        {
           printf("Out of Range!! \n");
        }
        printf("\nAccount Successfully Update \n");
    }
    printf("---------------------------------------------------------\n\n");
}

/**
  *@brief  Delete Customer Account
  *@param  List pointer to the client
  *@retval void
  */
void Delete_Customer_Account(struct Customer **List){
    struct Customer *Current = *List;
    struct Customer *previous = NULL;
    uint32 Id_Account = Zero;

    //if the list is empty
    if(*List == NULL)
    {
        printf("the List is Empty !! \n");
        return;
    }
    label_7: printf("=>Please Enter the Customer ID you want to Delete : ");
    scanf("%i",&Id_Account);

    // if The first Customer is Deleted
    if(Current->CustomerData.id == Id_Account)
    {
        (*List) = Current->CustomerLink;
        free(Current);
        return;
    }
    else
    {
        while(Current->CustomerData.id != Id_Account){
            previous = Current;
            Current = Current->CustomerLink;
        }
        previous->CustomerLink = Current->CustomerLink;
        free(Current);

    }
}

/**
  *@brief  Display All Customer
  *@param  List pointer to the client
  *@retval void
  */
void Display_All_Customer(struct Customer *List)
{
    struct Customer *Display_All_Customer = List;
    uint32 Num_choice = Zero;

    if(NULL == List)
    {
        printf("List is Empty \n");
    }
    printf("===============================\n");

    //loop to Display All customers Data
    while(NULL!=Display_All_Customer)
    {
        printf("=>Customer Data:  \n\n");
        printf("->Name         : %s \n",Display_All_Customer->CustomerData.name);
        printf("->ID           : %d \n",Display_All_Customer->CustomerData.id);
        printf("->Phone Number : +20%d \n",Display_All_Customer->CustomerData.Phone_Number);
        printf("->Age          : %d \n",Display_All_Customer->CustomerData.age);
        printf("->Money        : %f \n",Display_All_Customer->CustomerData.money);
        printf("------------------------------\n");

        Display_All_Customer = Display_All_Customer->CustomerLink;
        if(NULL == Display_All_Customer)
        {
            printf("All Customers Data were Displayed \n");
            printf("------------------------------\n");
        }
    }
}


