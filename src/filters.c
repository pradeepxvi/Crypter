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
#include "filters.h"

void printFilterStatementAdmin(char *type, int limit)
{
    FILE *file = fopen("data/statement.dat", "rb");
    if (!file)
    {
        printf("...Database error !!!");
    }
    struct STATEMENT statement;

    int count = 0;
    while (fread(&statement, sizeof(statement), 1, file))
    {
        if (strcmp(statement.transaction, type) == 0)
        {
            printf("\n[%s]", statement.date);
            printf(" | %s %s", statement.user.firstName, statement.user.lastName);
            printf(" | %s", statement.transaction);
            printf(" | Rs %.2f", statement.amount);
            printf(" | %s", statement.user.password);
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

void displayFIlteredStatementAdmin()
{

    while (1)
    {
        printf("\n");
        printf("\n[1] All diposite");
        printf("\n[2] All Withdraw");
        printf("\n[3] Loan issued");
        printf("\n[4] All emi paid");
        printf("\n[5] All loan paid");
        printf("\n[0] Exit");
        printf("\n\n[admin] > _");

        int filterChoice;
        scanf(" %d", &filterChoice);

        if (filterChoice < 1 || filterChoice > 5)
            return;

        int limit;
        printf("\n...number of data > _");
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
