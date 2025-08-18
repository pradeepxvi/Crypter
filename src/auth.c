#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "auth.h"

int login()
{
    char id[100];
    char password[100];

    printf("\n\n[Id / email / contact] : ");
    scanf(" %[^\n]", id);

    printf("\n[Password] : ");
    scanf(" %[^\n]", password);

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        perror("Error opening account file");
        return 0;
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
                if (!authFile)
                {
                    perror("\nError opening authenticated file");
                    fclose(file);
                    return 0;
                }

                fwrite(&user, sizeof(user), 1, authFile);
                fclose(authFile);
                fclose(file);
                return 1;
            }
            printf("\nWrong password\n");
            break;
        }
    }

    if (!found)
        printf("\nUser not found\n");

    fclose(file);
    printf("\nAuthentication failed");
    return 0;
}

void logout()
{
    remove("data/authenticated.dat");
    system("clear");
    displayIntro();
    exit(0);
}

struct INFORMATION getAuthUser()
{
    struct INFORMATION authUser;

    FILE *file = fopen("data/authenticated.dat", "rb");

    fread(&authUser, sizeof(authUser), 1, file);
    fclose(file);

    return authUser;
}

void saveAuthUser(struct INFORMATION authUser)
{

    FILE *file = fopen("data/authenticated.dat", "wb");
    fwrite(&authUser, sizeof(authUser), 1, file);
    fclose(file);
}
