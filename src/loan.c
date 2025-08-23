#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "account.h"
#include "admin.h"
#include "auth.h"
#include "banking.h"
#include "loan.h"
#include "utils.h"

float emiCalculator(float rate, float principle, int duration)
{
    float monthlyRate = rate / (12 * 100.0);
    float emi = (principle * monthlyRate * pow(1 + monthlyRate, duration)) /
                (pow(1 + monthlyRate, duration) - 1);
    return emi;
}

int isLoaned()
{
    struct INFORMATION authUser = getAuthUser();
    struct LOAN tempLoan = getLoan(authUser.accountNumber);

    if (tempLoan.inLoan == 1)
    {
        printf("\n...You are already in loan !!!");
        return 1;
    }
    return 0;
}

struct LOAN getLoan(char *loadId)
{
    struct LOAN emptyLoan = {0};

    FILE *file = fopen("data/loan.dat", "rb+");
    if (file == NULL)
    {
        perror("\n...Error on database !!!");
        return emptyLoan;
    }

    struct LOAN loan;
    while (fread(&loan, sizeof(loan), 1, file))
    {
        if (strcmp(loan.id, loadId) == 0)
        {
            fclose(file);
            return loan;
        }
    }
    fclose(file);
    return emptyLoan;
}

void saveLoan(struct LOAN loan)
{
    struct LOAN tempLoan;

    FILE *loanFile = fopen("data/loan.dat", "rb+");
    if (loanFile == NULL)
    {
        perror("\n...Error on database !!!");
        return;
    }
    while (fread(&tempLoan, sizeof(tempLoan), 1, loanFile))
    {
        if (strcmp(tempLoan.id, loan.id) == 0)
        {
            fseek(loanFile, -sizeof(tempLoan), SEEK_CUR);
            fwrite(&loan, sizeof(loan), 1, loanFile);
            fclose(loanFile);
            return;
        }
    }
    fclose(loanFile);
}

void requestLoan()
{

    if (isLoaned())
        return;

    struct INFORMATION authUser = getAuthUser();
    struct LOAN loan;

    strcpy(loan.id, authUser.accountNumber);

    while (1)
    {
        printf("\nEnter amount > _");
        scanf(" %f", &loan.principle);

        if (loan.principle < 100000 || loan.principle > 10000000)
        {
            printf("\n...Loan can be applied between 1,00,000 and  1,00,00,000 !!!");
            continue;
        }
        break;
    }

    loan.rate = 5.0f;

    while (1)
    {
        printf("\nEnter duration > _");
        scanf(" %d", &loan.duration);

        if (loan.duration < 6 || loan.duration > 120)
        {
            printf("\n...Loan can be applied 6 to 120 months !!!");
            continue;
        }
        break;
    }

    loan.emi = emiCalculator(loan.rate, loan.principle, loan.duration);

    printf("\n\n... Annual Interest rate : 5%%");
    printf("\n... Monthly emi : %.2f", loan.emi);

    loan.loanBalance = loan.principle;
    loan.user = authUser;
    loan.inLoan = 1;

    strcpy(loan.issueDate, getCurrentDateTime());

    char confirmation;
    printf("\n\n...Confirm loan application (y/n) > _ ");
    scanf(" %c", &confirmation);

    if (confirmation != 'y' && confirmation != 'Y')
    {
        printf("\n...Operation aborted !!!");
        return;
    }

    FILE *file = fopen("data/loan.dat", "ab");

    if (!file)
    {
        perror("\n...Error on opening file !!!");
        return;
    }

    fwrite(&loan, sizeof(loan), 1, file);
    fclose(file);

    authUser.balance += loan.principle;
    saveAuthUser(authUser);
    saveUser(authUser);

    saveStatement(getCurrentDateTime(), "loan_issue          ", loan.principle, loan.user);
}

void getLoanInfo()
{

    struct INFORMATION authUser = getAuthUser();
    struct LOAN loan = getLoan(authUser.accountNumber);

    if (strcmp(loan.id, authUser.accountNumber) == 0)
    {
        printf("\n...Loan Id     : %s", loan.id);
        printf("\n...Balance     : $%.2f", loan.loanBalance);
        printf("\n...Annual Rate : %.1f%%", loan.rate);
        printf("\n...Monthly Emi : $%.2f", loan.emi);
        printf("\n...Issued Date : %s", loan.issueDate);
        return;
    }

    printf("\n...You have no any loan data");
}

void payEmi()
{
    struct INFORMATION authUser = getAuthUser();

    struct LOAN currentUserLoan = getLoan(authUser.accountNumber);

    if (authUser.balance < currentUserLoan.emi)
    {
        printf("\n...Insufficient balance !!!");
        printf("\n...Balance : %.2f", authUser.balance);
        return;
    }

    char confirmation;
    printf("\n...Emi amount : %.2f", currentUserLoan.emi);
    printf("\n...Confirm Payment? [y/n] > _ ");
    scanf(" %c", &confirmation);

    if (confirmation != 'y' && confirmation != 'Y')
    {
        printf("\n...Operation aborted !!!");
        return;
    }

    float emi = currentUserLoan.emi;
    authUser.balance -= emi;
    currentUserLoan.loanBalance -= emi;

    saveAuthUser(authUser);
    saveUser(authUser);
    saveLoan(currentUserLoan);

    saveStatement(getCurrentDateTime(), "loan_emi_paid       ", currentUserLoan.emi, currentUserLoan.user);

    printf("\n...Emi paid");
    printf("\n...Current balance : %.2f", authUser.balance);
    printf("\n...Current loan balance : %.2f", currentUserLoan.loanBalance);
}

void loanPaid()
{

    struct INFORMATION authUser = getAuthUser();
    struct LOAN tempLoan = getLoan(authUser.accountNumber);

    if (authUser.balance < tempLoan.loanBalance)
    {
        printf("\n...Insufficient amount !!!");
        return;
    }

    FILE *file = fopen("data/loan.dat", "rb");
    FILE *tempFile = fopen("data/tempFile.dat", "wb");
    FILE *authFile = fopen("data/authenticated.dat", "rb");

    if (!file || !tempFile || !authFile)
    {
        perror("\nError opening file");
        return;
    }

    struct LOAN loan;

    fread(&authUser, sizeof(authUser), 1, authFile);

    int paid = 0;

    while (fread(&loan, sizeof(loan), 1, file))
    {
        if (
            strcmp(loan.id, authUser.accountNumber) == 0)
        {
            paid = 1;
        }
        else
        {
            fwrite(&loan, sizeof(loan), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);
    fclose(authFile);

    if (paid)
    {
        authUser.balance -= tempLoan.loanBalance;

        saveAuthUser(authUser);
        saveUser(authUser);

        saveStatement(getCurrentDateTime(), "loan_paid           ", loan.loanBalance, loan.user);

        remove("data/loan.dat");
        rename("data/tempFile.dat", "data/loan.dat");
        printf("\n...Loan paid successfully.");
    }
    else
    {
        printf("\nError occur.");
        remove("data/tempFile.dat");
    }
}
