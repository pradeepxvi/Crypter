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

int login()
{
    char id[100];
    char password[100];

    prompt("crypter", "Email / account number");
    scanf(" %[^\n]", id);

    prompt("crypter", "Password");
    system("stty -echo");
    scanf(" %[^\n]", password);
    system("stty echo");

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database error");
        return 1;
    }

    struct INFORMATION user;
    int found = 0;

    while (fread(&user, sizeof(user), 1, file))
    {
        if (
            strcmp(id, user.email) == 0 ||
            strcmp(id, user.accountNumber) == 0 ||
            strcmp(id, user.contact) == 0)
        {
            found = 1;

            if (strcmp(password, user.password) == 0)
            {
                FILE *authFile = fopen("data/authenticated.dat", "wb");
                if (authFile == NULL)
                {
                    errorMessage("Database error");
                    if (file)
                        fclose(file);
                    if (authFile)
                        fclose(authFile);
                    return 1;
                }

                fwrite(&user, sizeof(user), 1, authFile);
                if (file)
                    fclose(file);
                if (authFile)
                    fclose(authFile);
                return 0;
            }
            errorMessage("Wrong password");
            break;
        }
    }

    if (found == 0)
    {
        errorMessage("User not found");
    }

    if (file)
        fclose(file);
    return 1;
}

void logout()
{
    remove("data/authenticated.dat");
    exit(0);
}

struct INFORMATION getAuthUser()
{

    struct INFORMATION emptyAuthUser = {0};
    FILE *file = fopen("data/authenticated.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database error");
        return emptyAuthUser;
    }

    struct INFORMATION authUser;
    fread(&authUser, sizeof(authUser), 1, file);
    fclose(file);
    return authUser;
}

struct INFORMATION getUser(char *accountNumber)
{
    struct INFORMATION emptyUser = {0};

    FILE *file = fopen("data/account.dat", "rb+");
    if (file == NULL)
    {
        errorMessage("Database error");
        return emptyUser;
    }

    struct INFORMATION user;
    while (fread(&user, sizeof(user), 1, file))
    {
        if (strcmp(user.accountNumber, accountNumber) == 0)
        {
            fclose(file);
            return user;
        }
    }
    fclose(file);
    return emptyUser;
}

void saveAuthUser(struct INFORMATION authUser)
{

    FILE *file = fopen("data/authenticated.dat", "wb");
    if (file == NULL)
    {
        errorMessage("Database error");
        return;
    }
    fwrite(&authUser, sizeof(authUser), 1, file);
    fclose(file);
}

void saveUser(struct INFORMATION user)
{
    struct INFORMATION tempUser;

    FILE *file = fopen("data/account.dat", "rb+");
    if (file == NULL)
    {
        errorMessage("Database error");
        return;
    }
    while (fread(&tempUser, sizeof(struct INFORMATION), 1, file))
    {
        if (strcmp(tempUser.accountNumber, user.accountNumber) == 0)
        {
            fseek(file, -sizeof(struct INFORMATION), SEEK_CUR);
            fwrite(&user, sizeof(struct INFORMATION), 1, file);

            fclose(file);
            return;
        }
    }
    fclose(file);
}
