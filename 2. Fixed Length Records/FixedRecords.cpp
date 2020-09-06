#include <stdio.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <bits/stdc++.h>

using namespace std;
class Student
{
private:
	char name[10], sem[10], branch[10], buf[25];

public:
	void pack();
	void unpack();
	void add();
	void display();
	void search();
	void modify();
};

void Student::pack()
{
	strcpy(buf, name);
	strcat(buf, "|");
	strcat(buf, sem);
	strcat(buf, "|");
	strcat(buf, branch);
	for (int i = strlen(buf); i < 25; i++)
		strcat(buf, "#");
}

void Student::unpack()
{
	strcpy(name, strtok(buf, "|"));
	strcpy(sem, strtok(NULL, "|"));
	strcpy(branch, strtok(NULL, "#"));
}

void Student::add()
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
	fout << buf << endl;
	fout.close();
	cout << "Student record added\n";
}

void Student::display()
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

void Student::search()
{
	ifstream fin;
	fin.open("Student.txt");
	char key[10];
	cout << "Enter the name to search: ";
	cin >> key;
	while (!fin.eof())
	{
		fin >> buf;
		if (fin.fail())
			break;
		unpack();
		if (!strcmp(name, key))
		{
			cout << "\nStudent Found!"
				 << "\nName: " << name << "\nSem: " << sem << "\nBranch:" << branch << endl;
			fin.close();
			return;
		}
	}
	cout << "\nStudent not found\n";
	fin.close();
}

void Student::modify()
{
	fstream f;
	f.open("2student.txt", ios::in | ios::out);
	char key[10];
	cout << "Enter the name: ";
	cin >> key;
	while (!f.eof())
	{
		f >> buf;
		if (f.fail())
			break;
		unpack();
		if (!strcmp(name, key))
		{
			cout << "\nStudent found\n"
				 << "Enter new semester: ";
			cin >> sem;
			cout << "Enter new branch: ";
			cin >> branch;
			pack();
			f.seekp((int)f.tellg() - 25, ios::beg);
			f << buf;
			f.close();
			return;
		}
	}
	cout << "\nStudent not found\n";
	f.close();
}

int main()
{
	Student s;
	int ch;
	do
	{
		cout << "\n1. Add\n2. Display\n3. Search\n4. Modify\n5.Exit\n\nEnter choice: ";
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
			s.modify();
			break;
		case 5:
			break;
		default:
			cout << "Wrong choice!";
		}
	} while (ch != 5);
}
