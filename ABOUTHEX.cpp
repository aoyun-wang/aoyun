#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <iomanip>
#include <regex>
#include "Common.h"

using namespace std;


//根据hex的起始地址和结束地址决定文件内容，进行数据操作

void hexStoEad(string startaddress, string endaddress) {
	ifstream file_hex;  //读取该文件，获取文件内容
	file_hex.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.hex", ios::in); //打开固定文件

	//判断文件是否打开，未打开输出信息
	if (!file_hex.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	//定义文件输入读取的内容
	ofstream txt;
	txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.txt", ios::out);//生成固定文件并写入

	//定义字符流
	string buf;

	//读取文件的每一行数据，写入字符流中
	while (getline(file_hex, buf)) {
		//针对于每一行数据进行校验，获取校验通过的数据
		if (!buf.find(startaddress))
		{
			cout << buf << endl;
			txt << buf << endl;
			
		}
		else
		{
			cout << "找不到该关键字" << endl;
		}
	}
	file_hex.close();
	txt.close();
}



//打开一个文件把一个文件写入到一个不换行的文件内
void hexStoL() {
	ifstream file_hex;  //读取该文件，获取文件内容
	file_hex.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.hex", ios::in); //打开固定文件

	//判断文件是否打开，未打开输出信息
	if (!file_hex.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}
	//新定义一个txt文件存放数据
	ofstream txt;
	txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.txt", ios::out);//生成固定文件并写入

	//定义字符流
	string buf;

	//读取文件的每一行数据，写入字符流中
	while (getline(file_hex, buf)) {
		//每一行数据写入txt中，不区分行数
		cout << buf;
	}
	file_hex.close();
	txt.close();

}


void hexSad(string startaddress) {
	ifstream file_txt;  //读取该文件，获取文件内容
	file_txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.txt", ios::in); //打开固定文件

	//判断文件是否打开，未打开输出信息
	if (!file_txt.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}
	//新定义一个txt文件存放数据
	ofstream txt_2;
	txt_2.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63_2.txt", ios::out);//生成固定文件并写入

	//定义字符流
	string buf;
	string buf_1;
	string buf_2;
	//读取文件的每一行数据，写入字符流中
	while (getline(file_txt, buf)) {
		//每一行数据写入txt中，不区分行数
		int i = buf.find(":02000004" +startaddress.substr(0,4));

		buf_1 = buf.substr(i + 15, size(buf));
		txt_2 << buf_1;


		cout << size(buf_1)<<endl;
		
		
	}
	

	txt_2.close();

}


void hexrp () {
	ifstream file_txt;  //读取该文件，获取文件内容
	file_txt.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63_2.txt", ios::in); //打开固定文件

	string buf_2;

	ofstream txt_3;
	txt_3.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63_3.txt", ios::out);//生成固定文件并写入

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




//打开一个文件把一个文件写入到一个不换行的文件内
void CheckHex() {
	ifstream file_hex;  //读取该文件，获取文件内容
	file_hex.open("C:/Users/mac/Desktop/daily work/hex/EDC17C63.hex", ios::in); //打开固定文件

	//判断文件是否打开，未打开输出信息
	if (!file_hex.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}


	//定义字符流
	string buf;
	string line;
	string txt_address = "";

	//读取文件的每一行数据，写入字符流中
	while (getline(file_hex, buf)) {
		//判断地址是否连续
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


		cout << "相加为:" << lo_16 + acc_8 << endl;
		if (hi_16 = lo_16 + acc_8) {

			cout << "hex文件不连续"<<endl;

		}
		else
		{
			cout << "hex文件连续" << endl;
		}
	}
	file_hex.close();

}


void comp() {
	int score;
	cout << "请输入你的分数" << endl;
	cin >> score;

	if (score == 600) {
		cout << "你考上了一本" << endl;
	}
}

	int main() {
		//CheckHex();
		//hexStoL();
		comp();
		system("pause");
		return 0;
	}