
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

void clearScreen()
{
    system("cls");
}

void pauseScreen()
{
    system("pause");
}

class Member
{
private:
    int id;
    string name;
    string partyName;
    long long totalVotes;
    double votePercentage;
    int rank;

public:
    // Default constructor
    Member() : id(0), name(""), partyName(""), totalVotes(0), votePercentage(0.0), rank(0) {}

    // Parameterized constructor
    Member(int id, string name, string partyName, long long totalVotes, double votePercentage, int rank)
        : id(id), name(name), partyName(partyName), totalVotes(totalVotes), votePercentage(votePercentage), rank(rank) {}

    // Setters
    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setPartyName(string partyName) { this->partyName = partyName; }
    void setTotalVotes(long long totalVotes) { this->totalVotes = totalVotes; }
    void setVotePercentage(double votePercentage) { this->votePercentage = votePercentage; }
    void setRank(int rank) { this->rank = rank; }

    // Getters (optional but recommended for future usage)
    int getId() const { return id; }
    string getName() const { return name; }
    string getPartyName() const { return partyName; }
    long long getTotalVotes() const { return totalVotes; }
    double getVotePercentage() const { return votePercentage; }
    int getRank() const { return rank; }

    // Display function (optional)
    void display() const
    {
        cout << "ID: " << id << endl
             << "Name: " << name << endl
             << "Party: " << partyName << endl
             << "Votes: " << totalVotes << endl
             << "Percent: " << votePercentage << "%" << endl
             << "Rank: " << rank << endl;
    }
};

void calculateVotePercentages(Member members[], int count, long long totalVotes)
{
    for (int i = 0; i < count; ++i)
    {
        double percent = (double)members[i].getTotalVotes() / totalVotes * 100.0;
        members[i].setVotePercentage(percent);
    }
}

void assignRanks(Member members[], int count)
{

    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (members[j].getTotalVotes() < members[j + 1].getTotalVotes())
            {
                // Swap members[j] and members[j + 1]
                Member temp = members[j];
                members[j] = members[j + 1];
                members[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; ++i)
    {
        members[i].setRank(i + 1);
    }
}

void working()
{
    int numberOfParticipants = 0;
    while (true)
    {
        cout << "Enter the number of participants in voting: ";
        cin >> numberOfParticipants;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (numberOfParticipants > 1)
            break;

        cout << "---- Enter a number above 1 ----  " << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    Member *members = new Member[numberOfParticipants];
    long long totalVotes = 0;

    for (int i = 0; i < numberOfParticipants; ++i)
    {
        int id;
        string name, party;
        long long votes;

        cout << "\nEnter details for participant " << i + 1 << ":" << endl;

        bool uniqueId = false;
        while (!uniqueId)
        {
            cout << "ID: ";
            cin >> id;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID. Please enter a valid number.\n";
                continue;
            }
            cin.ignore();

            bool idExists = false;
            for (int j = 0; j < i; ++j)
            {
                if (members[j].getId() == id)
                {
                    idExists = true;
                    break;
                }
            }

            if (idExists)
            {
                cout << "ID already exists. Please enter a unique ID.\n";
            }
            else
            {
                uniqueId = true;
            }
        }

        cout << "Name: ";
        getline(cin, name);
        cout << "Party Name: ";
        getline(cin, party);

        cout << "Total Votes Received: ";
        cin >> votes;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid votes. Please enter a valid number.\n";
            --i;
            continue;
        }

        members[i].setId(id);
        members[i].setName(name);
        members[i].setPartyName(party);
        members[i].setTotalVotes(votes);

        totalVotes += votes;
        clearScreen();
    }

    calculateVotePercentages(members, numberOfParticipants, totalVotes);
    assignRanks(members, numberOfParticipants);

    int choice;
    do
    {
        cout << "\nWhat would you like to see?\n";
        cout << "1 - Who won?\n";
        cout << "2 - Percentage gap between participants\n";
        cout << "3 - Graphical report (horizontal bars)\n";
        cout << "4 - Details of a particular person\n";
        cout << "5 - Show all participant details\n";
        cout << "6 - Modify participant details\n";
        cout << "0 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please enter a number from the menu.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "\nWinner: " << members[0].getName() << " from " << members[0].getPartyName()
                 << " with " << members[0].getTotalVotes() << " votes (" << members[0].getVotePercentage() << "%)\n";
            break;
        case 2:
            cout << "\nVote Percentage Gaps (compared to the winner):\n";
            for (int i = 1; i < numberOfParticipants; ++i)
            {
                double gap = members[0].getVotePercentage() - members[i].getVotePercentage();
                cout << members[i].getName() << " is " << gap << "% behind "
                     << members[0].getName() << " (the winner).\n";
            }
            break;
        case 3:
            cout << "\nGraphical Report:\n";
            cout << left << setw(20) << "Candidate" << "| Vote Bar (max 25 *)" << " | Percentage\n";
            cout << "---------------------------------------------------------------\n";
            for (int i = 0; i < numberOfParticipants; ++i)
            {
                int barLength = static_cast<int>((members[i].getVotePercentage() / 100.0) * 25);
                cout << left << setw(20) << members[i].getName() << "| ";
                for (int j = 0; j < barLength; ++j)
                    cout << '*';
                cout << setw(27 - barLength) << " " << "| "
                     << fixed << setprecision(2) << members[i].getVotePercentage() << "%\n";
            }
            break;
        case 4:
        {
            int idQuery;
            cout << "Enter ID to search: ";
            cin >> idQuery;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID. Returning to menu.\n";
                break;
            }

            bool found = false;
            for (int i = 0; i < numberOfParticipants; ++i)
            {
                if (members[i].getId() == idQuery)
                {
                    cout << "\nDetails:\n";
                    members[i].display();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "No participant found with that ID.\n";
            }
            break;
        }
        case 5:
            cout << "\nAll Participants:\n";
            for (int i = 0; i < numberOfParticipants; ++i)
            {
                cout << "-----------------------------\n";
                members[i].display();
            }
            break;
        case 6:
        {
            int idToModify;
            cout << "Enter the ID of the participant whose details you want to modify: ";
            cin >> idToModify;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID. Returning to menu.\n";
                break;
            }

            bool found = false;
            for (int i = 0; i < numberOfParticipants; ++i)
            {
                if (members[i].getId() == idToModify)
                {
                    found = true;
                    string newName, newParty;
                    long long newVotes;

                    char modifyDetailChoice;
                    do
                    {
                        cout << "\nWhat would you like to change?\n";
                        cout << "1 - Change Name\n";
                        cout << "2 - Change Party\n";
                        cout << "3 - Change Votes\n";
                        cout << "0 - Exit modification\n";
                        cout << "Enter your choice: ";
                        cin >> modifyDetailChoice;
                        cin.ignore();

                        switch (modifyDetailChoice)
                        {
                        case '1':
                            cout << "Enter new Name: ";
                            getline(cin, newName);
                            members[i].setName(newName);
                            cout << "Name updated successfully.\n";
                            break;
                        case '2':
                            cout << "Enter new Party Name: ";
                            getline(cin, newParty);
                            members[i].setPartyName(newParty);
                            cout << "Party Name updated successfully.\n";
                            break;
                        case '3':
                            cout << "Enter new Total Votes Received: ";
                            cin >> newVotes;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Invalid input. Votes not updated.\n";
                                break;
                            }
                            members[i].setTotalVotes(newVotes);
                            cout << "Votes updated successfully.\n";
                            break;
                        case '0':
                            cout << "Exiting modification menu.\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                        }

                    } while (modifyDetailChoice != '0');
                    break;
                }
            }

            if (!found)
            {
                cout << "No participant found with the given ID.\n";
            }
            break;
        }
        case 0:
            cout << "Exiting report view.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    delete[] members;
}

int main()
{
    char repeatChoice;

    do
    {
        cout << " ------- Welcome To Voting Management System ------- " << endl;
        cout << "    Note :  " << endl
             << "          We'll be asking you for the number of participants in the voting scheme" << endl
             << "          Once the voting is done, we'll show you the report:" << endl
             << "           1 - Who won?" << endl
             << "           2 - Percentage gap" << endl
             << "           3 - Graphical report (Horizontal bars)" << endl
             << "           4 - Details of a particular person" << endl;

        pauseScreen();
        clearScreen();

        // Call the working function to handle the voting process
        working();

        // After finishing the voting process, ask the user if they want to restart
        cout << "\nWould you like to use the Voting System again? (y/n): ";
        cin >> repeatChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Exiting system.\n";
            break;
        }

        // Make sure the user enters a valid response
        while (repeatChoice != 'y' && repeatChoice != 'n')
        {
            cout << "Invalid choice. Please enter 'y' for Yes or 'n' for No: ";
            cin >> repeatChoice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Exiting system.\n";
                repeatChoice = 'n';
                break;
            }
        }

        clearScreen();

    } while (repeatChoice == 'y'); // Repeat if the user chooses 'y'

    cout << "Thank you for using the Voting Management System. Goodbye!" << endl;

    return 0;
}