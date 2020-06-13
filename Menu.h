#pragma once
#include "FileCommande.h"
using namespace std;
class Menu :public FileManager
{
public:
	Menu() {}
	void ShowMenu(int &choice);
	void SelectMenu(const int choice);
	void Create();
	void Delete();
	void Move();
	void Find();
	void Copy();
	void VievRename();
	void Size();
	void NewWay();
};
