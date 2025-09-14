// this is admin heaer file which contains only the function which can accessed by admin

#ifndef ADMIN
#define ADMIN

// this function authorize whether admin or not
int adminAccess();

// function to backup data, statement and loan information togther
void backupData();

// function to restore data, statement and loan information togther
void restoreData();

// function to display all user data
void showAllUserData();

// function to display all user's statement
void showStatements();

// function to detelete all user's statement
void deleteStatements();

// function to display all user's statement
void showLoans();

#endif