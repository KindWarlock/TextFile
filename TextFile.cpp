#include "TextFile.h"

void TextFile::ReturnToBeginning()
{
	if (ifs_file) {
		ifs_file.clear();
		ifs_file.seekg(0);
	}
	else {
		//exception
	}
}

string TextFile::NameFile()
{
	int cnt = 1;
	string file_name = "new_file.dat";
	fstream file;
	while (!file.good()) {
		file_name = "new_file_" + to_string(cnt) + ".dat";
		fstream file(file_name);
	}
	return file_name;
}

bool TextFile::CheckStream(string stream)
{
	if (stream == "input" && !(this->ifs_file)) {
		cout << "no input";
		return false;
	}
	else if (stream == "output" && !(this->ofs_file)) {
		cout << "no output";
		return false;
	}
	return true;
}

tuple <int, int> TextFile::FindPos(string line, int column) {
	int cnt = 0,
		pos_start = 0,
		str_length;
	while (cnt < column - 1) {
		pos_start = line.find(' ', pos_start) + 1;
		cnt++;
	}
	str_length = line.find(' ', pos_start) + 1 - pos_start;
	return { pos_start,  str_length };
}

int TextFile::CountLines()
{
	string line;
	int cnt = 0;
	while (getline(ifs_file, line)) {
		cnt++;
	}
	ReturnToBeginning();
	return cnt;
}

int TextFile::GetColumnType(int column)
{
	switch (column) {
	case 1:
	case 4:
	case 10:
		return INT_ID;
		break;
	case 2:
		return TIME_ID; 
		break;
	case 3:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		return FLOAT_ID;
		break;
	case 11:
		return STRING_ID;
		break;
	}
}

TextFile::TextFile() 
{
	ifstream new_file(NameFile());
}

TextFile::TextFile(string dir, char mode)
{
	if (mode == 'r') {
		ifs_file.open(dir);
		if (!ifs_file) {
			cout << "No such file!";
			//exception
		}
	}
	else if (mode == 'w') {
		ofs_file.open(dir);
	}
	else {
		cout << "Incorrect mode";
		//exception
	}
	
}

TextFile::~TextFile()
{
	if (this->CheckStream("output")) {
		this->ofs_file.close();
	}
	else 
		this->ifs_file.close();
	delete[] this;
}

void TextFile::CopyFile(TextFile cp_from)
{
	if (!cp_from.CheckStream("input")) {
		//exception
	}
	if (!this -> CheckStream("output")) {
		//exception
	}
	string line;
	while (getline(cp_from.ifs_file, line)) {
		this->ofs_file << line;
	}
	cp_from.ReturnToBeginning();
}

void TextFile::SortStrings(char mod, int column)
{
	string line;
	string *file_data = new string[CountLines()];
	int col_type = GetColumnType(column);
	switch (col_type) {
	case INT_ID:
		while (getline(this->ifs_file, line)) {
			// template Sort
			auto[pos_start, str_length] = FindPos(line, column);
			string col_data = line.substr(pos_start, str_length);
			stoi(col_data);
		}
		break;
	case TIME_ID:
		//time
		break;
	case FLOAT_ID:
		//float
		break;
	case STRING_ID:
		//string
		break;
	}
}

void TextFile::SumStrings(int column)
{

}
