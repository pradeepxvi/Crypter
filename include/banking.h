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

void saveStatement(struct STATEMENT statement);
struct STATEMENT getStatement();

void deposit();
void withdraw();

void readAllStatement();
#endif