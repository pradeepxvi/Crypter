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
    char accountNumber[16];
    char password[100];
    float balance;
};

// crud
void Register();
void readData();
void deleteAccount();

#endif
