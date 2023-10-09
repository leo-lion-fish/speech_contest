#include "speechManager.h"
#include <random>
//构造函数
speechManager::speechManager()
{
	//初始化容器 属性
	this->initSpeech();
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();
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
	this->m_Record.clear();
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
//比赛
void speechManager::speechContest()
{
	cout << "----------------第" << this->m_Index << "轮比赛正式开始------------------" << endl;
	//临时容器存放小组成绩
	multimap<double, int, greater<double>>groupScore;
	int num = 0;//记录人员个数 6 人一组
	vector<int>v_Src;//比赛选手容器
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
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f;
			//cout << score << "  ";   //打印所有分数
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front(); d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
		double avg = sum / double(d.size()); //平均分
		////打印平均分
		//cout << "编号为  " << *it <<"  姓名为" <<this->m_Speaker[*it].m_Name<< "  的选手第" << this->m_Index <<
		//	"轮的平均分为" << avg << endl;
		//将平均分放入容器
		this->m_Speaker[*it].m_Score[this->m_Index-1] = avg;
		groupScore.insert(make_pair(avg, *it)); 
		//每六人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次如下:  " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号为" << it->second << "   姓名是" << this->m_Speaker[it->second].m_Name << "   成绩： " <<
					this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
				
			}
			//取走前三名
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
	cout << "----------------------第" << this->m_Index << "轮比赛完毕-------------" << endl;
	cout << endl;
	system("pause");
}
//显示分数
//保存记录
void speechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out|ios::app);//追加的方式写文件
	//将每个人的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存好了" << endl;
	this->fileIsEmpty = false;
}
void speechManager::showScore()
{
	cout << "-----------------------第" << this->m_Index << "轮晋级选手信息如下---------------------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else { v = vVictory; }
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "  选手姓名：" << this->m_Speaker[*it].m_Name << "  得分："
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout <<endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
//开始演讲比赛
void speechManager::startSpeech()
{
	//  第一轮开始比赛
	// 1、抽签
	this->speechDraw();
	// 2、演讲比赛
	this->speechContest();
	//	3、显示晋级结果
	this->showScore();
	//  第二轮开始比赛
	this->m_Index++;
	// 1、抽签
	this->speechDraw();
	// 2、演讲比赛
	this->speechContest();
	//	3、显示最终结果
	this->showScore();
	// 4、保存分数到文件
	this->saveRecord();
	//重置比赛
	//初始化容器 属性
	this->initSpeech();
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();


	cout << "本届比赛完毕!" << endl;
	system("pause");
	system("cls");
}
//读取记录
void speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件存在 但清空了
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符放回
	string data;
	int index = 0;//第几届的标志
	while (ifs >> data)
	{
		vector<string>v;//存放六个字符串
		//cout << data << endl;  //测试用
		int pos = -1;//查到“  ， ”位置的变量
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//找不到的情况
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
//显示往届得分
void speechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空或文件不存在" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void speechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//初始化属性
		this->initSpeech();
		//创建选手
		this->createSpeaker();
		//获取往届记录
		this->loadRecord();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
//析构函数
speechManager::~speechManager()
{

}
