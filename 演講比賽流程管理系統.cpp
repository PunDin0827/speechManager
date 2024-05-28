#include<iostream>
#include"SpeechManager.h"
using namespace std;

int main()
{
	//隨機種子
	srand((unsigned int)time(NULL));
	//創建管理類別
	SpeechManager sm;

	//測試12名選手創建
	/*for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	{
		cout << "選手編號" << (*it).first << "選手姓名" << (*it).second.m_name 
			<< "分數" << (*it).second.m_score[0] << endl;
		
	}*/
	
	int choice = 0; //儲存用戶輸入

	while (true)
	{
		sm.show_Menu();

		cout << "請輸入選擇: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: //開始比賽
			sm.startSpeech();
			break;
		case 2: //查看歷屆比賽紀錄
			sm.showRecord();
			break;
		case 3: //清空比賽紀錄
			sm.clearRecord();
			break;
		case 0:  //退出系統
			sm.exit_System();
			break;
		default:
			system("cls"); //清除畫面
			break;
		}
	}


	system("pause");
	return 0;		
}