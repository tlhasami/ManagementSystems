/*
Student Record System: Design a system for storing and managing student records,
including details like personal information, course enrollment, and grades,
utilizing file handling to store data.
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include <iostream>
using namespace std;

void clearScreen()
{
    system("cls");
}

void pauseScreen()
{
    system("pause");
}

class Student
{
private:
    int id;
    string name;
    float gpa;
    int subjectCount;
    string subjects[10]; 

public:
    
    void setId(int _id)
    {
        id = _id;
    }

    void setName(string _name)
    {
        name = _name;
    }

    void setGpa(float _gpa)
    {
        gpa = _gpa;
    }

    void setSubjectCount(int count)
    {
        subjectCount = count;
    }

    void setSubject(int index, string subject)
    {
        if (index >= 0 && index < 10)
        {
            subjects[index] = subject;
        }
    }

    
    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    float getGpa()
    {
        return gpa;
    }

    int getSubjectCount()
    {
        return subjectCount;
    }

    string getSubject(int index)
    {
        if (index >= 0 && index < 10)
        {
            return subjects[index];
        }
        else
        {
            return "";
        }
    }

    void display()
    {
        cout << "ID: " << id << "\nName: " << name << "\nGPA: " << gpa << "\nSubjects: ";
        for (int i = 0; i < subjectCount; i++)
        {
            cout << subjects[i] << " ";
        }
        cout << "\n\n";
    }
};

void readStudentFormFile(const string& fileName, Student*& students, int& numberOfStudents)
{
    ifstream in(fileName);
    if (!in) {
        cout << "Error opening file!" << endl;
        return;
    }

   
    in >> numberOfStudents;
    in.ignore();  

    students = new Student[numberOfStudents];

    for (int i = 0; i < numberOfStudents; i++) {
        int id;
        string name;
        float gpa;
        int subjectCount;
        string subject;

       
        in >> id;
        in.ignore(); 
        getline(in, name);
        in >> gpa >> subjectCount;
        in.ignore(); 

        students[i].setId(id);
        students[i].setName(name);
        students[i].setGpa(gpa);
        students[i].setSubjectCount(subjectCount);

        for (int j = 0; j < subjectCount; j++) {
            getline(in, subject);
            students[i].setSubject(j, subject);
        }
    }

    in.close();
}

void writeStudentToFile(const string& fileName, Student* students, int numberOfStudents)
{
    ofstream out(fileName);
    if (!out) {
        cout << "Error opening file!" << endl;
        return;
    }

    out << numberOfStudents << endl;

    // Write each student's data
    for (int i = 0; i < numberOfStudents; i++) {
        out << students[i].getId() << endl;
        out << students[i].getName() << endl;
        out << students[i].getGpa() << endl;
        out << students[i].getSubjectCount() << endl;
        for (int j = 0; j < students[i].getSubjectCount(); j++) {
            out << students[i].getSubject(j) << endl;
        }
    }

    out.close();
}

int askUserInput()
{
    cout << " 1. See Details of All Students " << endl
         << " 2. See Details of a Single Student " << endl
         << " 3. Student in Same course " << endl
         << " 4. Students above 3 GPA " << endl
         << " 5. Medalist (Top 5 Students)" << endl
         << " 6. Remove Student " << endl
         << " 7. Add Student " << endl
         << " 0. Exit" << endl;

    int choice = 0;
    while (true)
    {
        cout << " Enter the Choice Between 0 - 7: ";
        cin >> choice;
        if (choice >= 0 && choice <= 7)
            break;
        cin.clear();
        cin.ignore(100, '\n');
        cout << " --- Invalid Entry ---" << endl;
    }
    return choice;
}

int main()
{
    
    Student *students = nullptr;
    int numberOfStudents = 0;

    readStudentFormFile("students.txt", students, numberOfStudents);
    
    int choice = -1;
    do
    {
        clearScreen();
        cout << " ----- Student Records ------" << endl;
        choice = askUserInput();
        
        switch (choice)
        {
            case 1:
            cout << endl
                 << "--- All Student Details ---" << endl;
            for (int i = 0; i < numberOfStudents; i++)
            {
                students[i].display();
            }
            break;

        case 2:
        {
            int searchId;
            cout << "Enter Student ID to search: ";
            cin >> searchId;
            bool found = false;
            for (int i = 0; i < numberOfStudents; i++)
            {
                if (students[i].getId() == searchId)
                {
                    students[i].display();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Student not found!" << endl;
            }
            break;
        }

        case 3:
        {
            string course;
            cout << "Enter course name to find students: ";
            cin.ignore();
            getline(cin, course);
            cout << endl
                 << "--- Students Enrolled in " << course << " ---" << endl;
            for (int i = 0; i < numberOfStudents; i++)
            {
                for (int j = 0; j < students[i].getSubjectCount(); j++)
                {
                    if (students[i].getSubject(j) == course)
                    {
                        students[i].display();
                        break;
                    }
                }
            }
            break;
        }

        case 4:
            cout << endl
                 << "--- Students with GPA above 3.0 ---" << endl;
            for (int i = 0; i < numberOfStudents; i++)
            {
                if (students[i].getGpa() > 3.0)
                {
                    students[i].display();
                }
            }
            break;

        case 5:
        {
            cout << endl
                 << "--- Top 5 Medalist Students (By GPA) ---" << endl;
            for (int i = 0; i < 5; i++)
            {
                int maxIdx = i;
                for (int j = i + 1; j < numberOfStudents; j++)
                {
                    if (students[j].getGpa() > students[maxIdx].getGpa())
                    {
                        maxIdx = j;
                    }
                }
                if (maxIdx != i)
                {
                    Student temp = students[i];
                    students[i] = students[maxIdx];
                    students[maxIdx] = temp;
                }
                students[i].display();
            }
            break;
        }
        case 6:
        {
            int removeId;
            cout << "Enter Student ID to remove: ";
            cin >> removeId;
            bool found = false;
            for (int i = 0; i < numberOfStudents; i++)
            {
                if (students[i].getId() == removeId)
                {
                    found = true;
                   
                    for (int j = i; j < numberOfStudents - 1; j++)
                    {
                        students[j] = students[j + 1];
                    }
                    numberOfStudents--; 

                    
                    Student *temp = new Student[numberOfStudents];
                    for (int k = 0; k < numberOfStudents; k++)
                    {
                        temp[k] = students[k];
                    }
                    delete[] students;
                    students = temp;

                    writeStudentToFile("students.txt", students, numberOfStudents);
                    cout << "Student removed successfully." << endl;
                    break;
                }
            }
            if (!found)
            {
                cout << "Student ID not found!" << endl;
            }
            break;
        }
        case 7:
        {
            int id;
            cout << "Enter Student ID (unique): ";
            cin >> id;

            
            bool idExists = false;
            for (int i = 0; i < numberOfStudents; i++)
            {
                if (students[i].getId() == id)
                {
                    idExists = true;
                    break;
                }
            }

            if (idExists)
            {
                cout << "Error: Student with ID " << id << " already exists!" << endl;
                break;
            }

            
            Student *temp = new Student[numberOfStudents + 1];
            for (int i = 0; i < numberOfStudents; i++)
            {
                temp[i] = students[i];
            }

            string name, subject;
            float gpa;
            int subjectCount;

            cin.ignore(); 
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter GPA: ";
            cin >> gpa;
            cout << "Enter number of subjects: ";
            cin >> subjectCount;

            temp[numberOfStudents].setId(id);
            temp[numberOfStudents].setName(name);
            temp[numberOfStudents].setGpa(gpa);
            temp[numberOfStudents].setSubjectCount(subjectCount);

            cin.ignore(); 
            for (int i = 0; i < subjectCount; i++)
            {
                cout << "Enter subject " << (i + 1) << ": ";
                getline(cin, subject);
                temp[numberOfStudents].setSubject(i, subject);
            }

            delete[] students;
            students = temp;
            numberOfStudents++;

            
            writeStudentToFile("students.txt", students, numberOfStudents);
            cout << "Student added successfully." << endl;
            break;
        }

        case 0:
            cout << endl
                 << "Exiting the program..." << endl;
            break;

        }

        if (choice != 0)
        {
            pauseScreen();
        }

    } while (choice != 0);

    delete[] students;
    return 0;
}