#pragma once

#include<iostream>
#include<string>
#include"Hotel.h"
#include"Stack.h"
using namespace std;
class traveler {
public:
	string m_name;//�ÿ�����
	string m_sex;//�ÿ��Ա�
	string m_workplace;//�ÿ͹�����λ
	string m_office;//�ÿ�ְ��
	string m_from;//�ÿ����Ժδ�
	string m_id;//�ÿ����֤��
	string room_num;//�ÿͷ���
	int bed_code;//�ÿʹ���
	MyStack<int> Empty_bed_num;//�ÿʹ���ջ
	int m_age;//�ÿ�����
	string in_date;//ס��ʱ��
	string out_date;//���ʱ��
	traveler(string name, string sex, string workplace, string office, string from, string id, int age,string room_num,int bed_code,string in_date);
	void showInfo();
	void showInfo_5();
};
