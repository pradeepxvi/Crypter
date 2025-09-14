// this file contains structure INFORMATION to store user data
//  and declaration of register, read and delete  function of user data

#include <stdio.h>

#ifndef ACCOUNT
#define ACCOUNT

// structure to store user data
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

// declaration of
// register function to make registration of new user
void registerAccount();

// function to display user data
void showUserData();

// function to delete user data along with statement and loan information
void deleteAccount();

#endif
