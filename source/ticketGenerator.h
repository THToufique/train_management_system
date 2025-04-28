#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string htmlHeader = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Train Ticket</title>
    <link rel="icon" src="img/favicon.png">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        body {
            font-family: 'Segoe UI', Arial, sans-serif;
            background: linear-gradient(135deg, #1e3c72, #2a5298);
            color: #333;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            padding: 20px;
        }
        .ticket-container {
            background: #fff;
            border-radius: 15px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
            max-width: 800px;
            width: 100%;
            overflow: hidden;
            border: 2px solid #ffd700;
        }
        header, footer {
            background: linear-gradient(to right, #ffd700, #ffaa00);
            color: #1e3c72;
            padding: 20px;
            text-align: center;
        }
        header h1 {
            font-size: 2em;
            margin-bottom: 5px;
        }
        .ticket-info, .passenger-info {
            padding: 20px;
            background: #f9f9f9;
        }
        .ticket-info h2, .passenger-info h2 {
            color: #1e3c72;
            font-size: 1.5em;
            margin-bottom: 15px;
            border-bottom: 2px solid #ffd700;
            display: inline-block;
        }
        .ticket-info p {
            font-size: 1.1em;
            margin: 10px 0;
            color: #555;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 15px;
        }
        th, td {
            padding: 12px;
            border: 1px solid #ddd;
            text-align: center;
        }
        th {
            background: #2a5298;
            color: #fff;
            font-weight: bold;
        }
        tr:nth-child(even) {
            background: #f2f2f2;
        }
        footer {
            font-size: 0.9em;
        }
        footer a {
            color: #1e3c72;
            text-decoration: none;
        }
        footer a:hover {
            text-decoration: underline;
        }
        @media (max-width: 600px) {
            .ticket-container {
                max-width: 100%;
            }
            header h1 {
                font-size: 1.5em;
            }
        }
    </style>
</head>
<body>
    <div class="ticket-container">
        <header>
            <h1>Train Booking System</h1>
            <p>Wishing you a happy and safe journey!</p>
        </header>
        <section class="ticket-info">
            <h2>Ticket Details</h2>
)";

string passengerSectionStart = R"(
        </section>
        <section class="passenger-info">
            <h2>Passenger Details</h2>
            <table>
                <tr>
                    <th>S.No</th>
                    <th>Name</th>
                    <th>Age</th>
                    <th>Gender</th>
                    <th>Seat No.</th>
                </tr>
)";

string htmlFooter = R"(
            </table>
        </section>
        <footer>
            <p>© 2025 Train Booking System. All rights reserved.</p>
            <p>Powered by Ticket Portal | <a href="#top">Back to Top</a></p>
            <p>Print this ticket: Press Ctrl + P</p>
        </footer>
    </div>
</body>
</html>
)";

string ticketInquiryNumber, trainDetails, totalPassengersStr, passengerName, gender, age, seatNumber;
int passengerCount, totalPassengers;

void printTicket();

void searchBooking()
{
    ifstream ticketFile("Tickets.txt");
    if (!ticketFile.is_open())
    {
        cout << "Error: Could not open Tickets.txt." << endl;
        return;
    }

    string searchTIN;
    cout << "Enter ticket inquiry number: ";
    cin >> searchTIN;

    string line;
    bool found = false;
    while (getline(ticketFile, line))
    {
        if (line == "Ticket inquiry number: " + searchTIN)
        {
            found = true;
            ticketInquiryNumber = line;
            getline(ticketFile, line);
            trainDetails = line;
            getline(ticketFile, line);
            totalPassengersStr = line;
            totalPassengers = stoi(totalPassengersStr.substr(28, 1));
            getline(ticketFile, line);

            for (passengerCount = 1; passengerCount <= totalPassengers; passengerCount++)
            {
                getline(ticketFile, line);
                passengerName = line.substr(15);
                getline(ticketFile, line);
                gender = line.substr(7, 8);
                age = line.substr(24);
                getline(ticketFile, line);
                seatNumber = line.substr(12);
                getline(ticketFile, line);
                printTicket();
            }
            break;
        }
    }
    ticketFile.close();

    if (!found)
    {
        cout << "Ticket not found." << endl;
    }
}

void printTicket()
{
    if (passengerCount == 1)
    {
        ofstream outputFile("yourTicket.html");
        if (!outputFile.is_open())
        {
            cout << "Error: Could not create yourTicket.html." << endl;
            return;
        }
        outputFile << htmlHeader;
        outputFile << "<p>" << ticketInquiryNumber << "</p>\n";
        outputFile << "<p>" << trainDetails << "</p>\n";
        outputFile << "<p>" << totalPassengersStr << "</p>\n";
        outputFile << passengerSectionStart;
        outputFile.close();
    }

    ofstream outputFile("yourTicket.html", ios::app);
    if (!outputFile.is_open())
    {
        cout << "Error: Could not append to yourTicket.html." << endl;
        return;
    }
    outputFile << "<tr><td>" << passengerCount << "</td><td>" << passengerName << "</td><td>" << age << "</td><td>" << gender << "</td><td>" << seatNumber << "</td></tr>\n";
    outputFile.close();

    if (passengerCount == totalPassengers)
    {
        ofstream outputFile("yourTicket.html", ios::app);
        if (!outputFile.is_open())
        {
            cout << "Error: Could not append to yourTicket.html." << endl;
            return;
        }
        outputFile << htmlFooter;
        outputFile.close();
        cout << "Your ticket has been generated successfully as 'yourTicket.html'." << endl;
    }
}