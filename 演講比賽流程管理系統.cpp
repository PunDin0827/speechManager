#include<iostream>
#include"SpeechManager.h"
using namespace std;

int main()
{
	//�H���ؤl
	srand((unsigned int)time(NULL));
	//�Ыغ޲z���O
	SpeechManager sm;

	//����12�W���Ы�
	/*for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	{
		cout << "���s��" << (*it).first << "���m�W" << (*it).second.m_name 
			<< "����" << (*it).second.m_score[0] << endl;
		
	}*/
	
	int choice = 0; //�x�s�Τ��J

	while (true)
	{
		sm.show_Menu();

		cout << "�п�J���: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1: //�}�l����
			sm.startSpeech();
			break;
		case 2: //�d�ݾ������ɬ���
			sm.showRecord();
			break;
		case 3: //�M�Ť��ɬ���
			sm.clearRecord();
			break;
		case 0:  //�h�X�t��
			sm.exit_System();
			break;
		default:
			system("cls"); //�M���e��
			break;
		}
	}


	system("pause");
	return 0;		
}