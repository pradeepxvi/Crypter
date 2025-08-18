#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "account.h"
#include "auth.h"
#include "admin.h"
#include "banking.h"

int main()
{
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
                    readAllStatement();
                    break;
                }
                break;
            case 3:
                break;
            case 0:
                logout();
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
            case 0:
                logout();
            }
        }
    }
    break;
    default:
        break;
    }

    return 0;
}