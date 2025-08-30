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

char *getCurrentDateTime()
{
    time_t tim = time(NULL);
    struct tm date = *localtime(&tim);

    static char dateTime[100]; // <-- static!
    sprintf(dateTime, "%.4d-%.2d-%.2d:%2d-%.2d-%.2d",
            date.tm_year + 1900,
            date.tm_mon + 1,
            date.tm_mday,
            date.tm_hour,
            date.tm_min,
            date.tm_sec);

    return dateTime;
}

void displayIntro()
{
    system("clear");
    FILE *file = fopen("data/intro.txt", "r");

    if (file == NULL)
    {
        perror("Error opening intro file");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(file);
}

void displayUnAuthMenu()
{
    printf("\n");
    printf("\n[1] Login");
    printf("\n[2] Register");
    printf("\n[3] Admin Access");
    printf("\n[0] Exit");
    printf("\n\n > _");
}

void displayMainMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[1] Account");
    printf("\n[2] Banking");
    printf("\n[3] Loan");
    printf("\n[0] Logout");
    printf("\n\n[%s %s]", authUser.firstName, authUser.lastName);
    printf(" > _");
}

void displayFilterDataMenu()
{
    printf("\n");
    printf("\n[1] Email");
    printf("\n[0] Exit");
    printf("\n\n> _");
}

void displayAdminMenu()
{
    printf("\n");
    printf("\n[1] Backup");
    printf("\n[2] Restore");
    printf("\n[3] Get all data");
    printf("\n[4] Read all statement");
    printf("\n[5] Delete all statement");
    printf("\n[6] Read all Loan Data");
    printf("\n[7] Filter statement");
    printf("\n[8] Filter data");
    printf("\n[0] Exit");
    printf("\n\n[admin] > _");
}

void displayAccountMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[1] Get Account Info");
    printf("\n[2] Delete Account");
    printf("\n[0] Back");
    printf("\n\n[%s %s]", authUser.firstName, authUser.lastName);
    printf(" > _");
}

void displayBankingMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[1] Deposit");
    printf("\n[2] Withdraw");
    printf("\n[3] See statement");
    printf("\n[0] Back");
    printf("\n\n[%s %s]", authUser.firstName, authUser.lastName);
    printf(" > _");
}

void displayLoanMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[1] Request Loan");
    printf("\n[2] Pay Emi");
    printf("\n[3] Complete loan");
    printf("\n[4] Get Loan info");
    printf("\n[0] Back");
    printf("\n\n[%s %s]", authUser.firstName, authUser.lastName);
    printf(" > _");
}
