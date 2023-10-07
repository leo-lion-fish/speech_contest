#include "speechManager.h"
//构造函数
speechManager::speechManager()
{
	//初始化容器 属性
	this->initSpeech();
	this->createSpeaker();
}
//展示菜单
void speechManager::show_Menu()
{
	cout << "**********************************************************" << endl;
	cout << "***********  欢迎参加演讲比赛  *****************************" << endl;
	cout << "***********  1、开始演讲比赛  *****************************" << endl;
	cout << "***********  2、查看往届记录  *****************************" << endl;
	cout << "***********  3、清空往届记录  *****************************" << endl;
	cout << "***********  0、退出比赛程序  *****************************" << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
}
//退出函数
void speechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
//初始化容器
void speechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
}
//创建选手
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "选手";
		name = +nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2;i++)
		{
			sp.m_Score[i] = 0;
		}
		//12名选手编号
		this->v1.push_back(i+10001);
		//选手编号及对应选手加入map中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//抽签
void speechManager::speechDraw()
{
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "-------------------------------------" << endl;
	cout << "抽签后的演讲顺序如下" << endl;
	if (m_Index == 1)
	{
		//第一轮
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << "  ";
		}
		cout << endl;
	}
	else
	{
		//第二轮
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << "  ";
		}
		cout << endl;
		cout << "*******************************************" << endl;
	}
	cout << "-------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//开始演讲比赛
void speechManager::startSpeech()
{
	//  第一轮开始比赛
	// 1、抽签
	this->speechDraw();
	// 2、演讲比赛
	//	3、显示晋级结果
	//  第二轮开始比赛
	// 1、抽签
	// 2、演讲比赛
	//	3、显示最终结果
	// 4、保存分数到文件
}
//析构函数
speechManager::~speechManager()
{

}
