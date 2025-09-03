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

int adminAccess()
{

    char username[100];
    char password[100];

    printf("[admin] username : ");
    scanf(" %s", username);
    printf("[admin] password : ");
    scanf(" %s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        return 1;
    }
    printf("\nAdmin authentication failed");

    return 0;
}

void backupData()
{

    // account
    FILE *file = fopen("data/account.dat", "rb");
    FILE *backupFile = fopen("data/accountBackup.dat", "wb");

    if (file == NULL || backupFile == NULL)
    {
        printf("\n...Database Error !!!");
        if (file)
            fclose(file);
        if (backupFile)
            fclose(backupFile);
        return;
    }

    struct INFORMATION user;

    while (fread(&user, sizeof(user), 1, file))
    {
        fwrite(&user, sizeof(user), 1, backupFile);
    }

    fclose(file);
    fclose(backupFile);

    // statement

    file = fopen("data/statement.dat", "rb");
    backupFile = fopen("data/statementBackup.dat", "wb");

    if (!file || !backupFile)
    {
        printf("\n...Database Error !!!");
        if (file)
            fclose(file);
        if (backupFile)
            fclose(backupFile);
        return;
    }

    struct STATEMENT statement;

    while (fread(&statement, sizeof(statement), 1, file))
    {
        fwrite(&statement, sizeof(statement), 1, backupFile);
    }

    fclose(file);
    fclose(backupFile);

    // loan

    file = fopen("data/loan.dat", "rb");
    backupFile = fopen("data/loanBackup.dat", "wb");

    if (!file || !backupFile)
    {
        printf("\n...Database Error !!!");
        if (file)
            fclose(file);
        if (backupFile)
            fclose(backupFile);
        return;
    }

    struct LOAN loan;

    while (fread(&loan, sizeof(loan), 1, file))
    {
        fwrite(&loan, sizeof(loan), 1, backupFile);
    }

    fclose(file);
    fclose(backupFile);

    printf("\nBackup completed successfully.\n");
}

void restoreData()
{

    // account

    FILE *file = fopen("data/account.dat", "wb");
    FILE *restoreFile = fopen("data/accountBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        printf("\n...Database Error !!!");
        if (file)
            fclose(file);
        if (restoreFile)
            fclose(restoreFile);
        return;
    }

    struct INFORMATION user;

    while (fread(&user, sizeof(user), 1, restoreFile))
    {
        fwrite(&user, sizeof(user), 1, file);
    }

    fclose(file);
    fclose(restoreFile);

    // statement

    file = fopen("data/statement.dat", "wb");
    restoreFile = fopen("data/statementBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        printf("\n...Database Error !!!");
        if (file)
            fclose(file);
        if (restoreFile)
            fclose(restoreFile);
        return;
    }

    struct STATEMENT statement;

    while (fread(&statement, sizeof(statement), 1, restoreFile))
    {
        fwrite(&statement, sizeof(statement), 1, file);
    }

    fclose(file);
    fclose(restoreFile);

    // loan

    file = fopen("data/loan.dat", "wb");
    restoreFile = fopen("data/loanBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        printf("\n...Database Error !!!");
        if (file)
            fclose(file);
        if (restoreFile)
            fclose(restoreFile);
        return;
    }

    struct LOAN loan;

    while (fread(&loan, sizeof(loan), 1, restoreFile))
    {
        fwrite(&loan, sizeof(loan), 1, file);
    }

    fclose(file);
    fclose(restoreFile);

    printf("\n...Restore completed successfully.\n");
}

void showAllUserData()
{

    FILE *file = fopen("data/account.dat", "rb");

    if (file == NULL)
    {
        printf("\n...Database Error !!!");
        return;
    }

    struct INFORMATION user;

    while (fread(&user, sizeof(user), 1, file))
    {
        printf("\n\n------------------------------------------");
        printf("\n...Name           : %s %s", user.firstName, user.lastName);
        printf("\n...Email          : %s", user.email);
        printf("\n...Address        : %s", user.address);
        printf("\n...Contact number : %s", user.contact);
        printf("\n...Account number : %s", user.accountNumber);
        printf("\n...Balance        : $%.2f", user.balance);
        printf("\n...Date joined    : %s", user.dateJoined);
        printf("\n------------------------------------------");
    }
}

void showStatements()
{

    FILE *file = fopen("data/statement.dat", "rb");
    if (file == NULL)
    {
        printf("\n...Database Error !!!");
        return;
    }

    struct STATEMENT statement;
    while (fread(&statement, sizeof(statement), 1, file) == 1)
    {
        printf("\n[%s]", statement.date);
        printf(" | %s %s", statement.user.firstName, statement.user.lastName);
        printf(" | %s", statement.transaction);
        printf(" | Rs %.2f", statement.amount);
    }
    fclose(file);
}

void deleteStatements()
{
    char confirmation;
    printf("\nAre you sure [y/n] > _ ");
    scanf(" %c", &confirmation);

    if (tolower(confirmation) != 'y')
    {
        printf("\n...Operation aborted !!!");
        return;
    }
    remove("data/statement.dat");
    printf("\n...Statement deleted successfully");
}

void showLoans()
{

    FILE *file = fopen("data/loan.dat", "rb");
    if (file == NULL)
    {
        printf("\n...Database Error !!!");
        return;
    }

    struct LOAN loan;
    while (fread(&loan, sizeof(loan), 1, file))
    {
        printf("\n\n------------------------------------------");
        printf("\n...User         : %s %s", loan.user.firstName, loan.user.lastName);
        printf("\n...Loan Id      : %s", loan.id);
        printf("\n...Loan Balance : $%.2f", loan.loanBalance);
        printf("\n...Annual Rate  : %.1f%%", loan.rate);
        printf("\n...Monthly Emi  : $%.2f", loan.emi);
        printf("\n------------------------------------------");
    }
    fclose(file);
}
