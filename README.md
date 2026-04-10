# 🏦 Bank System - C++

A console-based Bank Management System built in C++ as part .
The system allows managing client accounts through a simple text menu.

---

## ✨ Features

- 📋 View all clients in a formatted table
- ➕ Add new clients (with duplicate account number check)
- ❌ Delete clients (with Pin Code verification)
- ✏️ Update client info (with Pin Code verification)
- 🔍 Find a client by account number
- 📊 View bank statistics (total, highest, lowest, average balance)
- 🔃 Sort clients by Name, Balance, or Account Number

---

## 🗂️ Project Structure

```
BankSystem/
├── BankSystem.cpp     # Main source code
├── Clients.txt        # Data file (auto-created on first run)
├── README.md          # Project documentation
├── .gitignore         # Git ignore rules
└── LICENSE            # MIT License
```

---

## 🚀 How to Run

### Requirements
- C++ compiler (g++ or MSVC)
- Windows / Linux / Mac

### Compile & Run (g++)
```bash
g++ BankSystem.cpp -o BankSystem
./BankSystem
```

### Compile & Run (Windows)
```bash
g++ BankSystem.cpp -o BankSystem.exe
BankSystem.exe
```

---

## 📁 Data Storage

Client data is saved in `Clients.txt` using a custom separator `#//#`:

```
A1001#//#1234#//#Ahmed Ali#//#0501234567#//#5000.000000
A1002#//#5678#//#Sara Mohamed#//#0559876543#//#12000.000000
```

---

## 🧱 Code Structure

The project follows clean code principles with each function doing one job:

| Section | Description |
|---------|-------------|
| `SplitString` | Splits a string by a delimiter |
| `ConvertLineToRecord` | Parses a file line into a client struct |
| `ConvertRecordToLine` | Converts a client struct back to a file line |
| `LoadClientsFromFile` | Loads all clients from the data file |
| `SaveClientsToFile` | Saves all clients back to the data file |
| `IsAccountNumberExists` | Checks for duplicate account numbers |
| `VerifyClientPinCode` | Validates pin code before sensitive operations |
| `CalculateStatistics` | Computes bank-wide statistics |
| `SortClients` | Sorts clients using Bubble Sort |
| `Show___Screen` | One function per screen/menu |

---

## 📚 Concepts Used

- Structs
- Vectors
- File I/O (fstream)
- Functions & Procedures
- Enums
- String manipulation
- Bubble Sort


