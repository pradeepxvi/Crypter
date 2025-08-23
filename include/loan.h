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

float emiCalculator(float rate, float principle, int duration);
struct LOAN getLoan(char *loadId);
void saveLoan(struct LOAN loan);
void requestLoan();
void getLoanInfo();
void payEmi();
void loanPaid();

#endif