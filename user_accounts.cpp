#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_USERS = 25; // test number of max users
int userCount = 0;        // Keeps track of the number of users loaded from the file

// Function to create a new user account
void createnewaccount()
{
    string credential, name, password;

    cout << "Enter email/number/username to create new account: ";
    cin >> credential;

    // Check if the credential already exists in the file
    ifstream inputFile("accounts.txt"); // Open the accounts file for reading
    string line;
    bool exists = false;

    while (getline(inputFile, line))
    {                                                         // Read each line from the file
        size_t firstComma = line.find(',');                   // Find the first comma (separator)
        string storedCredential = line.substr(0, firstComma); // Extract the stored credential

        if (storedCredential == credential)
        { // Check if the credential already exists
            exists = true;
            break;
        }
    }
    inputFile.close(); // Close the file after reading

    if (exists)
    { // If the credential already exists, print an error and exit
        cout << "Error: The input email/number/username already exists\n"
             << endl;
        return;
    }

    // Prompt user for additional details to create the account
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter password for your new account: ";
    cin >> password;

    // Append the new account details to the file
    ofstream file("accounts.txt", ios::app);                      // Open the file in append mode
    file << credential << "," << name << "," << password << endl; // Write the details
    file.close();                                                 // Close the file

    cout << "New account created successfully!" << endl;
}

// Function to log in to an existing user account
bool login()
{
    string enteredEmail, enteredPass;
    string credentials[MAX_USERS]; // Array to store credentials loaded from the file
    string passwords[MAX_USERS];   // Array to store passwords loaded from the file

    // Load account data from file
    ifstream file("accounts.txt"); // Open the accounts file for reading
    string line;

    while (getline(file, line) && userCount < MAX_USERS)
    {                                                        // Read each line and ensure we don’t exceed MAX_USERS
        size_t firstComma = line.find(',');                  // Find the first comma (separator)
        size_t secondComma = line.find(',', firstComma + 1); // Find the second comma

        // Extract the email and password from the line
        string email = line.substr(0, firstComma);  // Extract email/username
        string pass = line.substr(secondComma + 1); // Extract password

        credentials[userCount] = email; // Store email in the array
        passwords[userCount] = pass;    // Store password in the array

        userCount++; // Increment the user count
    }

    file.close(); // Close the file after reading

    // Prompt user for login credentials
    cout << "Enter email/number/username: ";
    cin >> enteredEmail;
    cout << "Enter password: ";
    cin >> enteredPass;

    // Check if the entered credentials match any stored account
    for (int i = 0; i < userCount; i++)
    {
        if (credentials[i] == enteredEmail && passwords[i] == enteredPass)
        { // Successful login
            cout << "Login successful! Welcome!" << endl;
            cout << endl;
            return true;
        }
    }

    // If no match is found, display an error message
    cout << "Incorrect email/number/username or password!" << endl
         << endl;
    return false;
}