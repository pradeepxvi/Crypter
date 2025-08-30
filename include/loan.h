#include <stdio.h>
#include "account.h"

#ifndef LOAN_
#define LOAN_

struct LOAN
{
    char id[10];
    float principle;
    float rate;
    int duration;
    float emi;
    float loanBalance;
    struct INFORMATION user;
    int inLoan;
    char issueDate[100];
};

struct LOAN getLoan(char *loadId);
void saveLoan(struct LOAN loan);
void requestLoan();
void showUserLoan();
void payEmi();
void comlpeteLoan();

#endif