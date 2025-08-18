#include <stdio.h>
#include <string.h>
#include "account.h"

#ifndef AUTH
#define AUTH

int login();
void logout();
struct INFORMATION getAuthUser();
void saveAuthUser(struct INFORMATION authUser);

#endif