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
#include "validator.h"

void Register()
{
    struct INFORMATION user;
    strcpy(user.dateJoined, getCurrentDateTime());

    printf("\n\n...Enter details:");

    printf("\n\n...First name > _");
    scanf(" %[^\n]", user.firstName);

    printf("\n\n...Last name > _");
    scanf(" %[^\n]", user.lastName);

    do
    {
        printf("\n\n...Email > _");
        scanf(" %[^\n]", user.email);
    } while (!validateEmail(user.email));

    printf("\n\n...Address > _");
    scanf(" %[^\n]", user.address);

    do
    {
        printf("\n\n...Contact > _");
        scanf(" %[^\n]", user.contact);
    } while (!validateContact(user.contact));

    char check;
    printf("\n...Keep the account number same as contact (y/n) > _");
    scanf(" %c", &check);

    if (check == 'y' || check == 'Y')
    {
        strcpy(user.accountNumber, user.contact);
    }
    else
    {
        do
        {
            printf("\n\n...Account number > _");
            scanf(" %[^\n]", user.accountNumber);
        } while (!validateAccountNumber(user.accountNumber));
    }

    do
    {
        printf("\n\nPassword > _");
        scanf(" %[^\n]", user.password);
    } while (!validatePassword(user.password));

    user.balance = 0.0;

    FILE *file = fopen("data/account.dat", "ab");
    if (file == NULL)
    {
        printf("...Error opening file !!!");
        return;
    }

    fwrite(&user, sizeof(user), 1, file);
    fclose(file);

    printf("\n...Account created successfully\n");
}

void readData()
{
    struct INFORMATION user = getAuthUser();

    printf("\n\n------------------------------------------");
    printf("\nName           : %s %s", user.firstName, user.lastName);
    printf("\nEmail          : %s", user.email);
    printf("\nAddress        : %s", user.address);
    printf("\nContact number : %s", user.contact);
    printf("\nAccount number : %s", user.accountNumber);
    printf("\nPassword       : %s", user.password);
    printf("\nBalance        : %.2f", user.balance);
    printf("\nDate joined    : %s", user.dateJoined);
    printf("\n------------------------------------------");
}

void deleteAccount()
{
    char confirmation;
    printf("\nAre you sure (y/n) > _ ");
    scanf(" %c", &confirmation);

    if (confirmation != 'y' && confirmation != 'Y')
    {
        printf("\nOperation aborted");
        return;
    }

    // clear information
    FILE *file = fopen("data/account.dat", "rb");
    FILE *tempFile = fopen("data/tempFile.dat", "wb");

    if (!file || !tempFile)
    {
        perror("\nError opening file");
        return;
    }

    struct INFORMATION user;
    struct INFORMATION authUser = getAuthUser();

    int deleted = 0;

    while (fread(&user, sizeof(user), 1, file))
    {
        if (
            strcmp(user.accountNumber, authUser.accountNumber) == 0 &&
            strcmp(user.contact, authUser.contact) == 0 &&
            strcmp(user.email, authUser.email) == 0 &&
            strcmp(user.password, authUser.password) == 0)
        {
            deleted = 1;
        }
        else
        {
            fwrite(&user, sizeof(user), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (deleted)
    {
        remove("data/account.dat");
        rename("data/tempFile.dat", "data/account.dat");
    }
    else
    {
        printf("\nError while deleting account.");
        remove("data/tempFile.dat");
    }

    // clear loans
    file = fopen("data/loan.dat", "rb");
    tempFile = fopen("data/tempFile.dat", "wb");

    if (!file || !tempFile)
    {
        perror("\nError opening file");
        return;
    }

    struct LOAN loan;

    deleted = 0;

    while (fread(&loan, sizeof(loan), 1, file))
    {
        if (
            strcmp(loan.user.accountNumber, authUser.accountNumber) == 0)
        {
            deleted = 1;
        }
        else
        {
            fwrite(&loan, sizeof(loan), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (deleted)
    {
        backup();
        remove("data/loan.dat");
        rename("data/tempFile.dat", "data/loan.dat");
    }
    else
    {
        printf("\nError while deleting account.");
        remove("data/tempFile.dat");
    }

    // clear statement
    file = fopen("data/statement.dat", "rb");
    tempFile = fopen("data/tempFile.dat", "wb");

    if (!file || !tempFile)
    {
        perror("\nError opening file");
        return;
    }

    struct STATEMENT statement;

    deleted = 0;

    while (fread(&statement, sizeof(statement), 1, file))
    {
        if (
            strcmp(statement.user.accountNumber, authUser.accountNumber) == 0)
        {
            deleted = 1;
        }
        else
        {
            fwrite(&statement, sizeof(statement), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (deleted)
    {
        backup();
        remove("data/statement.dat");
        rename("data/tempFile.dat", "data/statement.dat");
    }
    else
    {
        printf("\nError while deleting account.");
        remove("data/tempFile.dat");
    }

    remove("data/authenticated.dat");
}
