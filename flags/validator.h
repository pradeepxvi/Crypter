// this file contains different validators require to validate data while creating account

#include <stdio.h>
#include <string.h>

#ifndef VALIDATOR
#define VALIDATOR

// validate email
int validateEmail(char *email);

// validate passowr
int validatePassword(char *password);

// validate contact
int validateContact(char *contact);

// validate account number
int validateAccountNumber(char *accountNumber);

#endif
