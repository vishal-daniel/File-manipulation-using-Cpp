#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Student
{
private:
    char name[10], sem[10], branch[10], buf[30];
    string line;
    int pos[20], i = 1;

public:
    Student()
    {
        fstream frd;
        frd.open("Student.txt", ios::in);
        pos[0] = frd.tellg();
        while (getline(frd, line))
        {
            pos[i] = frd.tellg();
            i++;
        }
    };

    void add()
    {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Sem: ";
        cin >> sem;
        cout << "Enter Branch: ";
        cin >> branch;
        pack();
        ofstream fout;
        fout.open("Student.txt", ios::app);
        pos[i] = fout.tellp();
        i++;
        fout << buf << endl;
        fout.close();
        cout << "Student record added\n";
    }

    void pack()
    {
        strcpy(buf, name);
        strcat(buf, "|");
        strcat(buf, sem);
        strcat(buf, "|");
        strcat(buf, branch);
        strcat(buf, "#");
    }

    void unpack()
    {
        strcpy(name, strtok(buf, "|"));
        strcpy(sem, strtok(NULL, "|"));
        strcpy(branch, strtok(NULL, "#"));
    }

    void search()
    {
        fstream fs;
        int rrn;
        cout << "Enter The RRN  : ";
        cin >> rrn;
        if (rrn >= i)
        {
            cout << "No Record";
            return;
        }
        fs.open("Student.txt", ios::in);
        fs.seekp(pos[rrn], ios::beg);
        fs >> buf;
        unpack();
        cout << "\nStudent Found!"
             << "\nName: " << name << "\nSem: " << sem << "\nBranch:" << branch << endl;
    }

    void display()
    {
        ifstream fin;
        fin.open("Student.txt");
        while (!fin.eof())
        {
            fin >> buf;
            if (fin.fail())
                break;
            unpack();
            cout << "\nName: " << name << "\nSem: " << sem << "\nBranch: " << branch << endl;
        }
        fin.close();
    }
};
int main()
{
    Student s;
    int ch;
    do
    {
        cout << "\n1. Add\n2. Display\n3. Search\n4. Exit\n\nEnter choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            s.add();
            break;
        case 2:
            s.display();
            break;
        case 3:
            s.search();
            break;
        case 4:
            break;
        default:
            cout << "Wrong choice!";
        }
    } while (ch != 4);
}
