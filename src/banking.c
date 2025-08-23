#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "account.h"
#include "auth.h"
#include "admin.h"
#include "banking.h"

void saveStatement(struct STATEMENT statement)
{

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
};

void readStatement()
{
    struct INFORMATION authUser = getAuthUser();

    struct STATEMENT statement;
    FILE *file = fopen("data/statement.dat", "rb");

    while (fread(&statement, sizeof(statement), 1, file) == 1)
    {
        if (strcmp(authUser.accountNumber, statement.user.accountNumber) == 0)
        {
            printf("\n[%s]", statement.date);
            printf(" - %s %s", statement.user.firstName, statement.user.lastName);
            printf(" - %s", statement.transaction);
            printf(" - Rs %.2f", statement.amount);
        }
    }

    fclose(file);
}