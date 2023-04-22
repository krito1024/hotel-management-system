#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "MyStack.h"

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
	string Bed_message="0000";//被占用床位信息数组
	struct Link* next = NULL;
}room;

//从头遍历输入结点
void finput_new(room* p)
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
		for (int i = 0; i < 7; i++)//分别输入数据
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
		//输入床位信息数组
		int n = atoi(temp1.c_str());
	    for (int k = 0; k < 4; k++)
		{
			if (n == 0) break;
			head->Bed_message[n%10] = '1';
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
//创建链表
room* creatlink()
{
	room* q = NULL, * p, * head;
	head = NULL;
	cout << "请输入该等级房间数：";
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

////打开文件输入节点数据函数
//void finput(room* p,int count)
//{
//	ifstream fp("room.txt", ios::in);
//	if (!fp.is_open())
//	{
//		cout << "文件打开失败。" << endl;
//		return;
//	}
//	int n = 0;
//	int result = sizeof(char) * count * 12;//将指针定位到每一行的开头
//	fp.seekg(result);//文件指针定位
//	string Bed_message;//床位信息字符串
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
	cout << "链表元素为：";
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

