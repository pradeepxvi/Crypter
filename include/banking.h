#include <stdio.h>
#include "account.h"

#ifndef BANKING
#define BANKING

struct STATEMENT
{
    char date[100];
    char transaction[100];
    float amount;
    struct INFORMATION user;
};

void saveStatement(char *date, char *type, float amount, struct INFORMATION user);

void deposit();
void withdraw();

void readStatement();
#endif