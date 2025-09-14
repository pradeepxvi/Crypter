
// this file handle loan department likr lone issue, emi
#include <stdio.h>
#include "account.h"

#ifndef LOAN_
#define LOAN_

// structure to store loan data
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

// this function return a particular loan data with the help of loadID(account number)
struct LOAN getLoan(char *loadId);

// save loan in exact position
void saveLoan(struct LOAN loan);

// handle loan issue
void requestLoan();

// display user's loan information
void showUserLoan();

// handle emi payment
void payEmi();

// handle loan complete payment
void comlpeteLoan();

#endif