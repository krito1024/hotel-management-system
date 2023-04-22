#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "MyStack.h"

using namespace std;

typedef struct Link
{
	MyStack<int> Empty_bed_num;//�մ�ջ
	string sex;//�����Ա�
	string room_rank;//����ȼ�
	string room_num;//����
	string bed_sum;//��λ����
	string bed_count;//�մ�λ��
	string bed_using_num;//ռ�ô�λ��
	string Bed_message="0000";//��ռ�ô�λ��Ϣ����
	struct Link* next = NULL;
}room;

//��ͷ����������
void finput_new(room* p)
{
	ifstream fp("room.txt", ios::in);
	if (!fp.is_open())
	{
		cout << "�ļ���ʧ�ܡ�" << endl;
		return;
	}
	room* head = p;
	while (head != NULL)//һ���ڵ�һ�����ѭ��
	{
		string temp1;
		for (int i = 0; i < 7; i++)//�ֱ���������
		{
			switch (i)
			{
			case 0:fp >> head->room_num; break;
			case 1:fp >> head->room_rank; break;
			case 2:fp >> head->bed_sum; break;
			case 3:fp >> head->bed_using_num; break;
			case 4:fp >> head->sex; break;
			case 5:fp >> head->bed_count; break;
			case 6:fp >> temp1; break;
			}
		}
		//���봲λ��Ϣ����
		int n = atoi(temp1.c_str());
	    for (int k = 0; k < 4; k++)
		{
			if (n == 0) break;
			head->Bed_message[n%10] = '1';
			n /= 10;
		}
		//�մ�λ��Ϣ��ջ
		
		int Temp_bed_sum;
		Temp_bed_sum = head->bed_sum[0] - '0';//��string���͵Ĵ�λ����ת��Ϊ����
		for (int j = 1; j <= Temp_bed_sum; j++)
		{
			if (head->Bed_message[j] == '0')
			{
				head->Empty_bed_num.push(j);
			}	
		}
		head = head->next;
	}
	fp.close();
}
//��������
room* creatlink()
{
	room* q = NULL, * p, * head;
	head = NULL;
	cout << "������õȼ���������";
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		p = new room;
		p->next = NULL;
		if (head == NULL) head = p;
		else q->next = p;
		q = p;
	}
	return head;
}

////���ļ�����ڵ����ݺ���
//void finput(room* p,int count)
//{
//	ifstream fp("room.txt", ios::in);
//	if (!fp.is_open())
//	{
//		cout << "�ļ���ʧ�ܡ�" << endl;
//		return;
//	}
//	int n = 0;
//	int result = sizeof(char) * count * 12;//��ָ�붨λ��ÿһ�еĿ�ͷ
//	fp.seekg(result);//�ļ�ָ�붨λ
//	string Bed_message;//��λ��Ϣ�ַ���
//	while (n<5)
//	{
//		switch (n)
//		{
//		case 0:fp >> p->sex; break;
//		case 1:fp >> p->room_num; break;
//		case 2:fp >> p->bed_sum; break;
//		case 3:fp >> p->bed_count; break;
//		case 4:fp >> Bed_message; break;
//		}
//		n++;
//	}
//	cout << p->sex<<" ";
//	cout << p->room_num<<" ";
//	cout << p->bed_sum<<" ";
//	cout << Bed_message << " ";
//	cout << p->bed_count<<" "<<endl;
//	fp.close();
//}
/*void showlink(room* head)
{
	cout << "����Ԫ��Ϊ��";
	room* h; h = head;
	while (h != NULL)
	{
		cout << h->a << " ";
		h = h->next;
	}
}
void chacreat(room* head, int n, int m)
{
	room* h; h = head;
	for (int i = 0; i < n - 1; i++)
	{
		h = h->next;
	}
	room* l = h->next;
	room* temp; temp = new room;
	temp->a = m;
	h->next = temp;
	temp->next = l;
}
void chchch(room* head, int n)
{
	room* h = head;
	while (h != NULL)
	{
		if (h->next->a > n) break;
		h = h->next;
	}
	room* p, * q;
	q = h->next;
	p = new room;
	p->a = n;
	h->next = p;
	p->next = q;
}*/

