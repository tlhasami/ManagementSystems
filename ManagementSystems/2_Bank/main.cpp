#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
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
    int ID;
    string name;
    double currentMoney;
    double WithdrawDraftMoney;
    string accountStatus; // Active or Suspended
    string accountType;   // e.g., Current, Savings
    string password;      // Password for the member

public:
    Member(int id, string n, double initialMoney, double draftMoney, string status, string type, string pwd)
        : ID(id), name(n), currentMoney(initialMoney), WithdrawDraftMoney(draftMoney),
          accountStatus(status), accountType(type), password(pwd) {}

    Member() : ID(0), name(""), currentMoney(0.0), WithdrawDraftMoney(0.0),
               accountStatus("Inactive"), accountType("Current"), password("") {}

    ~Member() {}

    // Setters
    void setID(int id) { ID = id; }
    void setName(string n) { name = n; }
    void setCurrentMoney(double money) { currentMoney = money; }
    void setWithdrawDraftMoney(double money) { WithdrawDraftMoney = money; }
    void setAccountStatus(string status) { accountStatus = status; }
    void setAccountType(string type) { accountType = type; }
    void setPassword(string pwd) { password = pwd; }

    int getID() const { return ID; }
    string getName() const { return name; }
    double getCurrentMoney() const { return currentMoney; }
    double getWithdrawDraftMoney() const { return WithdrawDraftMoney; }
    string getAccountStatus() const { return accountStatus; }
    string getAccountType() const { return accountType; }
    string getPassword() const { return password; }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            currentMoney += amount;
            cout << "Deposited " << amount << ". New balance: " << currentMoney << endl;
        }
        else
        {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0 && currentMoney >= amount)
        {
            currentMoney -= amount;
            cout << "Withdrawn " << amount << ". New balance: " << currentMoney << endl;
        }
        else if (amount > 0 && currentMoney < amount && WithdrawDraftMoney >= (amount - currentMoney))
        {
            double remainingAmount = amount - currentMoney;
            WithdrawDraftMoney -= remainingAmount;
            currentMoney = 0;
            cout << "Withdrawn " << amount << " (Remaining covered from Withdraw Draft Money). New balance: " << currentMoney << endl;
        }
        else
        {
            cout << "Insufficient funds or invalid amount!" << endl;
        }
    }

    void display() const
    {
        cout << "Member Details: " << endl;
        cout << "ID: " << ID << endl
             << "Name: " << name << endl
             << "Account Type: " << accountType << endl
             << "Account Status: " << accountStatus << endl
             << "Current Money: " << currentMoney << endl
             << "Withdraw Draft Money: " << WithdrawDraftMoney << endl;
    }

    void updateAccountStatus(string status)
    {
        accountStatus = status;
    }
};

void writeMembersToFile(const string &filename, Member *members, int numberOfMembers)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Could not open the file for writing: " << filename << endl;
        return;
    }

    file << numberOfMembers << endl;

    for (int i = 0; i < numberOfMembers; ++i)
    {
        file << members[i].getID() << endl;
        file << members[i].getName() << endl;
        file << members[i].getCurrentMoney() << endl;
        file << members[i].getWithdrawDraftMoney() << endl;
        file << members[i].getAccountStatus() << endl;
        file << members[i].getAccountType() << endl;
        file << members[i].getPassword() << endl;
    }

    file.close();
}

void readMembersFromFile(const string &filename, Member *&members, int &numberOfMembers)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Could not open the file for reading: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    numberOfMembers = stoi(line);

    members = new Member[numberOfMembers];

    for (int i = 0; i < numberOfMembers; ++i)
    {
        int id;
        string name, status, type, pwd;
        double currentMoney, draftMoney;

        file >> id;
        file.ignore();

        getline(file, name);
        file >> currentMoney >> draftMoney;
        file.ignore();

        getline(file, status);
        getline(file, type);
        getline(file, pwd);

        members[i] = Member(id, name, currentMoney, draftMoney, status, type, pwd);
    }

    file.close();
}

int menuUser()
{
    clearScreen();
    int choice;
    cout << "1. View Account Details" << endl
         << "2. Deposit Money" << endl
         << "3. Withdraw Money" << endl
         << "4. Change Password" << endl // Fixed the typo in "Change"
         << "0. Exit" << endl;
    cout << "Enter your choice: ";

    while (true) // Added validation loop
    {
        cin >> choice;

        // Check if the choice is valid
        if (choice >= 0 && choice <= 4)
        {
            break; // Exit loop if the choice is valid
        }
        else
        {
            cout << "Invalid choice. Please enter a number between 0 and 4: ";
        }
    }
    clearScreen();
    return choice;
}

int menuBank()
{
    clearScreen();
    int choice;
    cout << "1. View All Members" << endl
         << "2. Add a New Member" << endl
         << "3. Update Member Details" << endl
         << "0. Exit" << endl;
    cout << "Enter your choice: ";

    while (true) // Added validation loop
    {
        cin >> choice;

        // Check if the choice is valid
        if (choice >= 0 && choice <= 3)
        {
            break; // Exit loop if the choice is valid
        }
        else
        {
            cout << "Invalid choice. Please enter a number between 0 and 3: ";
        }
    }
    clearScreen();
    return choice;
}

void working(Member *&members, int &numberOfMembers)
{

    int userOrManager;
    while (true)
    {
        int choice = -1;
        clearScreen();
        cout << "Enter 1 for User or 2 for Manager 0 for exit : ";
        cin >> userOrManager;

        if (userOrManager == 1)
        {
            int id;
            string name, password;
            bool found = false;

            cout << "Enter Member ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin.ignore(); // Ignore any leftover newline characters
            getline(cin, name);

            cout << "Enter Password: ";
            cin >> password;
            clearScreen();
            for (int i = 0; i < numberOfMembers; ++i)
            {
                if (members[i].getID() == id && members[i].getName() == name)
                {
                    if (members[i].getPassword() == password)
                    {
                        found = true;
                        do
                        {
                            choice = menuUser();
                            switch (choice)
                            {
                            case 1:
                            clearScreen();
                                members[i].display();
                                pauseScreen();
                                break;
                            case 2:
                            clearScreen();
                                double depositAmount;
                                cout << "Enter deposit amount: ";
                                cin >> depositAmount;
                                members[i].deposit(depositAmount);
                                pauseScreen();
                                break;
                            case 3:
                            clearScreen();
                                double withdrawAmount;
                                cout << "Enter withdraw amount: ";
                                cin >> withdrawAmount;
                                members[i].withdraw(withdrawAmount);
                                pauseScreen();
                                break;
                            case 4:
                            {
                                clearScreen();
                                string newPassword;
                                cout << "Enter new password: ";
                                cin >> newPassword;
                                members[i].setPassword(newPassword); // Make sure setPassword is implemented in the Member class
                                cout << "Password updated successfully!" << endl;
                                pauseScreen();
                                break;
                            }
                            default:
                                break;
                            }
                        } while (choice != 0);
                    }
                    else
                    {
                        cout << "Incorrect password!" << endl;
                    }
                }
            }

            if (!found)
            {
                cout << "No member found with the provided ID and name." << endl;
                pauseScreen();
            }
        }
        else if (userOrManager == 2)
        {

            do
            {
                
                choice = menuBank();
                switch (choice)
                {
                case 1:
                clearScreen();
                    cout << " -------------- DETAILS -------------- " << endl;
                    for (int i = 0; i < numberOfMembers; ++i)
                    {
                        members[i].display();
                    }
                    break;
                    pauseScreen();
                case 2:
                {
                    clearScreen();
                    int id;
                    string name, status, type, password;
                    double currentMoney, draftMoney;
                    bool idExists = false;

                    cout << "Enter ID: ";
                    cin >> id;

                    // Check if ID already exists
                    for (int i = 0; i < numberOfMembers; ++i)
                    {
                        if (members[i].getID() == id)
                        {
                            idExists = true;
                            break;
                        }
                    }

                    if (idExists)
                    {
                        cout << "Error: A member with this ID already exists. Please choose a different ID.\n";
                    }
                    else
                    {
                        cin.ignore();
                        cout << "Enter name: ";
                        getline(cin, name);
                        cout << "Enter current money: ";
                        cin >> currentMoney;
                        cout << "Enter draft money: ";
                        cin >> draftMoney;
                        cout << "Enter account status: ";
                        cin.ignore();
                        getline(cin, status);
                        cout << "Enter account type: ";
                        getline(cin, type);
                        cout << "Enter password: ";
                        getline(cin, password);

                        // Create new member
                        Member newMember(id, name, currentMoney, draftMoney, status, type, password);

                        // Add new member to the array
                        Member *temp = new Member[numberOfMembers + 1];
                        for (int i = 0; i < numberOfMembers; ++i)
                        {
                            temp[i] = members[i]; // Copy existing members to new array
                        }
                        temp[numberOfMembers++] = newMember; // Add the new member at the end

                        delete[] members; // Delete old array
                        members = temp;   // Point members to the new array

                        // Write updated members to file
                        writeMembersToFile("members.txt", members, numberOfMembers);
                    }
                }
                pauseScreen();
                break;
                case 3:
                {
                    clearScreen();
                    int id;
                    cout << "Enter Member ID to update: ";
                    cin >> id;

                    for (int i = 0; i < numberOfMembers; ++i)
                    {
                        if (members[i].getID() == id)
                        {
                            int choice;
                            do
                            {
                                cout << "What do you want to update?\n";
                                cout << "1. Account Status\n";
                                cout << "2. Account Type\n";
                                cout << "3. Name\n";
                                cout << "4. Current Money\n";
                                cout << "5. Withdraw Draft Money\n";
                                cout << "6. Password\n";
                                cout << "0. Exit\n";
                                cout << "Enter your choice: ";
                                cin >> choice;

                                switch (choice)
                                {
                                case 1:
                                {
                                    string status;
                                    cout << "Enter new account status: ";
                                    cin >> status;
                                    members[i].updateAccountStatus(status);
                                    break;
                                }
                                case 2:
                                {
                                    string type;
                                    cout << "Enter new account type: ";
                                    cin >> type;
                                    members[i].setAccountType(type);
                                    break;
                                }
                                case 3:
                                {
                                    string name;
                                    cout << "Enter new name: ";
                                    cin >> name;
                                    members[i].setName(name);
                                    break;
                                }
                                case 4:
                                {
                                    double money;
                                    cout << "Enter new current money: ";
                                    cin >> money;
                                    members[i].setCurrentMoney(money);
                                    break;
                                }
                                case 5:
                                {
                                    double draftMoney;
                                    cout << "Enter new withdraw draft money: ";
                                    cin >> draftMoney;
                                    members[i].setWithdrawDraftMoney(draftMoney);
                                    break;
                                }
                                case 6:
                                {
                                    string pass;
                                    cout << "Enter new password: ";
                                    cin >> pass;
                                    members[i].setPassword(pass);
                                    break;
                                }
                                case 0:
                                {
                                    cout << "Exiting...\n";
                                    break;
                                }
                                default:
                                    cout << "Invalid choice. Please try again.\n";
                                    break;
                                }
                                writeMembersToFile("members.txt", members, numberOfMembers); // Save updates to file after each change
                            } while (choice != 0);
                        }
                    }
                }
                break;
                default:
                    break;
                }
            } while (choice != 0);
        }
        else if (userOrManager == 0)
        {
            cout << "Leaving...... " << endl;
            pauseScreen();
            break;
        }
    }
}



int main()
{
    Member *members = nullptr;
    int numberOfMembers = 0;

    readMembersFromFile("members.txt", members, numberOfMembers);

    working(members, numberOfMembers);

    delete[] members;
    return 0;
}
