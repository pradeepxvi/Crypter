#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "account.h"
#include "admin.h"
#include "auth.h"
#include "banking.h"
#include "loan.h"
#include "utils.h"
#include "validator.h"

// register account
void registerAccount()
{

    // initialize a INFORMATION structure as user
    struct INFORMATION user;

    // copy current date and time to user's dateJoned
    strcpy(user.dateJoined, getCurrentDateTime());

    // ask first name
    prompt("crypter", "First name");
    scanf(" %[^\n]", user.firstName);

    // ask last name
    prompt("crypter", "Last name");
    scanf(" %[^\n]", user.lastName);

    // ask email until it's a valid one
    do
    {
        prompt("crypter", "Email");
        scanf(" %[^\n]", user.email);
    } while (!validateEmail(user.email));

    // ask address
    prompt("crypter", "Address");
    scanf(" %[^\n]", user.address);

    // ask contact until it's a valid one
    do
    {
        prompt("crypter", "Contact");
        scanf(" %[^\n]", user.contact);
    } while (!validateContact(user.contact));

    // check if user want to keep accountnumber same as contact
    char check;

    prompt("crypter", "Keep the account number same as contact [y/n]");
    scanf(" %c", &check);

    // if yes copy contact to user's account number
    if (tolower(check) == 'y')
    {
        strcpy(user.accountNumber, user.contact);
    }
    else
    {
        // if no, ask for account number until it is a valid one
        do
        {
            prompt("crypter", "Account number");
            scanf(" %[^\n]", user.accountNumber);
        } while (!validateAccountNumber(user.accountNumber));
    }

    // ask  password until it is a valid
    do
    {
        prompt("crypter", "Password");
        system("stty -echo");
        scanf(" %[^\n]", user.password);
        system("stty echo");
    } while (!validatePassword(user.password));

    // set user's balance to 0
    user.balance = 0.0;

    // open file
    FILE *file = fopen("data/account.dat", "ab");

    // if file open/creation failed, hadle error
    if (file == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    // write data to file in binary form
    fwrite(&user, sizeof(user), 1, file);

    // flose file after writting data
    fclose(file);

    // backup data for new record
    backupData();

    // display success message
    successMessage("Account created successfully");
}

// show user's data
void showUserData()
{

    // get auth user
    struct INFORMATION user = getAuthUser();

    // display information
    printf(GREEN BOLD);
    printf("\nName           : %s %s", user.firstName, user.lastName);
    printf("\nEmail          : %s", user.email);
    printf("\nAddress        : %s", user.address);
    printf("\nContact number : %s", user.contact);
    printf("\nAccount number : %s", user.accountNumber);
    printf("\nBalance        : %.2f", user.balance);
    printf("\nDate joined    : %s", user.dateJoined);
    printf(RESET);
}
