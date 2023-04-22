#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"

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
	string Bed_message = "0000";//�մ�λ��Ϣ����
	string money_one;//����ÿ�����
	string money_all;//����ÿ�����
	struct Link* next = NULL;
}room;

void show_bednum(MyStack<int> ms, ofstream& of)
{
	if (ms.IsEmpty())
	{
		of << "0";
		of << "                  ";
		return;
	}
	while (!ms.IsEmpty())
	{
		of << ms.pop();
	}
	of << "                  ";
}
//��ͷ����������
void finput_new(room* p, ifstream& fp, int m)
{
	room* head = p;
	while (m)//һ���ڵ�һ�����ѭ��
	{
		string temp1;
		for (int i = 0; i < 9; i++)//�ֱ���������
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
			case 7:fp >> head->money_one; break;
			case 8:fp >> head->money_all; break;
			}
		}
		//���봲λ��Ϣ����
		int n = atoi(temp1.c_str());
		for (int k = 0; k < 4; k++)
		{
			if (n == 0) break;
			head->Bed_message[n % 10] = '1';
			n /= 10;
		}
		//�մ�λ��Ϣ��ջ

		int Temp_bed_sum;
		Temp_bed_sum = head->bed_sum[0] - '0';//��string���͵Ĵ�λ����ת��Ϊ����
		for (int j = 1; j <= Temp_bed_sum; j++)
		{
			if (head->Bed_message[j] == '1')
			{
				head->Empty_bed_num.push(j);
			}
		}
		head = head->next;
		m--;
	}
	/*fp.close();*/
}
//��������
room* creatlink(int n)
{
	room* q = NULL, * p, * head;
	head = NULL;
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

void input_new(room* p)
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
		for (int i = 0; i < 9; i++)//�ֱ���������
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
			case 7:fp >> head->money_one; break;
			case 8:fp >> head->money_all; break;
			}
		}
		//���봲λ��Ϣ����
		int n = atoi(temp1.c_str());
		for (int k = 0; k < 4; k++)
		{
			if (n == 0) break;
			head->Bed_message[n % 10] = '1';
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
