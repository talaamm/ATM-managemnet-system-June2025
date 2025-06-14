#include "header.h"
#include <stdio.h>
#include <windows.h>

void mainMenu(struct User u) {
  int option;
  system("clear");
  printf("\n\n\t\t======= ATM =======\n\n");
  printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
  printf("\n\t\t[1]- Create a new account\n");
  printf("\n\t\t[2]- Update account information\n");
  printf("\n\t\t[3]- Check accounts\n");
  printf("\n\t\t[4]- Check list of owned account\n");
  printf("\n\t\t[5]- Make Transaction\n");
  printf("\n\t\t[6]- Remove existing account\n");
  printf("\n\t\t[7]- Transfer ownership\n");
  printf("\n\t\t[8]- Exit\n");
  scanf("%d", &option);

  switch (option) {
  case 1:
    createNewAcc(u);
    break;
  case 2:
    // DONE-TODO : add your **Update account information** function
    Update_account_information(u);
    break;
  case 3:
    // DONE-TODO : add your **Check the details of existing accounts** function
    Check_details_of_existing_accounts(u);
    break;
  case 4:
    checkAllAccounts(u);
    break;
  case 5:
    // DONE-TODO : add your **Make transaction** function
    Make_transaction(u);
    break;
  case 6:
    // DONE-TODO : add your **Remove existing account** function
    Remove_existing_account(u);
    break;
  case 7:
    // DONE-TODO : add your **Transfer owner** function
    Transfer_ownership(u);
    break;
  case 8:
    exit(1);
    break;
  default:
    printf("Invalid operation!\n");
  }
};

void initMenu(struct User *u) {
  int r = 0;
  int option;
  system("clear");
  printf("\n\n\t\t\t\t======= ATM =======\n");
  printf("\n\t\t\t\t-->> Feel free to login / register :\n");
  printf("\n\t\t\t\t[1]- login\n");
  printf("\n\t\t\t\t[2]- register\n");
  printf("\n\t\t\t\t[3]- exit\n");
  while (!r) {
    scanf("%d", &option);
    switch (option) {
    case 1:
    login:
      loginMenu(u->name, u->password);
      getUserId(&(*u).id, u->name);
      // printf("username: %s\n", u->name);
      // printf("enetered pass: %s\n", u->password);
      // printf("found pass: %s\n", getPassword(*u));
      if (strcmp(u->password, getPassword(*u)) == 0) {
        printf("\n\nPassword Match!");
      } else {
        system("clear");
        printf("\nWrong password!! or User Name\n");
        goto login;
      }
      r = 1;
      break;
    case 2:
    // DONE-TODO : add your **Registration** function
    registeration:
      registerMenu(u->name, u->password);
      // getting id
      if (isUserRegistered(u->name)) {
        system("clear");
        printf("\n\nUser already exists!\n");
        goto registeration;
      }
      RegisterUser(*u);
      // printf("\n\nUser registered successfully!\n");
      r = 1;
      break;
    case 3:
      exit(1);
      break;
    default:
      printf("Insert a valid operation!\n");
    }
  }
};

int main() {
  SetConsoleOutputCP(CP_UTF8);
  struct User u;

  initMenu(&u);
  mainMenu(u);
  return 0;
}
