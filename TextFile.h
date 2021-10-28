#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

class TextFile
{
	ifstream ifs_file;
	ofstream ofs_file;
	static const int INT_ID = 1,
		TIME_ID = 2,
		FLOAT_ID = 3,
		STRING_ID = 4;

	void ReturnToBeginning();
	string NameFile();
	bool CheckStream(string stream);
	tuple <int, int> FindPos(string line, int column);
	int CountLines();
	int GetColumnType(int column);

public:
	TextFile();
	TextFile(string dir, char mode);
	~TextFile();

	void CopyFile(TextFile cp_from);
	void SortStrings(char mod, int column = 1);
	void SumStrings(int column);

	TextFile& operator += (const TextFile& cp_from); 
	TextFile operator + (const TextFile& cp_from) const;
	TextFile& operator -= (const TextFile& del_from); 
	TextFile operator - (const TextFile& del_from) const;
};
