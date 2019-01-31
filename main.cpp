#include"sujson.h"
#include<iostream>
#include<string>
using namespace std;
using namespace SU;
int main()
{
	int i;
	Json J;
	string str = R"(
	{
		"成绩":
				{
					"姓名":"AlexCui",
					"语文":33.6,
					"数学":30,  //这是她的数学成绩
					"理综":[50,60,70]    
				}
	})";
	J  << str;  
	J.at("成绩").at("理综").at(1) >> i;
	cout << i << endl;   // 输出 60
	getchar();
}
