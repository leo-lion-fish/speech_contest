#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include"speaker.h"
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
using namespace std;
//设计演讲管理类
class speechManager
{
public:
	speechManager();
	void show_Menu();
	void exitSystem();
	//初始化属性和容器
	void initSpeech();
	//创建选手
	void createSpeaker();
	//开始演讲比赛
	void startSpeech();
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示得分
	void showScore();
	//保存记录
	void saveRecord();

	~speechManager();

	vector<int>v1;//保存第一轮比赛选手编号
	vector<int>v2;//保存第二轮比赛选手编号(第一轮晋级选手)
	vector<int>vVictory;//胜出前三名选手编号
	//存放编号及其对应选手容器
	map<int, Speaker>m_Speaker;
	int m_Index;//比赛轮数
};