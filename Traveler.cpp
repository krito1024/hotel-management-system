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
	cout << "旅客姓名：" << this->m_name << "\n"
		<< "旅客性别：" << this->m_sex << "\n"
		<< "旅客年龄：" << this->m_age << "\n"
		<< "旅客工作单位：" << this->m_workplace << "\n"
		<< "旅客职务：" << this->m_office << "\n"
		<< "旅客住址：" << this->m_from << "\n"
		<< "旅客身份证号：" << this->m_id << "\n"
		<< "旅客房号：" << this->room_num << "\n"
		<< "旅客床号：";
	this->Empty_bed_num.show();
	cout << "旅客住店时间：" << this->in_date << "\n";
	cout << "----------------------------------------------" << endl;
}
void traveler::showInfo_5()
{
	cout << "----------------------------------------------" << endl;
	cout << "旅客姓名：" << this->m_name << "\n"
		<< "旅客性别：" << this->m_sex << "\n"
		<< "旅客年龄：" << this->m_age << "\n"
		<< "旅客工作单位：" << this->m_workplace << "\n"
		<< "旅客职务：" << this->m_office << "\n"
		<< "旅客住址：" << this->m_from << "\n"
		<< "旅客身份证号：" << this->m_id << "\n"
		<< "旅客房号：" << this->room_num << "\n"
		<< "旅客床号：";
	this->Empty_bed_num.show();
	cout << "旅客住店时间：" << this->in_date << "\n";
}