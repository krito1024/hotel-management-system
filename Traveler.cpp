#include<iostream>
#include<string>
#include"Traveler.h"
using namespace std;
traveler::traveler(string name, string sex, string workplace, string office, string from, string id, int age,string room_num,int bed_code, string in_date)
{
	this->m_name = name;
	this->m_sex = sex;
	this->m_workplace = workplace;
	this->m_office = office;
	this->m_from = from;
	this->m_id = id;
	this->m_age = age;
	this->room_num = room_num;
	this->bed_code = bed_code;
	if (bed_code >= 0)
	{	
		while (bed_code)
		{
			int temp_bed_code = bed_code % 10;
			this->Empty_bed_num.push(temp_bed_code);	
			bed_code /= 10;
		}
	}
	this->in_date = in_date;
	this->out_date = out_date;
}
void traveler::showInfo()
{
	cout << "----------------------------------------------" << endl;
	cout << "�ÿ�������" << this->m_name << "\n"
		<< "�ÿ��Ա�" << this->m_sex << "\n"
		<< "�ÿ����䣺" << this->m_age << "\n"
		<< "�ÿ͹�����λ��" << this->m_workplace << "\n"
		<< "�ÿ�ְ��" << this->m_office << "\n"
		<< "�ÿ�סַ��" << this->m_from << "\n"
		<< "�ÿ����֤�ţ�" << this->m_id << "\n"
		<< "�ÿͷ��ţ�" << this->room_num << "\n"
		<< "�ÿʹ��ţ�";
	this->Empty_bed_num.show();
	cout << "�ÿ�ס��ʱ�䣺" << this->in_date << "\n";
	cout << "----------------------------------------------" << endl;
}
void traveler::showInfo_5()
{
	cout << "----------------------------------------------" << endl;
	cout << "�ÿ�������" << this->m_name << "\n"
		<< "�ÿ��Ա�" << this->m_sex << "\n"
		<< "�ÿ����䣺" << this->m_age << "\n"
		<< "�ÿ͹�����λ��" << this->m_workplace << "\n"
		<< "�ÿ�ְ��" << this->m_office << "\n"
		<< "�ÿ�סַ��" << this->m_from << "\n"
		<< "�ÿ����֤�ţ�" << this->m_id << "\n"
		<< "�ÿͷ��ţ�" << this->room_num << "\n"
		<< "�ÿʹ��ţ�";
	this->Empty_bed_num.show();
	cout << "�ÿ�ס��ʱ�䣺" << this->in_date << "\n";
}