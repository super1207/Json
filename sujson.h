#ifndef __SUJSON_H__
#define __SUJSON_H__

#include<ostream>
#include<string>
#include<vector>
#include<map>

namespace SU {
	class Json
	{
	public:
		void JsonRead(const std::string &str);
		Json();
		Json(const std::string & str);
		Json(const std::vector<std::string> & vec);
		Json(const std::vector<Json> & vec);
		Json(const std::map<std::string, Json> & m);
		Json(double number);
		Json(int number);
		Json(void * null);
		Json(bool B);
		Json at(const std::string& key)const;
		Json at(size_t num)const;
		std::string type()const;
		int asInt()const;
		std::string asString()const;
		double asDouble()const;
		bool asBool()const;
		bool isNull()const;
		std::map<std::string, Json> asMap()const;
		std::vector<Json> asVec()const;
		Json & operator<<(const std::string & str);
		Json & operator>>(int & out);
		Json & operator>>(std::string & out);
		Json & operator>>(double & out);
		Json & operator>>(bool & out);
		Json & operator>>(void *& out);
		std::string toString()const;
		friend std::ostream& operator <<(std::ostream&, const Json&);
		std::vector<std::string> data;
	};
	std::ostream & operator<<(std::ostream &os, const Json  &ob);
}

#endif // !__SUJSON_H__
