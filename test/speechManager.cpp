#include "speechManager.h"
#include <random>
//���캯��
speechManager::speechManager()
{
	//��ʼ������ ����
	this->initSpeech();
	this->createSpeaker();
	//���������¼
	this->loadRecord();
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
	this->m_Record.clear();
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
	this->fileIsEmpty = false;
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
	//���ñ���
	//��ʼ������ ����
	this->initSpeech();
	this->createSpeaker();
	//���������¼
	this->loadRecord();


	cout << "����������!" << endl;
	system("pause");
	system("cls");
}
//��ȡ��¼
void speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ����� �������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż�
	string data;
	int index = 0;//�ڼ���ı�־
	while (ifs >> data)
	{
		vector<string>v;//��������ַ���
		//cout << data << endl;  //������
		int pos = -1;//�鵽��  �� ��λ�õı���
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//�Ҳ��������
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
//��ʾ����÷�
void speechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��ļ�������" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
				"������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void speechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//��ʼ������
		this->initSpeech();
		//����ѡ��
		this->createSpeaker();
		//��ȡ�����¼
		this->loadRecord();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
//��������
speechManager::~speechManager()
{

}
