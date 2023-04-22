#include<iostream>
#include"Hotel.h"
#include<fstream>
#include<string>
#include"Traveler.h"
#include"Time.h"

using namespace std;

bool flag = true;//���岼����־ȷ���Ƿ������������Ϣ

void read1()
{
	ifstream ifs;
	ifs.open("room.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ�ܡ�" << endl;
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
	room* head;//���������ȡroom�ļ������Ϣ
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
		cout << "                    ��ǰ��ס����Ϊ0" << endl;
		cout << endl;
		this->m_Tranum = 0;
		this->m_TraArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "                   ��ǰ��ס����Ϊ0" << endl;
		cout << endl;
		this->m_Tranum = 0;
		this->m_TraArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		//return;
	}
	else
	{
		//�ļ����ڣ�����¼����
		int num = this->get_Tranum();
		cout << "                        ��ǰ��ס����Ϊ��" << num << endl;
		cout << endl;
		this->m_Tranum = num;//��ǰ�ļ����ÿ�����
		this->m_TraArray = new traveler * [this->m_Tranum];  //����һ���ÿ�������ô��Ŀռ�
		this->init_Tra();  //�����ݴ����������
	}
	
	//���������ȼ��շ�ջ����
	room_level1 = creatlink(2);
	room_level2 = creatlink(3);
	room_level3 = creatlink(3);

	ifstream fp("room.txt", ios::in);
	if (!fp.is_open())
	{
		cout << "�ļ���ʧ�ܡ�" << endl;
		return;
	}
	//�����ļ����ݳ�ʼ�����ȼ���������
	finput_new(room_level1, fp, 2);
	finput_new(room_level2, fp, 3);
	finput_new(room_level3, fp, 3);
	fp.close();

	/*testshow(room_level1);
	testshow(room_level2);
	testshow(room_level3);*/

	//��շ�ջ����
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
void hotel::Add_Tra()//����ÿ�
{
	cout << "��������ס��������" << endl;
	
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_Tranum + addNum;//�ÿ���������Ҫ��ӵ�����
		traveler** newSpace = new traveler * [newSize];//newsize��ô����¿ռ�
		if (this->m_TraArray != NULL)
		{
			for (int i = 0; i < this->m_Tranum; i++)
			{
				newSpace[i] = this->m_TraArray[i];//���ÿ��ļ�������ݸ��¿ռ�
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			string name, sex, workplace, office, from, id,room_num,in_date,out_date;
			int age, bed_code = -1;
			cout << "���������" << i + 1 << "������" << endl;
			cin >> name;
			cout << "�����������Ա�" << endl;
			cin >> sex;
			cout << "��������������" << endl;
			cin >> age;
			cout << "���������乤����λ" << endl;
			cin >> workplace;
			cout << "����������ְ��" << endl;
			cin >> office;
			cout << "�������������Ժδ�" << endl;
			cin >> from;
			cout << "�������������֤��" << endl;
			cin >> id;
			in_date = getTime();//��ȡ���Ե�ʱ��
			in_date = getTime();//��ȡ���Ե�ʱ��
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
		cout << "��������" << endl;
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
		cout << "                  ��ǰ��ס����Ϊ0" << endl << endl;
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
	cout << "��ӭ�����ùݹ���ϵͳ�������������ķ���" << endl;
	cout << "�����Ǹ�������Ϣ��" << endl;
	cout << "----------------------------------------------" << endl;
	cout << "����     |����     |��λ��    |ռ�ô�λ��    |" << endl;
	cout << "----------------------------------------------" << endl;
	read();
	cout << "----------------------------------------------" << endl;
	cout << "���������·���" << endl;
	cout << "1.ס�����  2.�˷�  3.�˳�  4.����  5.����" << endl;
	cout << "----------------------------------------------" << endl;
}
void hotel::ExitSystem() {
	cout << "��ӭ�´�ʹ�á�" << endl;
	system("pause");
	exit(0);
}
void hotel::inroomfile()//���·�������
{
	ofstream of;
	of.open("room.txt", ios::trunc);
	if (!of.is_open())
	{
		cout << "�ļ���ʧ�ܣ�";
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
	of << "���� ���� ��λ���� ռ�ô�λ�� �Ա� �մ�λ�� �մ�λ��    ����ÿ�����     ����ÿ�����";
}
void hotel::in_serve1(int i)
{
	cout << "----------------------------------------------" << endl;
	cout << "��" << this->m_TraArray[this->m_Tranum - i]->m_name << "����Ҫ���еĲ�����" << endl;
	cout << "1.��������  2.��������  3.Ԥ������" << endl;
	cout << "----------------------------------------------" << endl;
	int n; cin >> n;//�������
	if (n == 1)//��Ҫ���е����������
	{
		cout << "��" << this->m_TraArray[this->m_Tranum - i]->m_name << "����Ҫס�ķ���ȼ���" << endl;
		cout << "----------------------------------------------" << endl;
		int m; cin >> m;//�������
		if (m == 1)//��ѡ�����һ������
		{
			if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(i);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					this->m_Tranum--;
					return;//ִ�����˵�����
				}
			}
			else if (ms1.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms1 = ms1;
				MyStack<room*> temp_temp_ms1;
				while (!temp_ms1.IsEmpty())
				{
					room* head = temp_ms1.top();
					if (this->m_TraArray[this->m_Tranum - i]->m_sex == head->sex || head->sex == "0")//���ÿ��Ա��뷿���Ա���ͬ,����һ����Ҳû�в��ҷ�������Ĵ�λ
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.push(head->Empty_bed_num.pop());//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						cout << "��ס�ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;
						head->bed_count[0] -= 1;//ס������մ�λ��һ
						head->bed_using_num[0] += 1;//ռ�ô�λ����һ
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms1.pop();
						}
						while (!temp_ms1.IsEmpty())
						{
							temp_temp_ms1.push(temp_ms1.pop());
						}
						ms1 = temp_temp_ms1;
						temp_ms1 = temp_temp_ms1;
						inroomfile();//���·����ļ�����
						this->save();
						break;
					}
					else
					{
						temp_temp_ms1.push(temp_ms1.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms1.IsEmpty() && !ms1.IsEmpty())//��ÿ�����䶼�������Ա�Ҫ��
				{
					if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ�������������ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(i);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}

		if (m == 2)//��ѡ����Ƕ�������
		{
			if (ms2.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(i);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					return;//ִ�����˵�����
				}
			}
			else if (ms2.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms2 = ms2;
				MyStack<room*> temp_temp_ms2;
				while (!temp_ms2.IsEmpty())
				{
					room* head = temp_ms2.top();
					if (this->m_TraArray[this->m_Tranum - i]->m_sex == head->sex || head->sex == "0")//���ÿ��Ա��뷿���Ա���ͬ,����һ����Ҳû��
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.push(head->Empty_bed_num.pop());//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						cout << "��ס�ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;
						head->bed_count[0] -= 1;//ס������մ�λ��һ
						head->bed_using_num[0] += 1;//ռ�ô�λ����һ
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms2.pop();
						}
						while (!temp_ms2.IsEmpty())
						{
							temp_temp_ms2.push(temp_ms2.pop());
						}
						ms2 = temp_temp_ms2;
						temp_ms2 = temp_temp_ms2;
						inroomfile();//���·����ļ�����
						save();
						break;
					}
					else
					{
						temp_temp_ms2.push(temp_ms2.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms2.IsEmpty() && !ms2.IsEmpty())//��ÿ�����䶼�������Ա�Ҫ��
				{
					if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ�������������ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(i);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}

		if (m == 3)//��ѡ�������������
		{
			if (ms3.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(i);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					return;//ִ�����˵�����
				}
			}
			else if (ms3.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms3 = ms3;
				MyStack<room*> temp_temp_ms3;
				while (!temp_ms3.IsEmpty())
				{
					room* head = temp_ms3.top();
					if (this->m_TraArray[this->m_Tranum - i]->m_sex == head->sex || head->sex == "0")//���ÿ��Ա��뷿���Ա���ͬ,����һ����Ҳû��
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.push(head->Empty_bed_num.pop());//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						cout << "��ס�ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;
						head->bed_count[0] -= 1;//ס������մ�λ��һ
						head->bed_using_num[0] += 1;//ռ�ô�λ����һ
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms3.pop();
						}
						while (!temp_ms3.IsEmpty())
						{
							temp_temp_ms3.push(temp_ms3.pop());
						}
						ms3 = temp_temp_ms3;
						temp_ms3 = temp_temp_ms3;
						inroomfile();//���·����ļ�����
						save();
						break;
					}
					else
					{
						temp_temp_ms3.push(temp_ms3.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms3.IsEmpty() && !ms3.IsEmpty())//��ÿ�����䶼�������Ա�Ҫ��
				{
					if (ms3.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ�������������ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(i);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}
	}
	else if (n == 2)//���а�������
	{
		cout << "��" << this->m_TraArray[this->m_Tranum - i]->m_name << "����Ҫ�����ķ���ȼ���" << endl;
		cout << "----------------------------------------------" << endl;
		int m; cin >> m;//�������
		if (m == 1)//��ѡ�����һ������
		{
			if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(i);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					this->m_Tranum--;
					return;//ִ�����˵�����
				}
			}
			else if (ms1.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms1 = ms1;
				MyStack<room*> temp_temp_ms1;
				while (!temp_ms1.IsEmpty())
				{
					room* head = temp_ms1.top();
					if (temp_ms1.top()->bed_using_num == "0")//���˷���Ϊ�գ�����԰���
					{
						
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num = head->Empty_bed_num;//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						while (!head->Empty_bed_num.IsEmpty())//���˷���մ�ջ���
						{
							head->Empty_bed_num.pop();
						}
						cout << "��ס�ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;

						head->bed_count = "0";//ס������մ�λ��0
						head->bed_using_num = head->bed_sum;//ռ�ô�λ����Ϊ��λ����
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms1.pop();
						}
						while (!temp_ms1.IsEmpty())
						{
							temp_temp_ms1.push(temp_ms1.pop());
						}
						ms1 = temp_temp_ms1;//������ԭ���Ŀշ�ջ
						temp_ms1 = temp_temp_ms1;
						inroomfile();//���·����ļ�����
						this->save();//�����ÿ��ļ�����
						break;
					}
					else
					{
						temp_temp_ms1.push(temp_ms1.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms1.IsEmpty() && !ms1.IsEmpty())//��ÿ�����䶼�����ϰ���Ҫ��
				{
					if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ������޿շ�����ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(i);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}

		else if (m == 2)//��ѡ����Ƕ�������
		{
			if (ms2.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(i);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					return;//ִ�����˵�����
				}
			}
			else if (ms2.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms2 = ms2;
				MyStack<room*> temp_temp_ms2;
				while (!temp_ms2.IsEmpty())
				{
					room* head = temp_ms2.top();
					if (temp_ms2.top()->bed_using_num=="0")//���˷���Ϊ�գ�����԰���
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num = head->Empty_bed_num;//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						while (!head->Empty_bed_num.IsEmpty())//���˷���մ�ջ���
						{
							head->Empty_bed_num.pop();
						}
						cout << "��ס�ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;

						head->bed_count = "0";//ס������մ�λ��0
						head->bed_using_num = head->bed_sum;//ռ�ô�λ����Ϊ��λ����
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms2.pop();
						}
						while (!temp_ms2.IsEmpty())
						{
							temp_temp_ms2.push(temp_ms2.pop());
						}
						ms2 = temp_temp_ms2;//������ԭ���Ŀշ�ջ
						temp_ms2 = temp_temp_ms2;
						inroomfile();//���·����ļ�����
						this->save();//�����ÿ��ļ�����
						break;
					}
					else
					{
						temp_temp_ms2.push(temp_ms2.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms2.IsEmpty() && !ms2.IsEmpty())//��ÿ�����䶼�����ϰ���Ҫ��
				{
					if (ms2.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ������޿շ�����ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(i);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}

		if (m == 3)//��ѡ�������������
		{
			if (ms3.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(i);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					return;//ִ�����˵�����
				}
			}
			else if (ms3.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms3 = ms3;
				MyStack<room*> temp_temp_ms3;
				while (!temp_ms3.IsEmpty())
				{
					room* head = temp_ms3.top();
					if (temp_ms3.top()->bed_using_num == "0")//���˷���Ϊ�գ�����԰���
					{
						this->m_TraArray[this->m_Tranum - i]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num = head->Empty_bed_num;//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						while (!head->Empty_bed_num.IsEmpty())//���˷���մ�ջ���
						{
							head->Empty_bed_num.pop();
						}
						cout << "��ס�ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - i]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - i]->Empty_bed_num.show();
						cout << endl;

						head->bed_count = "0";//ס������մ�λ��0
						head->bed_using_num = head->bed_sum;//ռ�ô�λ����Ϊ��λ����
						head->sex = this->m_TraArray[this->m_Tranum - i]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms3.pop();
						}
						while (!temp_ms3.IsEmpty())
						{
							temp_temp_ms3.push(temp_ms3.pop());
						}
						ms3 = temp_temp_ms3;//������ԭ���Ŀշ�ջ
						temp_ms3 = temp_temp_ms3;
						inroomfile();//���·����ļ�����
						this->save();//�����ÿ��ļ�����
						break;
					}
					else
					{
						temp_temp_ms3.push(temp_ms3.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms3.IsEmpty() && !ms3.IsEmpty())//��ÿ�����䶼�����ϰ���Ҫ��
				{
					if (ms3.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ������޿շ�����ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(i);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}
	}	
	else if (n == 3)//Ԥ������
	{
		string in_date;//Ҫ��������ʱ��
		cout << "��������ҪԤ����ʱ�䣨����ҪΪһ���Ժ�:" << endl;
		cin >> in_date;
		this->m_TraArray[this->m_Tranum - 1]->in_date = in_date;

		cout << "��" << this->m_TraArray[this->m_Tranum - 1]->m_name << "����Ҫס�ķ���ȼ���" << endl;
		cout << "----------------------------------------------" << endl;
		int m; cin >> m;//�������
		if (m == 1)//��ѡ�����һ������
		{
			if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(1);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					this->m_Tranum--;
					return;//ִ�����˵�����
				}
			}
			else if (ms1.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms1 = ms1;
				MyStack<room*> temp_temp_ms1;
				while (!temp_ms1.IsEmpty())
				{
					room* head = temp_ms1.top();
					if (this->m_TraArray[this->m_Tranum - 1]->m_sex == head->sex || head->sex == "0")//���ÿ��Ա��뷿���Ա���ͬ,����һ����Ҳû�в��ҷ�������Ĵ�λ
					{
						this->m_TraArray[this->m_Tranum - 1]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.push(head->Empty_bed_num.pop());//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						cout << "Ԥ���ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - 1]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.show();
						cout << endl;
						//head->bed_count[0] -= 1;//ס������մ�λ��һ
						//head->bed_using_num[0] += 1;//ռ�ô�λ����һ
						//head->sex = this->m_TraArray[this->m_Tranum - 1]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms1.pop();
						}
						while (!temp_ms1.IsEmpty())
						{
							temp_temp_ms1.push(temp_ms1.pop());
						}
						ms1 = temp_temp_ms1;
						temp_ms1 = temp_temp_ms1;
						//inroomfile();//���·����ļ�����
						this->save();
						break;
					}
					else
					{
						temp_temp_ms1.push(temp_ms1.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms1.IsEmpty() && !ms1.IsEmpty())//��ÿ�����䶼�������Ա�Ҫ��
				{
					if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ�������������ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(1);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}

		if (m == 2)//��ѡ����Ƕ�������
		{
			if (ms2.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(1);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					return;//ִ�����˵�����
				}
			}
			else if (ms2.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms2 = ms2;
				MyStack<room*> temp_temp_ms2;
				while (!temp_ms2.IsEmpty())
				{
					room* head = temp_ms2.top();
					if (this->m_TraArray[this->m_Tranum - 1]->m_sex == head->sex || head->sex == "0")//���ÿ��Ա��뷿���Ա���ͬ,����һ����Ҳû��
					{
						this->m_TraArray[this->m_Tranum - 1]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.push(head->Empty_bed_num.pop());//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						cout << "Ԥ���ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - 1]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.show();
						cout << endl;
						//head->bed_count[0] -= 1;//ס������մ�λ��һ
						//head->bed_using_num[0] += 1;//ռ�ô�λ����һ
						//head->sex = this->m_TraArray[this->m_Tranum - 1]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms2.pop();
						}
						while (!temp_ms2.IsEmpty())
						{
							temp_temp_ms2.push(temp_ms2.pop());
						}
						ms2 = temp_temp_ms2;
						temp_ms2 = temp_temp_ms2;
						//inroomfile();//���·����ļ�����
						this->save();
						break;
					}
					else
					{
						temp_temp_ms2.push(temp_ms2.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms2.IsEmpty() && !ms2.IsEmpty())//��ÿ�����䶼�������Ա�Ҫ��
				{
					if (ms1.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ�������������ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(1);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}

		if (m == 3)//��ѡ�������������
		{
			if (ms3.IsEmpty() == 1)//��ջΪ�գ����޿շ�
			{
				cout << "�˵ȼ�����������������ѡ��" << endl;
				cout << "1.����ס������  2.�������˵�" << endl;
				cout << "----------------------------------------------" << endl;
				int x; cin >> x;//�������
				if (x == 1)//��Ҫ����ס��
				{
					in_serve1(1);//�ݹ���з���1
				}
				else if (x == 2)//��Ҫ�������˵�
				{
					return;//ִ�����˵�����
				}
			}
			else if (ms3.IsEmpty() == 0)//��ջ��Ϊ�գ�˵���пշ�
			{
				MyStack<room*> temp_ms3 = ms3;
				MyStack<room*> temp_temp_ms3;
				while (!temp_ms3.IsEmpty())
				{
					room* head = temp_ms3.top();
					if (this->m_TraArray[this->m_Tranum - 1]->m_sex == head->sex || head->sex == "0")//���ÿ��Ա��뷿���Ա���ͬ,����һ����Ҳû��
					{
						this->m_TraArray[this->m_Tranum - 1]->room_num = head->room_num;//�ѷ��Ÿ��ÿ�
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.push(head->Empty_bed_num.pop());//�մ�ջ������λ���ÿͷ���ջ���ǵ��ٴ����ļ�д�봲λ��Ϣ��ʱ����ջд
						cout << "Ԥ���ɹ�,���ķ���Ϊ��" << this->m_TraArray[this->m_Tranum - 1]->room_num << endl;
						cout << "���Ĵ���Ϊ ";
						this->m_TraArray[this->m_Tranum - 1]->Empty_bed_num.show();
						cout << endl;
						//head->bed_count[0] -= 1;//ס������մ�λ��һ
						//head->bed_using_num[0] += 1;//ռ�ô�λ����һ
						//head->sex = this->m_TraArray[this->m_Tranum - 1]->m_sex;//�ѷ����Ա���Ϊ�˿��Ա�

						if (head->Empty_bed_num.IsEmpty())//������䴲λ����
						{
							temp_ms3.pop();
						}
						while (!temp_ms3.IsEmpty())
						{
							temp_temp_ms3.push(temp_ms3.pop());
						}
						ms3 = temp_temp_ms3;
						temp_ms3 = temp_temp_ms3;
						//inroomfile();//���·����ļ�����
						this->save();
						break;
					}
					else
					{
						temp_temp_ms3.push(temp_ms3.pop());//������������һ�����䣬���������ķ���ŵ���ʱջ��
					}
				}
				if (temp_ms3.IsEmpty() && !ms3.IsEmpty())//��ÿ�����䶼�������Ա�Ҫ��
				{
					if (ms3.IsEmpty() == 1)//��ջΪ�գ����޿շ�
					{
						cout << "�˵ȼ�������������ѡ�������" << endl;
						cout << "1.����ס������  2.�������˵�" << endl;
						cout << "----------------------------------------------" << endl;
						int x; cin >> x;//�������
						if (x == 1)//��Ҫ����ס��
						{
							in_serve1(1);//�ݹ���з���1
						}
						else if (x == 2)//��Ҫ�������˵�
						{
							return;//ִ�����˵�����
						}
					}
				}
			}
		}
	}
}
void hotel::in_serve2()//��������˷�
{
	bool flag = false;//�����־����Ƿ������
	this->init_Tra();
	double money;//��¼�Ǹ���ÿ�Ŵ��ķ���
	string name;//����
	string room_num;//����
	string room_rank;//��¼�Ǹ��˵ķ���ȼ�
	MyStack<int> temp_bed_num;//��¼�Ǹ��˵Ĵ���ջ
	int Tra_bed_count = 0;//��¼�Ǹ���ռ�˼�����
	cout << "������������";
	cin >> name;
	cout << "�����뷿�ţ�";
	cin >> room_num;
	room_rank = room_num[0];

	switch (atoi(room_rank.c_str()))
	{
	case 1:money = atoi(room_level1->money_one.c_str());
	case 2:money = atoi(room_level2->money_one.c_str());
	case 3:money = atoi(room_level3->money_one.c_str());
	}

	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < m_Tranum; i++)//ѭ�����˷����Ǹ���
	{
		if (this->m_TraArray[i]->m_name == name && this->m_TraArray[i]->room_num == room_num)//�ҵ���
		{
			this->m_TraArray[i]->out_date = getTime();//��¼��ǰ���ʱ��
			Tra_bed_count = this->m_TraArray[i]->Empty_bed_num.TopIndex;//��¼�Ǹ���ռ�˼�����
			temp_bed_num = this->m_TraArray[i]->Empty_bed_num;//��¼�Ǹ��˵Ĵ���ջ
			cout << "����Ҫ֧���ķ���Ϊ��";
			cout << DataMinus(this->m_TraArray[i]->in_date, this->m_TraArray[i]->out_date) * money * Tra_bed_count << endl;
			cout << "һ��������Ϊ��" << DataMinus(this->m_TraArray[i]->in_date, this->m_TraArray[i]->out_date) << endl;
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
		if (head1->room_num == room_num)//��������
		{
			flag = true;
			head1->bed_using_num[0] -= Tra_bed_count;//ռ�ô�λ�����ÿ�ռ�Ĵ�
			head1->bed_count[0] += Tra_bed_count;//�մ�λ�����ÿ�ռ�Ĵ�
			if (head1->bed_using_num == "0")//Ҫ�Ƿ�����˾Ͱѷ����Ա��Ϊ0
			{
				head1->sex = "0";
			}
			//int temp_temp_bed_num = temp_bed_num[0] - '0';
			cout << "���յĴ���Ϊ��";
			//cout << temp_temp_bed_num<<endl;
			temp_bed_num.show();
			while (!temp_bed_num.IsEmpty())
			{

				head1->Empty_bed_num.push(temp_bed_num.pop());//�Ѵ��ŷ���մ�ջ��
			}
			break;
		}
		head1 = head1->next;
	}

	room* head2 = room_level2;
	while (head2 != NULL)
	{
		if (head2->room_num == room_num)//��������
		{
			flag = true;
			head2->bed_using_num[0] -= Tra_bed_count;//ռ�ô�λ�����ÿ�ռ�Ĵ�
			head2->bed_count[0] += Tra_bed_count;//�մ�λ�����ÿ�ռ�Ĵ�
			if (head2->bed_using_num == "0")//Ҫ�Ƿ�����˾Ͱѷ����Ա��Ϊ0
			{
				head2->sex = "0";
			}
			//int temp_temp_bed_num = temp_bed_num[0] - '0';
			cout << "���յĴ���Ϊ��";
			//cout << temp_temp_bed_num<<endl;
			temp_bed_num.show();
			while (!temp_bed_num.IsEmpty())
			{

				head2->Empty_bed_num.push(temp_bed_num.pop());//�Ѵ��ŷ���մ�ջ��
			}
			break;
		}
		head2 = head2->next;
	}

	room* head3 = room_level3;
	while (head3 != NULL)
	{
		if (head3->room_num == room_num)//��������
		{
			flag = true;
			head3->bed_using_num[0] -= Tra_bed_count;//ռ�ô�λ�����ÿ�ռ�Ĵ�
			head3->bed_count[0] += Tra_bed_count;//�մ�λ�����ÿ�ռ�Ĵ�
			if (head3->bed_using_num == "0")//Ҫ�Ƿ�����˾Ͱѷ����Ա��Ϊ0
			{
				head3->sex = "0";
			}
			//int temp_temp_bed_num = temp_bed_num[0] - '0';
			cout << "���յĴ���Ϊ��";
			//cout << temp_temp_bed_num<<endl;
			temp_bed_num.show();
			while (!temp_bed_num.IsEmpty())
			{

				head3->Empty_bed_num.push(temp_bed_num.pop());//�Ѵ��ŷ���մ�ջ��
			}
			break;
		}
		head3 = head3->next;
	}
	if (!flag)
	{
		cout << "δ���ҵ����ˣ�������ѡ��"<<endl;
		cout << "1.��������  2.�������˵�"<<endl;
		cout << "----------------------------------------------" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) in_serve2();//�ݹ����
		else if (choice == 2) return;//�������˵�
	}
	else inroomfile();//Ҫ���ҵ��˾͸����ļ�����
}
void hotel::in_serve5()
{
	int n;
	cout << "----------------------------------------------" << endl;
	cout << "������Ҫ���еĲ�����" << endl;
	cout << "1.�����ÿ�  2.��ʾ�����ÿ�" << endl;
	cout << "----------------------------------------------" << endl;
	cin >> n;
	if (n == 1)
	{
		bool flag = false;//�����־����Ƿ������
		this->init_Tra();
		double money;//��¼�Ǹ���ÿ�Ŵ��ķ���
		string name;//����
		string room_num;//����
		string room_rank;//��¼�Ǹ��˵ķ���ȼ�
		MyStack<int> temp_bed_num;//��¼�Ǹ��˵Ĵ���ջ
		int Tra_bed_count;//��¼�Ǹ���ռ�˼�����
		cout << "������������";
		cin >> name;
		cout << "�����뷿�ţ�";
		cin >> room_num;
		room_rank = room_num[0];

		switch (atoi(room_rank.c_str()))
		{
		case 1:money = atoi(room_level1->money_one.c_str());
		case 2:money = atoi(room_level2->money_one.c_str());
		case 3:money = atoi(room_level3->money_one.c_str());
		}

		cout << "----------------------------------------------" << endl;
		for (int i = 0; i < m_Tranum; i++)//ѭ�����˷����Ǹ���
		{
			if (this->m_TraArray[i]->m_name == name && this->m_TraArray[i]->room_num == room_num)//�ҵ���
			{
				flag = true;
				this->m_TraArray[i]->showInfo_5();
				this->m_TraArray[i]->out_date = getTime();
				cout << "�ÿ�Ŀǰ��Ҫ֧���ķ���Ϊ��" ;

				Tra_bed_count = this->m_TraArray[i]->Empty_bed_num.TopIndex;//��¼�Ǹ���ռ�˼�����
				cout << (DataMinus(this->m_TraArray[i]->in_date, this->m_TraArray[i]->out_date)) * money * Tra_bed_count << endl;
				cout << "----------------------------------------------" << endl;
				temp_bed_num = this->m_TraArray[i]->Empty_bed_num;//��¼�Ǹ��˵Ĵ���ջ
				break;
			}
		}
		if (!flag)
		{
			cout << "δ���ҵ����ˣ�������ѡ��" << endl;
			cout << "1.��������  2.�������˵�" << endl;
			cout << "----------------------------------------------" << endl;
			int choice;
			cin >> choice;
			if (choice == 1) in_serve5();//�ݹ����
			else if (choice == 2) return;//�������˵�
		}
	}
	if (n == 2)
	{
		this->Show_Tra();//��ʾ�����ÿ�
	}
}