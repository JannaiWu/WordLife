#include<iostream>
#include<vector>

using namespace std;

int get_neightbor_cells(vector<vector<int>>& cur, int index_x, int index_y)
{
	int count = 0;
	int posx[8] = { -1,-1,-1,0,0,1,1,1 };
	int posy[8] = { -1,0,1,-1,1,-1,0,1 };
	for (int i = 0; i < 8; i++)
	{
		int x = index_x + posx[i];
		int y = index_y + posy[i];
		if (x < 0 || x >= cur.size() || y<0 || y >= cur[0].size())
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