#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAXUSERS = 25; // test number of max users

// Function to generate a random 4-digit key
string generateGroupKey()
{
    srand(time(0));                 // Seed for randomness to ensure unique keys
    int key = rand() % 9000 + 1000; // Ensures a 4-digit key (1000 to 9999 range)
    return to_string(key);
}

// Function to create groups
void createGroups()
{
    ofstream groupsFile("groups.txt", ios::app); // Open the file in append mode

    string groupName;
    cout << "Enter the name of the group: ";
    cin.ignore();            // Clear the input buffer before reading a full line
    getline(cin, groupName); // Read the group name as a single line

    string groupKey = generateGroupKey();               // Generate a unique group key
    groupsFile << groupName << "," << groupKey << "\n"; // Write group name and key to the file

    string memberName;
    cout << "Enter group members (type 'done' to finish):\n";
    bool firstMember = true; // Flag to track the first member
    while (true)
    {
        cin >> memberName;
        if (memberName == "done")
            break; // Exit loop when 'done' is entered

        if (!firstMember)
        {
            groupsFile << ", "; // Add a comma before each member except the first
        }
        groupsFile << memberName; // Write member name to the file
        firstMember = false;
    }

    groupsFile << "\n";                                                    // End the members list with a newline
    cout << "Group created successfully! Group key: " << groupKey << "\n"; // Confirmation message
    groupsFile.close();                                                    // Close the file
}

// Function to add friends to an existing group
void addFriendsToGroup()
{
    fstream groupsFile("groups.txt", ios::in | ios::out); // Open file in read-write mode

    string searchGroup, groupKey, enteredKey, line;
    cout << "Enter the name of the group to add members: ";
    cin.ignore();              // Clear the input buffer before reading a full line
    getline(cin, searchGroup); // Read the group name to search for

    // Reading file content to locate the group
    string fileContent = ""; // Temporary storage for file content
    bool groupFound = false; // Flag to track if the group is found
    while (getline(groupsFile, line))
    {
        size_t commaPos = line.find(',');                  // Find the position of the first comma
        string storedGroupName = line.substr(0, commaPos); // Extract the group name
        string storedGroupKey = line.substr(commaPos + 1); // Extract the group key

        if (storedGroupName == searchGroup)
        {
            groupFound = true; // Mark group as found
            cout << "Enter the 4-digit group key: ";
            cin >> enteredKey; // Read the entered group key

            if (enteredKey != storedGroupKey)
            {
                cout << "Invalid group key! Cannot add members.\n";
                return; // Exit the function if the key is invalid
            }

            fileContent += line + "\n"; // Append the group name and key
            getline(groupsFile, line);  // Read the next line containing members
            fileContent += line + ", "; // Append existing members with a comma
            string newMember;
            cout << "Enter new members to add (type 'done' to finish):\n";
            bool firstAddedMember = false; // Flag to track the first new member
            while (true)
            {
                cin >> newMember;
                if (newMember == "done")
                    break; // Exit loop when 'done' is entered

                // Add a comma before the first member being added
                if (!firstAddedMember)
                {
                    fileContent += newMember;
                    firstAddedMember = true;
                }
                else
                {
                    fileContent += ", " + newMember;
                }
            }
            fileContent += "\n"; // End the updated members list
        }
        else
        {
            fileContent += line + "\n"; // Retain other groups as is
        }
    }

    if (!groupFound)
    {
        cout << "Group not found!" << endl;
    }
    else
    {
        // Rewrite the file with the updated content
        groupsFile.close();                      // Close the file before reopening it in output mode
        ofstream outFile("groups.txt");          // Open file in write mode to overwrite
        outFile << fileContent;                  // Write updated content back to the file
        outFile.close();                         // Close the file
        cout << "Members added successfully!\n"; // Confirmation message
    }

    groupsFile.close(); // Close the file
}