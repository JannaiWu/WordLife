#includefstream
#includevector
#includestring
#includeiostream

using namespace std;

vectorvectorint getfile() 
{
	vectorvectorint v;
	string filename = test.txt;
	ifstream in;
	in.open(filename);
	string line;��ȡÿһ������
	����򲻿����������
	if (!in)
	{
		cout  ���ļ�����;
		return v;
	}
	vectorint tep;
	while (getline(in,line))
	{
		tep.clear();
		for (int i = 0; i  line.length(); i++)
		{
			switch (line[i])
			{
			case '1'
				tep.push_back(1);
				break;
			case '0'
				tep.push_back(0);
				break;
			default
				break;
			}	
		}
		v.push_back(tep);
	}
	return v;
}