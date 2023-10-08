#include "speechManager.h"
#include <random>
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
//����
void speechManager::speechContest()
{
	cout << "----------------��" << this->m_Index << "�ֱ�����ʽ��ʼ------------------" << endl;
	//��ʱ�������С��ɼ�
	multimap<double, int, greater<double>>groupScore;
	int num = 0;//��¼��Ա���� 6 ��һ��
	vector<int>v_Src;//����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			//cout << score << "  ";   //��ӡ���з���
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_front(); d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);//�ܷ�
		double avg = sum / double(d.size()); //ƽ����
		////��ӡƽ����
		//cout << "���Ϊ  " << *it <<"  ����Ϊ" <<this->m_Speaker[*it].m_Name<< "  ��ѡ�ֵ�" << this->m_Index <<
		//	"�ֵ�ƽ����Ϊ" << avg << endl;
		//��ƽ���ַ�������
		this->m_Speaker[*it].m_Score[this->m_Index-1] = avg;
		groupScore.insert(make_pair(avg, *it)); 
		//ÿ����ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С�������������:  " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���Ϊ" << it->second << "   ������" << this->m_Speaker[it->second].m_Name << "   �ɼ��� " <<
					this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
				
			}
			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
		
	}
	cout << "----------------------��" << this->m_Index << "�ֱ������-------------" << endl;
	cout << endl;
	system("pause");
}
//��ʾ����
//�����¼
void speechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out|ios::app);//׷�ӵķ�ʽд�ļ�
	//��ÿ���˵�����д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ��������" << endl;
}
void speechManager::showScore()
{
	cout << "-----------------------��" << this->m_Index << "�ֽ���ѡ����Ϣ����---------------------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else { v = vVictory; }
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << "  ѡ��������" << this->m_Speaker[*it].m_Name << "  �÷֣�"
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout <<endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
//��ʼ�ݽ�����
void speechManager::startSpeech()
{
	//  ��һ�ֿ�ʼ����
	// 1����ǩ
	this->speechDraw();
	// 2���ݽ�����
	this->speechContest();
	//	3����ʾ�������
	this->showScore();
	//  �ڶ��ֿ�ʼ����
	this->m_Index++;
	// 1����ǩ
	this->speechDraw();
	// 2���ݽ�����
	this->speechContest();
	//	3����ʾ���ս��
	this->showScore();
	// 4������������ļ�
	this->saveRecord();

	cout << "����������!" << endl;
	system("pause");
	system("cls");
}
//��������
speechManager::~speechManager()
{

}
