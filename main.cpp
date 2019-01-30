#include<iostream>
#include<string>
#include<vector>
#include<map>
#include <cstdlib>
using namespace std;

vector<string> JsonFromStr(string str)
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
				if (flag == 0)
				{
					key = vec.at(i - 1).substr(1, vec.at(i - 1).length()-2);
					ele.clear();
				}
				else
				{
					ele.push_back(":");
				}
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

string jsonType(const vector<string> & vec)
{
	switch (vec.at(0).at(0))
	{
		case '{':return "object";
		case '[':return "array";
		case '"':return "string";
		case 'n':return "null";
		case 't':return "true";
		case 'f':return "false";
		default:return "number";
	}
}

string jsonToStr(const vector<string> & vec)
{
	string ret = "";
	for(size_t i = 0;i< vec.size();++i)
	{
		ret.append(vec.at(i));
	}
	return ret;
}

class Json
{
public:
	void JsonRead(string str)
	{
		this->data = JsonFromStr(str);
	}
	Json()
	{
		data.push_back("0");
	}
	Json(string str)
	{
		data.push_back("\"");
		data.push_back(str);
		data.push_back("\"");
	}
	Json(const vector<string> & vec)
	{
		this->data = vec;
	}
	Json(map<string, vector<string>> & m)
	{
		data.push_back("{");
		map<string, vector<string>>::iterator it;
		for (it = m.begin();it!=m.end();++it)
		{
			data.push_back("\""+it->first+"\"");
			data.push_back(":");
			data.insert(data.begin(), it->second.begin(), it->second.end());
		}
		data.push_back("}");
	}
	Json(double number)
	{
		data.push_back(to_string(number));
	}
	Json(void * null)
	{
		data.push_back("null");
	}
	Json(bool B)
	{
		data.push_back(B ? "true" : "false");
	}
	Json operator[](string key)const
	{		
		return jsonObject(data).at(key);
	}
	Json operator[](size_t num)const
	{
		return jsonArray(data).at(num);
	}
	string type()const
	{
		return jsonType(data);
	}
	int asInt()const
	{
		return atoi(data.at(0).c_str());
	}
	string asString()const
	{
		return data.at(0);//data.at(0).substr(1, data.at(0).length()-2);
	}
	double asDouble()const
	{
		return atof(data.at(0).c_str());
	}
	bool asBool()const
	{
		return (data.at(0) == "true" ? true : false);
	}
	bool isNull()const
	{
		return (data.at(0) == "null");
	}
	map<string, vector<string>> asMap()const
	{
		return jsonObject(data);
	}
	vector<vector<string>> asVec()const
	{
		return jsonArray(data);
	}
	
	friend ostream& operator <<(ostream&, const Json&);
private:
	string toString()const
	{
		return jsonToStr(data);
	}
	vector<string> data; 
};
ostream & operator<<(ostream &os, const Json  &ob)
{
	os << ob.toString();
	return os;
}

int main()
{
	//simple example
	string str = R"(
	{
		"成绩":
				{
					"姓名":"AlexCui",
					"语文":33.6,
					"数学":30,
					"理综":[50,60,70]
				}
	}
	)";

	Json J; //使用无参构造所得的Json对象没有实际意义

	J.JsonRead(str);  //从str导入需要解析的Json

	cout << J << endl;  //因为重载了operator<<，所以可以直接cout输出(只能用于打印调试)

	cout << J.type() << endl; //可以打印出Json的类型"object","array","string","null","true","false","number"中的一种


	cout << J["成绩"]["理综"][0] << endl;//Json的简单访问

	//遍历Object
	for (const auto & i : J["成绩"].asMap())  //json不能直接迭代，但是可以转化成相应的标准类型后进行迭代
	{
		cout << i.first << ":";   //first为C++的标准string类型
		cout << Json(i.second) << endl; //second为字符串序列，不能直接输出，但是可以转化为Json对象后输出
	}
	//遍历array
	for (const auto & i : J["成绩"]["理综"].asVec())
	{
		//i为字符串序列，不能直接使用，但是我们可以先转化成Json对象
		cout << Json(i).asDouble() + 1 << " ";//要真正的使用Json对象，必须要先转化成C++的相应类型（使用asXxx成员函数）
	}
	
	getchar();
//以下是上面的程序的输出
/*
{"成绩":{"姓名":"AlexCui","语文":33.6,"数学":30,"理综":[50,60,70]}}
object
50
理综:[50,60,70]
数学:30
姓名:"AlexCui"
语文:33.6
51 61 71
*/
	return 0;
}
