#pragma once
#include <iostream>
#include <string>
#include "Traveler.h"
#include<fstream>
#include "Stack.h"
#include "Room.h"
using namespace std;
class traveler;

class hotel {
public:
	int m_Tranum;//�ÿ�����
	int addNum = 0;//����Ҫס������
	int temp_addNum = addNum;
	traveler** m_TraArray;//�ÿ���Ϣ����

	room* room_level1;//һ������
	room* room_level2;//��������
	room* room_level3;//��������
	MyStack<room*> ms1;//һ���շ�ջ
	MyStack<room*> ms2;//�����շ�ջ
	MyStack<room*> ms3;//�����շ�ջ

	hotel();
	void Show_Menu();          //չʾ�˵�
	void ExitSystem();        //�˳�
	void Add_Tra();     //����ÿ�
	void save();         //�����ļ�
	bool m_FileIsEmpty;  //�ж��ļ��Ƿ�Ϊ��
	int get_Tranum();    //ͳ������
	void init_Tra();     //��ʼ��
	void Show_Tra();     //��ʾְ��
	void in_serve1(int i);//����һ���������񣬽��ÿ���Ϣ���뵽����
	void in_serve2();//��������˷�
	void in_serve5();//�����壬����
	void inroomfile();
	~hotel() {};
};