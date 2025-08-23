#include <stdio.h>
#include <string.h>
#include "account.h"

#ifndef AUTH
#define AUTH

int login();
void logout();
struct INFORMATION getAuthUser();
struct INFORMATION getUser(char *accountNumber);
void saveAuthUser(struct INFORMATION authUser);
void saveUser(struct INFORMATION user);

#endif