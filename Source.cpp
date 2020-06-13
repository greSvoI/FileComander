#include "FileCommande.h"
#include "Menu.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = -1;
	Menu menu;
	while(choice!=0)
	menu.ShowMenu(choice);
}

