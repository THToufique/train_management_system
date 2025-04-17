#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "source/Administration.h"
#include "source/ticketBooking.h"
#include "source/decoration.h"
using namespace std;

bool signup(const string &role)
{
    string username, password;
    cout << ">> Enter username: ";
    cin >> username;
    cout << ">> Enter password: ";
    cin >> password;

    string filename = (role == "Admin") ? "admins.txt" : "users.txt";
    ifstream inFile(filename);
    string line;
    while (getline(inFile, line))
    {
        if (line == username)
        {
            cout << RED << "[!] Username already taken!\n"
                 << RESET;
            inFile.close();
            return false;
        }
        getline(inFile, line);
    }
    inFile.close();

    ofstream outFile(filename, ios::app);
    outFile << username << endl
            << password << endl;
    outFile.close();
    cout << GREEN << "[+] Signup successful!\n"
         << RESET;
    return true;
}

bool login(const string &role, string &username)
{
    string password;
    cout << ">> Enter username: ";
    cin >> username;
    cout << ">> Enter password: ";
    cin >> password;

    string filename = (role == "Admin") ? "admins.txt" : "users.txt";
    ifstream inFile(filename);
    string storedUser, storedPass;
    while (getline(inFile, storedUser))
    {
        getline(inFile, storedPass);
        if (storedUser == username && storedPass == password)
        {
            inFile.close();
            cout << GREEN << "[+] Login successful!\n"
                 << RESET;
            return true;
        }
    }
    inFile.close();
    cout << RED << "[!] Invalid username or password.\n"
         << RESET;
    return false;
}

void handleAuthMenu(const string &role, bool &authenticated, string &username)
{
    int choice;
    while (true)
    {
        printHeader();
        loginpage2();
        cin >> choice;

        switch (choice)
        {
        case 1:
            signup(role);
            break;
        case 2:
            if (login(role, username))
            {
                authenticated = true;
                return;
            }
            break;
        case 0:
            cout << YELLOW << "Exiting Train Xpress...\n"
                 << RESET;
            exit(0);
        default:
            cout << RED << "[!] Invalid option. Try again.\n"
                 << RESET;
        }
        cout << "\nPress any key to continue . . .";
        cin.ignore();
        cin.get();
    }
}

void handleAdminMenu(TrainManagement &trainManager, TicketBooking &ticketBooker)
{
    int choice;
    while (true)
    {
        printHeader();
        adminMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            trainManager.addNewTrain();
            break;
        case 2:
            trainManager.viewTrains();
            break;
        case 3:
            trainManager.searchTrain();
            break;
        case 4:
            ticketBooker.viewBookings();
            break;
        case 5:
            trainManager.deleteTrain();
            break;
        case 6:
        {
            UpdateTrain updater(trainManager);
            updater.dataUpdate();
            break;
        }
        case 0:
            cout << YELLOW << "Logging out...\n"
                 << RESET;
            return;
        default:
            cout << RED << "[!] Invalid option. Try again.\n"
                 << RESET;
        }
        cout << "\nPress any key to continue . . .";
        cin.ignore();
        cin.get();
    }
}

bool changePassword(const string &username)
{
    passwordMenu();
    string currentPass, newPass, confirmPass;
    cin >> currentPass;

    ifstream inFile("users.txt");
    string storedUser, storedPass;
    bool found = false;
    vector<string> fileContent;

    while (getline(inFile, storedUser))
    {
        getline(inFile, storedPass);
        fileContent.push_back(storedUser);
        fileContent.push_back(storedPass);
        if (storedUser == username && storedPass == currentPass)
        {
            found = true;
        }
    }
    inFile.close();

    if (!found)
    {
        cout << RED << "[!] Current password is incorrect.\n"
             << RESET;
        return false;
    }

    cout << "Enter new password: ";
    cin >> newPass;
    cout << "Confirm new password: ";
    cin >> confirmPass;

    if (newPass != confirmPass)
    {
        cout << RED << "[!] Passwords do not match.\n"
             << RESET;
        return false;
    }

    ofstream outFile("users.txt");
    for (size_t i = 0; i < fileContent.size(); i += 2)
    {
        outFile << fileContent[i] << endl;
        if (fileContent[i] == username)
        {
            outFile << newPass << endl;
        }
        else
        {
            outFile << fileContent[i + 1] << endl;
        }
    }
    outFile.close();

    cout << GREEN << "[+] Password changed successfully!\n"
         << RESET;
    return true;
}

void handleUserMenu(TrainManagement &trainManager, TicketBooking &ticketBooker, const string &username)
{
    int choice;
    string selectedTrainNum;
    bool trainSelected = false;
    string inquiryNum;

    srand(static_cast<unsigned>(time(0)));

    while (true)
    {
        printHeader();
        userMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            trainManager.viewTrains();
            break;
        case 2:
            trainManager.searchTrain();
            break;
        case 3:
        {
            if (!trainSelected)
            {
                cout << "Enter Train Number to book: ";
                cin >> selectedTrainNum;
                ticketBooker.loadTrainData(selectedTrainNum);
                trainSelected = true;
            }
            inquiryNum = to_string(1000 + (rand() % 9000));
            cout << "Ticket inquiry number assigned: " << inquiryNum << endl;
            ticketBooker.bookTicketWithDetails(inquiryNum);
            break;
        }
        case 4:
            ticketBooker.printTicket();
            break;
        case 5:
            changePassword(username);
            break;
        case 6:
            if (!trainSelected)
            {
                cout << "Enter Train Number to cancel: ";
                cin >> selectedTrainNum;
                ticketBooker.loadTrainData(selectedTrainNum);
                trainSelected = true;
            }
            ticketBooker.cancelTicket();
            break;
        case 0:
            cout << YELLOW << "Logging out...\n"
                 << RESET;
            return;
        default:
            cout << RED << "[!] Invalid option. Try again.\n"
                 << RESET;
        }
        cout << "\nPress any key to continue . . .";
        cin.ignore();
        cin.get();
    }
}

int main()
{
    TrainManagement trainManager;
    TicketBooking ticketBooker(trainManager);

    loading();
    cin.get();

    int roleChoice;
    bool authenticated = false;
    string username;

    while (!authenticated)
    {
        printHeader();
        loginpage1();
        cin >> roleChoice;

        if (roleChoice == 0)
        {
            cout << YELLOW << "Exiting Train Xpress...\n"
                 << RESET;
            return 0;
        }
        else if (roleChoice == 1)
        {
            handleAuthMenu("Admin", authenticated, username);
            if (authenticated)
            {
                handleAdminMenu(trainManager, ticketBooker);
            }
        }
        else if (roleChoice == 2)
        {
            handleAuthMenu("User", authenticated, username);
            if (authenticated)
            {
                handleUserMenu(trainManager, ticketBooker, username);
            }
        }
        else
        {
            cout << RED << "[!] Invalid option. Try again.\n"
                 << RESET;
            cout << "\nPress any key to continue . . .";
            cin.ignore();
            cin.get();
        }
    }

    cout << "\nPress any key to exit . . .";
    cin.ignore();
    cin.get();

    return 0;
}