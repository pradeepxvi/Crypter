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

void saveStatement(char *date, char *type, float amount, struct INFORMATION user)
{
    struct STATEMENT statement;
    strcpy(statement.date, date);
    statement.amount = amount;
    statement.user = user;
    strcpy(statement.transaction, type);

    FILE *file = fopen("data/statement.dat", "ab");
    fwrite(&statement, sizeof(statement), 1, file);
    fclose(file);
}

void deposit()
{
    struct INFORMATION authUser = getAuthUser();

    float amount;
    printf("\n\n[%s %s]", authUser.firstName, authUser.lastName);
    printf(" amount > _");
    scanf(" %f", &amount);

    if (amount <= 100)
    {
        printf("\n...Invalid amount. Deposit must be greater than 100 !!!");
        return;
    }

    saveStatement(getCurrentDateTime(), "deposite", amount, getAuthUser());

    struct INFORMATION user = getUser(authUser.accountNumber);
    authUser.balance += amount;
    saveAuthUser(authUser);
    saveUser(authUser);
}

void withdraw()
{
    struct INFORMATION authUser = getAuthUser();

    float amount;
    printf("\n\n[%s %s]", authUser.firstName, authUser.lastName);
    printf(" amount > _");
    scanf(" %f", &amount);

    if (amount > authUser.balance)
    {
        printf("\n...Out of balance !!!");
        return;
    }

    struct INFORMATION user = getUser(authUser.accountNumber);
    authUser.balance -= amount;
    saveAuthUser(authUser);
    saveUser(authUser);

    struct STATEMENT statement;
    statement.amount = amount;
    strcpy(statement.date, getCurrentDateTime());
    strcpy(statement.transaction, "withdraw");
    statement.user = getAuthUser();

    saveStatement(getCurrentDateTime(), "withdraw", amount, getAuthUser());
};

void showUserStatements()
{
    struct INFORMATION authUser = getAuthUser();

    struct STATEMENT statement;
    FILE *file = fopen("data/statement.dat", "rb");

    while (fread(&statement, sizeof(statement), 1, file) == 1)
    {
        if (strcmp(authUser.accountNumber, statement.user.accountNumber) == 0)
        {
            printf("\n[%s]", statement.date);
            printf(" | %s %s", statement.user.firstName, statement.user.lastName);
            printf(" | %s", statement.transaction);
            printf(" | Rs %.2f", statement.amount);
        }
    }

    fclose(file);
}