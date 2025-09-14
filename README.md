# Crypter – Secure Bank Management System

Crypter is a **CLI-based secure bank management system** written in **C programming** as a 2nd semester university project.  
It simulates the core features of a banking system with authentication, account management, transactions, loan services, and admin-level operations.  
Data persistence is implemented using **binary files** and session-based authentication.

## 🎯 Objectives

- To design and implement a **secure, modular bank management system** using C programming.
- To demonstrate the use of **file handling** for persistent storage of user, transaction, and loan data.
- To apply **session-based authentication** for controlled access to banking services.
- To gain practical experience in **structured programming**, modular code organization, and use of **header/source files**.
- To provide a **menu-driven CLI interface** that is user-friendly and easy to navigate.
- To simulate **real-world banking operations** such as account management, deposits, withdrawals, transfers, and loans.
- To implement **admin-level controls** (backup, restore, data filtering) to mimic real financial system requirements.

## 📌 Why This Project is Necessary

- **Understanding Core Banking Logic**: Helps students understand how banking systems handle accounts, transactions, and loans.
- **Practical Use of C Programming**: Strengthens knowledge of file handling, structures, functions, and modular programming in C.
- **Security Awareness**: Introduces authentication and controlled access concepts for secure system design.
- **Data Management Skills**: Shows how to maintain, back up, and restore critical financial data.
- **Real-World Application**: Provides a small-scale simulation of real banking software used in financial institutions.
- **Foundation for Advanced Projects**: Can be extended with encryption, database integration (SQL), or GUI in higher semesters.
- **Team/Individual Learning**: Encourages systematic problem-solving, debugging, and project documentation practices.

## 🚀 Features

### 👤 User Access

- **Login & Logout** with session authentication
  - A file `authenticated.dat` is created on login and deleted on logout.
- **Register** new users securely.

### 🏦 Account Management

- View account information
- Delete account

### 💳 Banking Services

- Deposit funds
- Withdraw funds
- View transaction statement
- Transfer funds

### 📄 Loan Services

- Request loan
- Pay EMI
- Complete loan
- View loan information

### 👨‍💼 Admin Access

- Backup and restore data
- View all user data
- Read all transactions
- Delete all transactions
- View all loan data
- Filter transactions by type (Deposit, Withdraw, Loan issue, EMI paid, Loan paid)
- Filter user data (by email / sort balance ascending or descending)

## 📂 Project Structure

```
.
├── data
│   ├── accountBackup.dat
│   ├── account.dat
│   ├── intro.txt
│   ├── loanBackup.dat
│   ├── loan.dat
│   ├── statementBackup.dat
│   └── statement.dat
├── docs
│   ├── crypter_01.png
│   ├── fileStructure
│   ├── programStructure.png
│   └── programStructure.txt
├── flags
│   ├── account.h
│   ├── admin.h
│   ├── auth.h
│   ├── banking.h
│   ├── cases.h
│   ├── filters.h
│   ├── loan.h
│   ├── utils.h
│   └── validator.h
├── Makefile
├── README.md
└── src
    ├── account.c
    ├── admin.c
    ├── auth.c
    ├── banking.c
    ├── cases.c
    ├── filters.c
    ├── loan.c
    ├── main.c
    ├── utils.c
    └── validator.c

```

## 🖥️ Program sturcture

```
[ 1 ] LOGIN
        [ 1 ] ACCOUNT MANAGEMENT
                [ 1 ] VIEW ACCOUNT INFORMATION
                [ 2 ] DELETE ACCOUNT
                [ 0 ] RETURN

        [ 2 ] BANKING SERVICES
                [ 1 ] DEPOSIT FUNDS
                [ 2 ] WITHDRAW FUNDS
                [ 3 ] VIEW STATEMENT
                [ 4 ] TRANSFER FUNDS
                [ 0 ] RETURN

        [ 3 ] LOAN SERVICES
                [ 1 ] REQUEST LOAN
                [ 2 ] PAY EMI
                [ 3 ] COMPLETE LOAN
                [ 4 ] VIEW LOAN INFORMATION
                [ 0 ] RETURN

        [ 0 ] LOGOUT

[ 2 ] REGISTER

[ 3 ] ADMIN ACCESS
        [ 1 ] BACKUP DATA
        [ 2 ] RESTORE DATA
        [ 3 ] VIEW ALL USER DATA
        [ 4 ] READ ALL TRANSACTIONS
        [ 5 ] DELETE ALL TRANSACTIONS
        [ 6 ] VIEW ALL LOAN DATA

        [ 7 ] FILTER TRANSACTIONS
                [ 1 ] Diposit
                [ 2 ] Withdraw
                [ 3 ] Loan issue
                [ 4 ] EMI paid
                [ 5 ] Loan paid
                [ 0 ] Exit

        [ 8 ] FILTER USER DATA
                [ 1 ] FILTER BY EMAIL
                [ 2 ] SORT BALANCE LOW TO HIGH
                [ 3 ] SORT BALANCE HIGH TO LOW
                [ 0 ] RETURN
        [ 0 ] EXIT
[ 0 ] EXIT
```

## 🛠️ Build & Run Instructions

**Make sure you have GCC installed.**

### Clone Repo

```bash
git clone https://github.com/pradeepxvi/Crypter
cd Crypter
```

### Build

```bash
make build
```

### Run

```bash
make run
```

### Clean output

```bash
make clean
```

### Help

```bash
make help
```

## 🔧 Technologies Used

- C Programming (Modularized with header & source files)

- File Handling for persistent storage

- Makefile for build automation

- CLI Interface (Terminal based)

## 🏆 Contributors

- **[**Pradeep**](https://www.pradeepxvi.me)** — _Lead Developer_
- **Abhistan** — _Documentation Specialist_
- **Binod** — _Presentation Designer_
