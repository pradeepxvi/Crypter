#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
        errorMessage("Database Error");
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
        errorMessage("Database Error");
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
    {
        errorMessage("You are already in loan");
        return;
    }

    struct INFORMATION authUser = getAuthUser();
    struct LOAN loan;

    strcpy(loan.id, authUser.accountNumber);

    while (1)
    {
        prompt(authUser.firstName, "Enter amount");
        scanf(" %f", &loan.principle);

        if (loan.principle < 100000 || loan.principle > 10000000)
        {
            errorMessage("Loan can be applied between 1,00,000 and  1,00,00,000");
            continue;
        }
        break;
    }

    loan.rate = 5.0f;

    while (1)
    {
        prompt(authUser.firstName, "Duration in month");
        scanf(" %d", &loan.duration);

        if (loan.duration < 6 || loan.duration > 120)
        {
            errorMessage("Loan can be applied 6 to 120 months");
            continue;
        }
        break;
    }

    loan.emi = emiCalculator(loan.rate, loan.principle, loan.duration);

    printf(GREEN BOLD);
    printf("\nAnnual Interest rate : 5%%");
    printf("\nMonthly emi : %.2f\n", loan.emi);
    printf(RESET);

    loan.loanBalance = loan.principle;
    loan.user = authUser;
    loan.inLoan = 1;

    strcpy(loan.issueDate, getCurrentDateTime());

    char confirmation;
    prompt(authUser.firstName, "Confirm loan application [y/n]");
    scanf(" %c", &confirmation);

    if (tolower(confirmation) != 'y')
    {
        errorMessage("Operation aborted");
        return;
    }

    FILE *file = fopen("data/loan.dat", "ab");
    if (file == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    fwrite(&loan, sizeof(loan), 1, file);
    fclose(file);

    authUser.balance += loan.principle;
    saveAuthUser(authUser);
    saveUser(authUser);

    saveStatement("loan_issue", loan.principle, loan.user);
    displayBalanceInfo("Loan issued", authUser.balance - loan.principle, loan.principle, authUser.balance);
}

void showUserLoan()
{

    if (!isLoaned())
    {
        successMessage("You are not in loan");
        return;
    }

    struct INFORMATION authUser = getAuthUser();
    struct LOAN loan = getLoan(authUser.accountNumber);

    printf("\n------------------------------------------");
    printf(GREEN BOLD);
    printf("\nLoan Id     : %s", loan.id);
    printf("\nLoan Balance: $%.2f", loan.loanBalance);
    printf("\nAnnual Rate : %.1f%%", loan.rate);
    printf("\nMonthly Emi : $%.2f", loan.emi);
    printf("\nIssued Date : %s", loan.issueDate);
    printf(RESET);
    printf("\n------------------------------------------");
}

void payEmi()
{

    if (!isLoaned())
    {
        successMessage("You are not in loan");
        return;
    }

    struct INFORMATION authUser = getAuthUser();
    struct LOAN currentUserLoan = getLoan(authUser.accountNumber);

    if (authUser.balance < currentUserLoan.emi)
    {
        errorMessage("Insufficient balance");
        return;
    }

    char confirmation;

    printf(GREEN BOLD);
    printf("\nEmi amount : %.2f", currentUserLoan.emi);
    printf(RESET);

    prompt(authUser.firstName, "Confirm Payment? [y/n]");
    scanf(" %c", &confirmation);

    if (tolower(confirmation) != 'y')
    {
        errorMessage("Operation aborted");
        return;
    }

    float emi = currentUserLoan.emi;
    authUser.balance -= emi;
    currentUserLoan.loanBalance -= emi;

    saveAuthUser(authUser);
    saveUser(authUser);
    saveLoan(currentUserLoan);
    saveStatement("loan_emi_paid", currentUserLoan.emi, currentUserLoan.user);
    displayBalanceInfo("Emi paid", authUser.balance + emi, emi, authUser.balance);
}

void comlpeteLoan()
{

    if (!isLoaned())
    {
        successMessage("You are not in loan");
        return;
    }

    struct INFORMATION authUser = getAuthUser();
    struct LOAN tempLoan = getLoan(authUser.accountNumber);
    struct LOAN loan;

    if (authUser.balance < tempLoan.loanBalance)
    {
        errorMessage("Insufficient amount");
        return;
    }

    FILE *file = fopen("data/loan.dat", "rb");
    FILE *tempFile = fopen("data/tempFile.dat", "wb");

    if (file == NULL || tempFile == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    showUserLoan();

    char confirmation;
    prompt(authUser.firstName, "Confirm Payment? [y/n]");
    scanf(" %c", &confirmation);

    if (tolower(confirmation) != 'y')
    {
        errorMessage("Operation aborted");
        return;
    }

    int paid = 0;
    while (fread(&loan, sizeof(loan), 1, file))
    {
        if (strcmp(loan.id, authUser.accountNumber) == 0)
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

    if (paid)
    {
        authUser.balance -= tempLoan.loanBalance;

        saveAuthUser(authUser);
        saveUser(authUser);

        saveStatement("loan_paid", loan.loanBalance, loan.user);
        successMessage("Loan paid successfully");
        displayBalanceInfo("Loan paid", authUser.balance + tempLoan.loanBalance, tempLoan.loanBalance, authUser.balance);

        remove("data/loan.dat");
        rename("data/tempFile.dat", "data/loan.dat");
    }
    else
    {
        errorMessage("Error occur");
        remove("data/tempFile.dat");
    }
}