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

int validateEmail(char *email)
{
    if (strlen(email) < 15)
    {
        printf("Email too short");
        return 0;
    }

    int hasAtSymbol = 0;
    for (int i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            hasAtSymbol = 1;
            break;
        }
    }

    if (!hasAtSymbol)
    {
        printf("\nEnter a valid email address with '@'");
        return 0;
    }

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    struct INFORMATION temp;
    while (fread(&temp, sizeof(temp), 1, file))
    {
        if (strcmp(email, temp.email) == 0)
        {
            printf("\nUser with this email already exists");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int validatePassword(char *password)
{
    if (strlen(password) < 8)
    {
        printf("Password too short : %lu", strlen(password));
        return 0;
    }
    return 1;
}

int validateContact(char *contact)
{
    if (strlen(contact) != 10)
    {
        printf("\nEnter 10 digit contact number : %lu", strlen(contact));
        return 0;
    }

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    struct INFORMATION temp;
    while (fread(&temp, sizeof(temp), 1, file))
    {
        if (strcmp(contact, temp.contact) == 0)
        {
            printf("\nUser with this contact already exists");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int validateAccountNumber(char *accountNumber)
{
    int len = 10;
    if (strlen(accountNumber) != len)
    {
        printf("\nEnter %d digit account number : %lu", len, strlen(accountNumber));
        return 0;
    }

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    struct INFORMATION temp;
    while (fread(&temp, sizeof(temp), 1, file))
    {
        if (strcmp(accountNumber, temp.accountNumber) == 0)
        {
            printf("\nUser with this account number already exists");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
