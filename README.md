# Crypter

**A Secure Bank Management System**

## Introduction

Crypter is a simple bank management system built in C, focused on security and practical learning. It supports account creation, secure login via PIN/password, money deposit/withdrawal, transaction history tracking, loans, and account deletion, all with robust file-based data storage. The project is designed to help users and students understand C programming concepts such as structures, file I/O, and authentication.

## Objectives

- Implement secure PIN/password authentication for banking operations.
- Allow account holders to deposit and withdraw money after authentication.
- Record and maintain transaction history for each account using separate files.
- Provide the option to securely delete an account.
- Support loan requests, EMI calculation, and repayments.
- Persist data using file handling for account info, loan info, and transaction logs.
- Enhance understanding of structured programming, file operations, and basic security mechanisms in C.

## Features

- **Register & Login**: Users can register with name, email, contact, account number, and password. Login is secured by password/PIN.
- **Account Management**: View your account details; securely delete your account.
- **Banking Operations**: Deposit and withdraw money; view transaction statement/history.
- **Loan Management**:
  - **Apply for a Loan**: Request loans between 100,000 and 10,000,000 units with a fixed annual interest rate (5%).
  - **EMI Calculation**: The system calculates monthly installments (EMI) using your requested amount, interest rate, and chosen duration (6–120 months).
  - **View Loan Info**: See your loan balance, EMI, and interest rate at any time.
  - **Pay EMI**: Make monthly payments toward your loan directly from your bank balance.
  - **Pay Off Loan**: Settle the remaining loan amount in full if you have enough balance.
  - **Loan Eligibility**: Only one active loan per account is allowed.
- **Admin Access**: Backup and restore all data, read/delete all statements (admin-only).
- **File-based Data Storage**: All user, loan, and transaction data is stored in files for persistence.

## How to Use

1. **Clone the Repository**

   ```sh
   git clone https://github.com/pradeepxvi/Crypter
   cd Crypter
   ```

2. **Build the Project**

   - Make sure you're in the root directory (`Crypter`)
   - Compile the code:
     ```sh
     make
     ```

3. **Run the Program**

   ```sh
   make run
   ```

4. **Other Commands**
   - Clear output files:
     ```sh
     make clean
     ```
   - Display available make commands:
     ```sh
     make help
     ```

## Usage Flow

- On running, the program displays an introduction and a menu:
  - [1] Login
  - [2] Register
  - [3] Admin Access
  - [0] Exit
- After login, access menus for:
  - **Account Management**: View info, delete your account.
  - **Banking**: Deposit, withdraw, view statement.
  - **Loan**: Apply for loan, view loan details, pay EMI, pay off loan.
  - **Logout**
- Admins can backup/restore data and manage statements.

## Example

```
$ make
$ make run
```

Follow the on-screen menu for registration, login, banking, and loan operations.

## Loan Feature Details

- **Applying for a Loan**:  
  Users can request a loan between 100,000 and 10,000,000 units. The annual interest rate is fixed at 5%. The duration must be between 6 and 120 months.
- **EMI Calculation**:  
  Monthly EMI is automatically calculated and shown before confirmation.
- **Loan Approval**:  
  After confirming, the loan amount is credited to the user's account.
- **Repayment**:  
  Users can pay EMI monthly or pay off the entire remaining balance. Payments are deducted from the user's account balance.
- **Loan Status**:  
  Only one active loan per user is allowed. You can always view your current loan status, EMI, and balance.

## Project Members

- Pradeep Kunwar - Developer
- Abhishant Poudel - Researcher
- Binod Bharati - Designer

---

Feel free to explore and contribute!
