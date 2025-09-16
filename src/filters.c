#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "admin.h"
#include "auth.h"
#include "banking.h"
#include "loan.h"
#include "utils.h"
#include "filters.h"

void printFilterStatementAdmin(char *type, int limit)
{
    FILE *file = fopen("data/statement.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    struct STATEMENT statement;
    int count = 0;

    while (fread(&statement, sizeof(statement), 1, file))
    {
        if (strcmp(statement.transaction, type) == 0)
        {
            printf(GREEN BOLD);
            printf("\n[%s]", statement.date);
            printf(" | %s %s", statement.user.firstName, statement.user.lastName);
            printf(" | %s", statement.transaction);
            printf(" | Rs %.2f", statement.amount);
            printf(RESET);
            count++;
        }
        if (limit == count)
        {
            return;
            fclose(file);
        }
    }
    fclose(file);
}

void filterStatement()
{

    while (1)
    {
        printf("\n");
        printf("\n[ 1 ] Diposit");
        printf("\n[ 2 ] Withdraw");
        printf("\n[ 3 ] Loan issue");
        printf("\n[ 4 ] EMI paid");
        printf("\n[ 5 ] Loan paid");
        printf("\n[ 0 ] Exit");
        printf("\n");
        prompt("admin", "");

        int filterChoice;
        scanf(" %d", &filterChoice);

        if (filterChoice < 1 || filterChoice > 5)
            return;

        int limit;
        prompt("admin", "Number of data");
        scanf(" %d", &limit);

        switch (filterChoice)
        {
        case 1:
            printFilterStatementAdmin("deposite", limit);
            break;
        case 2:
            printFilterStatementAdmin("withdraw", limit);
            break;
        case 3:
            printFilterStatementAdmin("loan_issue", limit);
            break;
        case 4:
            printFilterStatementAdmin("loan_emi_paid", limit);
            break;
        case 5:
            printFilterStatementAdmin("loan_paid", limit);
            break;
        }
    }
}

void filterDataByEmail()
{

    FILE *file = fopen("data/account.dat", "rb");

    if (file == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    struct INFORMATION temp;
    struct INFORMATION *users = NULL;
    int count = 0;

    while (fread(&temp, sizeof(struct INFORMATION), 1, file))
    {
        users = realloc(users, (count + 1) * sizeof(struct INFORMATION));

        if (!users)
        {
            printf("\n... Memory Error !!!");
            return;
        }
        users[count] = temp;
        count++;
    }
    fclose(file);

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {

            if (strcmp(users[i].email, users[j].email) > 0)
            {
                temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    printf(RED BOLD);

    printf("\n");
    printf("%-15s", "FIRSTNAME");
    printf("%-15s", "LASTNAME");
    printf("%-20s", "EMAIL");
    printf("%-25s", "ADDRESS");
    printf("%-12s", "CONTACT");
    printf("%-12s", "ACC_NUMBER");
    printf("%-20s", "DATEJOINED");
    printf("%10s", "BALANCE");
    printf("\n");

    printf(GREEN);

    for (int i = 0; i < count; i++)
    {
        printf("\n");
        printf("%-15s", users[i].firstName);
        printf("%-15s", users[i].lastName);
        printf("%-20s", users[i].email);
        printf("%-25s", users[i].address);
        printf("%-12s", users[i].contact);
        printf("%-12s", users[i].accountNumber);
        printf("%-20s", users[i].dateJoined);
        printf("$ %.2f", users[i].balance);
    }
    printf(RESET);
}

void filterDataByBalance(int status)
{

    FILE *file = fopen("data/account.dat", "rb");
    if (file == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    int count = 0;
    struct INFORMATION *users = NULL;
    struct INFORMATION temp;

    while (fread(&temp, sizeof(struct INFORMATION), 1, file) == 1)
    {
        users = realloc(users, (count + 1) * sizeof(struct INFORMATION));
        if (!users)
        {
            printf("\n... Memory Error !!!");
            return;
        }

        users[count] = temp;
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (status == 1)
            {
                if (users[i].balance > users[j].balance)
                {
                    temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
            else
            {
                if (users[i].balance < users[j].balance)
                {
                    temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
    }

    printf(RED BOLD);

    printf("\n");
    printf("%-15s", "FIRSTNAME");
    printf("%-15s", "LASTNAME");
    printf("%-20s", "EMAIL");
    printf("%-25s", "ADDRESS");
    printf("%-12s", "CONTACT");
    printf("%-12s", "ACC_NUMBER");
    printf("%-22s", "DATEJOINED");
    printf("%10s", "BALANCE");
    printf("\n");

    printf(GREEN);

    for (int i = 0; i < count; i++)
    {
        printf("\n");
        printf("%-15s", users[i].firstName);
        printf("%-15s", users[i].lastName);
        printf("%-20s", users[i].email);
        printf("%-25s", users[i].address);
        printf("%-12s", users[i].contact);
        printf("%-12s", users[i].accountNumber);
        printf("%-22s", users[i].dateJoined);
        printf("$ %.2f", users[i].balance);
    }
    printf(RESET);

    fclose(file);
}
