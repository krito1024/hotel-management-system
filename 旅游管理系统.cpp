#include<iostream>
#include<string>
#include<fstream>
#include"Traveler.h"
#include"Hotel.h"
using namespace std;
int main(int argc, const char* argv[])
{
	hotel wm;
	int choice;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入你所需要的服务数字：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			wm.Add_Tra();
			for (int i = wm.addNum; i >= 1; i--)
				wm.in_serve1(i);
			break;
		case 2:
			wm.in_serve2();
			break;
		case 3:
			wm.ExitSystem();
			break;
		case 4:
			system("cls");
			break;
		case 5:
			wm.in_serve5();
			break;
		}
	}
	system("pause");
	return 0;
}