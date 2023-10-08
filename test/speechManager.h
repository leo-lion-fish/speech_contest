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
//����ݽ�������
class speechManager
{
public:
	speechManager();
	void show_Menu();
	void exitSystem();
	//��ʼ�����Ժ�����
	void initSpeech();
	//����ѡ��
	void createSpeaker();
	//��ʼ�ݽ�����
	void startSpeech();
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�÷�
	void showScore();
	//�����¼
	void saveRecord();

	~speechManager();

	vector<int>v1;//�����һ�ֱ���ѡ�ֱ��
	vector<int>v2;//����ڶ��ֱ���ѡ�ֱ��(��һ�ֽ���ѡ��)
	vector<int>vVictory;//ʤ��ǰ����ѡ�ֱ��
	//��ű�ż����Ӧѡ������
	map<int, Speaker>m_Speaker;
	int m_Index;//��������
};