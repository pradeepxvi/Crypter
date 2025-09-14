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

// authorize admin
int adminAccess()
{

    char username[100];
    char password[100];

    // ask for admin username
    prompt("admin", "Username");
    scanf(" %s", username);

    // ask for admin password
    prompt("admin", "Password");
    scanf(" %s", password);

    // check if admin id and password matched to "admin" and "admin" respectively or not
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        // if matched return 1
        return 1;
    }

    // if doesn't matched return 0
    printf("\nAdmin authentication failed");
    return 0;
}

void backupData()
{

    // open main file on read mode and backupFile in write mode
    // read all data from main file and write it to backupFile in loop

    // backup account information .........................
    FILE *file = fopen("data/account.dat", "rb");
    FILE *backupFile = fopen("data/accountBackup.dat", "wb");

    if (file == NULL || backupFile == NULL)
    {
        errorMessage("Database Error");
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

    // backup statement .........................
    file = fopen("data/statement.dat", "rb");
    backupFile = fopen("data/statementBackup.dat", "wb");

    if (!file || !backupFile)
    {
        errorMessage("Database Error");
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

    // backup load data .........................

    file = fopen("data/loan.dat", "rb");
    backupFile = fopen("data/loanBackup.dat", "wb");

    if (!file || !backupFile)
    {
        errorMessage("Database Error");
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

    successMessage("Backup completed successfully");
}

void restoreData()
{

    // open backupFile file on read mode and main file in write mode
    // read all data from  backupFile and write it to main file in loop

    // restore account information .........................

    FILE *file = fopen("data/account.dat", "wb");
    FILE *restoreFile = fopen("data/accountBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        errorMessage("Database Error");
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

    // restore statement .........................

    file = fopen("data/statement.dat", "wb");
    restoreFile = fopen("data/statementBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        errorMessage("Database Error");
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

    // restore loan data .........................

    file = fopen("data/loan.dat", "wb");
    restoreFile = fopen("data/loanBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        errorMessage("Database Error");
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

    successMessage("Restore completed successfully");
}

void showAllUserData()
{

    // open file, handle error in case
    FILE *file = fopen("data/account.dat", "rb");

    if (file == NULL)
    {
        printf("\n...Database Error !!!");
        return;
    }

    struct INFORMATION user;

    // read all data in loop and display
    while (fread(&user, sizeof(user), 1, file))
    {
        printf("\n\n------------------------------------------");
        printf(GREEN BOLD);
        printf("\n...Name           : %s %s", user.firstName, user.lastName);
        printf("\n...Email          : %s", user.email);
        printf("\n...Address        : %s", user.address);
        printf("\n...Contact number : %s", user.contact);
        printf("\n...Account number : %s", user.accountNumber);
        printf("\n...Balance        : $%.2f", user.balance);
        printf("\n...Date joined    : %s", user.dateJoined);
        printf(RESET);
        printf("\n------------------------------------------");
    }
}

void showStatements()
{
    // open file, handle error in case

    FILE *file = fopen("data/statement.dat", "rb");
    if (file == NULL)
    {
        printf("\n...Database Error !!!");
        return;
    }

    // read all statement and display in loop
    struct STATEMENT statement;
    while (fread(&statement, sizeof(statement), 1, file) == 1)
    {
        printf(GREEN BOLD);
        printf("\n[%s]", statement.date);
        printf(" | %s %s", statement.user.firstName, statement.user.lastName);
        printf(" | %s", statement.transaction);
        printf(" | Rs %.2f", statement.amount);
        printf(RESET);
    }
    fclose(file);
}

void deleteStatements()
{

    // confirm user to delete statements
    char confirmation;
    prompt("admin", "Are you sure [y/n]");
    scanf(" %c", &confirmation);

    // if user doesn't allows terminat the program
    if (tolower(confirmation) != 'y')
    {
        errorMessage("Operation aborted");
        return;
    }
    // if user allows delete statement.dat file
    remove("data/statement.dat");
    successMessage("Statement deleted successfully");
}

void showLoans()
{

    // open file, handle error in case
    FILE *file = fopen("data/loan.dat", "rb");
    if (file == NULL)
    {
        printf("\n...Database Error !!!");
        return;
    }

    // read all loan data and display in loop
    struct LOAN loan;
    while (fread(&loan, sizeof(loan), 1, file))
    {
        printf("\n\n------------------------------------------");
        printf(GREEN BOLD);
        printf("\n...User         : %s %s", loan.user.firstName, loan.user.lastName);
        printf("\n...Loan Id      : %s", loan.id);
        printf("\n...Loan Balance : $%.2f", loan.loanBalance);
        printf("\n...Annual Rate  : %.1f%%", loan.rate);
        printf("\n...Monthly Emi  : $%.2f", loan.emi);
        printf(RESET);
        printf("\n------------------------------------------");
    }
    fclose(file);
}
