#include "header.h"

const char *RECORDS = "../data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  &r->country,
                  &r->phone,
                  &r->amount,
                  &r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖️ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔️ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    printf("curr id: %d", u.id);
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖️ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%19s", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
    // printf("im here");
    r.id = getNextAccId();
    // printf("%d", u.id);
    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

// void Update_account_information(struct User u)
// {
//     /*The Update information of existing account feature, users must be able to update their country or phone number.

// 2.1. You must ask users to input the account id they want to change, followed by a prompt asking which field they want to also change (the only fields that are permitted to update is the phone number and the country).

// 2.2. Whenever users update an account, it must be saved into the corresponding file.*/

//    }

void Update_account_information(struct User u)
{
    int accountId, option;
    struct Record r;
    struct Record records[1000];
    char userNames[1000][50];
    int count = 0, idx = -1;

    FILE *pf = fopen(RECORDS, "r");
    if (!pf)
    {
        printf("Error opening records file!\n");
        return;
    }

    // Read all records into memory
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r.id, &r.userId, r.name, &r.accountNbr,
                  &r.deposit.month, &r.deposit.day, &r.deposit.year,
                  r.country, r.phone, &r.amount, r.accountType) == 11)
    {
        strcpy(userNames[count], r.name);
        records[count] = r;
        count++;
    }
    fclose(pf);

    system("clear");
    printf("\t\t\t===== Update account information =====\n");
    printf("\nEnter the account number you want to update:");
    scanf("%d", &accountId);

    // Find the record to update
    for (int i = 0; i < count; i++)
    {
        if (strcmp(userNames[i], u.name) == 0 && records[i].accountNbr == accountId)
        {
            idx = i;
            break;
        }
    }

    if (idx == -1)
    {
        stayOrReturn(0, Update_account_information, u);
        return;
    }

    printf("\nWhat do you want to update?\n1. Country\n2. Phone number\nEnter your choice:");
    scanf("%d", &option);
    system("clear");
    printf("\t\t\t===== Update account information =====\n");
    if (option == 1)
    {
        printf("\nEnter new country:");
        scanf("%s", records[idx].country);
    }
    else if (option == 2)
    {
        printf("\nEnter new phone number:");
        scanf("%19s", records[idx].phone);
    }
    else
    {
        printf("Invalid option!\n");
        return Update_account_information(u);
    }

    // Rewrite the file with updated records
    pf = fopen(RECORDS, "w");
    if (!pf)
    {
        printf("Error opening records file for writing!\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(pf, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                records[i].id, records[i].userId, records[i].name, records[i].accountNbr,
                records[i].deposit.month, records[i].deposit.day, records[i].deposit.year,
                records[i].country, records[i].phone, records[i].amount, records[i].accountType);
    }
    fclose(pf);

    success(u);
}

void Check_details_of_existing_accounts(struct User u)
{

    char userName[50];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");
    int accnbr;
    system("clear");
    printf("\t\t\t===== Check details of existing accounts =====\n");
    printf("\nEnter the account number to check:");
    scanf("%d", &accnbr);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && accnbr == r.accountNbr)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%s \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
            /*3.2. If the account is either savings, fixed01, fixed02 and fixed03 the system will display the information of that account and the interest you will acquire depending on the account:

            savings: interest rate 7%

fixed01(1 year account): interest rate 4%

fixed02(2 year account): interest rate 5%

fixed03(3 year account): interest rate 8%

If the account is current you must display You will not get interests because the account is of type current

For example: for an account of type savings with a deposit date of 10/10/2002 and an amount of $1023.20 the system will show "You will get $5.97 as interest on day 10 of every month".*/
            fclose(pf);
            float rate = r.amount;
            if (strcmp(r.accountType, "saving") == 0)
            {
                rate *= 7 / 100.0;
            }
            else if (strcmp(r.accountType, "fixed01") == 0)
            {
                rate *= 4 / 100.0;
            }
            else if (strcmp(r.accountType, "fixed02") == 0)
            {
                rate *= 5 / 100.0;
            }
            else if (strcmp(r.accountType, "fixed03") == 0)
            {
                rate *= 6 / 100.0;
            }

            if (strcmp(r.accountType, "current") == 0)
                printf("You will not get interests because the account is of type current");
            else
                printf("You will get $%.2f as interest on day %d of every month", rate, r.deposit.day);
        }
    }
    success(u);
}

void Make_transaction(struct User u)
{
    int accountNbr, option;
    struct Record r;
    struct Record records[1000];
    char userNames[1000][50];
    int count = 0, idx = -1;

    FILE *pf = fopen(RECORDS, "r");
    if (!pf)
    {
        printf("Error opening records file!\n");
        return;
    }

    // Read all records into memory
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r.id, &r.userId, r.name, &r.accountNbr,
                  &r.deposit.day, &r.deposit.month, &r.deposit.year,
                  r.country, r.phone, &r.amount, r.accountType) == 11)
    {
        strcpy(userNames[count], r.name);
        records[count] = r;
        count++;
    }
    fclose(pf);

    system("clear");
    printf("\t\t\t===== Make transaction =====\n");
    printf("\nEnter the account number to make a transaction:");
    scanf("%d", &accountNbr);

    // Find the record to update
    for (int i = 0; i < count; i++)
    {
        // printf("checking name: %s accNum: %d", userNames[i], records[i].accountNbr);
        if (strcmp(userNames[i], u.name) == 0 && records[i].accountNbr == accountNbr)
        {
            idx = i;
            break;
        }
    }

    if (idx == -1)
    {
        stayOrReturn(0, Make_transaction, u);
        return;
    }

    if (strcmp(records[idx].accountType, "fixed01") == 0 ||
        strcmp(records[idx].accountType, "fixed02") == 0 ||
        strcmp(records[idx].accountType, "fixed03") == 0)
    {
        printf("✖️ Transactions are not allowed for fixed accounts!\n");
        return Make_transaction(u);
    }

    printf("\nChoose the transaction type:\n1. Deposit\n2. Withdraw\nEnter your choice:");
    scanf("%d", &option);

    if (option == 1)
    {
        double depositAmount;
        printf("\nEnter amount to deposit: $");
        scanf("%lf", &depositAmount);
        records[idx].amount += depositAmount;
        // Optionally update deposit date here
        printf("✔️ Amount deposited successfully!\n");
    }
    else if (option == 2)
    {
        double withdrawAmount;
        printf("\nEnter amount to withdraw: $");
        scanf("%lf", &withdrawAmount);
        if (withdrawAmount > records[idx].amount)
        {
            printf("✖️ Insufficient funds!\n");
            return Make_transaction(u);
        }
        records[idx].amount -= withdrawAmount;
        // Optionally update withdraw date here
        printf("✔️ Amount withdrawn successfully!\n");
    }
    else
    {
        printf("✖️ Invalid option!\n");
        return Make_transaction(u);
    }

    // Rewrite the file with updated records
    pf = fopen(RECORDS, "w");
    if (!pf)
    {
        printf("Error opening records file for writing!\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(pf, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                records[i].id, records[i].userId, records[i].name, records[i].accountNbr,
                records[i].deposit.month, records[i].deposit.day, records[i].deposit.year,
                records[i].country, records[i].phone, records[i].amount, records[i].accountType);
    }
    fclose(pf);

    success(u);
}

void Remove_existing_account(struct User u)
{
    int accountNbr;
    char userName[50];
    struct Record r;
    struct Record records[1000];
    char userNames[1000][50];
    int count = 0, idx = -1;

    FILE *pf = fopen(RECORDS, "r");
    if (!pf)
    {
        printf("Error opening records file!\n");
        return;
    }

    // Read all records into memory
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r.id, &r.userId, r.name, &r.accountNbr,
                  &r.deposit.month, &r.deposit.day, &r.deposit.year,
                  r.country, r.phone, &r.amount, r.accountType) == 11)
    {
        strcpy(userNames[count], r.name);
        records[count] = r;
        count++;
    }
    fclose(pf);

    system("clear");
    printf("\t\t\t===== Remove existing account =====\n");
    printf("\nEnter the account number to delete:");
    scanf("%d", &accountNbr);

    // Find the record to delete
    for (int i = 0; i < count; i++)
    {
        if (strcmp(userNames[i], u.name) == 0 && records[i].accountNbr == accountNbr)
        {
            idx = i;
            break;
        }
    }

    if (idx == -1)
    {
        stayOrReturn(0, Remove_existing_account, u);
        return;
    }

    // Rewrite the file without the deleted record
    pf = fopen(RECORDS, "w");
    if (!pf)
    {
        printf("Error opening records file for writing!\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        if (i == idx)
            continue; // Skip the record to delete
        fprintf(pf, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                records[i].id, records[i].userId, records[i].name, records[i].accountNbr,
                records[i].deposit.month, records[i].deposit.day, records[i].deposit.year,
                records[i].country, records[i].phone, records[i].amount, records[i].accountType);
    }
    fclose(pf);

    printf("✔️ Account removed successfully!\n");
    success(u);
}

void Transfer_ownership(struct User u)
{
    /*The Transfer owner feature, users can transfer their account to another user, by:

    6.1. Identifying the account and the user they want to transfer the ownership to

    6.2. Saving the information in the corresponding file*/

    int accountNbr;
    char userName[50];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");
    if (!pf)
    {
        printf("Error opening records file!\n");
        return;
    }
    // Read all records into an array
    struct Record records[1000];
    char userNames[1000][50];
    int count = 0;
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %s %lf %s",
                  &r.id, &r.userId, r.name, &r.accountNbr,
                  &r.deposit.month, &r.deposit.day, &r.deposit.year,
                  r.country, r.phone, &r.amount, r.accountType) == 11)
    {
        records[count] = r;
        strcpy(userNames[count], r.name);
        count++;
    }
    fclose(pf);

    // find the record to transfer
    int found = 0;
    int idx = -1;

    system("clear");
    printf("\t\t\t===== Transferring Account =====\n");

    printf("\nEnter the account number to transfer:");
    scanf("%d", &accountNbr);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(userNames[i], u.name) == 0 && records[i].accountNbr == accountNbr)
        {
            found = 1;
            idx = i;
            break;
        }
    }

    if (!found)
    {
        stayOrReturn(0, Transfer_ownership, u);
        return;
    }

    // Proceed with transfer
    char newOwner[50];
    printf("\nEnter the new owner's username:");
    scanf("%s", newOwner);

    // Validate new owner
    if (!isUserRegistered(newOwner))
    {
        printf("✖️ New owner is not registered!\n");
        fclose(pf);
        return Transfer_ownership(u);
    }

    int newOwnerId;
    getUserId(&newOwnerId, newOwner);
    // Update the record
    records[idx].userId = newOwnerId;
    strcpy(records[idx].name, newOwner);

    // Rewrite the file
    pf = fopen(RECORDS, "w");
    if (!pf)
    {
        printf("Error opening records file for writing!\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(pf, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n\n",
                records[i].id, records[i].userId, records[i].name, records[i].accountNbr,
                records[i].deposit.month, records[i].deposit.day, records[i].deposit.year,
                records[i].country, records[i].phone, records[i].amount, records[i].accountType);
    }
    // // Update account ownership
    // fseek(pf, -sizeof(struct Record), SEEK_CUR);
    // r.userId = newOwnerId;
    // strcpy(r.name, newOwner);
    // fwrite(&r, sizeof(struct Record), 1, pf);

    fclose(pf);
    printf("✔️ Account ownership transferred successfully!\n");
    success(u);
}

int isUserRegistered(const char *username)
{
    FILE *fp = fopen("../data/users.txt", "r");
    if (!fp)
    {
        printf("Error opening users file!\n");
        return 0;
    }

    struct User userChecker;
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, username) == 0)
        {
            fclose(fp);
            return 1; // User found
        }
    }

    fclose(fp);
    return 0; // User not found
}

int getNextAccId()
{
    FILE *fp = fopen(RECORDS, "r");
    if (!fp)
    {
        printf("Error opening users file!\n");
        exit(1);
    }
    int maxId = 0;
    // struct Record r
    // each line is:  3 -1732249792 tala 55 5/5/2005 usa 5223662 510.00 saving
    // Scan only the first number (account id) in the line
    int tmp;
    while (fscanf(fp, "%d", &tmp) == 1)
    {
        if (tmp > maxId)
            maxId = tmp;
        // Skip the rest of the line
        int ch;
        while ((ch = fgetc(fp)) != '\n' && ch != EOF)
            ;
    }
    fclose(fp);
    return maxId + 1;
    // while (fscanf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s", &r.id) != EOF)
    // {
    //     if (r.id > maxId)
    //         maxId = r.id;
    // }

    // fclose(fp);
    // return maxId + 1;
}