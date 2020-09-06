#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct index
{
        string usn, name;
        int addr;
} ind[100];

int cnt = -1;
fstream fp;

class student
{
public:
        string usn, name, sem;

        student()
        {
                int pos, i;
                string seg, usnbuf, namebuf;
                fp.open("record6.txt", ios::in);
                if (!fp)
                {
                        return;
                }
                while (fp)
                {
                        pos = fp.tellg();
                        getline(fp, usnbuf, '|');
                        getline(fp, namebuf, '|');
                        getline(fp, seg);
                        if (usnbuf[0] == '*' || usnbuf.length() == 0)
                                continue;
                        cnt++;
                        ind[cnt].usn = usnbuf;
                        ind[cnt].name = namebuf;
                        ind[cnt].addr = pos;
                }
                fp.close();
                write_index();
        };

        void write_index()
        {
                fstream fin;
                fin.open("indexfile6.txt", ios::out);
                for (int i = 0; i <= cnt; i++)
                {
                        fin << ind[i].usn << "|" << ind[i].name << "|" << ind[i].addr << "\n";
                }
                fin.close();
        }

        void add()
        {
                cout << "Enter usn: ";
                cin >> usn;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter sem: ";
                cin >> sem;
                pack();
        }

        void pack()
        {
                fp.open("record6.txt", ios::app);
                int pos = fp.tellg();
                int flag = 0;
                for (int i = 0; i <= cnt; i++)
                {
                        if (ind[i].usn == usn)
                        {
                                cout << "Already exists!";
                                flag = 1;
                        }
                }
                if (flag == 0)
                {
                        string buf = usn + "|" + name + "|" + sem + "|";
                        fp << buf << endl;
                        cnt++;
                        ind[cnt].usn = usn;
                        ind[cnt].name = name;
                        ind[cnt].addr = pos;
                        write_index();
                        fp.close();
                }
        }

        void search()
        {
                int i = 0, found = 0;
                string key;
                cout << "Enter the Name of the student to be searched: ";
                cin >> key;
                while (i <= cnt)
                {
                        if (ind[i].name == key)
                        {
                                found = 1;
                                cout << "Record found\n";
                                fp.open("record6.txt", ios::in);
                                fp.seekg(ind[i].addr, ios::beg);
                                unpack();
                                fp.close();
                                cout << "\nStudent Found!"
                                     << "\nUSN: " << usn << "\nName: " << name << "\nSem:" << sem << endl;
                        }
                        i++;
                }
                if (found == 0)
                        cout << "No Record Found!\n\n";
        }

        void unpack()
        {
                getline(fp, usn, '|');
                getline(fp, name, '|');
                getline(fp, sem, '|');
        }

        void del()
        {
                int i = 0, found = 0;
                string key;
                cout << "Enter the Name of the student to be deleted : ";
                cin >> key;
                while (i <= cnt)
                {
                        if (ind[i].name == key)
                        {
                                found = 1;
                                cout << "\nRecord found and deleted\n";
                                fp.open("record6.txt", ios::out | ios::in);
                                fp.seekp(ind[i].addr, ios::beg);
                                fp.put('*');
                                fp.close();
                                for (int j = i; j <= cnt; j++)
                                {
                                        ind[j].usn = ind[j + 1].usn;
                                        ind[j].name = ind[j + 1].name;
                                        ind[j].addr = ind[j + 1].addr;
                                }
                                cnt--;
                                i--;
                        }
                        i++;
                }
                if (found == 0)
                {
                        cout << "No Record Found!\n\n";
                        return;
                }
                fstream fin;
                fin.open("indexfile6.txt", ios::out);
                for (int i = 0; i <= cnt; i++)
                {
                        fin << ind[i].usn << "|" << ind[i].name << "|" << ind[i].addr << "\n";
                }
        }
};

int main()
{
        int choice;
        student s;
        while (1)
        {
                cout << "1. to Add Record\n2. to Search for a record\n3. to delete a record\n4. Exit\n\nEnter choice : ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                        s.add();
                        break;
                case 2:
                        s.search();
                        break;
                case 3:
                        s.del();
                        break;
                default:
                        exit(0);
                }
        }
}
