#include<iostream>
#include "speechManager.h"
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
	speechManager  sm;
	////测试是否正确产生选手
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first
	//		<< " 姓名： " << it->second.m_Name
	//		<< " 成绩： " << it->second.m_Score[0] << endl;
	//}

	int choice=0;
	while (true)
	{
		sm.show_Menu();
		cout << "请输入选项" << endl;
		cin >> choice;//接受选项
		switch (choice)
		{
		case 1: //开始比赛
			sm.startSpeech();
			break;
		case 2: //查看记录
			break;
		case 3: //清空记录
			break;
		case 0: //退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}
	system("pause");
	return 0;
}