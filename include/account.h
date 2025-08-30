#include <stdio.h>

#ifndef ACCOUNT
#define ACCOUNT

struct INFORMATION
{
    char firstName[250];
    char lastName[250];
    char email[250];
    char address[250];
    char contact[250];
    char accountNumber[250];
    char password[250];
    float balance;
    char dateJoined[250];
};

// crud
void registerAccount();
void showUserData();
void deleteAccount();

#endif
