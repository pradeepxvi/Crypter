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

void saveStatement(char *type, float amount, struct INFORMATION user)
{
    struct STATEMENT statement;

    strcpy(statement.date, getCurrentDateTime());
    strcpy(statement.transaction, type);
    statement.amount = amount;
    statement.user = user;

    FILE *file = fopen("data/statement.dat", "ab");
    if (file == NULL)
    {
        errorMessage("Database error");
        return;
    }

    fwrite(&statement, sizeof(statement), 1, file);
    fclose(file);
}

void deposit()
{
    struct INFORMATION authUser = getAuthUser();

    float amount;

    prompt(authUser.firstName, "Amount");
    scanf(" %f", &amount);

    if (amount <= 100 || amount > 100000)
    {
        errorMessage("Deposit $100 to $100000");
        return;
    }

    authUser.balance += amount;

    saveAuthUser(authUser);
    saveUser(authUser);

    saveStatement("deposit", amount, authUser);
    displayBalanceInfo("Deposited", authUser.balance - amount, amount, authUser.balance);
}

void withdraw()
{
    struct INFORMATION authUser = getAuthUser();

    float amount;

    prompt(authUser.firstName, "Amount");
    scanf(" %f", &amount);

    if (amount > authUser.balance)
    {
        errorMessage("Out of balance");
        return;
    }

    if (amount > 100000)
    {
        errorMessage("Withdraw $100 to $100000");
        return;
    }

    authUser.balance -= amount;

    saveAuthUser(authUser);
    saveUser(authUser);

    saveStatement("withdraw", amount, authUser);
    displayBalanceInfo("Withdrew", authUser.balance + amount, amount, authUser.balance);
};

void transferBalance()
{
    struct INFORMATION sender = getAuthUser();

    char accountNumber[100];

    prompt(sender.firstName, "Account number");
    scanf(" %[^\n]", accountNumber);

    if (strcmp(accountNumber, sender.accountNumber) == 0)
    {
        errorMessage("Cannot transfer to own");
        return;
    }

    struct INFORMATION receiver = getUser(accountNumber);
    if (strlen(receiver.accountNumber) == 0)
    {
        errorMessage("User not found");
        return;
    }

    printf(GREEN BOLD);
    printf("\nReceiver Details");
    printf("\nName           : %s %s", receiver.firstName, receiver.lastName);
    printf("\nContact number : %s", receiver.contact);
    printf("\nAccount number : %s\n", receiver.accountNumber);
    printf(RESET);

    char confirmation;
    prompt(sender.firstName, "Confirm account ? [y/n]");
    scanf(" %c", &confirmation);

    if (tolower(confirmation) != 'y')
    {
        errorMessage("Operation cancelled by user");
        return;
    }

    float amount;
    prompt(sender.firstName, "Amount");
    scanf(" %f", &amount);

    if (amount > sender.balance)
    {
        errorMessage("Out of balance");
        return;
    }

    if (amount < 1000 || amount > 10000)
    {
        errorMessage("Transfer $1000 to $100000");
        return;
    }

    sender.balance -= amount;
    receiver.balance += amount;

    successMessage("Transfer successful");

    saveAuthUser(sender);
    saveUser(sender);
    saveUser(receiver);
    saveStatement("trasfer", amount, sender);
    displayBalanceInfo("Transferred", sender.balance + amount, amount, sender.balance);
}

void showUserStatements()
{

    FILE *file = fopen("data/statement.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    struct INFORMATION authUser = getAuthUser();
    struct STATEMENT statement;

    while (fread(&statement, sizeof(statement), 1, file))
    {
        if (strcmp(authUser.accountNumber, statement.user.accountNumber) == 0)
        {
            printf(GREEN BOLD);
            printf("\n[%s]", statement.date);
            printf(" | %s %s", statement.user.firstName, statement.user.lastName);
            printf(" | %s", statement.transaction);
            printf(" | Rs %.2f", statement.amount);
            printf(RESET);
        }
    }

    fclose(file);
}