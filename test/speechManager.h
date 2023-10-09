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
	//��ȡ��¼
	void loadRecord();
	//��ʾ����÷�
	void showRecord();
	//��ռ�¼
	void clearRecord();


	~speechManager();

	vector<int>v1;//�����һ�ֱ���ѡ�ֱ��
	vector<int>v2;//����ڶ��ֱ���ѡ�ֱ��(��һ�ֽ���ѡ��)
	vector<int>vVictory;//ʤ��ǰ����ѡ�ֱ��
	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	//�����¼����
	map<int, vector<string>>m_Record;
	//��ű�ż����Ӧѡ������
	map<int, Speaker>m_Speaker;
	int m_Index;//��������
};