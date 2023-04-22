#ifndef LOCATIONTIME_H
#define LOCATIONTIME_H

#include<iostream>
#include<time.h>
#include<string>
#include<stdlib.h>
using namespace std;

const int MOUTHDAYS[12]{ 31,28,31,30,31,30,31,31,30,31,30,31 };

string getTime()
{
	time_t timep;
	time(&timep);
	char tmp[64];
	tm Nowtime;
	localtime_s(&Nowtime, &timep);
	strftime(tmp, sizeof(tmp), "%Y/%m/%d-%H:%M:%S", &Nowtime);
	return tmp;
}

//返回某年某月天数
int inline MouthDays(int mouth, int year)
{
	if (year % 4 == 0)
		if (mouth == 2)
			return 29;
	return  MOUTHDAYS[mouth - 1];
}
void inline Transformation(string str, int& year, int& mouth, int& day, int& hour)
{
	int flag1 = str.find("/");
	year = atoi(str.substr(0, flag1).c_str());
	str = str.substr(flag1 + 1);
	int flag2 = str.find("/");
	mouth = atoi(str.substr(0, flag2).c_str());
	str = str.substr(flag2 + 1);
	int flag3 = str.find("-");
	day = atoi(str.substr(0, flag3).c_str());
	str = str.substr(flag3 + 1);
	int flag4 = str.find(":");
	hour = atoi(str.substr(0, flag4).c_str());
}
double DataMinus(string str1, string str2)//计算时间差
{
	int year1, year2;
	int mouth1, mouth2;
	int day1, day2;
	int hour1, hour2;
	Transformation(str1, year1, mouth1, day1, hour1);
	Transformation(str2, year2, mouth2, day2, hour2);
	int num = 0;//总天数统计
	int num1 = 0;
	int num2 = 0;
	double num3 = 0;
	for (int i = year1; i < year2; i++)
	{
		if (i % 4 == 0)
		{
			num += 366;
		}
		else
		{
			num += 365;
		}
	}
	for (int j = mouth1; j <= 12; j++)
	{
		num1 += MouthDays(j, year1);
	}
	num1 = num1 - day1;
	for (int j = mouth2; j <= 12; j++)
	{
		num2 += MouthDays(j, year1);
	}
	num2 = num2 - day2;
	num += (num1 - num2);
	if (hour1 <= hour2) num3 = (double)(hour2)-(double)(hour1);
	else {
		num--;
		num3 = (double)(hour2)+24 - (double)(hour1);
	}
	if (num3 >= 12) num3 = 1;
	else {
		if (num3 == 0) num3 = 0;
		else {
			if (num3 > 0 && num3 < 12) num3 = 0.5;
		}
	}
	num3 = num3 + num;
	return num3;
}

/*int main()
{
	string time = getTime();
	cout << time << endl;
	system("pause");
	return 0;
}*/

/*int main()
{
	string str1("2022/8/24 12:00:00");
	string str2("2022/8/26 14:00:00");
	cout << DataMinus(str1, str2) << endl;
	return 0;
}*/

#endif
