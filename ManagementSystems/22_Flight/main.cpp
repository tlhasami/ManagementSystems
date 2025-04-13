#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Person
{
    bool isBooked;
    string name;
    int flightId;
    int seatRow;
    int seatCol;

public:
    Person()
    {
        isBooked = false;
        name = "";
        flightId = 0;
        seatRow = -1;
        seatCol = -1;
    }

    void setDetails(string n, int id, int row, int col)
    {
        name = n;
        flightId = id;
        seatRow = row;
        seatCol = col;
        isBooked = true;
    }

    void setName(string n)
    {
        name = n;
    }

    void setSeatRow(int row)
    {
        seatRow = row;
    }

    void setSeatCol(int col)
    {
        seatCol = col;
    }

    string getName()
    {
        return name;
    }

    int getFlightId()
    {
        return flightId;
    }

    int getSeatRow()
    {
        return seatRow;
    }

    int getSeatCol()
    {
        return seatCol;
    }

    void showInfo()
    {
        cout << "-----------------------------" << endl;
        cout << "Passenger Name : " << name << endl;
        cout << "Flight ID      : " << flightId << endl;
        cout << "Seat Row       : " << seatRow + 1 << endl;
        cout << "Seat Column    : " << seatCol + 1 << endl;
        cout << "Booking Status : " << (isBooked ? "Booked" : "Not Booked") << endl;
        cout << "-----------------------------" << endl;
    }
};

class Flight
{
    char seats[10][5];
    Person passengers[50];
    int passengerCount;

public:
    Flight()
    {
        passengerCount = 0;
        
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                seats[i][j] = 'O';
            }
        }
    }

    void bookSeat()
    {
        if (passengerCount >= 50)
        {
            cout << "Flight is full!" << endl;
            return;
        }

        string name;
        int id, row, col;

        cout << "Enter Passenger Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Flight ID (must be unique): ";
        cin >> id;

        
        for (int i = 0; i < passengerCount; i++)
        {
            if (passengers[i].getFlightId() == id)
            {
                cout << "Flight ID already exists. Try again." << endl;
                return;
            }
        }

        cout << "Enter Seat Row (1 to 10): ";
        cin >> row;
        cout << "Enter Seat Column (1 to 5): ";
        cin >> col;

        row--; 
        col--;

        if (row < 0 || row >= 10 || col < 0 || col >= 5)
        {
            cout << "Invalid seat location!" << endl;
            return;
        }

        if (seats[row][col] == 'X')
        {
            cout << "Seat already taken!" << endl;
            return;
        }

        
        seats[row][col] = 'X';

        
        passengers[passengerCount].setDetails(name, id, row, col);
        passengerCount++;

        cout << "Seat booked successfully!" << endl;
    }

    void changeDetails()
    {
        int id;
        cout << "Enter your Flight ID: ";
        cin >> id;

        bool found = false;

        for (int i = 0; i < passengerCount; i++)
        {
            if (passengers[i].getFlightId() == id)
            {
                found = true;

                cout << "What do you want to change?" << endl;
                cout << "1. Name" << endl;
                cout << "2. Seat Row" << endl;
                cout << "3. Seat Column" << endl;
                cout << "Enter choice: ";

                int choice;
                cin >> choice;

                
                if (cin.fail())
                {
                    cin.clear();           
                    cin.ignore(100, '\n'); 
                    cout << "Invalid input! Please enter a valid choice." << endl;
                    return;
                }

                if (choice == 1)
                {
                    string newName;
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, newName);
                    passengers[i].setName(newName);
                    cout << "Name updated!" << endl;
                }
                else if (choice == 2)
                {
                    int newRow;
                    cout << "Enter new seat row (1-10): ";
                    cin >> newRow;
                    newRow--;

                    if (newRow >= 0 && newRow < 10)
                    {
                        passengers[i].setSeatRow(newRow);
                        cout << "Seat row updated!" << endl;
                    }
                    else
                    {
                        cout << "Invalid row!" << endl;
                    }
                }
                else if (choice == 3)
                {
                    int newCol;
                    cout << "Enter new seat column (1-5): ";
                    cin >> newCol;
                    newCol--;

                    if (newCol >= 0 && newCol < 5)
                    {
                        passengers[i].setSeatCol(newCol);
                        cout << "Seat column updated!" << endl;
                    }
                    else
                    {
                        cout << "Invalid column!" << endl;
                    }
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }

                break;
            }
        }

        if (!found)
        {
            cout << "Flight ID not found." << endl;
        }
    }

    void showSeats()
    {
        cout << "\nFlight Seat Map (O = Open, X = Booked)" << endl;
        cout << "------------------------------" << endl;

        for (int i = 0; i < 10; i++) 
        {
            cout << "Row " << setw(2)<< i + 1 
                 << " : | "; 

            for (int j = 0; j < 5; j++) 
            {
                cout << seats[i][j]; 
            }

            
            cout << endl;
            
        }

        cout << "------------------------------" << endl;
    }

    void showPassengers()
    {
        if (passengerCount == 0)
        {
            cout << "No passengers booked." << endl;
            return;
        }

        for (int i = 0; i < passengerCount; i++)
        {
            passengers[i].showInfo();
        }
    }

    void cancelSeatBooking()
    {
        int id;
        cout << "Enter your Flight ID to cancel booking: ";
        cin >> id;

        bool found = false;

        for (int i = 0; i < passengerCount; i++)
        {
            if (passengers[i].getFlightId() == id)
            {
                found = true;
                
                int row = passengers[i].getSeatRow();
                int col = passengers[i].getSeatCol();
                seats[row][col] = 'O'; 

                
                passengers[i] = Person();

                passengerCount--; 
                cout << "Booking canceled successfully!" << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Flight ID not found. No booking to cancel." << endl;
        }
    }
};

int main()
{
    Flight myFlight;
    int choice;

    cout << "===== Welcome to Flight Management System =====" << endl;

    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Book a Seat" << endl;
        cout << "2. Change Passenger Details" << endl;
        cout << "3. Show Seat Map" << endl;
        cout << "4. Show All Passenger Info" << endl;
        cout << "5. Cancel Seat Booking" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Input validation for choice
        if (cin.fail())
        {
            cin.clear();           
            cin.ignore(100, '\n'); 
            cout << "Invalid input! Please enter a valid number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            myFlight.bookSeat();
            break;
        case 2:
            myFlight.changeDetails();
            break;
        case 3:
            myFlight.showSeats();
            break;
        case 4:
            myFlight.showPassengers();
            break;
        case 5:
            myFlight.cancelSeatBooking();
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }

    } while (choice != 0);

    cout << "Thank you for using the Flight Management System. We hope you had a great experience!\n";
    cout << "System is now shutting down...\n";
    cout << "Goodbye!\n";

    return 0;
}
