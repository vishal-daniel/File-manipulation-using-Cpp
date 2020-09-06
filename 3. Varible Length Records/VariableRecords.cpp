#include <stdio.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <bits/stdc++.h>

using namespace std;
class Student
{
private:
	char name[10], sem[10], branch[15], buf[25];

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
	fout.open("3student.txt", ios::app);
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
		cout << "\nName: " << name << "  Sem: " << sem << "  Branch: " << branch << endl;
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
				 << "\nName: " << name << "  Sem: " << sem << "  Branch:" << branch << endl;
			fin.close();
			return;
		}
	}
	cout << "\nStudent not found\n";
	fin.close();
}

void Student::modify()
{
	ifstream f;
	f.open("Student.txt");
	char key[10];
	cout << "Enter the name: ";
	cin >> key;
	int i = 0, flag = 0;
	Student s[10];
	while (!f.eof())
	{
		f >> buf;
		if (f.fail())
			break;
		unpack();
		strcpy(s[i].name, name);
		strcpy(s[i].sem, sem);
		strcpy(s[i].branch, branch);
		i++;
	}
	f.close();

	for (int j = 0; j < i; j++)
	{
		if (strcmp(key, s[j].name) == 0)
		{
			flag = 1;
			cout << "Record Found" << endl;
			cout << "Enter new details" << endl;
			cin >> s[j].name;
			cin >> s[j].sem;
			cin >> s[j].branch;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "Record not found" << endl;
		return;
	}

	ofstream f1;
	f1.open("3student.txt");
	for (int k = 0; k < i; k++)
	{
		strcpy(name, s[k].name);
		strcpy(sem, s[k].sem);
		strcpy(branch, s[k].branch);
		pack();
		f1 << buf << endl;
	}
	f1.close();
	return;
}

int main()
{
	Student s;
	int ch;
	do
	{
		cout << "\n1. Add\n2. Display\n3. Search\n4. Modify\n5. Exit\n\nEnter choice: ";
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
