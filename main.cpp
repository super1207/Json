#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

vector<string> DFA(const string & str)
{
	vector<string> ret;
	for (size_t i = 0; i < str.length();)
	{
		if (str.at(i) == ',')
		{
			ret.push_back(",");
			++i;
		}
		else if (str.at(i) == ':')
		{
			ret.push_back(":");
			++i;
		}
		else if (str.at(i) == '{')
		{
			ret.push_back("{");
			++i;
		}
		else if (str.at(i) == '[')
		{
			ret.push_back("[");
			++i;
		}
		else if (str.at(i) == ']')
		{
			ret.push_back("]");
			++i;
		}
		else if (str.at(i) == '}')
		{
			ret.push_back("}");
			++i;
		}
		else if (str.at(i) == 'n')
		{
			ret.push_back("null");
			i+=4;
		}
		else if (str.at(i) == 'f')
		{
			ret.push_back("false");
			i+=5;
		}
		else if (str.at(i) == 't')
		{
			ret.push_back("true");
			i += 4;
		}
		else if ((str.at(i) <= '9'&& str.at(i) >= '0') || str.at(i) == '-') //isnum
		{
			string n = "";
			do
			{
				n.push_back(str.at(i++));
			} while ((str.at(i) <= '9'&& str.at(i) >= '0') || str.at(i) == '-'|| str.at(i) == '.');
			ret.push_back(n);
		}
		else if (str.at(i) == '\"')
		{
			string n = "";
			n.push_back('\"');
			++i;
			while (true)
			{
				if (str.at(i) == '\\')
				{
					++i;
					if (str.at(i) == 'u')
					{
						n.append("\\u");
						n.push_back(str.at(i) + 1);
						n.push_back(str.at(i) + 2);
						n.push_back(str.at(i) + 3);
						n.push_back(str.at(i) + 4);
						i += 5;
					}
					else
					{
						n.push_back(str.at(i));
						++i;
					}
				}
				else if (str.at(i) == '\"')
				{
					n.push_back('"');
					++i;
					break;
				}
				else
				{
					n.push_back(str.at(i));
					++i;
				}
			}

			ret.push_back(n);
		}
		else
		{
			++i;
		}
	}
	return ret;
}
vector<vector<string> > jsonArray(const vector<string> & vec)
{
	vector<vector<string>> ret;
	size_t flag = 0;
	if (vec.size() > 2)
	{
		ret.push_back({});
		for (size_t i = 1; i < vec.size() - 1; ++i)
		{
			if (vec.at(i) == ",")
			{
				if (flag == 0)
				{
					ret.push_back({});
				}
				else
				{
					ret.at(ret.size() - 1).push_back(",");
				}
			}
			else if (vec.at(i) == "{" || vec.at(i) == "[")
			{
				++flag;
				ret.at(ret.size() - 1).push_back(vec.at(i));
			}
			else if (vec.at(i) == "}" || vec.at(i) == "]")
			{
				--flag;
				ret.at(ret.size() - 1).push_back(vec.at(i));
			}
			else
			{
				ret.at(ret.size() - 1).push_back(vec.at(i));
			}
		}
	}
	return ret;
}
map<string, vector<string>> jsonObject(const vector<string> & vec)
{
	map<string,vector<string>> ret;
	string key = "";
	vector<string> ele;
	size_t flag = 0;
	if (vec.size() > 2)
	{
		for (size_t i = 1; i < vec.size() - 1; ++i)
		{
			if (vec.at(i) == ",")
			{
				if (flag == 0)
				{
					ret.insert({ key, ele });
				}
				else
				{
					ele.push_back(",");
				}
			}
			else if (vec.at(i) == "{" || vec.at(i) == "[")
			{
				++flag;
				ele.push_back(vec.at(i));
			}
			else if (vec.at(i) == "}" || vec.at(i) == "]")
			{
				--flag;
				ele.push_back(vec.at(i));
			}
			else if (vec.at(i) == ":")
			{
				key = vec.at(i - 1);
				ele.clear();
			}
			else 
			{
				ele.push_back(vec.at(i));
			}
		}
		ret.insert({ key, ele });
	}
	return ret;
}
int main()
{
	string str = R"({"12345":123,"2222":[1,2,[1,2,3],3,4]})";
	
	auto ret = DFA(str);
	for (auto i : ret)
	{
		cout << i ;
	}
	cout << endl;
	auto arrvec = jsonObject(ret);
	cout << arrvec.size() << endl;
	for (auto i : arrvec)
	{
		cout << "key:" << i.first << "val:" ;
		for (auto k : i.second)
		{
			cout <<k;
		}
	}
	getchar();
	return 0;
}
