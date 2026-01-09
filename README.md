# Splitwise: Expense Manager

### Description
A C++ expense tracker for managing shared finances. Features include secure user login, group creation via unique access keys, and expense logging with equal or unequal splits. Uses file I/O to persist user accounts and transaction history between sessions.

### Features
* **User Authentication:** Secure login system using `accounts.txt`.
* **Group Management:** Create groups with unique 4-digit keys to add friends securely.
* **Flexible Expenses:** Support for splitting bills equally or by specific amounts.
* **Settlement Engine:** Calculates who owes whom and tracks balances.

### How to Run
1.  Ensure all `.cpp` helper files are in the same directory as the main file.
2.  Compile the code:
    ```bash
    g++ 2024302_2024203_2024532_miniproject_3.cpp.cpp -o splitwise
    ```
3.  Run the application:
    * **Windows:** `.\splitwise.exe`
    * **Mac/Linux:** `./splitwise`
