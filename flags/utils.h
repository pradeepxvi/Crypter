// this file contain other important function....

#include <stdio.h>

#ifndef UTILS
#define UTILS

// color code
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"

#define CYAN "\033[36m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define GRAY "\033[90m"

// other stufffs
// -windows
// #define INPUT_SYMBOL ">_"
// #define SUCCESS_SYMBOL "* "
// #define ERROR_SYMBOL "!! "
// #define CLS "cls"

// -linux
#define INPUT_SYMBOL "❯"
#define SUCCESS_SYMBOL "✔ "
#define ERROR_SYMBOL "✘ "
#define CLS "clear"

#define CRYPTER "crypter"

#include "account.h"

// returns current date and time in string format
char *getCurrentDateTime();

// display menu
void displayIntro();
void displayUnAuthMenu();
void displayAdminMenu();
void displayMainMenu();
void displayAccountMenu();
void displayBankingMenu();
void displayLoanMenu();
void displayFilterDataMenu();

// this function displays balance information
void displayBalanceInfo(char *transaction, float currentBalance, float amount, float newBalance);

void prompt(char *username, char *message);

void errorMessage(char *message);
void successMessage(char *message);

#endif