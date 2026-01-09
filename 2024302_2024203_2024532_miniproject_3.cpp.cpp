// Mohammad Hassaan #2024302
// Hamza Ali #2024208
// Raja Hamza Sikandar #2024532

// Note: We have used <string> library to use string functions such as find, substr etc for string manipulation
// (got sir sajid's approval on this),
// string functions were mainly used for the following:
// reading groupname, groupkey, groupmembers from file stored between commas
// Note: Used copilot to get suggestions when getting stuck and improving efficiency of code, and
// understanding and researching concepts of file handling and string manipulation

#include <iostream>
#include "user_accounts.cpp"
#include "create_groups_add_friends.cpp"
#include "expenses_settling.cpp"

using namespace std;
int main()
{
    int choice;
    int loggedchoice;

    do
    {
        cout << "---------- Welcome to Splitwise ----------\n";
        cout << endl;
        cout << "----------------- Main Menu ----------\n";
        cout << endl;
        cout << "1. Create new account\n";
        cout << "2. Login\n";
        cout << "3. Print Settlement Summaries\n";
        cout << "4. Exit\n";
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            createnewaccount();
            break;
        }
        case 2:
        {
            if (login())
            {
                do
                {
                    cout << "-------- Account Menu -----------" << endl;
                    cout << endl;
                    cout << "1. Create group\n";
                    cout << "2. Add friends to existing group\n";
                    cout << "3. Add expenses\n";
                    cout << "4. Settle up\n";
                    cout << "5. Log out\n";
                    cout << endl;
                    cout << "Enter your choice: \n";
                    cin >> loggedchoice; // Read user input for loggedchoice
                    switch (loggedchoice)
                    {
                    case 1:
                    {
                        createGroups();
                        break;
                    }
                    case 2:
                    {
                        addFriendsToGroup();
                        break;
                    }
                    case 3:
                    {
                        addExpenses();
                        break;
                    }
                    case 4:
                    {
                        settleUp();
                        break;
                    }
                    case 5:
                    {
                        cout << "Logging out...\n";
                        cout << endl;
                        break;
                    }
                    default:
                    {
                        cout << "Invalid choice. Please try again.\n";
                        cout << endl;
                        break;
                    }
                    }
                } while (loggedchoice != 5);
            }

            break;
        }
        case 3:
        {
            printsummary();
            break;
        }
        case 4:
        {
            cout << "Thank you for using Splitwise!\n";
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
            cout << endl;
            break;
        }
        }
    } while (choice != 4);
    return 0;
}
