#include<iostream>
#include<string>
#include<vector>
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
			} while ((str.at(i) <= '9'&& str.at(i) >= 0) || str.at(i) == '-'|| str.at(i) == '.');
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
int main()
{
	string str = R"(
{
    "employees": [
{ "fir\"stName":"Bill" , "last Name":"Gates" },

{ " firstName":false ,      "lastName":33.5 },

{ "firstName":"trues" , "lastName":"Carter" }

]
})";
	
	auto ret = DFA(str);
	for (auto i : ret)
	{
		cout << i ;
	}
	getchar();
	return 0;
}
