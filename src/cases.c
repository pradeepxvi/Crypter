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

void accountCase()
{
    displayAccountMenu();
    int choice;
    scanf(" %d", &choice);

    switch (choice)
    {
    case 1:
        showUserData();
        break;
    case 2:
        deleteAccount();
        break;
    case 0:
        break;
    default:
        break;
    }
}

void bankingCase()
{

    displayBankingMenu();

    int choice;
    scanf(" %d", &choice);

    switch (choice)
    {
    case 1:
        deposit();
        break;
    case 2:
        withdraw();
        break;
    case 3:
        showUserStatements();
        break;
    case 0:
        break;
    default:
        break;
    }
}

void loanCase()
{
    displayLoanMenu();

    int choice;
    scanf(" %d", &choice);

    switch (choice)
    {
    case 1:
        requestLoan();
        break;
    case 2:
        payEmi();
        break;
    case 3:
        comlpeteLoan();
        break;
    case 4:
        showUserLoan();
        break;
    case 0:
        break;
    default:
        break;
    }
}

void mainCase()
{

    login();

    while (1)
    {
        displayMainMenu();
        int choice;
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            accountCase();
            break;
        case 2:
            bankingCase();
            break;
        case 3:
            loanCase();
            break;
        case 0:
            logout();
        default:
            break;
        }
    }
}

void filterDataCase()
{
    while (1)
    {
        displayFilterDataMenu();

        int choice;
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            filterDataByEmail();
            break;
        case 0:
            return;
        default:
            break;
        }
    }
}

void adminCase()
{

    if (!adminAccess())
    {
        return;
    }

    while (1)
    {
        displayAdminMenu();
        int choice;
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            backupData();
            break;
        case 2:
            restoreData();
            break;
        case 3:
            showAllUserData();
            break;
        case 4:
            showStatements();
            break;
        case 5:
            deleteStatements();
            break;
        case 6:
            showLoans();
            break;
        case 7:
            filterStatement();
            break;
        case 8:
            filterDataCase();
            break;
        case 0:
            return;
        default:
            break;
        }
    }
}

void theBegning()
{

    displayUnAuthMenu();
    int choice;
    scanf(" %d", &choice);

    switch (choice)
    {
    case 1:
        mainCase();
        break;
    case 2:
        registerAccount();
        break;
    case 3:
        adminCase();
        break;
    case 0:
        break;
    default:
        break;
    }
}
