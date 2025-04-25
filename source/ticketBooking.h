#ifndef TICKETBOOKING_H
#define TICKETBOOKING_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Administration.h"
#include "decoration.h"
#include "ticketGenerator.h"
using namespace std;

class TicketBooking
{
private:
	TrainManagement &train;
	int bookedSeats;
	string ticketInquiryNum;
	struct Passenger
	{
		string name;
		string gender;
		int age;
		string seatNumber;
	};
	vector<Passenger> passengers;

	void saveTicketToFile(const string &inquiryNum)
	{
		ofstream outFile("Tickets.txt", ios::app);
		if (!outFile.is_open())
		{
			cout << RED << "[!] Error: Could not save ticket to Tickets.txt.\n"
				 << RESET;
			return;
		}
		outFile << "Ticket inquiry number: " << inquiryNum << endl;
		outFile << "Train: " << train.getTrainNumber().substr(13) << " " << train.getTrainName().substr(14) << endl;
		outFile << "Total number of passengers: " << bookedSeats << endl;
		outFile << "\n";
		for (const auto &p : passengers)
		{
			outFile << "Passenger name: " << p.name << endl;
			outFile << "Gender: " << p.gender << "      Age: " << p.age << endl;
			outFile << "Seat number: " << p.seatNumber << endl;
			outFile << "\n";
		}
		outFile << "__________________________\n";
		outFile.close();
	}

public:
	TicketBooking(TrainManagement &t) : train(t), bookedSeats(0), ticketInquiryNum("") {}

	void loadTrainData(const string &trainNum)
	{
		ifstream inFile("train.txt");
		if (!inFile)
		{
			cout << "No trains available.\n";
			return;
		}
		string line;
		string searchNum = "Train number: " + trainNum;
		while (getline(inFile, line))
		{
			if (line == searchNum)
			{
				train.setTrainNumber(line);
				getline(inFile, line);
				train.setTrainName(line);
				getline(inFile, line);
				train.setTrainRoute(line);
				getline(inFile, line);
				train.setNumberOfSeats(line);
				getline(inFile, line);
				train.setTrainTime(line);
				getline(inFile, line);
				train.setTrainFare(line);
				bookedSeats = 0;
				passengers.clear();
				ticketInquiryNum = "";
				inFile.close();
				return;
			}
		}
		inFile.close();
		cout << "Train not found.\n";
	}

	void displayAvailableSeats() const
	{
		string seatsStr = train.getNumberOfSeats();
		int totalSeats = stoi(seatsStr.substr(seatsStr.find(": ") + 2));
		cout << "Available seats: " << (totalSeats - bookedSeats) << " / " << totalSeats << endl;
	}

	bool bookTicket(int numSeats, const vector<Passenger> &newPassengers)
	{
		string seatsStr = train.getNumberOfSeats();
		int totalSeats = stoi(seatsStr.substr(seatsStr.find(": ") + 2));
		if (numSeats <= 0 || numSeats > (totalSeats - bookedSeats))
		{
			cout << "Invalid number of seats or not enough available seats.\n";
			return false;
		}
		bookedSeats += numSeats;
		for (const auto &p : newPassengers)
		{
			passengers.push_back(p);
		}
		cout << "Successfully booked " << numSeats << " seat(s)!\n";
		return true;
	}

	bool bookTicketWithDetails(const string &inquiryNum)
	{
		ticketInquiryNum = inquiryNum;
		int numSeats;
		cout << "Enter total number of passengers: ";
		cin >> numSeats;
		string seatsStr = train.getNumberOfSeats();
		int totalSeats = stoi(seatsStr.substr(seatsStr.find(": ") + 2));
		if (numSeats <= 0 || numSeats > (totalSeats - bookedSeats))
		{
			cout << "Invalid number of seats or not enough available seats.\n";
			return false;
		}

		vector<Passenger> newPassengers;
		vector<string> bookedSeatNumbers;
		for (const auto &p : passengers)
		{
			bookedSeatNumbers.push_back(p.seatNumber);
		}

		for (int i = 0; i < numSeats; i++)
		{
			Passenger p;
			cout << "\nPassenger " << (i + 1) << ":\n";
			cout << "Enter passenger name: ";
			cin >> p.name;
			cout << "Enter gender: ";
			cin >> p.gender;
			cout << "Enter age: ";
			cin >> p.age;
			seatNumberShow(bookedSeatNumbers);
			cin >> p.seatNumber;
			if (stoi(p.seatNumber) < 1 || stoi(p.seatNumber) > 55 || find(bookedSeatNumbers.begin(), bookedSeatNumbers.end(), p.seatNumber) != bookedSeatNumbers.end())
			{
				cout << RED << "[!] Invalid or already booked seat number.\n"
					 << RESET;
				return false;
			}
			bookedSeatNumbers.push_back(p.seatNumber);
			newPassengers.push_back(p);
		}
		if (bookTicket(numSeats, newPassengers))
		{
			saveTicketToFile(inquiryNum);
			displayTicket(inquiryNum);
			return true;
		}
		return false;
	}

	void cancelTicket()
	{
		int numSeats;
		cout << "Enter number of seats to cancel: ";
		cin >> numSeats;
		if (numSeats <= 0 || numSeats > bookedSeats)
		{
			cout << "Invalid number of seats to cancel.\n";
			return;
		}
		bookedSeats -= numSeats;
		passengers.resize(bookedSeats);
		cout << "Cancelled " << numSeats << " seat(s).\n";
	}

	void viewBookings() const
	{
		if (bookedSeats == 0)
		{
			cout << "No bookings yet.\n";
			return;
		}
		cout << "Booking Details:\n";
		train.displayTrainData();
		cout << "Booked seats: " << bookedSeats << endl;
		displayAvailableSeats();
	}

	void displayTicket(const string &inquiryNum) const
	{
		if (bookedSeats == 0)
		{
			cout << "No bookings to display.\n";
			return;
		}
		cout << "Ticket inquiry number: " << inquiryNum << endl;
		cout << "Train: " << train.getTrainNumber().substr(13) << " " << train.getTrainName().substr(14) << endl;
		cout << "Total number of passengers: " << bookedSeats << "\n\n";
		for (const auto &p : passengers)
		{
			cout << "Passenger name: " << p.name << endl;
			cout << "Gender: " << p.gender << "      Age: " << p.age << endl;
			cout << "Seat number: " << p.seatNumber << "\n";
		}
		cout << "__________________________\n";
	}

	void printTicket() const
	{
		searchBooking();
	}

	string getInquiryNumber() const { return ticketInquiryNum; }
};

#endif