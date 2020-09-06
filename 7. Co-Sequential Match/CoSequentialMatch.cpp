#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void match()
{
        char list1[50][20], list2[50][20];
        string line;
        int i, j, m, n;
        fstream out1, out2, out3;
        out1.open("f1.txt", ios::in);
        out2.open("f2.txt", ios::in);
        out3.open("out.txt", ios::out);
        m = n = i = j = 0;
        out1 >> line;
        if (out1.fail())
        {
                cout << "File1 is Empty\n";
                exit(0);
        }
        out2 >> line;
        if (out2.fail())
        {
                cout << "File2 is Empty\n";
                exit(0);
        }
        cout << "The names in file1 are:\n";
        while (!out1.eof())
        {
                out1.getline(list1[i], 30, '\n');
                cout << list1[i] << endl;
                i++;
                m++;
        }
        cout << "The names in file2 are:\n";
        while (!out2.eof())
        {
                out2.getline(list2[j], 30, '\n');
                cout << list2[j] << endl;
                j++;
                n++;
        }
        cout << "\nCommon names are:\n";
        i = j = 0;
        int f = 0;
        while (i < m && j < n)
        {
                if (strcmp(list1[i], list2[j]) == 0)
                {
                        f = 1;
                        cout << list1[i] << endl;
                        out3 << list1[i] << '\n';
                        i++;
                        j++;
                }
                else if (strcmp(list1[i], list2[j]) < 0)
                        i++;
                else
                        j++;
        }
        if (f == 0)
        {
                cout << "NO";
        }
}

int main()
{
        match();
        return 0;
}