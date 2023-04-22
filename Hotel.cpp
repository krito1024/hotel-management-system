#include<iostream>
#include"Hotel.h"
#include<fstream>
#include<string>
#include"Traveler.h"
#include"Time.h"

using namespace std;

bool flag = true;//定义布尔标志确定是否输入过个人信息

void read1()
{
	ifstream ifs;
	ifs.open("room.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败。" << endl;
		return;
	}
	string buf;
	while (getline(ifs, buf)) {
		cout << buf << endl;
	}
	ifs.close();
}
void read()
{
	room* head;//创建链表读取room文件里的信息
	head = creatlink(8);
	input_new(head);
	while (head != NULL)
	{
		cout << head->room_num << "       ";
		cout << head->room_rank << "         ";
		cout << head->bed_sum << "         ";
		cout << head->bed_using_num << "        ";
		cout << endl;
		head = head->next;
	}
}
hotel::hotel()
{
	ifstream ifs;
	ifs.open("traveler.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "                    当前入住人数为0" << endl;
		cout << endl;
		this->m_Tranum = 0;
		this->m_TraArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "                   当前入住人数为0" << endl;
		cout << endl;
		this->m_Tranum = 0;
		this->m_TraArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		//return;
	}
	else
	{
		//文件存在，并记录数据
		int num = this->get_Tranum();
		cout << "                        当前入住人数为：" << num << endl;
		cout << endl;
		this->m_Tranum = num;//当前文件内旅客人数
		this->m_TraArray = new traveler * [this->m_Tranum];  //开辟一个旅客人数那么大的空间
		this->init_Tra();  //将数据存放在数组中
	}
	
	//创建三个等级空房栈链表
	room_level1 = creatlink(2);
	room_level2 = creatlink(3);
	room_level3 = creatlink(3);

	ifstream fp("room.txt", ios::in);
	if (!fp.is_open())
	{
		cout << "文件打开失败。" << endl;
		return;
	}
	//根据文件内容初始化各等级房间链表
	finput_new(room_level1, fp, 2);
	finput_new(room_level2, fp, 3);
	finput_new(room_level3, fp, 3);
	fp.close();

	/*testshow(room_level1);
	testshow(room_level2);
	testshow(room_level3);*/

	//入空房栈操作
	room* head1 = room_level1;
	while (head1 != NULL)
	{
		if (head1->bed_count != "0")
		{
			ms1.push(head1);
		}
		head1 = head1->next;
	}

	room* head2 = room_level2;
	while (head2 != NULL)
	{
		if (head2->bed_count != "0")
		{
			ms2.push(head2);
		}
		head2 = head2->next;
	}

	room* head3 = room_level3;
	while (head3 != NULL)
	{
		if (head3->bed_count != "0")
		{
			ms3.push(head3);
		}
		head3 = head3->next;
	}

}
void hotel::Add_Tra()//添加旅客
{
	cout << "请输入入住的人数：" << endl;
	
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_Tranum + addNum;//旅客人数加上要添加的人数
		traveler** newSpace = new traveler * [newSize];//newsize那么大的新空间
		if (this->m_TraArray != NULL)
		{
			for (int i = 0; i < this->m_Tranum; i++)
			{
				newSpace[i] = this->m_TraArray[i];//把旅客文件里的内容给新空间
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			string name, sex, workplace, office, from, id,room_num,in_date,out_date;
			int age, bed_code = -1;
			cout << "请您输入第" << i + 1 << "个姓名" << endl;
			cin >> name;
			cout << "请您输入其性别" << endl;
			cin >> sex;
			cout << "请您输入其年龄" << endl;
			cin >> age;
			cout << "请您输入其工作单位" << endl;
			cin >> workplace;
			cout << "请您输入其职务" << endl;
			cin >> office;
			cout << "请您输入其来自何处" << endl;
			cin >> from;
			cout << "请您输入其身份证号" << endl;
			cin >> id;
			in_date = getTime();//获取电脑的时间
			in_date = getTime();//获取电脑的时间
			traveler* tra = NULL;
			tra = new traveler(name, sex, workplace, office, from, id, age,room_num,bed_code,in_date);
			newSpace[this->m_Tranum + i] = tra;
		}
		delete[] this->m_TraArray;
		this->m_TraArray = newSpace;
		this->m_Tranum = newSize;
		this->m_FileIsEmpty = false;
		//this->save();

	}
	else
	{
		cout << "输入有误。" << endl;
	}

}
void hotel::save()
{
	ofstream ofs;
	ofs.open("traveler.txt", ios::out);
	for (int i = 0; i < this->m_Tranum; i++)
	{
		ofs << this->m_TraArray[i]->m_name << " "
			<< this->m_TraArray[i]->m_sex << " "
			<< this->m_TraArray[i]->m_age << " "
			<< this->m_TraArray[i]->m_workplace << " "
			<< this->m_TraArray[i]->m_office << " "
			<< this->m_TraArray[i]->m_from << " "
			<< this->m_TraArray[i]->m_id << " "
			<< this->m_TraArray[i]->room_num << " ";
			this->m_TraArray[i]->Empty_bed_num.fshow(ofs);
		ofs << " "<<this->m_TraArray[i]->in_date << " "
			<< this->m_TraArray[i]->out_date << endl;
	}
	ofs.close();
}

int hotel::get_Tranum()
{
	ifstream ifs;
	ifs.open("traveler.txt", ios::in);
	string name, sex, workplace, office, from, id, room_num, in_date, out_date;
	int age;
	int num = 0, bed_code = -1;
	while (ifs >> name && ifs >> sex && ifs >> age && ifs >> workplace && ifs >> office && ifs >> from && ifs >> id && ifs >> room_num && ifs >> bed_code && ifs >> in_date)
	{
		num++;
	}
	return num;
}
void hotel::init_Tra()
{
	ifstream ifs;
	ifs.open("traveler.txt", ios::in);
	string name, sex, workplace, office, from, id, room_num, in_date, out_date;
	int age, index = 0, bed_code = -1;
	while (ifs >> name && ifs >> sex && ifs >> age && ifs >> workplace && ifs >> office && ifs >> from && ifs >> id && ifs >> room_num && ifs >> bed_code && ifs >> in_date)
	{
		traveler* Traveler = new traveler(name, sex, workplace, office, from, id, age, room_num, bed_code, in_date);
		this->m_TraArray[index] = Traveler;
		index++;
	}
	ifs.close();
}
void hotel::Show_Tra()
{
	if (this->m_FileIsEmpty)
	{
		cout << "                  当前入住人数为0" << endl << endl;
	}
	else
	{
		for (int i = 0; i < m_Tranum; i++)
		{
			this->m_TraArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}
void hotel::Show_Menu()
{
	cout << "欢迎来到旅馆管理系统，这里给您最棒的服务：" << endl;
	cout << "以下是各房间信息表：" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "房间     |级别     |床位数    |占用床位数    |" << endl;
	cout << "----------------------------------------------" << endl;
	read();
	cout << "----------------------------------------------" << endl;
	cout << "本店有以下服务：" << endl;
	cout << "1.住店服务  2.退房  3.退出  4.清屏  5.其他" << endl;
	cout << "----------------------------------------------" << endl;
}
void hotel::ExitSystem() {
	cout << "欢迎下次使用。" << endl;
	system("pause");
	exit(0);
}
void hotel::inroomfile()//更新房间内容
{
	ofstream of;
	of.open("room.txt", ios::trunc);
	if (!of.is_open())
	{
		cout << "文件打开失败！";
		return;
	}
	room* head1 = room_level1;
	room* head2 = room_level2;
	room* head3 = room_level3;
	while (head1)
	{
		of << head1->room_num << "   " << head1->room_rank << "   "
			<< head1->bed_sum << "            " << head1->bed_using_num << "                 "
			<< head1->sex << "     " << head1->bed_count << "            ";
		show_bednum(head1->Empty_bed_num, of);
		of << head1->money_one << "                   " << head1->money_all << endl;
		head1 = head1->next;
	}

	while (head2)
	{
		of << head2->room_num << "   " << head2->room_rank << "   "
			<< head2->bed_sum << "            " << head2->bed_using_num << "                 "
			<< head2->sex << "     " << head2->bed_count << "            ";
		show_bednum(head2->Empty_bed_num, of);
		of << head2->money_one << "                   " << head2->money_all << endl;
		head2 = head2->next;
	}

	while (head3)
	{
		of << head3->room_num << "   " << head3->room_rank << "   "
			<< head3->bed_sum << "            " << head3->bed_using_num << "                 "
			<< head3->sex << "     " << head3->bed_count << "            ";
		show_bednum(head3->Empty_bed_num, of);
		of << head3->money_one << "                   " << head3->money_all << endl;
		head3 = head3->next;
	}
	of << "房间 级别 床位总数 占用床位数 性别 空床位数 空床位号    单床每天费用     包房每天费用";
}
void hotel::in_serve1(int i)
{
	cout << "----------------------------------------------" << endl;
	cout << "请" << this->m_TraArray[this->m_Tranum - i]->m_name << "输入要进行的操作：" << endl;
	cout << "1.单床服务  2.包房服务  3.预定房间" << endl;
	cout << "----------------------------------------------" << endl;
	int n; cin >> n;//输入操作
	if (n == 1)//若要进行单床服务操作
	{
		cout << "请" << this->m_TraArray[this->m_Tranum - i]->m_name << "输入要住的房间等级：" << endl;
		cout << "----------------------------------------------" << endl;
		int m; cin >> m;//输入操作
		if (m == 1)//若选择的是一级房间
		{
			if (ms1.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(i);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					this->m_Tranum--;
					return;//执行主菜单服务
				}
			}
			else if (ms1.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms1 = ms1;
				MyStack<room*> temp_temp_ms1;
				while (!temp_ms1.IsEmpty())
				{
					room* head = temp_ms1.top();
					if (this->m_TraArray[this->m_Tranum - i]->m_sex == head->sex || head->sex == "0")//若旅客性别与房间性别相同,或者一个人也没有并且房间里面的床位
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.push(head->Empty_bed_num.pop());//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						cout << "入住成功,您的房号为：" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;
						head->bed_count[0] -= 1;//住进来则空床位减一
						head->bed_using_num[0] += 1;//占用床位数加一
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms1.pop();
						}
						while (!temp_ms1.IsEmpty())
						{
							temp_temp_ms1.push(temp_ms1.pop());
						}
						ms1 = temp_temp_ms1;
						temp_ms1 = temp_temp_ms1;
						inroomfile();//更新房间文件内容
						this->save();
						break;
					}
					else
					{
						temp_temp_ms1.push(temp_ms1.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms1.IsEmpty() && !ms1.IsEmpty())//若每个房间都不符合性别要求
				{
					if (ms1.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级床铺已满，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(i);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}

		if (m == 2)//若选择的是二级房间
		{
			if (ms2.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(i);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					return;//执行主菜单服务
				}
			}
			else if (ms2.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms2 = ms2;
				MyStack<room*> temp_temp_ms2;
				while (!temp_ms2.IsEmpty())
				{
					room* head = temp_ms2.top();
					if (this->m_TraArray[this->m_Tranum - i]->m_sex == head->sex || head->sex == "0")//若旅客性别与房间性别相同,或者一个人也没有
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.push(head->Empty_bed_num.pop());//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						cout << "入住成功,您的房号为：" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;
						head->bed_count[0] -= 1;//住进来则空床位减一
						head->bed_using_num[0] += 1;//占用床位数加一
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms2.pop();
						}
						while (!temp_ms2.IsEmpty())
						{
							temp_temp_ms2.push(temp_ms2.pop());
						}
						ms2 = temp_temp_ms2;
						temp_ms2 = temp_temp_ms2;
						inroomfile();//更新房间文件内容
						save();
						break;
					}
					else
					{
						temp_temp_ms2.push(temp_ms2.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms2.IsEmpty() && !ms2.IsEmpty())//若每个房间都不符合性别要求
				{
					if (ms1.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级床铺已满，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(i);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}

		if (m == 3)//若选择的是三级房间
		{
			if (ms3.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(i);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					return;//执行主菜单服务
				}
			}
			else if (ms3.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms3 = ms3;
				MyStack<room*> temp_temp_ms3;
				while (!temp_ms3.IsEmpty())
				{
					room* head = temp_ms3.top();
					if (this->m_TraArray[this->m_Tranum - i]->m_sex == head->sex || head->sex == "0")//若旅客性别与房间性别相同,或者一个人也没有
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.push(head->Empty_bed_num.pop());//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						cout << "入住成功,您的房号为：" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;
						head->bed_count[0] -= 1;//住进来则空床位减一
						head->bed_using_num[0] += 1;//占用床位数加一
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms3.pop();
						}
						while (!temp_ms3.IsEmpty())
						{
							temp_temp_ms3.push(temp_ms3.pop());
						}
						ms3 = temp_temp_ms3;
						temp_ms3 = temp_temp_ms3;
						inroomfile();//更新房间文件内容
						save();
						break;
					}
					else
					{
						temp_temp_ms3.push(temp_ms3.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms3.IsEmpty() && !ms3.IsEmpty())//若每个房间都不符合性别要求
				{
					if (ms3.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级床铺已满，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(i);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}
	}
	else if (n == 2)//进行包房服务
	{
		cout << "请" << this->m_TraArray[this->m_Tranum - i]->m_name << "输入要包房的房间等级：" << endl;
		cout << "----------------------------------------------" << endl;
		int m; cin >> m;//输入操作
		if (m == 1)//若选择的是一级房间
		{
			if (ms1.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(i);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					this->m_Tranum--;
					return;//执行主菜单服务
				}
			}
			else if (ms1.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms1 = ms1;
				MyStack<room*> temp_temp_ms1;
				while (!temp_ms1.IsEmpty())
				{
					room* head = temp_ms1.top();
					if (temp_ms1.top()->bed_using_num == "0")//若此房间为空，则可以包房
					{
						
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num = head->Empty_bed_num;//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						while (!head->Empty_bed_num.IsEmpty())//将此房间空床栈清空
						{
							head->Empty_bed_num.pop();
						}
						cout << "入住成功,您的房号为：" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;

						head->bed_count = "0";//住进来则空床位变0
						head->bed_using_num = head->bed_sum;//占用床位数变为床位总数
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms1.pop();
						}
						while (!temp_ms1.IsEmpty())
						{
							temp_temp_ms1.push(temp_ms1.pop());
						}
						ms1 = temp_temp_ms1;//更新最原本的空房栈
						temp_ms1 = temp_temp_ms1;
						inroomfile();//更新房间文件内容
						this->save();//更新旅客文件内容
						break;
					}
					else
					{
						temp_temp_ms1.push(temp_ms1.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms1.IsEmpty() && !ms1.IsEmpty())//若每个房间都不符合包房要求
				{
					if (ms1.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级房间无空房，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(i);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}

		else if (m == 2)//若选择的是二级房间
		{
			if (ms2.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(i);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					return;//执行主菜单服务
				}
			}
			else if (ms2.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms2 = ms2;
				MyStack<room*> temp_temp_ms2;
				while (!temp_ms2.IsEmpty())
				{
					room* head = temp_ms2.top();
					if (temp_ms2.top()->bed_using_num=="0")//若此房间为空，则可以包房
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num = head->Empty_bed_num;//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						while (!head->Empty_bed_num.IsEmpty())//将此房间空床栈清空
						{
							head->Empty_bed_num.pop();
						}
						cout << "入住成功,您的房号为：" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;

						head->bed_count = "0";//住进来则空床位变0
						head->bed_using_num = head->bed_sum;//占用床位数变为床位总数
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms2.pop();
						}
						while (!temp_ms2.IsEmpty())
						{
							temp_temp_ms2.push(temp_ms2.pop());
						}
						ms2 = temp_temp_ms2;//更新最原本的空房栈
						temp_ms2 = temp_temp_ms2;
						inroomfile();//更新房间文件内容
						this->save();//更新旅客文件内容
						break;
					}
					else
					{
						temp_temp_ms2.push(temp_ms2.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms2.IsEmpty() && !ms2.IsEmpty())//若每个房间都不符合包房要求
				{
					if (ms2.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级房间无空房，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(i);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}

		if (m == 3)//若选择的是三级房间
		{
			if (ms3.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(i);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					return;//执行主菜单服务
				}
			}
			else if (ms3.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms3 = ms3;
				MyStack<room*> temp_temp_ms3;
				while (!temp_ms3.IsEmpty())
				{
					room* head = temp_ms3.top();
					if (temp_ms3.top()->bed_using_num == "0")//若此房间为空，则可以包房
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num = head->Empty_bed_num;//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						while (!head->Empty_bed_num.IsEmpty())//将此房间空床栈清空
						{
							head->Empty_bed_num.pop();
						}
						cout << "入住成功,您的房号为：" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;

						head->bed_count = "0";//住进来则空床位变0
						head->bed_using_num = head->bed_sum;//占用床位数变为床位总数
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms3.pop();
						}
						while (!temp_ms3.IsEmpty())
						{
							temp_temp_ms3.push(temp_ms3.pop());
						}
						ms3 = temp_temp_ms3;//更新最原本的空房栈
						temp_ms3 = temp_temp_ms3;
						inroomfile();//更新房间文件内容
						this->save();//更新旅客文件内容
						break;
					}
					else
					{
						temp_temp_ms3.push(temp_ms3.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms3.IsEmpty() && !ms3.IsEmpty())//若每个房间都不符合包房要求
				{
					if (ms3.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级房间无空房，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(i);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}
	}	
	else if (n == 3)//预定房间
	{
		string in_date;//要输入的入店时间
		cout << "请输入您要预定的时间（至少要为一周以后）:" << endl;
		cin >> in_date;
		this->m_TraArray[this->m_Tranum - 1]->in_date = in_date;

		cout << "请" << this->m_TraArray[this->m_Tranum - 1]->m_name << "输入要住的房间等级：" << endl;
		cout << "----------------------------------------------" << endl;
		int m; cin >> m;//输入操作
		if (m == 1)//若选择的是一级房间
		{
			if (ms1.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(1);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					this->m_Tranum--;
					return;//执行主菜单服务
				}
			}
			else if (ms1.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms1 = ms1;
				MyStack<room*> temp_temp_ms1;
				while (!temp_ms1.IsEmpty())
				{
					room* head = temp_ms1.top();
					if (this->m_TraArray[this->m_Tranum - 1]->m_sex == head->sex || head->sex == "0")//若旅客性别与房间性别相同,或者一个人也没有并且房间里面的床位
					{
						this->m_TraArray[this->m_Tranum - 1]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.push(head->Empty_bed_num.pop());//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						cout << "预定成功,您的房号为：" << this->m_TraArray[this->m_Tranum - 1]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.show();
						cout << endl;
						//head->bed_count[0] -= 1;//住进来则空床位减一
						//head->bed_using_num[0] += 1;//占用床位数加一
						//head->sex = this->m_TraArray[this->m_Tranum - 1]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms1.pop();
						}
						while (!temp_ms1.IsEmpty())
						{
							temp_temp_ms1.push(temp_ms1.pop());
						}
						ms1 = temp_temp_ms1;
						temp_ms1 = temp_temp_ms1;
						//inroomfile();//更新房间文件内容
						this->save();
						break;
					}
					else
					{
						temp_temp_ms1.push(temp_ms1.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms1.IsEmpty() && !ms1.IsEmpty())//若每个房间都不符合性别要求
				{
					if (ms1.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级床铺已满，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(1);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}

		if (m == 2)//若选择的是二级房间
		{
			if (ms2.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(1);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					return;//执行主菜单服务
				}
			}
			else if (ms2.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms2 = ms2;
				MyStack<room*> temp_temp_ms2;
				while (!temp_ms2.IsEmpty())
				{
					room* head = temp_ms2.top();
					if (this->m_TraArray[this->m_Tranum - 1]->m_sex == head->sex || head->sex == "0")//若旅客性别与房间性别相同,或者一个人也没有
					{
						this->m_TraArray[this->m_Tranum - 1]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.push(head->Empty_bed_num.pop());//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						cout << "预定成功,您的房号为：" << this->m_TraArray[this->m_Tranum - 1]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.show();
						cout << endl;
						//head->bed_count[0] -= 1;//住进来则空床位减一
						//head->bed_using_num[0] += 1;//占用床位数加一
						//head->sex = this->m_TraArray[this->m_Tranum - 1]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms2.pop();
						}
						while (!temp_ms2.IsEmpty())
						{
							temp_temp_ms2.push(temp_ms2.pop());
						}
						ms2 = temp_temp_ms2;
						temp_ms2 = temp_temp_ms2;
						//inroomfile();//更新房间文件内容
						this->save();
						break;
					}
					else
					{
						temp_temp_ms2.push(temp_ms2.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms2.IsEmpty() && !ms2.IsEmpty())//若每个房间都不符合性别要求
				{
					if (ms1.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级床铺已满，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(1);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}

		if (m == 3)//若选择的是三级房间
		{
			if (ms3.IsEmpty() == 1)//若栈为空，则无空房
			{
				cout << "此等级床铺已满，请重新选择：" << endl;
				cout << "1.继续住房服务  2.返回主菜单" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//输入操作
				if (x == 1)//还要继续住房
				{
					in_serve1(1);//递归进行服务1
				}
				else if (x == 2)//若要返回主菜单
				{
					return;//执行主菜单服务
				}
			}
			else if (ms3.IsEmpty() == 0)//若栈不为空，说明有空房
			{
				MyStack<room*> temp_ms3 = ms3;
				MyStack<room*> temp_temp_ms3;
				while (!temp_ms3.IsEmpty())
				{
					room* head = temp_ms3.top();
					if (this->m_TraArray[this->m_Tranum - 1]->m_sex == head->sex || head->sex == "0")//若旅客性别与房间性别相同,或者一个人也没有
					{
						this->m_TraArray[this->m_Tranum - 1]->room_num = head->room_num;//把房号给旅客
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.push(head->Empty_bed_num.pop());//空床栈弹出床位给旅客房号栈，记得再次向文件写入床位信息的时候用栈写
						cout << "预定成功,您的房号为：" << this->m_TraArray[this->m_Tranum - 1]->room_num << endl;
						cout << "您的床号为 ";
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.show();
						cout << endl;
						//head->bed_count[0] -= 1;//住进来则空床位减一
						//head->bed_using_num[0] += 1;//占用床位数加一
						//head->sex = this->m_TraArray[this->m_Tranum - 1]->m_sex;//把房间性别标记为顾客性别

						if (head->Empty_bed_num.IsEmpty())//如果房间床位满了
						{
							temp_ms3.pop();
						}
						while (!temp_ms3.IsEmpty())
						{
							temp_temp_ms3.push(temp_ms3.pop());
						}
						ms3 = temp_temp_ms3;
						temp_ms3 = temp_temp_ms3;
						//inroomfile();//更新房间文件内容
						this->save();
						break;
					}
					else
					{
						temp_temp_ms3.push(temp_ms3.pop());//若不合适则看下一个房间，并将弹出的房间放到临时栈内
					}
				}
				if (temp_ms3.IsEmpty() && !ms3.IsEmpty())//若每个房间都不符合性别要求
				{
					if (ms3.IsEmpty() == 1)//若栈为空，则无空房
					{
						cout << "此等级床铺已满，请选择操作：" << endl;
						cout << "1.继续住房服务  2.返回主菜单" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//输入操作
						if (x == 1)//还要继续住房
						{
							in_serve1(1);//递归进行服务1
						}
						else if (x == 2)//若要返回主菜单
						{
							return;//执行主菜单服务
						}
					}
				}
			}
		}
	}
}
void hotel::in_serve2()//服务二，退房
{
	bool flag = false;//定义标志检查是否检索到
	this->init_Tra();
	double money;//记录那个人每张床的费用
	string name;//名字
	string room_num;//房号
	string room_rank;//记录那个人的房间等级
	MyStack<int> temp_bed_num;//记录那个人的床号栈
	int Tra_bed_count = 0;//记录那个人占了几个床
	cout << "请输入姓名：";
	cin >> name;
	cout << "请输入房号：";
	cin >> room_num;
	room_rank = room_num[0];

	switch (atoi(room_rank.c_str()))
	{
	case 1:money = atoi(room_level1->money_one.c_str());
	case 2:money = atoi(room_level2->money_one.c_str());
	case 3:money = atoi(room_level3->money_one.c_str());
	}

	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < m_Tranum; i++)//循环找退房的那个人
	{
		if (this->m_TraArray[i]->m_name == name && this->m_TraArray[i]->room_num == room_num)//找到了
		{
			this->m_TraArray[i]->out_date = getTime();//记录当前离店时间
			Tra_bed_count = this->m_TraArray[i]->Empty_bed_num.TopIndex;//记录那个人占了几个床
			temp_bed_num = this->m_TraArray[i]->Empty_bed_num;//记录那个人的床号栈
			cout << "您需要支付的费用为：";
			cout << DataMinus(this->m_TraArray[i]->in_date, this->m_TraArray[i]->out_date) * money * Tra_bed_count << endl;
			cout << "一共的天数为：" << DataMinus(this->m_TraArray[i]->in_date, this->m_TraArray[i]->out_date) << endl;
			while (i < m_Tranum)
			{
				if (i == m_Tranum - 1) this->m_TraArray[i] = NULL;
				else this->m_TraArray[i] = this->m_TraArray[i + 1];
				i++;
			}
			m_Tranum--;
			break;
		}
	}
	this->save();

	room* head1 = room_level1;
	while (head1 != NULL)
	{
		if (head1->room_num == room_num)//检索到了
		{
			flag = true;
			head1->bed_using_num[0] -= Tra_bed_count;//占用床位数减旅客占的床
			head1->bed_count[0] += Tra_bed_count;//空床位数加旅客占的床
			if (head1->bed_using_num == "0")//要是房间空了就把房间性别变为0
			{
				head1->sex = "0";
			}
			//int temp_temp_bed_num = temp_bed_num[0] - '0';
			cout << "回收的床号为：";
			//cout << temp_temp_bed_num<<endl;
			temp_bed_num.show();
			while (!temp_bed_num.IsEmpty())
			{

				head1->Empty_bed_num.push(temp_bed_num.pop());//把床号放入空床栈中
			}
			break;
		}
		head1 = head1->next;
	}

	room* head2 = room_level2;
	while (head2 != NULL)
	{
		if (head2->room_num == room_num)//检索到了
		{
			flag = true;
			head2->bed_using_num[0] -= Tra_bed_count;//占用床位数减旅客占的床
			head2->bed_count[0] += Tra_bed_count;//空床位数加旅客占的床
			if (head2->bed_using_num == "0")//要是房间空了就把房间性别变为0
			{
				head2->sex = "0";
			}
			//int temp_temp_bed_num = temp_bed_num[0] - '0';
			cout << "回收的床号为：";
			//cout << temp_temp_bed_num<<endl;
			temp_bed_num.show();
			while (!temp_bed_num.IsEmpty())
			{

				head2->Empty_bed_num.push(temp_bed_num.pop());//把床号放入空床栈中
			}
			break;
		}
		head2 = head2->next;
	}

	room* head3 = room_level3;
	while (head3 != NULL)
	{
		if (head3->room_num == room_num)//检索到了
		{
			flag = true;
			head3->bed_using_num[0] -= Tra_bed_count;//占用床位数减旅客占的床
			head3->bed_count[0] += Tra_bed_count;//空床位数加旅客占的床
			if (head3->bed_using_num == "0")//要是房间空了就把房间性别变为0
			{
				head3->sex = "0";
			}
			//int temp_temp_bed_num = temp_bed_num[0] - '0';
			cout << "回收的床号为：";
			//cout << temp_temp_bed_num<<endl;
			temp_bed_num.show();
			while (!temp_bed_num.IsEmpty())
			{

				head3->Empty_bed_num.push(temp_bed_num.pop());//把床号放入空床栈中
			}
			break;
		}
		head3 = head3->next;
	}
	if (!flag)
	{
		cout << "未查找到此人，其重新选择"<<endl;
		cout << "1.重新输入  2.返回主菜单"<<endl;
		cout << "----------------------------------------------" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) in_serve2();//递归操作
		else if (choice == 2) return;//返回主菜单
	}
	else inroomfile();//要是找到了就更新文件内容
}
void hotel::in_serve5()
{
	int n;
	cout << "----------------------------------------------" << endl;
	cout << "请输入要进行的操作：" << endl;
	cout << "1.查找旅客  2.显示所有旅客" << endl;
	cout << "----------------------------------------------" << endl;
	cin >> n;
	if (n == 1)
	{
		bool flag = false;//定义标志检查是否检索到
		this->init_Tra();
		double money;//记录那个人每张床的费用
		string name;//名字
		string room_num;//房号
		string room_rank;//记录那个人的房间等级
		MyStack<int> temp_bed_num;//记录那个人的床号栈
		int Tra_bed_count;//记录那个人占了几个床
		cout << "请输入姓名：";
		cin >> name;
		cout << "请输入房号：";
		cin >> room_num;
		room_rank = room_num[0];

		switch (atoi(room_rank.c_str()))
		{
		case 1:money = atoi(room_level1->money_one.c_str());
		case 2:money = atoi(room_level2->money_one.c_str());
		case 3:money = atoi(room_level3->money_one.c_str());
		}

		cout << "----------------------------------------------" << endl;
		for (int i = 0; i < m_Tranum; i++)//循环找退房的那个人
		{
			if (this->m_TraArray[i]->m_name == name && this->m_TraArray[i]->room_num == room_num)//找到了
			{
				flag = true;
				this->m_TraArray[i]->showInfo_5();
				this->m_TraArray[i]->out_date = getTime();
				cout << "旅客目前需要支付的费用为：" ;

				Tra_bed_count = this->m_TraArray[i]->Empty_bed_num.TopIndex;//记录那个人占了几个床
				cout << (DataMinus(this->m_TraArray[i]->in_date, this->m_TraArray[i]->out_date)) * money * Tra_bed_count << endl;
				cout << "----------------------------------------------" << endl;
				temp_bed_num = this->m_TraArray[i]->Empty_bed_num;//记录那个人的床号栈
				break;
			}
		}
		if (!flag)
		{
			cout << "未查找到此人，其重新选择" << endl;
			cout << "1.重新输入  2.返回主菜单" << endl;
			cout << "----------------------------------------------" << endl;
			int choice;
			cin >> choice;
			if (choice == 1) in_serve5();//递归操作
			else if (choice == 2) return;//返回主菜单
		}
	}
	if (n == 2)
	{
		this->Show_Tra();//显示所有旅客
	}
}