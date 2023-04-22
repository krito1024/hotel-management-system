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
	int m_Tranum;//旅客人数
	int addNum = 0;//输入要住的人数
	int temp_addNum = addNum;
	traveler** m_TraArray;//旅客信息数组

	room* room_level1;//一级房间
	room* room_level2;//二级房间
	room* room_level3;//三级房间
	MyStack<room*> ms1;//一级空房栈
	MyStack<room*> ms2;//二级空房栈
	MyStack<room*> ms3;//三级空房栈

	hotel();
	void Show_Menu();          //展示菜单
	void ExitSystem();        //退出
	void Add_Tra();     //添加旅客
	void save();         //保存文件
	bool m_FileIsEmpty;  //判断文件是否为空
	int get_Tranum();    //统计人数
	void init_Tra();     //初始化
	void Show_Tra();     //显示职工
	void in_serve1(int i);//服务一，单床服务，将旅客信息输入到房间
	void in_serve2();//服务二，退房
	void in_serve5();//服务五，其他
	void inroomfile();
	~hotel() {};
};