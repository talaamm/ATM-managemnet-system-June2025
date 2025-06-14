#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif
#include "header.h"

char *USERS = "../data/users.txt";

void loginMenu(char a[50], char pass[50]) {
  // system("clear");
  printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
  scanf("%s", a);

#ifdef _WIN32
  printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
  int i = 0;
  char ch;
  while ((ch = _getch()) != '\r' && i < 49) { // Enter key
    if (ch == '\b' && i > 0) {                // Backspace
      i--;
      printf("\b \b");
    } else if (ch != '\b') {
      pass[i++] = ch;
      printf("*");
    }
  }
  pass[i] = '\0';
  printf("\n");
#else
  struct termios oflags, nflags;
  // disabling echo
  tcgetattr(fileno(stdin), &oflags);
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;
  nflags.c_lflag |= ECHONL;

  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
    perror("tcsetattr");
    exit(1);
  }
  printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
  scanf("%s", pass);

  // restore terminal
  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
    perror("tcsetattr");
    exit(1);
  }
#endif
}

// void loginMenu(char a[50], char pass[50])
// {
//     struct termios oflags, nflags;

//     system("clear");
//     printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User
//     Login:"); scanf("%s", a);

//     // disabling echo
//     tcgetattr(fileno(stdin), &oflags);
//     nflags = oflags;
//     nflags.c_lflag &= ~ECHO;
//     nflags.c_lflag |= ECHONL;

//     if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
//     {
//         perror("tcsetattr");
//         return exit(1);
//     }
//     printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
//     scanf("%s", pass);

//     // restore terminal
//     if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
//     {
//         perror("tcsetattr");
//         return exit(1);
//     }
// };

const char *getPassword(struct User u) {
  FILE *fp;
  struct User userChecker;

  if ((fp = fopen("../data/users.txt", "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  // printf("file opened now reading\n");
  while (fscanf(fp, "%d %s %s", &userChecker.id, &userChecker.name,
                &userChecker.password) != EOF) {
    // printf("read data %s %s \n", userChecker.password, userChecker.name);
    if (strcmp(userChecker.name, u.name) == 0) {
      fclose(fp);
      char *buff = userChecker.password;
      return buff;
    }
  }

  fclose(fp);
  return "no user found";
}

void registerMenu(char a[50], char pass[50]) {
  system("clear");
  printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Register:");
  scanf("%s", a);
#ifdef _WIN32
  printf("\n\n\n\n\n\t\t\t\tEnter the password to register:");
  int i = 0;
  char ch;
  while ((ch = _getch()) != '\r' && i < 49) { // Enter key
    if (ch == '\b' && i > 0) {                // Backspace
      i--;
      printf("\b \b");
    } else if (ch != '\b') {
      pass[i++] = ch;
      printf("*");
    }
  }
  pass[i] = '\0';
  printf("\n");
#else
  struct termios oflags, nflags;
  // disabling echo
  tcgetattr(fileno(stdin), &oflags);
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;
  nflags.c_lflag |= ECHONL;
  if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
    perror("tcsetattr");
    exit(1);
  }
  printf("\n\n\n\n\n\t\t\t\tEnter the password to register:");
  scanf("%s", pass);
  // restore terminal
  if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
    perror("tcsetattr");
    exit(1);
  }
#endif
}

int getNextUserId() {
  FILE *fp = fopen(USERS, "r");
  if (!fp) {
    printf("Error opening users file!\n");
    return -1;
  }

  int maxId = 0;
  struct User user;
  while (fscanf(fp, "%d %s %s", &user.id, &user.name, &user.password) != EOF) {
    if (user.id > maxId)
      maxId = user.id;
  }

  fclose(fp);
  return maxId + 1;
}

void RegisterUser(struct User u) {
  FILE *fp = fopen(USERS, "a");
  if (!fp) {
    printf("Error opening users file!\n");
    return;
  }

  u.id = getNextUserId();
  // printf("%d" , u.id);
  fprintf(fp, "%d %s %s\n", u.id, u.name, u.password);
  fclose(fp);

  printf("\n✔️  User registered successfully!\n");
}

void getUserId(int *id, char name[50]) {
  FILE *fp = fopen(USERS, "r");
  if (!fp) {
    printf("Error opening users file!\n");
    return;
  }

  struct User user;
  while (fscanf(fp, "%d %s %s", &user.id, &user.name, &user.password) != EOF) {
    if (strcmp(user.name, name) == 0)
      *id = user.id;
  }

  fclose(fp);
}