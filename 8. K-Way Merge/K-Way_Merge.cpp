#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;
char highvalue[10] = "zzzzzzzz";

int getitem(ifstream &file, string name)
{
	file >> name;
	if (file.fail())
	{
		strcpy(name, highvalue);
		return 0;
	}
	return 1;
}

void merge(string file1, string file2, string output)
{
	string name1, name2;
	ifstream f1, f2;
	ofstream f3;
	f1.open(file1);
	f2.open(file2);
	f3.open(output);

	int moreitems1 = getitem(f1, name1);
	int moreitems2 = getitem(f2, name2);

	while (moreitems1 || moreitems2)
	{
		if (moreitems1 == 0)
		{
			f3 << name2 << endl;
			moreitems2 = getitem(f2, name2);
			continue;
		}

		if (moreitems2 == 0)
		{
			f3 << name1 << endl;
			moreitems1 = getitem(f1, name1);
			continue;
		}

		int cmp = strcmp(name1,name2);

		if (name1 < name2)
		{
			f3 << name1 << endl;
			moreitems1 = getitem(f1, name1);
		}

		else if (name1 == name2)
		{
			f3 << name1 << endl;
			moreitems1 = getitem(f1, name1);
			moreitems2 = getitem(f2, name2);
		}
		else
		{
			f3 << name2 << endl;
			moreitems2 = getitem(f2, name2);
		}
	}
	f1.close();
	f2.close();
	f3.close();
}

void main()
{
	merge("1.txt", "2.txt", "m1.txt");
	merge("3.txt", "4.txt", "m2.txt");
	merge("5.txt", "6.txt", "m3.txt");
	merge("7.txt", "8.txt", "m4.txt");
	merge("m1.txt", "m2.txt", "k1.txt");
	merge("m3.txt", "m4.txt", "k2.txt");
	merge("k1.txt", "k2.txt", "final.txt");
}
