// this file handles the function related to user authorization

#include <stdio.h>
#include <string.h>
#include "account.h"

#ifndef AUTH
#define AUTH

// function to authorize a valid user
int login();

// function to logout user
void logout();

// this function returns logged in users
struct INFORMATION getAuthUser();

// this function resturn a user with argument account number
struct INFORMATION getUser(char *accountNumber);

// this function save the logged in user
void saveAuthUser(struct INFORMATION authUser);

// this function save user's details in correct position
void saveUser(struct INFORMATION user);

#endif