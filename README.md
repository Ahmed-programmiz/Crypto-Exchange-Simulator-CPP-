# Crypto Exchange Simulator (C++)

A console-based cryptocurrency exchange **simulation** built in C++ using object-oriented programming (OOP). Users can register, log in, manage simulated USDT balances, and buy or sell BTC, ETH, and DOGE at manually entered prices.

> **Educational simulation only.** This program does not connect to an exchange, blockchain, wallet provider, or live market. It does not transfer or hold real cryptocurrency.

## Features

- Register accounts and log in with a username and password.
- View simulated balances for **BTC, ETH, DOGE, and USDT**.
- Deposit and withdraw simulated USDT.
- Place buy or sell orders for BTC, ETH, or DOGE using a price entered by the user.
- View the logged-in user's recorded orders.
- Cancel the user's most recently recorded order and reverse its balances (subject to the limitations noted below).

## Technologies and concepts

- **Language:** C++
- **Interface:** Terminal / console
- **Concepts:** OOP, classes, arrays, loops, conditional logic, and input validation
- **Main classes:** `Wallet`, `User`, `Order`, and `Exchange`

## Build and run

Requires a C++ compiler such as **g++**.

```bash
g++ -std=c++17 CES.cpp -o CES
./CES
```

On Windows (MinGW / g++):

```powershell
g++ -std=c++17 CES.cpp -o CES.exe
.\CES.exe
```

## How to use

1. Select **Register** and create a username and password.
2. Select **Login** with your credentials.
3. Select **Deposit USDT** to add a simulated balance.
4. Select **Place Order** to buy or sell BTC, ETH, or DOGE.
5. Use **Show Wallet**, **View My Orders**, or **Cancel Last Order** to inspect or adjust the simulation.
6. Select **Logout** when finished.

## Current limitations

- All data lives in memory and is lost when the program exits. No database or file storage is implemented.
- Supports a maximum of **20 users**, **50 recorded orders in total**, and **5 current orders per user**.
- Prices are entered manually; there are no live quotes, order matching, transaction fees, or actual crypto transfers.
- Passwords are stored as plain text in memory. Do **not** reuse real passwords or use this project for production authentication.
- Orders are applied to balances immediately, so the order list is a record of simulated trades rather than a market order book.
- The cancellation routine does not reliably check whether later transactions leave sufficient balances for reversal; it can produce unrealistic or negative balances. It is a learning feature, not production-grade accounting.
- Numeric input errors are not robustly handled.

## Project structure

```text
Crypto-Exchange-Simulator-CPP/
├── CES.cpp       # C++ application source
├── README.md     # Project documentation
└── .gitignore    # Excludes compiled executables and build files
```

## Disclaimer

This repository is for learning and demonstration, **not** for real trading or financial services.