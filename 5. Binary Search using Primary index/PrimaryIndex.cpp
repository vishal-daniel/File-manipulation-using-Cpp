#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct index
{
        string usn;
        int addr;
} ind[20], temp;

int cnt = -1;
fstream fp;

class student
{
public:
        string usn, name, sem;
        student()
        {
                int pos;
                string seg, usnbuf;
                fp.open("record5.txt", ios::in);
                if (!fp)
                {
                        return;
                }
                while (fp)
                {
                        pos = fp.tellg();
                        getline(fp, usnbuf, '|');
                        getline(fp, seg);
                        if (usnbuf[0] == '*' || usnbuf.length() == 0)
                                continue;
                        cnt++;
                        ind[cnt].usn = usnbuf;
                        ind[cnt].addr = pos;
                }
                fp.close();
                sort_index();
        };

        void sort_index()
        {
                for (int i = 0; i <= cnt; i++)
                {
                        for (int j = i + 1; j <= cnt; j++)
                                if (ind[i].usn > ind[j].usn)
                                {
                                        temp.usn = ind[i].usn;
                                        temp.addr = ind[i].addr;

                                        ind[i].usn = ind[j].usn;
                                        ind[i].addr = ind[j].addr;

                                        ind[j].usn = temp.usn;
                                        ind[j].addr = temp.addr;
                                }
                }
                fstream fin;
                fin.open("indexfile5.txt", ios::out);
                for (int i = 0; i <= cnt; i++)
                {
                        fin << ind[i].usn << "|" << ind[i].addr << "\n";
                }
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
                fp.open("record5.txt", ios::app);
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
                        ind[cnt].addr = pos;
                        sort_index();
                        fp.close();
                }
        }

        void search()
        {
                string key;
                cout << "Enter the USN of the student to be searched: ";
                cin >> key;
                int pos = bin_srch(key);
                if (pos == -1)
                {
                        cout << "Record Not Found \n";
                        return;
                }
                cout << "Record found\n";
                fp.open("record5.txt", ios::in);
                if (!fp)
                        exit(0);
                fp.seekg(ind[pos].addr, ios::beg);
                unpack();
                fp.close();
                cout << "\nStudent Found!"
                     << "\nUSN: " << usn << "\nName: " << name << "\nSem:" << sem << endl;
        }

        int bin_srch(string usn_srch)
        {
                int l = 0, h = cnt, mid;
                while (l <= h)
                {
                        mid = (l + h) / 2;
                        if (ind[mid].usn == usn_srch)
                        {
                                return mid;
                        }
                        if (ind[mid].usn < usn_srch)
                                l = mid + 1;
                        if (ind[mid].usn > usn_srch)
                                h = mid - 1;
                }
                return -1;
        }

        void unpack()
        {
                getline(fp, usn, '|');
                getline(fp, name, '|');
                getline(fp, sem, '|');
        }

        void del()
        {
                string usn_srch;
                cout << "Enter the USN of the student to be deleted : ";
                cin >> usn_srch;
                int pos = bin_srch(usn_srch);
                if (pos == -1)
                {
                        cout << "\nRecord Not Found \n";
                        return;
                }
                cout << "\nRecord found and deleted\n";
                fp.open("record5.txt", ios::out | ios::in);
                fp.seekp(ind[pos].addr, ios::beg);
                fp.put('*');
                fp.close();

                for (int i = pos; i < cnt; i++)
                {
                        ind[i].usn = ind[i + 1].usn;
                        ind[i].addr = ind[i + 1].addr;
                }
                cnt--;

                fstream fin;
                fin.open("indexfile5.txt", ios::out);
                for (int i = 0; i <= cnt; i++)
                {
                        fin << ind[i].usn << "|" << ind[i].addr << "\n";
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