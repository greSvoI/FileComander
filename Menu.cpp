#include "Menu.h"
#include "FileCommande.h"
void Menu::ShowMenu(int &choice)
{
	
	ShowDir(path);
	cout << "\n1.  Create " << endl;
	cout << "2.  Delete " << endl;
	cout << "3.  Move " << endl;
	cout << "4.  Find " << endl;
	cout << "5.  Copy " << endl;
	cout << "6.  Viev/Rename file " << endl;
	cout << "7.  Size directory " << endl;
	cout << "8.  Go to another directory" << endl;
	cout << "0.  Exit" << endl;
	
	while (true)
	{
		cout << "The choice : ";
		if (!(cin >> choice))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
			choice = -1;
		}
		if (choice > 0 && choice <= 8)
		{
			SelectMenu(choice);
 			system("pause");
			system("cls");
			break;
		}
		if (choice == 0)
			break;
	}
}
void Menu::SelectMenu(const int choice)
{
	if (choice == 1)Create();
	if (choice == 2)Delete();	
	if (choice == 3)Move();	
	if (choice == 4)Find();
	if (choice == 5)Copy();	
	if (choice == 6)VievRename();
	if (choice == 7)Size();
	if (choice == 8)NewWay();
}
void Menu::Create()
{
	int key; string name;
	while (true) {
		cout << "1. New file\t2. New folder\t0. Return"<<endl;
		if (!(cin >> key))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (key == 1)
		{
			cout << "Enter a new file name : ";
			getline(cin.ignore(247, '\n'), name);
			NewFile(name); 
			break;
		}
		if (key == 2)
		{
			cout << "Enter a new folder name : ";
			getline(cin.ignore(247, '\n'), name);
			CreateFolder(name);
			break;
		}
		if (key==0)
			break;
	}
}
void Menu::Delete()
{
	int key; string name;
	while (true) {
		cout << "1. Delete file\t2. Delete folder\t0. Return"<<endl;
		if (!(cin >> key))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (key == 1)
		{
			cout << "Enter file name : ";
			getline(cin.ignore(247,'\n'), name);
			RemoveFile(name);
			break;
		}
		if (key == 2)
		{
			cout << "Enter folder name : ";
			getline(cin.ignore(247, '\n'), name);
			cout << "\nAre you sure you want to permanently delete this folder ?"<<endl;
			cout <<setw(5)<< " Yes"<<"- 1"<<endl;
			cout << setw(5) << "No"<<"- Other"<<endl;
			cin >> key;
			if (key == 1)
			{
				SlashSearch(name);
				DleteDirectory(name);
				name.resize(name.size() - 3);
				DeleteFolder(name);
			}
			break;
		}
		if (key == 0)
			break;
	}
}
void Menu::Move() 
{
	int key; string name,name_to;
	while (true) {
		cout << "1. Move file\t2. Move directory\t0. Return"<<endl;
		if (!(cin >> key))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (key == 1)
		{
			ChangeFileCatalog();
			break;
		}
		if (key == 2)
		{
			cout << "Enter directory name : ";
			getline(cin.ignore(247, '\n'), name);
			cout << "Where to move the directory : ";
			cin.sync();
			getline(cin, name_to);
			RemoveSpaceSlash(name_to);
			name_to += name;
			if (!_mkdir(name_to.c_str()))
			{
				SlashSearch(name);
				RemoveSpaceSlash(name_to);
				CopyDirectory(name, name_to);
				DleteDirectory(name);
				name.resize(name.size() - 3);
				_rmdir(name.c_str());
				cout << "\nOk!" << endl;
				system("pause");
			}
			else
			cout << "\nWrong path for copy!"<<endl;
			break;
		}
		if (key == 0)
			break;
	}

}
void Menu::Find()
{
	int key,total=0; string name,name_temp;
	name_temp = path;
	name_temp += "\\*.*";
	while (true) {
		cout << "1. Find file\t2. Find folder\t0. Return"<<endl;
		if (!(cin >> key))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (key == 1)
		{
			cout << "Enter a file name with or without extension (*jpg) (file_name.txt)!!! : ";
			getline(cin.ignore(247, '\n'), name);
			Search(name_temp, name, total);
			cout << "Found files : " << total<<endl;
			if(total==0)
			cout << "Try again and enter at the beginning *" << endl;
			break;
		}
		if (key == 2)
		{
			cout << "Enter folder name !!! : ";
			getline(cin.ignore(247, '\n'), name);
			Search(name_temp, name, total);
			break;
		}
		if (key == 0)
			break;
	}

}
void Menu::Copy() 
{
	int key; string name, name_to;
	while (true) {
		cout << "1. Copy file\t2. Copy directory\t0. Return" << endl;
		if (!(cin >> key))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (key == 1)
		{
			CopyFiles();
			break;
		}
		if (key == 2)
		{
			cout << "Enter directory name : ";
			getline(cin.ignore(247, '\n'), name);
			cout << "Where to copy the directory : ";
			cin.sync();
			getline(cin, name_to);
			RemoveSpaceSlash(name_to);
			name_to += name;
			if (!_mkdir(name_to.c_str()))
			{
				SlashSearch(name);
				RemoveSpaceSlash(name_to);
				CopyDirectory(name, name_to);
				cout << "\nDirectory is copy!"<<endl;
			}
			else
				cout << "\nWrong path for copy!" << endl;
			break;
		}
		if (key == 0)
			break;
	}
}
void Menu::VievRename()
{
	int key; string name;
	while (true) {
		cout << "1. Viev file\t2. Rename file\\folder\t0. Return" << endl;
		if (!(cin >> key))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (key == 1)
		{
			ShowFile();
			break;
		}
		if (key == 2)
		{
			RenameFile();
			break;
		}
		if (key == 0)
			break;
	}
	
}
void Menu::Size()
{
	int key;
	string name;
	INT64 size=0;
	while (true)
	{
		cout << "\n1. Directory Size\t2. Size of all directories\t0. Return" << endl;
		if (!(cin >> key))
		{
			cout << "\nRepeat Entry!" << endl;
			cin.clear();
			cin.ignore(50, '\n');
		}
		if (key == 1)
		{
			cout << "Enter directory name : ";
			getline(cin.ignore(247, '\n'),name);
			SlashSearch(name);
			SizeFolder(name, size);
			cout<<"\nSize folder :" <<setw(10)<< fixed << setprecision(0) << size << endl;
			break;
		}
		if (key == 2)
		{
			ShowDirSize(size);
			break;
		}
		if (key == 0)
			break;
	}
}
void Menu::NewWay()
{
	string new_path;
	cout << "\nEnter directory path :"<<endl;
	getline(cin.ignore(247, '\n'),new_path);
	if (ChangeWay(new_path))
		cout << "\nOk!" << endl;
	else 
		cout << "\nIncorrectly entered path" << endl;
}