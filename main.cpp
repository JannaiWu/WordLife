#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<windows.h>


using namespace std;

vector<vector<int>> getfile() 
{
	vector<vector<int>> v;
	string filename = "Glider.txt";
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

int get_neightbor_cells(vector<vector<int>>& cur, int index_x, int index_y)
{
	int count = 0;
	int posx[8] = { -1,-1,-1,0,0,1,1,1 };
	int posy[8] = { -1,0,1,-1,1,-1,0,1 };
	for (int i = 0; i < 8; i++)
	{
		int x = index_x + posx[i];
		int y = index_y + posy[i];
		if (x < 0 || x >= cur.size() || y < 0 || y >= cur[0].size())
			continue;
		count += cur[x][y];
	}

	return count;
}

int nextlife(int now, int count)
{
	if (count < 2 || count >3)
		return 0;
	if (now == 0 && count == 3)
		return 1;
	return now;
}

void getnext(vector<vector<int>> & cur, vector<vector<int>> & next)
{
	int w = cur.size();
	int l = cur[0].size();
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < l; j++)
		{
			int count = get_neightbor_cells(cur, i, j);
			next[i][j] = nextlife(cur[i][j], count);
		}
	}
	return;
}

void printworld(vector<vector<int>>& cur)
{
	for (int i = 0; i < cur.size(); i++)
	{
		for (int j = 0; j < cur[i].size(); j++)
		{
			if (cur[i][j] == 0)
				cout << '.';
			else
				cout << '*';
		}
		cout << endl;
	}
	return;
}

int main()
{
	vector<vector<int>> v = getfile();
	vector<vector<int>> next(v);
	int n = 100;
	while (n)
	{
		printworld(v);
		getnext(v, next);
		v = next;
		n--;
		Sleep(500);
		system("cls");
	}
}