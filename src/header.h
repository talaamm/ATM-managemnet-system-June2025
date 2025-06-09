#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    char phone[20];
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);
void registerMenu(char a[50], char pass[50]);
int getNextUserId();
void RegisterUser(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void Transfer_ownership(struct User u);
void Remove_existing_account(struct User u);
void Make_transaction(struct User u);
void Update_account_information(struct User u);
void Check_details_of_existing_accounts(struct User u);
int isUserRegistered(const char *username);
int getNextAccId();
void getUserId(int *id, char name[50]);
