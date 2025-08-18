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
struct STATEMENT getStatement()
{
    struct STATEMENT statement;
    FILE *file = fopen("data/statement.dat", "rb");
    fread(&statement, sizeof(statement), 1, file);
    fclose(file);
    return statement;
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
        printf("Invalid amount. Deposit must be greater than 100.\n");
        return;
    }

    struct INFORMATION user;

    FILE *file = fopen("data/account.dat", "rb+");
    if (file == NULL)
    {
        perror("Error opening account file");
        return;
    }

    while (fread(&user, sizeof(user), 1, file) == 1)
    {
        if (strcmp(user.accountNumber, authUser.accountNumber) == 0)
        {

            struct STATEMENT statement;
            strcpy(statement.date, getCurrentDateTime());
            strcpy(statement.transaction, "deposit");
            statement.amount = amount;
            statement.user = authUser;
            saveStatement(statement);

            user.balance += amount;
            fseek(file, -sizeof(user), SEEK_CUR);
            fwrite(&user, sizeof(user), 1, file);
            saveAuthUser(user);
            break;
        }
    }
    fclose(file);
};

void withdraw()
{
    struct INFORMATION authUser = getAuthUser();

    float amount;
    printf("\n\n[%s %s]", authUser.firstName, authUser.lastName);
    printf(" amount > _");
    scanf(" %f", &amount);

    if (amount > authUser.balance)
    {
        printf("Out of balance");
        return;
    }

    struct INFORMATION user;

    FILE *file = fopen("data/account.dat", "rb+");
    if (file == NULL)
    {
        perror("Error opening account file");
        return;
    }

    while (fread(&user, sizeof(user), 1, file) == 1)
    {
        if (strcmp(user.accountNumber, authUser.accountNumber) == 0)
        {
            struct STATEMENT statement;
            strcpy(statement.date, getCurrentDateTime());
            strcpy(statement.transaction, "withdraw");
            statement.amount = amount;
            statement.user = authUser;
            saveStatement(statement);

            fseek(file, -sizeof(user), SEEK_CUR);
            user.balance -= amount;
            fwrite(&user, sizeof(user), 1, file);
            saveAuthUser(user);
            break;
        }
    }
    fclose(file);
};

void readAllStatement()
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