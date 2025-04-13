#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// --------------- nested class --------------------//

class Contact
{
private:
    string name;
    string phone;
    string email;

public:
    bool isValidEmail(const string &email) const // email validation
    {
        int atCount = 0;
        for (char c : email)
            if (c == '@')
                atCount++;
        if (atCount != 1)
            return false;

        int atPos = email.find('@');
        string localPart = email.substr(0, atPos);
        string domain = email.substr(atPos + 1);
        if (localPart.empty())
            return false;

        int dotPos = domain.find('.');
        if (dotPos == string::npos)
            return false;

        string extension = domain.substr(dotPos + 1);
        if (extension.length() < 2)
            return false;

        for (char c : localPart)
            if (!isalnum(c) && c != '.' && c != '_' && c != '-' && c != '+')
                return false;
        for (char c : domain)
            if (!isalnum(c) && c != '.' && c != '-')
                return false;

        return true;
    }

    bool isValidPhone(const string &phone) const // phone number vlaidation
    {
        if (phone.length() < 10 || phone.length() > 15)
            return false;
        for (char c : phone)
            if (c < '0' || c > '9')
                return false;

        return true;
    }

    void getDetails() // inout details
    {
        cout << "Enter contact name: ";
        getline(cin, name);

        do
        {
            cout << "Enter phone number (10-15 digits): ";
            getline(cin, phone);
            if (!isValidPhone(phone))
                cout << "Invalid phone number!!! Enter again \n";
        } while (!isValidPhone(phone));

        do
        {
            cout << "Enter email address: ";
            getline(cin, email);
            if (!isValidEmail(email))
                cout << "Invalid phone number!!! Enter again \n";
        } while (!isValidEmail(email));
    }

    void show() const // show details
    {
        cout << "\n--- Contact ---\n";
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "---------------\n";
    }

    bool matches(const string &k) const // fiund matching one
    {
        return name.find(k) != string::npos || phone.find(k) != string::npos;
    }

    void saveToFile(ofstream &f) const // write in file
    {
        f << name << endl
          << phone << endl
          << email << endl
          << "---" << endl;
    }

    bool loadFromFile(ifstream &f) // loading from file
    {
        getline(f, name);
        if (name.empty())
            return false;
        getline(f, phone);
        getline(f, email);
        string s;
        getline(f, s);
        return true;
    }
};

//----------- main class -----------------------//

class ContactManager
{
private:
    string filename;
    void clearInput()
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

public:
    ContactManager(const string &file) : filename(file) {} // default

    void addContact() // adding contact fxn
    {
        ofstream f(filename);
        if (!f.is_open())
        {
            cerr << "Error !!! no file opened \n";
            return;
        }
        Contact c;
        clearInput();
        c.getDetails();
        c.saveToFile(f);
        f.close();
        cout << "Contact saved successful!\n";
    }

    void viewAllContacts() // vew all fxns contact
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "No contacts found.\n";
            return;
        }

        Contact c;
        while (c.loadFromFile(file))
        {
            c.show();
        }
        file.close();
    }

    void updateContact() // updating contact fxn
    {
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");

        if (!inFile.is_open() || !tempFile.is_open())
        {
            cerr << "Error processing files.\n";
            return;
        }

        string keyword;
        clearInput();
        cout << "Enter contact to update (name or phone): ";
        getline(cin, keyword);

        Contact currentContact;
        bool updated = false;

        while (currentContact.loadFromFile(inFile))
        {
            if (currentContact.matches(keyword))
            {
                cout << "Editing contact:\n";
                currentContact.show();

                Contact updatedContact;
                cout << "\nEnter new details:\n";
                updatedContact.getDetails();
                updatedContact.saveToFile(tempFile);
                updated = true;
            }
            else
            {
                currentContact.saveToFile(tempFile);
            }
        }

        inFile.close();
        tempFile.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        cout << (updated ? "Contact updated.\n" : "Contact not found.\n");
    }

    void searchContact() // search contact fxn
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "No contacts to search.\n";
            return;
        }

        string term;
        clearInput();
        cout << "Search name or phone: ";
        getline(cin, term);

        Contact c;
        bool found = false;

        while (c.loadFromFile(file))
        {
            if (c.matches(term))
            {
                cout << "\nMatch found:\n";
                c.show();
                found = true;
            }
        }

        if (!found)
            cout << "No matches found.\n";
        file.close();
    }

    void deleteContact() // delete contact xn
    {
        ifstream in(filename);
        ofstream out("temp.txt");
        if (!in || !out)
        {
            cerr << "File error\n";
            return;
        }

        string term;
        clearInput();
        cout << "Delete contact (name/phone): ";
        getline(cin, term);

        Contact c;
        bool deleted = false;

        while (c.loadFromFile(in))
        {
            if (c.matches(term))
            {
                cout << "Deleting:\n";
                c.show();
                deleted = true;
            }
            else
            {
                c.saveToFile(out);
            }
        }

        in.close();
        out.close();

        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        cout << (deleted ? "Deleted\n" : "Not found\n");
    }

    void menu() // meny for user fxn
    {
        int choice;
        do
        {
            cout << "\n=== Contact Manager ==="
                 << "\n1. Add Contact"
                 << "\n2. View Contacts"
                 << "\n3. Search"
                 << "\n4. Update"
                 << "\n5. Delete"
                 << "\n0. Exit"
                 << "\nYour choice: ";

            if (!(cin >> choice))
            {
                clearInput();
                cout << "Numbers only please!\n";
                continue;
            }

            switch (choice)
            {
            case 1:
                addContact();
                break;
            case 2:
                viewAllContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                deleteContact();
                break;
            case 0:
                cout << "--------- Program End -------------!\n";
                break;
            default:
                cout << "Try 1-5 or 0\n";
            }
        } while (choice != 0);
    }
};

// ----------- main fxn ---------------- //
int main()
{

    ContactManager list("data.txt");
    list.menu();
    return 0;
}