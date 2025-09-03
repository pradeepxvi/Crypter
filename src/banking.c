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

    if (amount <= 100 || amount > 100000)
    {
        printf("\n...Deposit $100 to $100000!!!");
        return;
    }

    authUser.balance += amount;

    saveAuthUser(authUser);
    saveUser(authUser);

    saveStatement(getCurrentDateTime(), "deposite", amount, authUser);
    displayBalanceInfo("...Deposited", authUser.balance - amount, amount, authUser.balance);
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

    if (amount > 100000)
    {
        printf("\n...Withdraw $100 to $ 100000!!!");
        return;
    }

    authUser.balance -= amount;

    saveAuthUser(authUser);
    saveUser(authUser);

    saveStatement(getCurrentDateTime(), "Withdrew", amount, authUser);
    displayBalanceInfo("...Withdrew", authUser.balance + amount, amount, authUser.balance);
};

void transferBalance()
{
    char accountNumber[100];
    printf("\nAccount number > _");
    scanf(" %[^\n]", accountNumber);

    struct INFORMATION sender = getAuthUser();

    if (strcmp(accountNumber, sender.accountNumber) == 0)
    {
        printf("\n...Cannot transfer to own !!!");
        return;
    }

    struct INFORMATION receiver = getUser(accountNumber);
    if (strlen(receiver.accountNumber) == 0)
    {
        printf("\n...User not found !!!");
        return;
    }

    printf("\n\n------------------------------------------");
    printf("\n...Receiver Details");
    printf("\n...Name           : %s %s", receiver.firstName, receiver.lastName);
    printf("\n...Contact number : %s", receiver.contact);
    printf("\n...Account number : %s", receiver.accountNumber);
    printf("\n------------------------------------------");

    char confirmation;
    printf("\n\nConfirm ? [y/n] > _");
    scanf(" %c", &confirmation);

    if (confirmation != 'y' && confirmation != 'Y')
    {
        printf("\n...Operation cancelled by user !!!");
        return;
    }

    float amount;
    printf("\n...amount > _");
    scanf(" %f", &amount);

    if (amount < 1000)
    {
        printf("\n...Transfer at least $1000 !!!");
        return;
    }

    if (amount > sender.balance)
    {
        printf("\n...Out of balance !!!");
        return;
    }

    sender.balance -= amount;
    receiver.balance += amount;

    printf("\n...$%.2f is successfully transferred to %s %s", amount, receiver.firstName, receiver.lastName);

    displayBalanceInfo("...Trasnferred", sender.balance + amount, amount, sender.balance);
    saveAuthUser(sender);
    saveUser(sender);
    saveUser(receiver);
    saveStatement(getCurrentDateTime(), "Trasfer", amount, sender);
}

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