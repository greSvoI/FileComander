#pragma once
#pragma warning (disable:4996)
#include <iostream>
#include <string>
#include <io.h>
#include <direct.h>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
class FileManager
{
public:
	char path[MAX_PATH];
	FileManager();
	bool ChangeWay(string way);
	bool ShowDir(const char* path);
	bool ShowDirSize(INT64& size);
	bool SizeFolder(string path_temp, INT64& size);
	void ShowCurrentDir(const char *path);
	void CreateFolder(string name);
	void DeleteFolder(string name);
	void DleteDirectory(string name);
	void RemoveFile(string name);
	void CopyFiles();
	void ShowFile();
	void RenameFile();
	void ChangeFileCatalog();
	void NewFile(const string name);
	void RemoveSpaceSlash(string& str);
	void CopyDirectory(string path,string newpath);
	void Search(string path, string mask, int& total);
	string Path(string name_t);
	string SlashSearch(string& name);
	~FileManager() {}
};
