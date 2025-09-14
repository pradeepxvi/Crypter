// this header file contains the function that handles banking activities like
// deposit
// withdraw
// transfer
// handle statement

#include <stdio.h>
#include "account.h"

#ifndef BANKING
#define BANKING

// structure to store statament data
struct STATEMENT
{
    char date[100];
    char transaction[100];
    float amount;
    struct INFORMATION user;
};

// function to save statement
void saveStatement(char *type, float amount, struct INFORMATION user);

// handle deposit
void deposit();

// handle withdraw
void withdraw();

// handle transfer of balance
void transferBalance();

// displau user's statement
void showUserStatements();

#endif