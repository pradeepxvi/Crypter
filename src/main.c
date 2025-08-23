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

int main()
{

    remove("data/authenticated.dat");
    displayIntro();
    displayUnAuthMenu();

    int unAuthOperation;
    scanf(" %d", &unAuthOperation);

    switch (unAuthOperation)
    {
    case 1:
    {
        if (!login())
            break;
        while (1)
        {

            int mainMenu;
            displayMainMenu();
            scanf(" %d", &mainMenu);

            switch (mainMenu)
            {
            case 1:
                int accountMenu;
                displayAccountMenu();
                scanf(" %d", &accountMenu);

                switch (accountMenu)
                {
                case 1:
                    readData();
                    break;
                case 2:
                    deleteAccount();
                    break;
                default:
                    break;
                }
                break;

            case 2:
                int bankingMenu;
                displayBankingMenu();
                scanf(" %d", &bankingMenu);

                switch (bankingMenu)
                {
                case 0:
                    break;
                case 1:
                    deposit();
                    break;
                case 2:
                    withdraw();
                    break;
                case 3:
                    readStatement();
                    break;
                }
                break;

            case 3:
                displayLoanMenu();

                int loanMenu;
                scanf(" %d", &loanMenu);

                switch (loanMenu)
                {
                case 0:
                    break;
                case 1:
                    requestLoan();
                    break;
                case 2:
                    payEmi();
                    break;
                case 3:
                    loanPaid();
                    break;
                case 4:
                    getLoanInfo();
                    break;
                default:
                    printf("\nEnter valid operation");
                    break;
                }
                break;

            case 0:
                logout();
                break;
            }
        }
    }
    break;

    case 2:
        Register();
        break;

    case 3:
    {
        if (!adminAccess())
            break;

        while (1)
        {
            int adminMenu;
            displayAdminMenu();
            scanf(" %d", &adminMenu);

            switch (adminMenu)
            {
            case 1:
                backup();
                break;
            case 2:
                restore();
                break;
            case 3:
                readAdminn();
                break;
            case 4:
                readALLStatementAdmin();
                break;
            case 5:
                deleteAllStatementAdmin();
                break;
            case 6:
                readAllLoan();
                break;
            case 0:
                logout();
            default:
                break;
            }
        }
    }
    break;

    default:
        break;
    }

    return 0;
}