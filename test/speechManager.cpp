#include "speechManager.h"
//���캯��
speechManager::speechManager()
{
	//��ʼ������ ����
	this->initSpeech();
	this->createSpeaker();
}
//չʾ�˵�
void speechManager::show_Menu()
{
	cout << "**********************************************************" << endl;
	cout << "***********  ��ӭ�μ��ݽ�����  *****************************" << endl;
	cout << "***********  1����ʼ�ݽ�����  *****************************" << endl;
	cout << "***********  2���鿴�����¼  *****************************" << endl;
	cout << "***********  3����������¼  *****************************" << endl;
	cout << "***********  0���˳���������  *****************************" << endl;
	cout << "**********************************************************" << endl;
	cout << endl;
}
//�˳�����
void speechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
//��ʼ������
void speechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
}
//����ѡ��
void speechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "ѡ��";
		name = +nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2;i++)
		{
			sp.m_Score[i] = 0;
		}
		//12��ѡ�ֱ��
		this->v1.push_back(i+10001);
		//ѡ�ֱ�ż���Ӧѡ�ּ���map��
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ǩ
void speechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------" << endl;
	cout << "��ǩ����ݽ�˳������" << endl;
	if (m_Index == 1)
	{
		//��һ��
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << "  ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ���
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

//��ʼ�ݽ�����
void speechManager::startSpeech()
{
	//  ��һ�ֿ�ʼ����
	// 1����ǩ
	this->speechDraw();
	// 2���ݽ�����
	//	3����ʾ�������
	//  �ڶ��ֿ�ʼ����
	// 1����ǩ
	// 2���ݽ�����
	//	3����ʾ���ս��
	// 4������������ļ�
}
//��������
speechManager::~speechManager()
{

}
