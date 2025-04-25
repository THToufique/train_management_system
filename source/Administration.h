#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class TrainManagement
{
private:
    string trainNumber;
    string trainName;
    string trainRoute;
    string numberOfSeats;
    string trainTime;
    string trainFare;
    string tempData;

    void updateFile(const string &oldLine, const string &newLine)
    {
        ifstream inFile("train.txt");
        ofstream outFile("temp.txt");
        string line;
        while (getline(inFile, line))
        {
            if (line == oldLine)
            {
                outFile << newLine << endl;
            }
            else
            {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove("train.txt");
        rename("temp.txt", "train.txt");
    }

public:
    TrainManagement()
    {
        trainNumber = "Train number: Unknown";
        trainName = "Name of train: Unknown";
        trainRoute = "Route: Unknown";
        numberOfSeats = "Number of seats: 0";
        trainTime = "Timing: Unknown";
        trainFare = "Fare: 0";
    }

    string getTrainNumber() const { return trainNumber; }
    string getTrainName() const { return trainName; }
    string getTrainRoute() const { return trainRoute; }
    string getNumberOfSeats() const { return numberOfSeats; }
    string getTrainTime() const { return trainTime; }
    string getTrainFare() const { return trainFare; }
    string getTempData() const { return tempData; }

    void setTrainNumber(const string &num) { trainNumber = num; }
    void setTrainName(const string &name) { trainName = name; }
    void setTrainRoute(const string &route) { trainRoute = route; }
    void setNumberOfSeats(const string &seats) { numberOfSeats = seats; }
    void setTrainTime(const string &time) { trainTime = time; }
    void setTrainFare(const string &fare) { trainFare = fare; }
    void setTempData(const string &data) { tempData = data; }

    void updateFilePublic(const string &oldLine, const string &newLine)
    {
        updateFile(oldLine, newLine);
    }

    void displayTrainData() const
    {
        cout << trainNumber << endl;
        cout << trainName << endl;
        cout << trainRoute << endl;
        cout << numberOfSeats << endl;
        cout << trainTime << endl;
        cout << trainFare << endl;
    }

    void addNewTrain()
    {
        char addMore;
        do
        {
            string num, name, route, seats, time, fare;
            cout << "Enter train number (4 digits): ";
            cin >> num;
            if (num.length() != 4 || !isdigit(num[0]) || !isdigit(num[1]) || !isdigit(num[2]) || !isdigit(num[3]))
            {
                cout << "Invalid train number! Must be 4 digits.\n";
                return;
            }
            cout << "Enter train name: ";
            cin >> name;
            cout << "Enter trainRoute: ";
            cin >> route;
            cout << "Enter timings (eg. 6:00pm-7:00am): ";
            cin >> time;
            cout << "Enter number of seats: ";
            cin >> seats;
            cout << "Enter fare: ";
            cin >> fare;

            ofstream outFile("train.txt", ios::app);
            outFile << "Train number: " << num << endl;
            outFile << "Name of train: " << name << endl;
            outFile << "Route: " << route << endl;
            outFile << "Number of seats: " << seats << endl;
            outFile << "Timing: " << time << endl;
            outFile << "Fare: " << fare << endl;
            outFile.close();

            setTrainNumber("Train number: " + num);
            setTrainName("Name of train: " + name);
            setTrainRoute("Route: " + route);
            setNumberOfSeats("Number of seats: " + seats);
            setTrainTime("Timing: " + time);
            setTrainFare("Fare: " + fare);
            cout << "Train added!\n";

            cout << "Do you want to add more? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');
    }

    void viewTrains()
    {
        ifstream inFile("train.txt");
        if (!inFile)
        {
            cout << "No trains available.\n";
            return;
        }
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
    }

    void searchTrain()
    {
        cout << "Enter Train Number to search: ";
        string searchNum;
        cin >> searchNum;
        searchNum = "Train number: " + searchNum;
        ifstream inFile("train.txt");
        if (!inFile)
        {
            cout << "No trains available.\n";
            return;
        }
        string line;
        bool found = false;
        while (getline(inFile, line))
        {
            if (line == searchNum)
            {
                found = true;
                cout << line << endl;
                for (int i = 0; i < 5; i++)
                {
                    getline(inFile, line);
                    cout << line << endl;
                }
                break;
            }
        }
        if (!found)
            cout << "Train not found.\n";
        inFile.close();
    }

    void deleteTrain()
    {
        cout << "Enter Train Number to delete: ";
        string delNum;
        cin >> delNum;
        delNum = "Train number: " + delNum;
        ifstream inFile("train.txt");
        ofstream outFile("temp.txt");
        string line;
        bool found = false;
        while (getline(inFile, line))
        {
            if (line == delNum)
            {
                found = true;
                for (int i = 0; i < 5; i++)
                    getline(inFile, line);
            }
            else
            {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();
        remove("train.txt");
        rename("temp.txt", "train.txt");
        if (found)
            cout << "Train deleted!\n";
        else
            cout << "Train not found.\n";
    }
};

class UpdateTrain
{
private:
    TrainManagement &train;
    string currentNumber;

public:
    UpdateTrain(TrainManagement &t) : train(t) {}

    void loadTrainData()
    {
        ifstream trainFile("train.txt");
        if (!trainFile)
        {
            cout << "Error opening train.txt" << endl;
            return;
        }
        string tempData;
        string result = train.getTrainNumber();
        while (getline(trainFile, tempData))
        {
            if (tempData == result.substr(0, tempData.length()))
            {
                currentNumber = tempData;
                string name, route, seats, time, fare;
                getline(trainFile, name);
                getline(trainFile, route);
                getline(trainFile, seats);
                getline(trainFile, time);
                getline(trainFile, fare);
                train.setTrainNumber(currentNumber);
                train.setTrainName(name);
                train.setTrainRoute(route);
                train.setNumberOfSeats(seats);
                train.setTrainTime(time);
                train.setTrainFare(fare);
            }
        }
        trainFile.close();
    }

    void updateTrainNumber(const string &newNumber)
    {
        train.updateFilePublic(train.getTrainNumber(), "Train number: " + newNumber);
        train.setTrainNumber("Train number: " + newNumber);
    }

    void updateTrainName(const string &newName)
    {
        train.updateFilePublic(train.getTrainName(), "Name of train: " + newName);
        train.setTrainName("Name of train: " + newName);
    }

    void updateTrainRoute(const string &newRoute)
    {
        train.updateFilePublic(train.getTrainRoute(), "Route: " + newRoute);
        train.setTrainRoute("Route: " + newRoute);
    }

    void updateTrainNumberOfSeats(const string &newSeats)
    {
        train.updateFilePublic(train.getNumberOfSeats(), "Number of seats: " + newSeats);
        train.setNumberOfSeats("Number of seats: " + newSeats);
    }

    void updateTrainTime(const string &newTime)
    {
        train.updateFilePublic(train.getTrainTime(), "Timing: " + newTime);
        train.setTrainTime("Timing: " + newTime);
    }

    void updateTrainFare(const string &newFare)
    {
        train.updateFilePublic(train.getTrainFare(), "Fare: " + newFare);
        train.setTrainFare("Fare: " + newFare);
    }

    void dataUpdate()
    {
        loadTrainData();
        cout << "Current Train Data:\n";
        train.displayTrainData();
        cout << "Enter new train number: ";
        string newNumber;
        cin >> newNumber;
        updateTrainNumber(newNumber);
        cout << "Train data updated!\n";
    }
};

#endif