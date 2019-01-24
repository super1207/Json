#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<functional>
using namespace std;

vector<pair<string, string> > fun1(string str)
{
	vector<pair<string, string> > ret;     //  用于存放结果： 标准格式,描述
	vector<pair<function<string(string)>, string> > match;	//用于存放：分割规则 描述 返回标准格式

	match = {
		{[](string str)->string {if (regex_match(str,regex(R"([+=]*[0-9]+(\.[0-9]*)?)")))return str; else return ""; },"number"},
		{[](string str)->string {if (regex_match(str,regex(R"(\s*)")))return str; else return ""; }," "},
		{[](string str)->string {if (regex_match(str,regex(R"("(([^"])|(\\"))*")")))return str; else return ""; },"string"},
		{[](string str)->string {if (regex_match(str,regex(R"(\[)")))return str; else return ""; },"["},
		{[](string str)->string {if (regex_match(str,regex(R"(\])")))return str; else return ""; },"]"},
		{[](string str)->string {if (regex_match(str,regex(R"(,)")))return str; else return ""; },","},
		{[](string str)->string {if (regex_match(str,regex(R"(:)")))return str; else return ""; },":"},
		{[](string str)->string {if (regex_match(str,regex(R"(\{)")))return str; else return ""; },"{"},
		{[](string str)->string {if (regex_match(str,regex(R"(\})")))return str; else return ""; },"}"},
		{[](string str)->string {if (regex_match(str,regex(R"(true)")))return str; else return ""; },"true"},
		{[](string str)->string {if (regex_match(str,regex(R"(false)")))return str; else return ""; },"false"},
		{[](string str)->string {if (regex_match(str,regex(R"(null)")))return str; else return ""; },"null"}
	};
	size_t i, j, k, add;
	string sub;
	size_t len = str.length();
	size_t matLen = match.size();
	for (i = 0; i < len; )
	{

		for (j = len; j > i; --j)
		{
			add = j - i;
			sub = str.substr(i, add);
			for (k = 0; k < matLen; ++k)
			{
				string subret = (match.at(k).first)(sub);
				if (subret != "")
				{
					if (match.at(k).second != " ")ret.push_back(make_pair(subret, match.at(k).second));
					i += add;
					goto nex;
				}
			}
		}
		cout << "fun1 error in pos:" << i << ":\"" << sub << "\"" << endl;
		while (1);
	nex:;
	}
	return ret;
}
string fun2(string fun1_ret_0_second)
{
	//返回Json的7种类型
	if (fun1_ret_0_second.at(0) == '{')return "object";
	if (fun1_ret_0_second.at(0) == '[')return "array";
	if (fun1_ret_0_second.at(0) == 's')return "string";
	if (fun1_ret_0_second.at(0) == 'n')return "null";
	if (fun1_ret_0_second.at(0) == 't')return "true";
	if (fun1_ret_0_second.at(0) == 'f')return "false";
	return "number";
}
pair<string, vector<pair<vector<size_t>, string>>> fun3(vector<pair<string, string>> fun1_ret)
{

	//返回主 结点类型，各子节点的标准格式序数集合与类型
	pair<string, vector<pair<vector<size_t>, string>>> ret;
	ret.first = fun2(fun1_ret.at(0).second);
	size_t fun1_ret_size = fun1_ret.size();
	for (size_t i = 1; i < fun1_ret_size - 1; )
	{
		if (fun1_ret.at(i).second == "[")
		{
			ret.second.push_back({ vector<size_t>{}, string("array") });
			size_t num = 0;
			size_t ret_pos = ret.second.size() - 1;
			for (size_t j = i; j < fun1_ret_size - 1; ++j)
			{
				if (fun1_ret.at(j).second == "[")++num;
				else if (fun1_ret.at(j).second == "]")--num;
				ret.second.at(ret_pos).first.push_back(j);
				if (num == 0)
				{
					i = j + 1;
					break;
				}
				if (j == fun1_ret_size - 1 - 1)
				{
					throw "fun3 error[";
					cout << "fun3 error"<< endl;
					while (1);
				}
			}
		}
		else if (fun1_ret.at(i).second == "{")
		{
			ret.second.push_back({ vector<size_t>{}, string("object") });
			size_t num = 0;
			size_t ret_pos = ret.second.size() - 1;
			for (size_t j = i; j < fun1_ret_size - 1; ++j)
			{
				if (fun1_ret.at(j).second == "{")++num;
				else if (fun1_ret.at(j).second == "}")--num;
				ret.second.at(ret_pos).first.push_back(j);
				if (num == 0)
				{
					i = j + 1;
					break;
				}
				if (j == fun1_ret_size - 1 - 1)
				{
					throw "fun3 error{";
					cout << "fun3 error" << endl;
					while (1);
				}
			}
		}
		else if (fun1_ret.at(i).second == "string")
		{
			ret.second.push_back({ vector<size_t>{}, string("string") });
			size_t ret_pos = ret.second.size() - 1;
			ret.second.at(ret_pos).first.push_back(i);
			++i;
		}
		else if (fun1_ret.at(i).second == "null")
		{
			ret.second.push_back({ vector<size_t>{}, string("null") });
			size_t ret_pos = ret.second.size() - 1;
			ret.second.at(ret_pos).first.push_back(i);
			++i;
		}
		else if (fun1_ret.at(i).second == "true")
		{
			ret.second.push_back({ vector<size_t>{}, string("true") });
			size_t ret_pos = ret.second.size() - 1;
			ret.second.at(ret_pos).first.push_back(i);
			++i;
		}
		else if (fun1_ret.at(i).second == "false")
		{
			ret.second.push_back({ vector<size_t>{}, string("false") });
			size_t ret_pos = ret.second.size() - 1;
			ret.second.at(ret_pos).first.push_back(i);
			++i;
		}
		else if (fun1_ret.at(i).second == ",")
		{
			++i;
		}
		else
		{
			//throw "fun3 error";
			cout << "fun3 error" << fun1_ret.at(i).second << endl;
			while (1);
		}
	}
	return ret;
}
int main()
{
	string str = R"({

"employees": [
{ "first\"Name":"Bill" , "last Name":"Gates" },

{ " firstName":"George" ,      "lastName":"Bush" },

{ "firstName":"Thomas" , "lastName":"Carter" }

]
})";
	vector<pair<string, string> > ret = fun1(str);
	for (auto i : ret)
	{
		cout << i.first;;
	}
	pair<string, vector<pair<vector<size_t>, string>>> fun3_ret = fun3(ret);
	for (auto i : fun3_ret.second)
	{
		cout << i.second << endl;
	}
	getchar();
	return 0;
}
