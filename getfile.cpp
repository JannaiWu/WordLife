﻿#include<fstream>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

vector<vector<int>> getfile() 
{
	vector<vector<int>> v;
	string filename = "test.txt";
	ifstream in;
	in.open(filename);
	string line;//读取每一行数据
	//如果打不开的情况另考虑
	if (!in)
	{
		cout << "打开文件出错";
		return v;
	}
	vector<int> tep;
	while (getline(in,line))
	{
		tep.clear();
		for (int i = 0; i < line.length(); i++)
		{
			switch (line[i])
			{
			case '1':
				tep.push_back(1);
				break;
			case '0':
				tep.push_back(0);
				break;
			default:
				break;
			}	
		}
		v.push_back(tep);
	}
	return v;
}