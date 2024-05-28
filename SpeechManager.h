#pragma once
#include <iostream>
#include<vector>
#include<map>
#include"Speaker.h"
#include<fstream>
using namespace std;
//�]�p�t�����ɺ޲z���O
class SpeechManager
{
public:
	//�c�y���
	SpeechManager();

	//��ܵ��
	void show_Menu();

	//�h�X�t��
	void exit_System();


	//��l�Ʈe��
	void initSpeech();
	
	//�O�s�Ĥ@�����ɪ����s��
	vector<int> v1;

	//�Ĥ@���ʯŪ����s��
	vector<int> v2;

	//�ӥX���e�T�W���s��
	vector<int> vVictory;

	//�x�s���s���������m�W
	map<int, Speaker> m_Speaker;

	//�s����ɽ���
	int m_Index;

	//�Ы�12�W���
	void createSpeaker();

	//���ɬy�{����
	void startSpeech();

	//����
	void speechDraw();

	//����
	void speechContest();

	//��ܱo��
	void showScore();

	//�O�s����
	void saveRecoed();

	//Ū������
	void loadRecord();

	//��ܾ�������
	void showRecord();

	//�P�_���O�_����
	bool fileIsEmpty;
	
	//�s������������e��
	map<int, vector<string>> m_Record;

	//�M�Ŭ���
	void clearRecord();

	//�Ѻc���
	~SpeechManager();
	
};