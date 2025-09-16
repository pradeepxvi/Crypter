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
        errorMessage("Email is too short");
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
        errorMessage("Email must contain @");
        return 0;
    }

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database error");
        return 0;
    }

    struct INFORMATION temp;
    while (fread(&temp, sizeof(temp), 1, file))
    {
        if (strcmp(email, temp.email) == 0)
        {
            errorMessage("Email already exists");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int validatePassword(char *password)
{
    char confirmPassword[250];

    if (strlen(password) < 8)
    {
        errorMessage("Password is too short");
        return 0;
    }

    prompt("crypter", "Confirm password");
    system("stty -echo");
    scanf(" %[^\n]", confirmPassword);
    system("stty echo");

    if (strcmp(password, confirmPassword) != 0)
    {
        errorMessage("Password must match");
        return 0;
    }
    return 1;
}

int validateContact(char *contact)
{
    if (strlen(contact) != 10)
    {
        errorMessage("Enter 10 digit contact");

        return 0;
    }

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database error");
        return 1;
    }

    struct INFORMATION temp;
    while (fread(&temp, sizeof(temp), 1, file))
    {
        if (strcmp(contact, temp.contact) == 0)
        {
            errorMessage("Contact already exists");
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
        errorMessage("Enter 10 digit account number");
        return 0;
    }

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database error");
        return 1;
    }

    struct INFORMATION temp;
    while (fread(&temp, sizeof(temp), 1, file))
    {
        if (strcmp(accountNumber, temp.accountNumber) == 0)
        {
            errorMessage("Account number already exists");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
