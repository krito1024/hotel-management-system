#pragma once

#include<iostream>
#include<string>
#include"Hotel.h"
#include"Stack.h"
using namespace std;
class traveler {
public:
	string m_name;//旅客姓名
	string m_sex;//旅客性别
	string m_workplace;//旅客工作单位
	string m_office;//旅客职务
	string m_from;//旅客来自何处
	string m_id;//旅客身份证号
	string room_num;//旅客房号
	int bed_code;//旅客床号
	MyStack<int> Empty_bed_num;//旅客床号栈
	int m_age;//旅客年龄
	string in_date;//住店时间
	string out_date;//离店时间
	traveler(string name, string sex, string workplace, string office, string from, string id, int age,string room_num,int bed_code,string in_date);
	void showInfo();
	void showInfo_5();
};
