#pragma once
#include <iostream>
#include<vector>
#include<map>
#include"Speaker.h"
#include<fstream>
using namespace std;
//設計演講比賽管理類別
class SpeechManager
{
public:
	//構造函數
	SpeechManager();

	//顯示菜單
	void show_Menu();

	//退出系統
	void exit_System();


	//初始化容器
	void initSpeech();
	
	//保存第一輪比賽的選手編號
	vector<int> v1;

	//第一輪晉級的選手編號
	vector<int> v2;

	//勝出的前三名選手編號
	vector<int> vVictory;

	//儲存選手編號對應選手姓名
	map<int, Speaker> m_Speaker;

	//存放比賽輪數
	int m_Index;

	//創建12名選手
	void createSpeaker();

	//比賽流程控制
	void startSpeech();

	//抽籤
	void speechDraw();

	//比賽
	void speechContest();

	//顯示得分
	void showScore();

	//保存紀錄
	void saveRecoed();

	//讀取紀錄
	void loadRecord();

	//顯示歷屆紀錄
	void showRecord();

	//判斷文件是否為空
	bool fileIsEmpty;
	
	//存放歷屆紀錄的容器
	map<int, vector<string>> m_Record;

	//清空紀錄
	void clearRecord();

	//解構函數
	~SpeechManager();
	
};