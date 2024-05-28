#include"SpeechManager.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>

SpeechManager::SpeechManager()
{
	//初始化容器和屬性
	this->initSpeech();

	//創建12名選手
	this->createSpeaker();

	//載入歷屆紀錄
	this->loadRecord();
}
//顯示菜單
void SpeechManager::show_Menu()
{
	cout << "**************************" << endl;
	cout << "****  歡迎參加演講比賽  ****" << endl;
	cout << "****  1.開始演講比賽  ****" << endl;
	cout << "****  2.查看歷屆紀錄  ****" << endl;
	cout << "****  3.清空比賽紀錄  ****" << endl;
	cout << "****  0.退出比賽程式  ****" << endl;
	cout << "***************************" << endl;
	cout << endl;
}
//退出系統
void SpeechManager::exit_System()
{
	cout << "歡迎再次使用" << endl;
	system("pause");
	exit(0);
}
//初始化容器
void SpeechManager::initSpeech()
{
	//容器先置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比賽輪數
	this->m_Index = 1;

	//將記錄清空
	this->m_Record.clear();
}
//創建12名選手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "選手";
		name += nameSeed[i];

		//創建具體選手
		Speaker sp;
		sp.m_name = name;
		for (int j = 0; j < 2 ;j++)
		{
			sp.m_score[j] = 0;
		}
		//創建選手編號並放入v1容器
		this->v1.push_back(i + 10001);
		//選手編號及對應選手姓名放入map容器
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
//比賽流程控制
void SpeechManager::startSpeech()
{
	//開始第一輪比賽
	
	//1.抽籤
	this->speechDraw();

	//2.比賽
	this->speechContest();

	//3.顯示晉級結果
	this->showScore();

	//開始第二輪比賽
	this->m_Index++;

	//1.抽籤
	this->speechDraw();

	//2.比賽
	this->speechContest();

	//3.顯示最終結果
	this->showScore();

	//4.保存分數到文件中
	this->saveRecoed();

	//重置比賽 獲取紀錄
	//初始化容器和屬性
	this->initSpeech();

	//創建12名選手
	this->createSpeaker();

	//載入歷屆紀錄
	this->loadRecord();

	cout << "本屆比賽完畢! " << endl;
	system("pause");
	system("cls");
}
//抽籤
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_Index << "輪選手正在抽籤 " << endl;
	cout << "---------------------" << endl;
	cout << "抽籤後演講順序如下 " << endl;
	if (m_Index == 1)
	{
		//第一輪比賽
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二輪比賽
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}
//比賽
void SpeechManager::speechContest()
{
	//準備臨時容器存放小組成績
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //記錄人員個數  6人一組

	cout << "-----第"<< this->m_Index << "輪比賽正式開始-----" << endl;
	vector<int> v_src; //比賽選手容器
	if (m_Index == 1)
	{
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}
	//所有選手進行比賽
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		//評審打分數
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  //600~1000隨機數
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>()); //排序
		d.pop_front(); //去除最高分
		d.pop_back(); //去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f); //總分
		double avg = sum / (double)d.size(); //平均分數

		//每個人的平均分數
		//cout << "編號 " << *it << "姓名 " << this->m_Speaker[*it].m_name
			//<<"平均獲得分數: " << avg << endl;

		//將平均分數放到map容器中
		this->m_Speaker[*it].m_score[this->m_Index - 1] = avg;

		//將分數放到臨時小組容器中
		groupScore.insert(make_pair(avg, *it));  // key:得分 ,value:選手編號
		//每6個人取前3名
		if (num % 6 == 0)
		{
			cout << "第 " << num / 6 << "小組比賽名次: " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "編號: " << it->second << "姓名" << this->m_Speaker[it->second].m_name << " "
					<< "分數: " << this->m_Speaker[it->second].m_score[m_Index - 1] << endl;
			}
			//取得前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&& count<3 ; it++, count++)
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
			groupScore.clear(); //小組容器清空
			cout << endl;

		}

	}
	cout << "-----第" << this->m_Index << "輪比賽完畢-----" << endl;
	system("pause");

}
//顯示得分
void SpeechManager::showScore()
{
	cout << "-------第" << this->m_Index << "輪晉級選手的訊息如下: -------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "選手編號" << *it << "姓名" << this->m_Speaker[*it].m_name
			<< "得分" << this->m_Speaker[*it].m_score[this->m_Index - 1] << endl; 
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
//保存紀錄
void SpeechManager::saveRecoed()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //用追加的方式寫入文件

	//將每個選手的數據寫入文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	//關閉文件
	ofs.close();
	cout << "紀錄已經保存 " << endl;

	//更新文件狀態
	this->fileIsEmpty = false;

}
//讀取紀錄
void SpeechManager::loadRecord()
{
	ifstream ifs ("speech.csv", ios::in);//讀文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件清空的情況
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件為空 " << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不為空
	this->fileIsEmpty = false;
	ifs.putback(ch); //將上面讀取的字符放回去
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;//存放6個sring的容器(前三名選手的編號和分數)
		//cout << data << endl;
		//10002,86.675,10009,81.3,10007,78.55 <=用逗號分割文件裡的資料
		int pos = -1; //查到","位置的變數
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//沒有找到的情況
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end();it++)
	{
		cout << it->first << "冠軍編號: " << it->second[0] << " 分數: " << it->second[1] << endl;
	}*/
}
//顯示歷屆紀錄
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件為空或不存在! " << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "屆"
				<< "冠軍編號為: " << this->m_Record[i][0] << " 得分為: " << this->m_Record[i][1] << " "
				<< "亞軍編號為: " << this->m_Record[i][2] << " 得分為: " << this->m_Record[i][3] << " "
				<< "季軍編號為: " << this->m_Record[i][4] << " 得分為: " << this->m_Record[i][5] << " " << endl;
		}
	}
	
	system("pause");
	system("cls");
}
//清空紀錄
void SpeechManager::clearRecord()
{
	cout << "是否確定清空紀錄 ?" << endl;
	cout << "1.是 " << endl;
	cout << "2.否 " << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//確定清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//初始化容器和屬性
		this->initSpeech();

		//創建12名選手
		this->createSpeaker();

		//載入歷屆紀錄
		this->loadRecord();

		cout << "清空成功! " << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager()
{
}