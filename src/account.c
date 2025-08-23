#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "validator.h"
#include "utils.h"
#include "auth.h"

void Register()
{
    struct INFORMATION customer;

    printf("\n\nEnter details:");

    printf("\n\nFirst name >> ");
    scanf(" %[^\n]", customer.firstName);

    printf("\n\nLast name >> ");
    scanf(" %[^\n]", customer.lastName);

    do
    {
        printf("\n\nEmail >> ");
        scanf(" %[^\n]", customer.email);
    } while (!validateEmail(customer.email));

    printf("\n\nAddress >> ");
    scanf(" %[^\n]", customer.address);

    do
    {
        printf("\n\nContact >> ");
        scanf(" %[^\n]", customer.contact);
    } while (!validateContact(customer.contact));

    char check;
    printf("\nKeep the account number same as contact (y/n) >> ");
    scanf(" %c", &check);

    if (check == 'y' || check == 'Y')
    {
        strcpy(customer.accountNumber, customer.contact);
    }
    else
    {
        do
        {
            printf("\n\nAccount number >> ");
            scanf(" %[^\n]", customer.accountNumber);
        } while (!validateAccountNumber(customer.accountNumber));
    }

    do
    {
        printf("\n\nPassword >> ");
        scanf(" %[^\n]", customer.password);
    } while (!validatePassword(customer.password));

    customer.balance = 0.0;

    FILE *file = fopen("data/account.dat", "ab");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    fwrite(&customer, sizeof(customer), 1, file);
    fclose(file);

    printf("\nAccount created successfully!\n");
}

void readData()
{
    struct INFORMATION user = getAuthUser();

    printf("\n\n------------------------------------------");
    printf("\nName = %s %s", user.firstName, user.lastName);
    printf("\nEmail = %s", user.email);
    printf("\nAddress = %s", user.address);
    printf("\nContact number = %s", user.contact);
    printf("\nAccount number = %s", user.accountNumber);
    printf("\nPassword = %s", user.password);
    printf("\nBalance = %f", user.balance);
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
    remove("data/authenticated.dat");

    if (deleted)
    {
        remove("data/account.dat");
        rename("data/tempFile.dat", "data/account.dat");
        printf("\nAccount deleted successfully.");
    }
    else
    {
        printf("\nError while deleting account.");
        remove("data/tempFile.dat");
    }
}
