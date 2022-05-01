#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <iomanip>
#include <regex>
#include "Common.h"

using namespace std;


//����hex����ʼ��ַ�ͽ�����ַ�����ļ����ݣ��������ݲ���

void hexStoEad(string startaddress, string endaddress) {
	ifstream file_hex;  //��ȡ���ļ�����ȡ�ļ�����
	file_hex.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.hex", ios::in); //�򿪹̶��ļ�

	//�ж��ļ��Ƿ�򿪣�δ�������Ϣ
	if (!file_hex.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	//�����ļ������ȡ������
	ofstream txt;
	txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.txt", ios::out);//���ɹ̶��ļ���д��

	//�����ַ���
	string buf;

	//��ȡ�ļ���ÿһ�����ݣ�д���ַ�����
	while (getline(file_hex, buf)) {
		//�����ÿһ�����ݽ���У�飬��ȡУ��ͨ��������
		if (!buf.find(startaddress))
		{
			cout << buf << endl;
			txt << buf << endl;
			
		}
		else
		{
			cout << "�Ҳ����ùؼ���" << endl;
		}
	}
	file_hex.close();
	txt.close();
}



//��һ���ļ���һ���ļ�д�뵽һ�������е��ļ���
void hexStoL() {
	ifstream file_hex;  //��ȡ���ļ�����ȡ�ļ�����
	file_hex.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.hex", ios::in); //�򿪹̶��ļ�

	//�ж��ļ��Ƿ�򿪣�δ�������Ϣ
	if (!file_hex.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	//�¶���һ��txt�ļ��������
	ofstream txt;
	txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.txt", ios::out);//���ɹ̶��ļ���д��

	//�����ַ���
	string buf;

	//��ȡ�ļ���ÿһ�����ݣ�д���ַ�����
	while (getline(file_hex, buf)) {
		//ÿһ������д��txt�У�����������
		cout << buf;
	}
	file_hex.close();
	txt.close();

}


void hexSad(string startaddress) {
	ifstream file_txt;  //��ȡ���ļ�����ȡ�ļ�����
	file_txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.txt", ios::in); //�򿪹̶��ļ�

	//�ж��ļ��Ƿ�򿪣�δ�������Ϣ
	if (!file_txt.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	//�¶���һ��txt�ļ��������
	ofstream txt_2;
	txt_2.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63_2.txt", ios::out);//���ɹ̶��ļ���д��

	//�����ַ���
	string buf;
	string buf_1;
	string buf_2;
	//��ȡ�ļ���ÿһ�����ݣ�д���ַ�����
	while (getline(file_txt, buf)) {
		//ÿһ������д��txt�У�����������
		int i = buf.find(":02000004" +startaddress.substr(0,4));

		buf_1 = buf.substr(i + 15, size(buf));
		txt_2 << buf_1;


		cout << size(buf_1)<<endl;
		
		
	}
	

	txt_2.close();

}


void hexrp () {
	ifstream file_txt;  //��ȡ���ļ�����ȡ�ļ�����
	file_txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63_2.txt", ios::in); //�򿪹̶��ļ�

	string buf_2;

	ofstream txt_3;
	txt_3.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63_3.txt", ios::out);//���ɹ̶��ļ���д��

	for (int n = 0;n < 3000;n++) {
		while (getline(file_txt, buf_2)) {
			if (buf_2.find(":")) {
				buf_2.replace(buf_2.find(":"), 1, "/n");
				cout << n << endl << buf_2.find(":") << endl;
				file_txt.close();

			}
			
			
		}

	}
}




//��һ���ļ���һ���ļ�д�뵽һ�������е��ļ���
void CheckHex() {
	ifstream file_hex;  //��ȡ���ļ�����ȡ�ļ�����
	file_hex.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.hex", ios::in); //�򿪹̶��ļ�

	//�ж��ļ��Ƿ�򿪣�δ�������Ϣ
	if (!file_hex.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return;
	}


	//�����ַ���
	string buf;
	string line;
	string txt_address = "";

	//��ȡ�ļ���ÿһ�����ݣ�д���ַ�����
	while (getline(file_hex, buf)) {
		//�жϵ�ַ�Ƿ�����
		if (buf.substr(7,2) == "00"){
			string loaddress = buf.substr(1, 6);
			
			txt_address.append(loaddress);
			
		}
	}
	cout << txt_address<<endl;
	

	for (int i = 1;i < txt_address.length() / 6;i++) {
		string hiadd = Common::hexStrToBytes(txt_address.substr(2 + 6 * i, 4).c_str(),4);
		uint16_t hi_16 = static_cast<uint16_t>(htons(*(uint16_t*)(hiadd.data())));
		cout << "hi_16:" << std::hex << hi_16 << endl;

		string loadd = Common::hexStrToBytes(txt_address.substr(2+ 6 * (i-1), 4).c_str(),4);
		uint16_t lo_16 = static_cast<uint16_t>(htons(*(uint16_t*)(loadd.data())));
		cout << "lo_16:" << lo_16 << endl;

		string acckey = Common::hexStrToBytes(txt_address.substr(6 * (i - 1), 2).c_str(),2);
		uint8_t acc_8 = static_cast<uint8_t>(htons(*(uint8_t*)(acckey.data())));
		cout << "acc_8:" << acc_8 << endl;


		cout << "���Ϊ:" << lo_16 + acc_8 << endl;
		if (hi_16 = lo_16 + acc_8) {

			cout << "hex�ļ�������"<<endl;

		}
		else
		{
			cout << "hex�ļ�����" << endl;
		}
	}
	file_hex.close();

}


void comp() {
	int score;
	cout << "��������ķ���" << endl;
	cin >> score;

	if (score == 600) {
		cout << "�㿼����һ��" << endl;
	}
}

	int main() {
		//CheckHex();
		//hexStoL();
		comp();
		system("pause");
		return 0;
	}