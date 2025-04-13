#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class book;

class info
{
    int Id;
    string name;
    string status;

public:
    info() : Id(0), name(""), status("") {}
    info(int i, string n, string s) : Id(i), name(n), status(s) {}

    ~info() {}

    void setId(int i) { Id = i; }
    void setName(string n) { name = n; }
    void setStatus(string s) { status = s; }

    int getId() const { return Id; }
    string getName() const { return name; }
    string getStatus() const { return status; }

    void display() const
    {
        cout << "Info Details: " << endl;
        cout << "ID: " << Id << endl
             << "Name: " << name << endl
             << "Status: " << status << endl;
    }

    friend void FullStoreReport(info *&person, book *&b, const int &numberOfMember, const int &numberOfBooks);
};

class book
{
    int Id;
    string name;
    string author;
    bool borrowed;
    int borrowedByWhomId;

public:
    book() : Id(0), name(""), author(""), borrowed(false), borrowedByWhomId(-1) {}
    book(int i, string n, string a, bool b, int bWI)
        : Id(i), name(n), author(a), borrowed(b), borrowedByWhomId(bWI) {}

    ~book() {}

    void setId(int i) { Id = i; }
    void setName(string n) { name = n; }
    void setAuthor(string a) { author = a; }
    void setBorrowed(bool b) { borrowed = b; }
    void setBorrowedByWhomId(int id) { borrowedByWhomId = id; }

    int getId() const { return Id; }
    string getName() const { return name; }
    string getAuthor() const { return author; }
    bool isBorrowed() const { return borrowed; }
    int getBorrowedByWhomId() const { return borrowedByWhomId; }

    void display() const
    {
        cout << "Book Details:\n";
        cout << "ID: " << Id << "\nName: " << name << "\nAuthor: " << author
             << "\nBorrowed: " << (borrowed ? "Yes" : "No")
             << "\nBorrowed By ID: " << borrowedByWhomId << endl;
    }

    friend void FullStoreReport(info *&person, book *&b, const int &numberOfMember, const int &numberOfBooks);
};

void FullStoreReport(info *&person, book *&b, const int &numberOfMember, const int &numberOfBooks)
{
    for (int i = 0; i < numberOfBooks; i++)
    {
        b[i].display();

        if (b[i].borrowed)
        {
            cout << "Detail of the Person who Borrowed the Book:\n";
            for (int j = 0; j < numberOfMember; j++)
            {
                if (b[i].borrowedByWhomId == person[j].Id)
                {
                    person[j].display();
                    break;
                }
            }
        }
    }
}

void readMembersFromTXT(const string &filename, info *&members, int &numberOfMembers)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Could not open the file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);          
    numberOfMembers = stoi(line); 

    members = new info[numberOfMembers];

    for (int i = 0; i < numberOfMembers; i++)
    {
        int id;
        string name, status;

        getline(file, line);
        id = stoi(line);

        getline(file, name);

        getline(file, status);

        members[i] = info(id, name, status);
    }

    file.close();
}

void readBooksFromTXT(const string &filename, book *&books, int &numberOfBooks)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Could not open the file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);       
    numberOfBooks = stoi(line);

    books = new book[numberOfBooks];

    for (int i = 0; i < numberOfBooks; i++)
    {
        int id, borrowedBy;
        string name, author;
        bool borrowed;

        getline(file, line);
        id = stoi(line); 

        getline(file, name);

        getline(file, author);

        getline(file, line);
        borrowed = (line == "1");
 
        getline(file, line);
        borrowedBy = stoi(line);

        books[i] = book(id, name, author, borrowed, borrowedBy);
    }

    file.close();
}
void writeDataToFiles(const string &membersFile, const string &booksFile, const info *members, const book *books, int numberOfMembers, int numberOfBooks)
{
    // Writing members data to the file
    ofstream membersOutFile(membersFile);
    if (!membersOutFile)
    {
        cout << "Could not open members file for writing!" << endl;
        return;
    }

    membersOutFile << numberOfMembers << endl;
    for (int i = 0; i < numberOfMembers; i++)
    {
        membersOutFile << members[i].getId() << endl;
        membersOutFile << members[i].getName() << endl;
        membersOutFile << members[i].getStatus() << endl;
    }
    membersOutFile.close();

    // Writing books data to the file
    ofstream booksOutFile(booksFile);
    if (!booksOutFile)
    {
        cout << "Could not open books file for writing!" << endl;
        return;
    }

    booksOutFile << numberOfBooks << endl;
    for (int i = 0; i < numberOfBooks; i++)
    {
        booksOutFile << books[i].getId() << endl;
        booksOutFile << books[i].getName() << endl;
        booksOutFile << books[i].getAuthor() << endl;
        booksOutFile << (books[i].isBorrowed() ? "1" : "0") << endl;
        booksOutFile << books[i].getBorrowedByWhomId() << endl;
    }
    booksOutFile.close();

    cout << "Data successfully written to files!" << endl;
}

void clearScreen()
{
    system("cls");
}

void pauseScreen()
{
    system("pause");
}

int menu()
{
    cout << " 1. Show Full Report of the Book " << endl
         << " 2. Check Details of a Particular Book " << endl
         << " 3. Check Details of a Particular Member " << endl
         << " 0. To Exit " << endl
         << " Enter your Options : ";
    int choice;
    cin >> choice;
    while (choice < 0 || choice > 6 || cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << " Enter a valid option between ( 0 - 6 ): ";
        cin >> choice;
    }

    return choice;
}

int main()
{
    int numberOfMember = 0, numberOfBooks = 0;
    info *members = nullptr;
    book *inventory = nullptr;

    readMembersFromTXT("members.txt", members, numberOfMember);
    readBooksFromTXT("books.txt", inventory, numberOfBooks);

    int choice = -1;
    do
    {
        clearScreen();
        choice = menu();
        switch (choice)
        {
        case 1:
        {

            clearScreen();
            FullStoreReport(members, inventory, numberOfMember, numberOfBooks);
            pauseScreen();
            break;
        }
        case 2:
        {
            clearScreen();
            int book;
            cout << "Enter Book Id for which you want to check: ";
            cin >> book;

            while (cin.fail() || book < 1)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Book ID greater than 0: ";
                cin >> book;
            }

            clearScreen();
            bool present = false;
            for (int i = 0; i < numberOfBooks; i++)
            {
                if (inventory[i].getId() == book)
                {
                    present = true;
                    inventory[i].display();
                    break;
                }
            }

            if (!present)
            {
                cout << "There is no book with this ID." << endl;
            }

            pauseScreen();
            break;
        }

        case 3:
        {
            clearScreen();
            int memberId;
            cout << "Enter Member Id for which you want to check: ";
            cin >> memberId;

            
            while (memberId < 1 || memberId > numberOfMember || cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Member ID between 1 and " << numberOfMember << ": ";
                cin >> memberId;
            }

            clearScreen();
            bool found = false;
            for (int i = 0; i < numberOfMember; i++)
            {
                if (members[i].getId() == memberId)
                {
                    found = true;
                    members[i].display();
                    break;
                }
            }

            if (!found)
            {
                cout << "No member found with the given ID." << endl;
            }

            pauseScreen();
            break;
        }
        case 4:
        {
            clearScreen();
            int memberId, bookId;
            cout << "Enter your Member ID: ";
            cin >> memberId;

            // Validate Member ID (Check if valid)
            while (cin.fail() || memberId < 1 || memberId > numberOfMember)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Member ID between 1 and " << numberOfMember << ": ";
                cin >> memberId;
            }

            cout << "Enter Book ID to borrow: ";
            cin >> bookId;

            // Validate Book ID (Check if valid)
            while (cin.fail() || bookId < 1 || bookId > numberOfBooks)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Book ID between 1 and " << numberOfBooks << ": ";
                cin >> bookId;
            }

            bool foundBook = false, bookAvailable = false;
            for (int i = 0; i < numberOfBooks; i++)
            {
                if (inventory[i].getId() == bookId)
                {
                    foundBook = true;
                    if (!inventory[i].isBorrowed())
                    {
                        bookAvailable = true;
                        inventory[i].setBorrowed(true);
                        inventory[i].setBorrowedByWhomId(memberId);
                        cout << "Book borrowed successfully!" << endl;
                        break;
                    }
                    else
                    {
                        cout << "The book is already borrowed by someone else." << endl;
                    }
                }
            }

            if (!foundBook)
            {
                cout << "No book found with ID: " << bookId << endl;
            }
            else if (!bookAvailable)
            {
                cout << "The book is currently unavailable." << endl;
            }

            pauseScreen();
            break;
        }

        case 5:
        {
            clearScreen();
            int memberId, bookId;
            cout << "Enter your Member ID: ";
            cin >> memberId;

            // Validate Member ID (Check if valid)
            while (cin.fail() || memberId < 1 || memberId > numberOfMember)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Member ID between 1 and " << numberOfMember << ": ";
                cin >> memberId;
            }

            cout << "Enter Book ID to return: ";
            cin >> bookId;

            // Validate Book ID (Check if valid)
            while (cin.fail() || bookId < 1 || bookId > numberOfBooks)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Book ID between 1 and " << numberOfBooks << ": ";
                cin >> bookId;
            }

            bool foundBook = false, bookReturned = false;
            for (int i = 0; i < numberOfBooks; i++)
            {
                if (inventory[i].getId() == bookId)
                {
                    foundBook = true;
                    if (inventory[i].isBorrowed() && inventory[i].getBorrowedByWhomId() == memberId)
                    {
                        bookReturned = true;
                        inventory[i].setBorrowed(false);
                        inventory[i].setBorrowedByWhomId(-1); // Reset borrowed by ID
                        cout << "Book returned successfully!" << endl;
                        break;
                    }
                    else if (!inventory[i].isBorrowed())
                    {
                        cout << "This book is not currently borrowed." << endl;
                    }
                    else
                    {
                        cout << "You have not borrowed this book." << endl;
                    }
                }
            }

            if (!foundBook)
            {
                cout << "No book found with ID: " << bookId << endl;
            }
            else if (!bookReturned)
            {
                cout << "You cannot return this book." << endl;
            }

            pauseScreen();
            break;
        }

        case 6:
        {
            clearScreen();

            int newId;
            string newName, newStatus;
            bool idExists = false;

            cout << "Enter New Member's ID: ";
            cin >> newId;

            // Validate ID (Check if ID already exists)
            while (cin.fail() || newId < 1)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Member ID: ";
                cin >> newId;
            }

            // Check if the ID already exists in the system
            for (int i = 0; i < numberOfMember; i++)
            {
                if (members[i].getId() == newId)
                {
                    idExists = true;
                    break;
                }
            }

            if (idExists)
            {
                cout << "A member with this ID already exists. Try again with a unique ID." << endl;
                pauseScreen();
                break;
            }

            cout << "Enter New Member's Name: ";
            cin.ignore(); // to ignore any leftover new line characters
            getline(cin, newName);

            cout << "Enter New Member's Status (Student/Teacher/Researcher/etc.): ";
            getline(cin, newStatus);

            while (newStatus.empty())
            {
                cout << "Status cannot be empty. Please enter a valid status: ";
                getline(cin, newStatus);
            }

            // Dynamically expand the members array to accommodate the new member
            info *tempMembers = new info[numberOfMember + 1];

            // Copy old members into the new array
            for (int i = 0; i < numberOfMember; i++)
            {
                tempMembers[i] = members[i];
            }

            // Add the new member to the array
            tempMembers[numberOfMember] = info(newId, newName, newStatus);

            // Delete old members array and assign the new one
            delete[] members;
            members = tempMembers;

            // Increase the number of members count
            numberOfMember++;

            cout << "New Member added successfully!" << endl;

            pauseScreen();
            break;
        }

        case 7:
        {
            clearScreen();

            int newBookId;
            string newBookName, newBookAuthor;
            bool borrowed = false;
            int borrowedById = -1;
            bool bookIdExists = false;

            cout << "Enter New Book's ID: ";
            cin >> newBookId;

           
            while (cin.fail() || newBookId < 1)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter a valid Book ID: ";
                cin >> newBookId;
            }

            
            for (int i = 0; i < numberOfBooks; i++)
            {
                if (inventory[i].getId() == newBookId)
                {
                    bookIdExists = true;
                    break;
                }
            }

            if (bookIdExists)
            {
                cout << "A book with this ID already exists. Try again with a unique ID." << endl;
                pauseScreen();
                break;
            }

            cout << "Enter New Book's Name: ";
            cin.ignore(); 
            getline(cin, newBookName);

            cout << "Enter New Book's Author: ";
            getline(cin, newBookAuthor);

           
            cout << "Is the book borrowed (0 = No, 1 = Yes)? ";
            cin >> borrowed;

            
            if (borrowed)
            {
                cout << "Enter the ID of the person who borrowed the book: ";
                cin >> borrowedById;

                
                bool validBorrower = false;
                for (int i = 0; i < numberOfMember; i++)
                {
                    if (members[i].getId() == borrowedById)
                    {
                        validBorrower = true;
                        break;
                    }
                }

                if (!validBorrower)
                {
                    cout << "Invalid Borrower ID. Book will not be marked as borrowed." << endl;
                    borrowed = false; 
                    borrowedById = -1;
                }
            }

            book *tempBooks = new book[numberOfBooks + 1];

            for (int i = 0; i < numberOfBooks; i++)
            {
                tempBooks[i] = inventory[i];
            }

            tempBooks[numberOfBooks] = book(newBookId, newBookName, newBookAuthor, borrowed, borrowedById);

            delete[] inventory;
            inventory = tempBooks;

            numberOfBooks++;

            cout << "New Book added successfully!" << endl;

            pauseScreen();
            break;
        }

        default:
            clearScreen();
            cout << " ---- Thanks for Using My Program ----" << endl;
            pauseScreen();
            break;
        }
        writeDataToFiles("members.txt", "books.txt", members, inventory, numberOfMember, numberOfBooks);
    } while (choice != 0);

    delete[] members;
    delete[] inventory;

    return 0;
}
