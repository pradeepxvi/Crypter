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
        scanf(" %[^\n]", user.password);
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

// delete account
void deleteAccount()
{
    struct INFORMATION authUser = getAuthUser();

    char username[100];
    strcpy(username, authUser.firstName);

    // ask for confirmation to delete account or not
    char confirmation;
    prompt(authUser.firstName, "Are you sure [y/n]");
    scanf(" %c", &confirmation);

    // is not confirmed cancel deleteion
    if (tolower(confirmation) != 'y')
    {
        errorMessage("Account deletion failed");
        return;
    }

    // delete user's data............................................

    // open file and a temporary file to rewrite data

    FILE *file = fopen("data/account.dat", "rb");
    FILE *tempFile = fopen("data/tempFile.dat", "wb");

    // if file open/creation failed , handle error
    if (file == NULL || tempFile == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    // initialzer INFORMATION as user and authuser
    struct INFORMATION user;

    // set deleted to 0
    int deleted = 0;

    // read each data , write data to temp file if it doesnot match to auth user
    while (fread(&user, sizeof(user), 1, file))
    {
        if (strcmp(user.accountNumber, authUser.accountNumber) == 0)
        {

            // is data match to auth user , set deleted to 1
            deleted = 1;
        }
        else
        {
            fwrite(&user, sizeof(user), 1, tempFile);
        }
    }

    // close filesss
    if (file)
        fclose(file);
    if (tempFile)
        fclose(tempFile);

    // if data was deleted , remove file and rename tempfile to file
    if (deleted)
    {
        if (remove("data/account.dat") == 1 || rename("data/tempFile.dat", "data/account.dat") == 1)
        {
            errorMessage("Database Error");
            return;
        }
    }
    else
    {
        errorMessage("Error while deleting account");
        if (remove("data/tempFile.dat") == 1)
        {
            errorMessage("Database Error");
            return;
        }
    }

    // delete user's statement ............................................

    file = fopen("data/loan.dat", "rb");
    tempFile = fopen("data/tempFile.dat", "wb");

    if (file == NULL || tempFile == NULL)

    {
        errorMessage("Database Error");
        return;
    }

    struct LOAN loan;

    while (fread(&loan, sizeof(loan), 1, file))
    {
        if (strcmp(loan.user.accountNumber, authUser.accountNumber) != 0)
        {
            fwrite(&loan, sizeof(loan), 1, tempFile);
        }
    }

    if (file)
        fclose(file);
    if (tempFile)
        fclose(tempFile);

    if (remove("data/loan.dat") == 1 || rename("data/tempFile.dat", "data/loan.dat") == 1)
    {
        errorMessage("Database Error");
        return;
    }

    // delete user's loan data............................................

    file = fopen("data/statement.dat", "rb");
    tempFile = fopen("data/tempFile.dat", "wb");

    if (file == NULL || tempFile == NULL)
    {
        errorMessage("Database Error");
        return;
    }

    struct STATEMENT statement;

    while (fread(&statement, sizeof(statement), 1, file))
    {
        if (strcmp(statement.user.accountNumber, authUser.accountNumber) != 0)
        {
            fwrite(&statement, sizeof(statement), 1, tempFile);
        }
    }

    if (file)
        fclose(file);
    if (tempFile)
        fclose(tempFile);

    if (remove("data/statement.dat") == 1 || rename("data/tempFile.dat", "data/statement.dat") == 1)
    {
        errorMessage("Database Error");
        return;
    }

    // finally remove session file, since user is deleted
    if (remove("data/authenticated.dat") == 1)
    {
        errorMessage("Database Error");
        return;
    }
    successMessage("User deleted");

    logout();
}
