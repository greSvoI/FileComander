#include "FileCommande.h"
#include "Menu.h"
FileManager::FileManager()
{
	//GetCurrentDirectory(sizeof(path), path);
	string t = "D:";
	strcpy(path,t.c_str());
}
bool FileManager::ChangeWay(string way)
{
	RemoveSpaceSlash(way);
	if (way[1] == ':')
		if (ShowDir(way.c_str()))
		{
			strcpy(this->path, way.c_str());
			return true;
		}
		else
			return false;
	else return false;
}
bool FileManager::ShowDir(const char* path)
{
	_finddata_t find;
	string pathfind = path;
	pathfind += "\\*.*";
	string info = "Такой Директории Нет";
	int result = _findfirst(pathfind.c_str(), &find);
	system("cls");
	int flag = result;
	if (flag == -1) {
		cout << setw(10) << info;
		return false;
	}
	while (flag != -1) {
		if (strcmp(find.name, ".") && strcmp(find.name, ".."))
		{
			find.attrib& _A_SUBDIR ? info = "Каталог" : info = "Файл";
			cout << setw(30) << find.name << setw(10) << info << setw(10) << find.size << endl;
		}
		flag = _findnext(result, &find);
	}


	ShowCurrentDir(path);
	_findclose(result);
	return true;
}
bool FileManager::ShowDirSize(INT64& size)
{
	_finddata32i64_t find;
	string pathfind = path;
	pathfind += "\\*.*";
	string info = "Not directory name!";
	int result = _findfirst32i64(pathfind.c_str(), &find);
	system("cls");
	int flag = result;
	if (flag == -1) {
		cout << setw(10) << info;
		return false;
	}
	while (flag != -1) {
		if (strcmp(find.name, ".") && strcmp(find.name, ".."))
		{
			if (find.attrib & _A_SUBDIR)
			{
				pathfind.resize(pathfind.size() - 3);
				pathfind += find.name;
				string temp = find.name;
				pathfind += "\\*.*";
				SizeFolder(pathfind, size);
				pathfind.resize(pathfind.size() - ((temp.size()) + 5));
				pathfind += "\\*.*";
				cout << setw(70) << find.name << setw(10) << "Directory" << setw(20) << fixed << setprecision(0) << size <<" byte"<< endl;
				size = 0;
			}
			else
				cout << setw(70) << find.name << setw(10) << "File" << setw(20) << find.size << endl;
		}
		flag = _findnext32i64(result, &find);
	}
	_findclose(result);
	return true;
}
bool FileManager::SizeFolder(string path_temp, INT64& size)
{
	_finddata32i64_t find;
	int result = _findfirst32i64(path_temp.c_str(), &find);
	int flag = result;
	while (flag != -1)

	{
		if (strcmp(find.name, ".") && strcmp(find.name, ".."))
		{
			if (find.attrib & _A_SUBDIR)
			{
				path_temp.resize(path_temp.size() - 3);
				path_temp += find.name;
				string temp = find.name;
				path_temp += "\\*.*";
				size += SizeFolder(path_temp, size);
				path_temp.resize(path_temp.size() - temp.size() - 5);
				path_temp += "\\*.*";
			}
			size += find.size;
		}
		flag = _findnext32i64(result, &find);
	}
	return size;
}
void FileManager::ShowCurrentDir(const char* path) { cout << path << ">" << endl; }
void FileManager::CreateFolder(string name)
{
	if (!_mkdir(Path(name).c_str()))
		cout << "\nFolder created!"<<endl;
	else
		cout << "\nError not created folder!"<<endl;
}
void FileManager::DeleteFolder(string name)
{

	if (!_rmdir(name.c_str()))
		cout << "\nDirectory deleted !"<<endl;
	else
		cout << "\nError no deleted!"<<endl;
}
void FileManager::DleteDirectory(string path)
{
	string t;
	string file = path;
	_finddata_t f_fold;
	int result = _findfirst(path.c_str(), &f_fold);
	int flag = result;
	while (flag != -1)
	{
		if (strcmp(f_fold.name, ".") && strcmp(f_fold.name, ".."))
		{
			if (f_fold.attrib & _A_SUBDIR)
			{
				path.resize(path.size() - 3);
				path += f_fold.name;
				t = f_fold.name;
				path += "\\*.*";
				DleteDirectory(path);
				path.resize(path.size() - 3);
				_rmdir(path.c_str());
				path.resize(path.size() - (t.size() + 2));
				path += "\\*.*";
			}
			else
			{
				t = f_fold.name;
				file = path;
				file.resize(file.size() - 3);
				file += f_fold.name;
				remove(file.c_str());

			}
		}

		flag = _findnext(result, &f_fold);
	}

	_findclose(result);



}
void FileManager::RemoveFile(string name)
{
	if (!remove(Path(name).c_str()))
		cout << "\nFile deleted!"<<endl;
	else
		cout << "\nError no deleted!"<<endl;
}
void FileManager::CopyFiles()
{
	string name, name_to,name_temp;
	cout << "\nEnter a file name (Test.jpg) : ";
	getline(cin.ignore(247, '\n'), name);
	name_to = name;
	name = Path(name);
	cout << "Enter where to copy (C:\\Temp\\) : ";
	cin.sync();
	getline(cin, name_temp);
	RemoveSpaceSlash(name_temp);
	name_temp += name_to;
	if (CopyFile(name.c_str(), name_temp.c_str(), true))
	cout << "\nOk !!!"<<endl;
	else cout << "\nInvalid input !!!"<<endl;
}
void FileManager::ShowFile()
{
	string str,name;
	cout << "\nEnter file name : ";
	getline(cin.ignore(247, '\n'), name);
	ifstream fin(name);
	if (!fin.is_open())
		cout << "Error!\n Неверное имя файла! \n\n";
	else
		while (!fin.eof())
		{
			getline(fin, str);
			cout << str << endl;
		}
	cout << endl << endl;

}
void FileManager::RenameFile()
{
	string name, name2;
	cout << "File name : ";
	getline(cin.ignore(247, '\n'), name);
	cout << "New file name : ";
	cin.sync();
	getline(cin, name2);
	name2 = Path(name2);
	if (rename(Path(name).c_str(), name2.c_str()) != 0)
		cout << "Error! Invalid file name! \n\n";
	else
		cout << "OK...\n\n";
}
void FileManager::ChangeFileCatalog()
{
	string name_is, name_to;
	cout << "\nFile name : ";
	getline(cin.ignore(247, '\n'),name_is );
	cout << "\nWhere to move : ";
	cin.sync();
	getline(cin, name_to);
	RemoveSpaceSlash(name_to);
	name_to += name_is;
	if (rename(Path(name_is).c_str(), name_to.c_str()) != 0)
		cout << "Error!\nInvalid file name!Or such a file already exists!! \n\n";
	else
		cout << "OK...\n\n";
	Sleep(1000);
}
void FileManager::NewFile(const string name)
{
	ofstream fout;
	fout.open(Path(name));
	if (!fout.is_open())
		cout << "Error!";
	else
		cout << "New file created!";
	cout << endl;
	fout.close();
}
void FileManager::RemoveSpaceSlash(string& str)
{
	int index = str.length() - 1;
	while (str[index] == '\\' || str[index] == ' ')
	{
		index--;
	}
	str.resize(index + 1);
	str += "\\";
}
void FileManager::Search(string root, string mask,int &total)
{

	_finddata_t f_file;
	string temp = root;
	temp.resize(temp.size() - 3);
	temp += mask;
	int result = _findfirst(temp.c_str(), &f_file);
	int flag = result;
	if (flag != -1)
		cout << endl << root << endl;
	while (flag != -1)
	{

		if (strcmp(f_file.name, ".") && strcmp(f_file.name, ".."))
		{
			cout << f_file.name << endl; total++;

		}
		flag = _findnext(result, &f_file);
	}
	_finddata_t f_fold;
	result = _findfirst(root.c_str(), &f_fold);
	flag = result;
	while (flag != -1)
	{
		if (strcmp(f_fold.name, ".") && strcmp(f_fold.name, ".."))
		{
			if (f_fold.attrib & _A_SUBDIR)
			{

				root.resize(root.size() - 3);
				root += f_fold.name;
				string t = f_fold.name;
				root += "\\*.*";
				Search(root,mask, total);
				root.resize(root.size() - (t.size() + 5));
				root += "\\*.*";
			}
		}
		flag = _findnext(result, &f_fold);
	}
	_findclose(result);
}
void FileManager::CopyDirectory(string path, string newPath)
{

	string t;
	string file=path;
	_finddata_t f_fold;
	int result = _findfirst(path.c_str(), &f_fold);
	int flag = result;
	while (flag != -1)
	{
		if (strcmp(f_fold.name, ".") && strcmp(f_fold.name, ".."))
		{
			if (f_fold.attrib & _A_SUBDIR)
			{
				path.resize(path.size() - 3);
				path += f_fold.name;
				newPath += f_fold.name;
				newPath += "\\";
				_mkdir(newPath.c_str());
				t = f_fold.name;
				path += "\\*.*";
				CopyDirectory(path, newPath);
				newPath.resize(newPath.size() - t.size() - 1);
				path.resize(path.size() - (t.size() + 5));
				path += "\\*.*";
			}
			else
			{
				t = f_fold.name;
				newPath += t;
				file = path;
				file.resize(file.size() - 3);
				file += f_fold.name;
				CopyFile(file.c_str(), newPath.c_str(), true);
				newPath.resize(newPath.size() - t.size());
			}
		}

		flag = _findnext(result, &f_fold);
	}

	_findclose(result);


}
string FileManager::SlashSearch(string& name)
{
	string temp;
	if (name[0] == ' ')
	{
		for (int i = 0; i < name.size(); i++)
		{
			if (name[i] != ' ')
				temp += name[i];
		}
		name = temp;
	}
	temp = this->path;
	temp += "\\";
	temp += name;
	name = temp;
	int index = name.length();
	if (name[index] != '\\')
		name += "\\*.*";
	return name;
}
string FileManager::Path(string name_t)
{
	string temp;
	temp = this->path;
	temp += "\\";
	temp += name_t;
	return temp;
}