#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<string.h>

using namespace std;

int main()
{
	string name;
	fstream fin;
	ofstream fout;
	fin.open("in.txt",ios::in|ios::out);
	fout.open("out.txt",ios::out);
	while(!fin.eof())
	{
		fin>>name;
		if(fin.good())
		{
			reverse(name.begin(),name.end());
			fout<<name<<endl;
		}
	}
	fout.close();
}
