#ifndef DECORATION_H
#define DECORATION_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string BOLD = "\033[1m";

void loading()
{
     system("cls");
     cout << RED << "  .::[ TRAIN XPRESS ]::.\n";
     cout << "  +---------------------+\n";
     cout << "  |  ALL ABOARD!       |\n";
     cout << "  +---------------------+\n";
     cout << "  /~~~~~~~~~~~~~~~~~~~~~\\\n";
     cout << " /|  ***  ***  ***  *** |\\\n";
     cout << "( |_____________________| )\n";
     cout << " | [][][][][][][][][][] |\n";
     cout << " | [][][][][][][][][][] |\n";
     cout << " `~~~~~~~~~~~~~~~~~~~~~'\n"
          << RESET;
     cout << BOLD << YELLOW << "  Welcome to Train Xpress!\n"
          << RESET;
     cout << CYAN << "  Your ticket to a smooth ride awaits.\n";
     cout << "  Log in or sign up to get on track!\n"
          << RESET;
     cout << "\n  Press Enter to start your journey...";
}

void printHeader()
{
     system("cls");
     cout << CYAN << "  +-----------------------------+\n";
     cout << BOLD << "  |    TRAIN XPRESS TERMINAL   |\n";
     cout << "  +-----------------------------+\n"
          << RESET;
     cout << YELLOW << "  Embark on your journey with us!\n"
          << RESET;
     cout << "\n";
}

void adminMenu()
{
     cout << CYAN << "-------------------------------------------------------------------------\n";
     cout << BOLD << "                         -----ADMIN MAIN MENU-----\n";
     cout << "-------------------------------------------------------------------------\n"
          << RESET;
     cout << GREEN << "\n1. Add Train                                    2. Display Trains\n";
     cout << "\n3. Search Trains                                4. Display Bookings\n";
     cout << "\n5. Delete Train                                 6. Update\n";
     cout << "\n0. Logout\n\n"
          << RESET;
     cout << CYAN << "-------------------------------------------------------------------------\n";
     cout << "Select an option: ";
}

void userMenu()
{
     cout << CYAN << "-------------------------------------------------------------------------\n";
     cout << BOLD << "                  -----TRAIN BOOKING TICKET SERVICE-----\n";
     cout << "-------------------------------------------------------------------------\n"
          << RESET;
     cout << "\n"
          << YELLOW << "Welcome to our Train Booking System. Begin your journey with us!\n"
          << RESET;
     cout << "\n"
          << YELLOW << "Hello user, Welcome back!\n"
          << RESET;
     cout << CYAN << "-------------------------------------------------------------------------\n";
     cout << BOLD << "                         -----USER MAIN MENU-----\n";
     cout << "-------------------------------------------------------------------------\n"
          << RESET;
     cout << GREEN << "\n1. Display Trains                               2. Search Trains\n";
     cout << "\n3. Book Ticket                                  4. Print Ticket\n";
     cout << "\n5. Change Password                              6. Cancel Ticket\n";
     cout << "\n0. Logout\n\n"
          << RESET;
     cout << CYAN << "-------------------------------------------------------------------------\n";
     cout << "Select an option: ";
}

void loginpage1()
{
     cout << CYAN << "  +-----------------------------+\n";
     cout << BOLD << "  |       ACCESS GATEWAY       |\n";
     cout << "  +-----------------------------+\n"
          << RESET;
     cout << GREEN << "  ------------- \n";
     cout << "  | 1. Admin    |\n";
     cout << "  ------------- \n";
     cout << "  | 2. Passenger|\n";
     cout << "  ------------- \n";
     cout << "  | 0. Exit     |\n";
     cout << "  ------------- \n"
          << RESET;
     cout << CYAN << "  +-----------------------------+\n";
     cout << "  >> Select your role: ";
}

void loginpage2()
{
     cout << CYAN << "  +-----------------------------+\n";
     cout << BOLD << "  |      AUTHENTICATION        |\n";
     cout << "  +-----------------------------+\n"
          << RESET;
     cout << GREEN << "  ------------- \n";
     cout << "  | 1. Sign Up  |\n";
     cout << "  ------------- \n";
     cout << "  | 2. Log In   |\n";
     cout << "  ------------- \n";
     cout << "  | 0. Exit     |\n";
     cout << "  ------------- \n"
          << RESET;
     cout << CYAN << "  +-----------------------------+\n";
     cout << "  >> Select an option: ";
}

void seatNumberShow(const vector<string> &bookedSeats)
{
     system("cls");
     cout << CYAN << "  +-----------------------------+\n";
     cout << BOLD << "  |      SEAT SELECTION        |\n";
     cout << "  +-----------------------------+\n"
          << RESET;
     cout << "  SL   SU   LB   MB   UB\n";
     cout << "  ------------------------ \n";
     for (int i = 1; i <= 55; i += 5)
     {
          for (int j = 0; j < 5; j++)
          {
               string seatNum = (i + j < 10 ? "0" : "") + to_string(i + j);
               bool isBooked = false;
               for (const auto &booked : bookedSeats)
               {
                    if (booked == seatNum)
                    {
                         isBooked = true;
                         break;
                    }
               }
               if (isBooked)
               {
                    cout << RED << "BOOKED" << RESET;
               }
               else
               {
                    cout << GREEN << seatNum << RESET;
               }
               cout << (j < 4 ? "  " : "\n");
          }
     }
     cout << CYAN << "  +-----------------------------+\n";
     cout << "  >> Choose your seat number: ";
}

void paymentPage(int amount)
{
     cout << CYAN << "  +-----------------------------+\n";
     cout << BOLD << "  |      PAYMENT STATION       |\n";
     cout << "  +-----------------------------+\n"
          << RESET;
     cout << BOLD << "  Total Fare: Rs. " << amount << "\n"
          << RESET;
     cout << "  Select Payment Method:\n";
     cout << GREEN << "  ------------- \n";
     cout << "  | 1. Cash     |\n";
     cout << "  ------------- \n";
     cout << "  | 2. Card     |\n";
     cout << "  ------------- \n";
     cout << "  | 3. UPI      |\n";
     cout << "  ------------- \n"
          << RESET;
     cout << CYAN << "  +-----------------------------+\n";
     cout << "  >> Select an option: ";
}

void passwordMenu()
{
     system("cls");
     cout << CYAN << "  +-----------------------------+\n";
     cout << BOLD << "  |      PASSWORD UPDATE       |\n";
     cout << "  +-----------------------------+\n"
          << RESET;
     cout << "  Enter your current password: ";
}

void updateTrainMenu()
{
     system("cls");
     cout << CYAN << "  +-----------------------------+\n";
     cout << BOLD << "  |     TRAIN UPDATE PANEL     |\n";
     cout << "  +-----------------------------+\n"
          << RESET;
     cout << "  What needs updating?\n";
     cout << GREEN << "  ----------------------------- \n";
     cout << "  | 1. Train No | 2. Train Name |\n";
     cout << "  ----------------------------- \n";
     cout << "  | 3. Route    | 4. Seats      |\n";
     cout << "  ----------------------------- \n";
     cout << "  | 5. Time     | 6. Fare       |\n";
     cout << "  ----------------------------- \n";
     cout << "  | 0. Back     |               |\n";
     cout << "  ----------------------------- \n"
          << RESET;
     cout << CYAN << "  +-----------------------------+\n";
     cout << "  >> Select an option: ";
}

#endif