#include <stdio.h>
#include <ctype.h>
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
        printf("\n...Database Error !!!");
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
    printf("\n[ 1 ] LOGIN");
    printf("\n[ 2 ] REGISTER");
    printf("\n[ 3 ] ADMIN ACCESS");
    printf("\n[ 0 ] EXIT");
    printf("\n");
    prompt("CRYPTER", "");
}

void displayMainMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[ 1 ] ACCOUNT MANAGEMENT");
    printf("\n[ 2 ] BANKING SERVICES");
    printf("\n[ 3 ] LOAN SERVICES");
    printf("\n[ 0 ] LOGOUT");
    printf("\n");
    prompt(authUser.firstName, "");
}

void displayFilterDataMenu()
{
    printf("\n");
    printf("\n[ 1 ] FILTER BY EMAIL");
    printf("\n[ 2 ] SORT BALANCE LOW TO HIGH");
    printf("\n[ 3 ] SORT BALANCE HIGH TO LOW");
    printf("\n[ 0 ] RETURN");
    printf("\n");
    prompt("crypter", "");
}

void displayAdminMenu()
{
    printf("\n");
    printf("\n[ 1 ] BACKUP DATA");
    printf("\n[ 2 ] RESTORE DATA");
    printf("\n[ 3 ] VIEW ALL USER DATA");
    printf("\n[ 4 ] READ ALL TRANSACTIONS");
    printf("\n[ 5 ] DELETE ALL TRANSACTIONS");
    printf("\n[ 6 ] VIEW ALL LOAN DATA");
    printf("\n[ 7 ] FILTER TRANSACTIONS");
    printf("\n[ 8 ] FILTER USER DATA");
    printf("\n[ 0 ] EXIT");
    printf("\n");
    prompt("ADMIN", "");
}

void displayAccountMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[ 1 ] VIEW ACCOUNT INFORMATION");
    printf("\n[ 2 ] DELETE ACCOUNT");
    printf("\n[ 0 ] RETURN");
    printf("\n");
    prompt(authUser.firstName, "");
}

void displayBankingMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[ 1 ] DEPOSIT FUNDS");
    printf("\n[ 2 ] WITHDRAW FUNDS");
    printf("\n[ 3 ] VIEW STATEMENT");
    printf("\n[ 4 ] TRANSFER FUNDS");
    printf("\n[ 0 ] RETURN");
    printf("\n");
    prompt(authUser.firstName, "");
}

void displayLoanMenu()
{
    struct INFORMATION authUser = getAuthUser();

    printf("\n");
    printf("\n[ 1 ] REQUEST LOAN");
    printf("\n[ 2 ] PAY EMI");
    printf("\n[ 3 ] COMPLETE LOAN");
    printf("\n[ 4 ] VIEW LOAN INFORMATION");
    printf("\n[ 0 ] RETURN");
    printf("\n");
    prompt(authUser.firstName, "");
}

void displayBalanceInfo(char *transaction, float currentBalance, float amount, float newBalance)
{
    printf(GREEN BOLD);
    printf("\n%-20s : $%.2f", "Current Balance", currentBalance);
    printf("\n%-20s : $%.2f", transaction, amount);
    printf("\n%-20s : $%.2f", "New Balance", newBalance);
    printf(RESET);
}

char *makeCapital(char *text)
{
    int len = strlen(text);
    char *newText = malloc(len);

    for (int i = 0; i < len; i++)
    {
        newText[i] = toupper(text[i]);
    }
    return newText;
}

void prompt(char *username, char *message)
{
    printf("\n[ %s%s%s%s ] %s %s ", BLUE, BOLD, makeCapital(username), RESET, message, INPUT_SYMBOL);
}

void errorMessage(char *message)
{
    printf("\n%s%s%s%s%s\n", YELLOW, ERROR_YMBOL, BOLD, message, RESET);
}

void successMessage(char *message)
{
    printf("\n%s%s%s%s%s\n", GREEN, SUCCESS_SYMBOL, BOLD, message, RESET);
}