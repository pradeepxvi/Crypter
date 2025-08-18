#include <stdio.h>
#include "admin.h"
#include "account.h"
#include "auth.h"
#include "banking.h"

void adminMenu()
{
    printf("\n\n0.Exit");
    printf("\n1.Backup ");
    printf("\n2.Restore");
    printf("\n3.Real all data");
    printf("\n\n>> ");
}

int adminAccess()
{

    char username[100];
    char password[100];

    printf("[admin] username : ");
    scanf(" %s", username);
    printf("[admin] password : ");
    scanf(" %s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
    {
        return 1;
    }
    printf("\nAdmin authentication failed");

    return 0;
}

void backup()
{

    // account
    FILE *file = fopen("data/account.dat", "rb");
    FILE *backupFile = fopen("data/accountBackup.dat", "wb");

    if (!file || !backupFile)
    {
        perror("\nError on opening files");
        if (file)
            fclose(file);
        if (backupFile)
            fclose(backupFile);
        return;
    }

    struct INFORMATION user;

    while (fread(&user, sizeof(user), 1, file))
    {
        fwrite(&user, sizeof(user), 1, backupFile);
    }

    printf("\nBackup completed successfully.\n");

    fclose(file);
    fclose(backupFile);

    // statement

    file = fopen("data/statement.dat", "rb");
    backupFile = fopen("data/statementBackup.dat", "wb");

    if (!file || !backupFile)
    {
        perror("\nError on opening files");
        if (file)
            fclose(file);
        if (backupFile)
            fclose(backupFile);
        return;
    }

    struct STATEMENT statement;

    while (fread(&statement, sizeof(statement), 1, file))
    {
        fwrite(&statement, sizeof(statement), 1, backupFile);
    }

    printf("\nBackup completed successfully.\n");

    fclose(file);
    fclose(backupFile);
}

void restore()
{

    // account

    FILE *file = fopen("data/account.dat", "wb");
    FILE *restoreFile = fopen("data/accountBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        perror("\nError on opening files");
        if (file)
            fclose(file);
        if (restoreFile)
            fclose(restoreFile);
        return;
    }

    struct INFORMATION user;

    while (fread(&user, sizeof(user), 1, restoreFile))
    {
        fwrite(&user, sizeof(user), 1, file);
    }

    printf("\nRestore completed successfully.\n");
    fclose(file);
    fclose(restoreFile);

    // statement

    file = fopen("data/statement.dat", "wb");
    restoreFile = fopen("data/statementBackup.dat", "rb");

    if (!file || !restoreFile)
    {
        perror("\nError on opening files");
        if (file)
            fclose(file);
        if (restoreFile)
            fclose(restoreFile);
        return;
    }

    struct STATEMENT statement;
    while (fread(&statement, sizeof(statement), 1, restoreFile))
    {
        fwrite(&statement, sizeof(statement), 1, file);
    }

    printf("\nRestore completed successfully.\n");
    fclose(file);
    fclose(restoreFile);
}

void readAdminn()
{

    FILE *file = fopen("data/account.dat", "rb");

    if (!file)
    {
        perror("\nError on opening file");
        return;
    }

    struct INFORMATION user;

    while (fread(&user, sizeof(user), 1, file))
    {
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
}

void readALLStatementAdmin()
{
    struct STATEMENT statement;

    FILE *file = fopen("data/statement.dat", "rb");

    if (!file)
    {
        perror("\nStatement are not available");
        return;
    }

    while (fread(&statement, sizeof(statement), 1, file) == 1)
    {
        printf("\n[%s]", statement.date);
        printf(" - %s %s", statement.user.firstName, statement.user.lastName);
        printf(" - %s", statement.transaction);
        printf(" - Rs %.2f", statement.amount);
    }

    fclose(file);
}

void deleteAllStatementAdmin()
{
    char confirmation;
    printf("\nAre you sure (y/n) > _ ");
    scanf(" %c", &confirmation);

    if (confirmation != 'y' && confirmation != 'Y')
    {
        printf("\nOperation aborted");
        return;
    }
    remove("data/statement.dat");
}