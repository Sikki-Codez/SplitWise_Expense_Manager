#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to add expenses to a group
void addExpenses()
{
    fstream groupsFile("groups.txt", ios::in); // Open the groups file for reading

    string groupName;
    cout << "Enter the group name to add an expense: "; // Prompt user for the group name
    cin.ignore();                                       // Clear the input buffer
    getline(cin, groupName);                            // Read the group name

    string groupKey;
    string line;
    bool groupFound = false;
    string groupMembers;

    // Locate group in the groups file and retrieve key and members
    while (getline(groupsFile, line))
    {
        size_t pos = line.find(","); // Find the position of the comma separating name and key
        if (pos != string::npos)
        {
            string name = line.substr(0, pos); // Extract the group name
            string key = line.substr(pos + 1); // Extract the group key

            if (name == groupName) // Check if the group name matches
            {
                groupKey = key;
                groupFound = true;

                // Read the next line to get the group members
                if (getline(groupsFile, groupMembers))
                {
                    break; // Exit loop when group is found
                }
            }
        }
    }

    groupsFile.close(); // Close the groups file after reading

    // If the group is not found, inform the user
    if (!groupFound)
    {
        cout << "Group not found!" << endl;
        return; // Exit the function if the group does not exist
    }

    ofstream expensesFile("expenses.txt", ios::app); // Open the expenses file for appending

    double totalExpense;
    cout << "Enter the total expense amount: "; // Prompt user for the total expense
    cin >> totalExpense;

    string payer;
    cout << "Enter the name of the payer: "; // Prompt user for the payer's name
    cin.ignore();                            // Clear input buffer
    getline(cin, payer);                     // Read payer's name

    double payerContribution;
    cout << "Enter how much the payer contributed: "; // Ask how much the payer contributed
    cin >> payerContribution;

    // Split the group members string into an array
    string members[25]; // Assuming there are at most 25 members in a group
    int memberCount = 0;
    size_t startPos = 0, pos = 0;

    // Split the members list by commas
    while ((pos = groupMembers.find(",", startPos)) != string::npos)
    {
        string member = groupMembers.substr(startPos, pos - startPos);
        if (!member.empty()) // Avoid empty members
        {
            members[memberCount++] = member; // Add member to the array
        }
        startPos = pos + 1; // Update the starting position
    }

    // Add the last member (after the last comma)
    string lastMember = groupMembers.substr(startPos);
    if (!lastMember.empty())
    {
        members[memberCount++] = lastMember; // Add last member if not empty
    }

    // Ask if the remaining expense should be split equally or unequally
    double remainingExpense = totalExpense - payerContribution;
    string equalSplit;
    cout << "Should the remaining amount be split equally among members? (yes/no): ";
    cin >> equalSplit;

    double totalSplit = 0;     // To track the total contributions for unequal split
    string contributions = ""; // To store the contributions' details

    // If the remaining amount is to be split equally
    if (equalSplit == "yes")
    {
        double splitAmount = remainingExpense / (memberCount - 1); // Exclude the payer from the split

        // Loop through members and calculate the equal split
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i] != payer) // Payer does not owe anything
            {
                contributions += members[i] + " owes " + payer + " " + to_string(splitAmount) + " rupees.\n";
            }
        }
    }
    else // If the split is unequal, ask for individual contributions
    {
        cout << "Enter individual contributions (ensure the total matches the remaining expense):\n";
        double totalContributions = 0.0; // Variable to sum individual contributions

        // Loop through members and ask for each person's contribution
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i] != payer) // Payer does not owe any money
            {
                double contribution;
                cout << members[i] + "'s contribution: "; // Prompt for individual contribution
                cin >> contribution;
                totalContributions += contribution; // Add to the total contributions
                contributions += members[i] + " owes " + payer + " " + to_string(contribution) + " rupees.\n";
            }
        }

        // Check if total contributions match the remaining expense
        if (totalContributions != remainingExpense)
        {
            cout << "Error: Total contributions do not match the remaining expense.\n";
            expensesFile.close(); // Close the file if there is an error
            return;
        }
    }

    // Write the expense details into the expenses file
    expensesFile << "Group: " << groupName << ", Key: " << groupKey << endl;
    expensesFile << "Payer: " << payer << " paid " << totalExpense << " rupees, contributing " << payerContribution << " rupees towards the total.\n";
    expensesFile << contributions;
    expensesFile.close(); // Close the expenses file after writing
    cout << "Expense added successfully!" << endl;
}

// Function to settle up expenses for a group
void settleUp()
{
    fstream expensesFile("expenses.txt", ios::in); // Open the expenses file for reading

    string balances[25][2] = {}; // For simplicity, storing up to 25 users' balances
    int balanceCount = 0;
    string line;

    // Process each line in the expenses file to calculate balances
    while (getline(expensesFile, line))
    {
        if (line.find("Group:") != string::npos || line.find("Payer:") != string::npos)
            continue; // Skip lines that are not relevant for balances

        size_t pos = 0;
        string payer, contributionsStr;
        double amount;
        string groupName, groupKey;

        // Extract payer's name and the amount paid
        if (line.find("Payer:") != string::npos)
        {
            size_t start = line.find("Payer: ") + 7;
            size_t end = line.find(" paid");
            payer = line.substr(start, end - start);

            start = line.find("paid ") + 5;
            end = line.find(" rupees");
            amount = stod(line.substr(start, end - start));
        }

        // Update the payer's balance
        bool payerFound = false;
        for (int i = 0; i < balanceCount; i++)
        {
            if (balances[i][0] == payer)
            {
                balances[i][1] = to_string(stod(balances[i][1]) + amount); // Add the amount to payer's balance
                payerFound = true;
                break;
            }
        }

        if (!payerFound && balanceCount < 25)
        {
            balances[balanceCount][0] = payer;
            balances[balanceCount][1] = to_string(amount); // Add a new entry for the payer
            balanceCount++;
        }

        // Process each contribution to update the balances
        while (getline(expensesFile, line) && line.find("Contributions:") == string::npos)
        {
            string contributions = line.substr(line.find(": ") + 2); // Get the contributions string
            size_t contribPos = 0;

            // Split and process each member's contribution
            while ((contribPos = contributions.find("|")) != string::npos)
            {
                string memberSplit = contributions.substr(0, contribPos);
                contributions.erase(0, contribPos + 1);

                size_t splitPos = memberSplit.find(",");
                string member = memberSplit.substr(0, splitPos);
                double contribution = stod(memberSplit.substr(splitPos + 1));

                // Update each member's balance
                bool memberFound = false;
                for (int i = 0; i < balanceCount; i++)
                {
                    if (balances[i][0] == member)
                    {
                        balances[i][1] = to_string(stod(balances[i][1]) - contribution); // Deduct contribution
                        memberFound = true;
                        break;
                    }
                }

                if (!memberFound && balanceCount < 25)
                {
                    balances[balanceCount][0] = member;
                    balances[balanceCount][1] = to_string(-contribution); // Add a new member entry with negative contribution
                    balanceCount++;
                }
            }
        }
    }

    expensesFile.close(); // Close the expenses file after processing

    cout << "Expenses settled for this group. Head back to the main menu to check settlement summary." << endl;
}

// Function to print a summary of all registered groups and expenses
void printsummary()
{
    ifstream expensesFile("expenses.txt"); // Open the expenses file for reading

    cout << "Summary of all groups registered on Splitwise:" << endl;
    string line;
    while (getline(expensesFile, line)) // Print each line of the expenses file
    {
        cout << line << endl;
    }
    cout << endl;
    expensesFile.close(); // Close the file after reading
}
