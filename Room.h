#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"

using namespace std;

typedef struct Link
{
	MyStack<int> Empty_bed_num;//空床栈
	string sex;//房间性别
	string room_rank;//房间等级
	string room_num;//房号
	string bed_sum;//床位总数
	string bed_count;//空床位数
	string bed_using_num;//占用床位数
	string Bed_message = "0000";//空床位信息数组
	string money_one;//单床每天费用
	string money_all;//包房每天费用
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
//从头遍历输入结点
void finput_new(room* p, ifstream& fp, int m)
{
	room* head = p;
	while (m)//一个节点一个结点循环
	{
		string temp1;
		for (int i = 0; i < 9; i++)//分别输入数据
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
		//输入床位信息数组
		int n = atoi(temp1.c_str());
		for (int k = 0; k < 4; k++)
		{
			if (n == 0) break;
			head->Bed_message[n % 10] = '1';
			n /= 10;
		}
		//空床位信息入栈

		int Temp_bed_sum;
		Temp_bed_sum = head->bed_sum[0] - '0';//将string类型的床位总数转化为整形
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
//创建链表
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
		cout << "文件打开失败。" << endl;
		return;
	}
	room* head = p;
	while (head != NULL)//一个节点一个结点循环
	{
		string temp1;
		for (int i = 0; i < 9; i++)//分别输入数据
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
		//输入床位信息数组
		int n = atoi(temp1.c_str());
		for (int k = 0; k < 4; k++)
		{
			if (n == 0) break;
			head->Bed_message[n % 10] = '1';
			n /= 10;
		}
		//空床位信息入栈

		int Temp_bed_sum;
		Temp_bed_sum = head->bed_sum[0] - '0';//将string类型的床位总数转化为整形
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
