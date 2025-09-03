#include <stdio.h>
#include "account.h"

#ifndef INTRO
#define INTRO

char *getCurrentDateTime();

void displayIntro();
void displayUnAuthMenu();
void displayAdminMenu();
void displayMainMenu();
void displayAccountMenu();
void displayBankingMenu();
void displayLoanMenu();
void displayBalanceInfo(char *transaction, float currentBalance, float amount, float newBalance);

void displayFilterDataMenu();

#endif