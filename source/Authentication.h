#include <fstream>
#include <string>
#include <cstdlib>
#include "decoration.h"

string currentUsername;
string currentPassword;

class Auth
{
private:
    string username;
    string password;

    bool usernameExists(const string &checkUsername)
    {
        ifstream loginFile("login.txt");
        if (!loginFile.is_open())
        {
            cout << "Error: Could not open login.txt for reading." << endl;
            return false;
        }
        string line;
        while (loginFile >> line)
        {
            if (line == "Username:" + checkUsername)
            {
                loginFile.close();
                return true;
            }
        }
        loginFile.close();
        return false;
    }

public:
    bool signup(char userType)
    {
        ofstream signupFile("login.txt", ios::app);
        if (!signupFile.is_open())
        {
            cout << "Error: Could not open login.txt for writing." << endl;
            return false;
        }

        while (true)
        {
            cout << "\nEnter username: ";
            cin >> username;
            if (usernameExists(username))
            {
                cout << "Username already exists. Please choose a different one." << endl;
                continue;
            }
            break;
        }

        cout << "\nEnter password: ";
        cin >> password;

        if (userType == '1')
        {
            signupFile << "Type: admin" << endl;
        }
        else if (userType == '2')
        {
            signupFile << "Type: user" << endl;
        }
        signupFile << "Username:" << username << endl;
        signupFile << "Password:" << password << endl
                   << endl;
        signupFile.close();
        return true;
    }

    bool login(char userType)
    {
        ifstream loginFile("login.txt");
        if (!loginFile.is_open())
        {
            cout << "Error: Could not open login.txt for reading." << endl;
            return false;
        }

        cout << "\nEnter username: ";
        cin >> username;
        currentUsername = username;
        cout << "\nEnter password: ";
        cin >> password;
        currentPassword = password;

        string typeLine = (userType == '1') ? "Type: admin" : "Type: user";
        string userLine = "Username:" + username;
        string passLine = "Password:" + password;
        string line;

        while (getline(loginFile, line))
        {
            if (line == typeLine)
            {
                getline(loginFile, line);
                if (line == userLine)
                {
                    getline(loginFile, line);
                    if (line == passLine)
                    {
                        loginFile.close();
                        return true;
                    }
                }
            }
        }
        loginFile.close();
        return false;
    }
};

void printWelcomeMessage()
{
    cout << "Hello " << currentUsername << ", Welcome back!" << endl;
}

bool changePassword()
{
    passwordMenu();
    string oldPassword;
    cout << "Enter current password: ";
    cin >> oldPassword;

    if (oldPassword != currentPassword)
    {
        return false;
    }

    string newPassword;
    cout << "\nEnter new password: ";
    cin >> newPassword;

    ifstream loginFile("login.txt");
    ofstream tempFile("TempFile.txt");
    if (!loginFile.is_open() || !tempFile.is_open())
    {
        cout << "Error: Could not open files for password update." << endl;
        return false;
    }

    string line;
    while (getline(loginFile, line))
    {
        tempFile << (line == "Password:" + currentPassword ? "Password:" + newPassword : line) << endl;
    }

    loginFile.close();
    tempFile.close();
    remove("login.txt");
    rename("TempFile.txt", "login.txt");
    currentPassword = newPassword;
    return true;
}

void processUserChoice(char userType)
{
    Auth auth;
    while (true)
    {
        char choice;
        printHeader();
        cout << "\nSelect an option: ";
        cin >> choice;

        if (choice == '1')
        {
            cout << "                            -----SIGNUP-----" << endl;
            cout << "-------------------------------------------------------------------------" << endl;
            if (auth.signup(userType))
            {
                cout << "\n\t\tYour account has been created successfully....\n"
                     << endl;
                system("pause");
                exit(0);
            }
        }
        else if (choice == '2')
        {
            cout << "                            -----LOGIN-----" << endl;
            cout << "-------------------------------------------------------------------------" << endl;
            while (true)
            {
                if (auth.login(userType))
                {
                    cout << "\n\t\t\tLogin successful....\n"
                         << endl;
                    system("pause");
                    return;
                }
                else
                {
                    cout << "Login failed" << endl;
                    system("pause");
                    cout << "Try again? (y/n): ";
                    char retry;
                    cin >> retry;
                    if (retry != 'y' && retry != 'Y')
                    {
                        exit(0);
                    }
                }
            }
        }
        else if (choice == '0')
        {
            cout << "Thanks for reaching out !!" << endl;
            system("pause");
            exit(0);
        }
        else
        {
            cout << "Invalid input" << endl;
            system("pause");
        }
    }
}