#include "sujson.h"
#include <cstdlib>
using namespace std;
namespace SU
{
	vector<string> JsonFromStr(const string & str)
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
				i += 4;
			}
			else if (str.at(i) == 'f')
			{
				ret.push_back("false");
				i += 5;
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
				} while ((str.at(i) <= '9'&& str.at(i) >= '0') || str.at(i) == '-' || str.at(i) == '.');
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
			else if (str.at(i) == '/')
			{
				while (str.at(i++) != '\n');
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
		map<string, vector<string>> ret;
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
						key = vec.at(i - 1).substr(1, vec.at(i - 1).length() - 2);
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
		for (size_t i = 0; i < vec.size(); ++i)
		{
			ret.append(vec.at(i));
		}
		return ret;
	}


	void SU::Json::JsonRead(const string &str)
	{
		this->data = JsonFromStr(str);
	}
	SU::Json::Json()
	{
		data.push_back("null");
	}
	SU::Json::Json(const string & str)
	{
		data.push_back("\""+str+"\"");
	}
	SU::Json::Json(const vector<string> & vec)
	{
		this->data = vec;
	}
	SU::Json::Json(const vector<SU::Json> & vec)
	{
		data.push_back("[");
		if (vec.size() > 0)
		{
			for (size_t i = 0; i < vec.size() - 1; ++i)
			{
				data.insert(data.end(), vec.at(i).data.begin(), vec.at(i).data.end());
				data.push_back(",");
			}
			data.insert(data.end(), vec.at(vec.size() - 1).data.begin(), \
				vec.at(vec.size() - 1).data.end());
		}
		data.push_back("]");
	}
	SU::Json::Json(const std::map<std::string, Json> & m)
	{
		data.push_back("{");
		if (m.size() > 0)
		{
			map<string, Json>::const_iterator it;
			for (it = m.begin(); it != m.end(); ++it)
			{
				data.push_back("\"" + it->first + "\"");
				data.push_back(":");
				data.insert(data.end(), it->second.data.begin(), it->second.data.end());
				data.push_back(",");
			}
			data.pop_back();
		}
		data.push_back("}");
	}
	SU::Json::Json(double number)
	{
		data.push_back(to_string(number));
	}
	Json::Json(int number)
	{
		data.push_back(to_string(number));
	}
	SU::Json::Json(bool B)
	{
		data.push_back(B ? "true" : "false");
	}
	SU::Json::Json(const char * str)
	{
		data.push_back("\"" + std::string(str) + "\"");
	}
	Json SU::Json::at(const string& key)const
	{
		return jsonObject(data).at(key);
	}
	Json SU::Json::at(size_t num)const
	{
		return jsonArray(data).at(num);
	}
	string SU::Json::type()const
	{
		return jsonType(data);
	}
	int SU::Json::asInt()const
	{
		return atoi(data.at(0).c_str());
	}
	string SU::Json::asString()const
	{
		return data.at(0).substr(1, data.at(0).length()-2);
	}
	double SU::Json::asDouble()const
	{
		return atof(data.at(0).c_str());
	}
	bool SU::Json::asBool()const
	{
		return (data.at(0) == "true" ? true : false);
	}
	bool SU::Json::isNull()const
	{
		return (data.at(0) == "null");
	}
	map<string, SU::Json> SU::Json::asMap()const
	{
		map<string, vector<string>> mmp = jsonObject(data);
		map<string, SU::Json> ret;
		for (auto & it: mmp)
		{
			ret.insert({ std::move(it.first), std::move(it.second) });
		}
		return ret;
	}
	vector<SU::Json> SU::Json::asVec()const
	{
		
		vector<vector<string>> arr = jsonArray(data);
		vector<SU::Json> ret(arr.size());
		for (size_t i = 0; i < arr.size(); ++i)
		{
			ret.at(i).data = std::move(arr.at(i));
		}
		return ret;
	}
	string SU::Json::toString()const
	{
		return jsonToStr(data);
	}
	std::string Json::formatString()
	{
		string t = "";
		string ret = "";
		for (const string & i : this->data)
		{
			
			if (i == "{" || i == "[")
			{
				if(ret.size()!=0)ret.append("\n");
				
				ret.append(t+i);
				t.push_back('\t');
				ret.append('\n'+t);
			}
			else if (i == "}" || i == "]")
			{
				t.pop_back();
				ret.append('\n'+t + i);
			}
			else if (i == ",")
			{
				ret.append(i+'\n'+t);
			}
			else
			{
				ret.append(i);
			}
		}
		return ret;
	}
	SU::Json & SU::Json::operator<<(const std::string & str)
	{
		this->JsonRead(str);
		return *this;
	}
	SU::Json & SU::Json::operator>>(int & out)
	{
		out = this->asInt();
		return *this;
	}
	SU::Json & SU::Json::operator>>(std::string & out)
	{
		out = this->asString();
		return *this;
	}
	SU::Json & SU::Json::operator>>(double & out)
	{
		out = this->asDouble();
		return *this;
	}
	SU::Json & SU::Json::operator>>(bool & out)
	{
		out = this->asBool();
		return *this;
	}
	SU::Json & SU::Json::operator>>(void * & out)
	{
		out = (this->isNull() ? nullptr : (void*)1);
		return *this;
	}
	ostream & operator<<(ostream &os, const SU::Json  &ob)
	{
		os << ob.toString();
		return os;
	}
}




