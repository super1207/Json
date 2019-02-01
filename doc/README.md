* [sujson使用说明(v1\.0\.0)](#sujson%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8Ev100)
  * [怎样读取一个原始的json字符串](#%E6%80%8E%E6%A0%B7%E8%AF%BB%E5%8F%96%E4%B8%80%E4%B8%AA%E5%8E%9F%E5%A7%8B%E7%9A%84json%E5%AD%97%E7%AC%A6%E4%B8%B2)
    * [使用&lt;&lt;](#%E4%BD%BF%E7%94%A8)
    * [使用JsonRead 成员函数](#%E4%BD%BF%E7%94%A8jsonread-%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
  * [怎样获取一个Json对象的类型](#%E6%80%8E%E6%A0%B7%E8%8E%B7%E5%8F%96%E4%B8%80%E4%B8%AAjson%E5%AF%B9%E8%B1%A1%E7%9A%84%E7%B1%BB%E5%9E%8B)
  * [打印一个json对象](#%E6%89%93%E5%8D%B0%E4%B8%80%E4%B8%AAjson%E5%AF%B9%E8%B1%A1)
  * [Json对象的构建](#json%E5%AF%B9%E8%B1%A1%E7%9A%84%E6%9E%84%E5%BB%BA)
    * [从double或int构建](#%E4%BB%8Edouble%E6%88%96int%E6%9E%84%E5%BB%BA)
    * [从std::string构建](#%E4%BB%8Estdstring%E6%9E%84%E5%BB%BA)
    * [从bool构建](#%E4%BB%8Ebool%E6%9E%84%E5%BB%BA)
    * [从void \* 构建](#%E4%BB%8Evoid--%E6%9E%84%E5%BB%BA)
    * [从std::vector&lt;Json&gt; 构建](#%E4%BB%8Estdvectorjson-%E6%9E%84%E5%BB%BA)
    * [从std::map&lt;std::string,Json&gt;构建](#%E4%BB%8Estdmapstdstringjson%E6%9E%84%E5%BB%BA)
  * [如何将Json对象转化为具体的C\+\+中的类型](#%E5%A6%82%E4%BD%95%E5%B0%86json%E5%AF%B9%E8%B1%A1%E8%BD%AC%E5%8C%96%E4%B8%BA%E5%85%B7%E4%BD%93%E7%9A%84c%E4%B8%AD%E7%9A%84%E7%B1%BB%E5%9E%8B)
    * [转化为double或者int](#%E8%BD%AC%E5%8C%96%E4%B8%BAdouble%E6%88%96%E8%80%85int)
    * [转化为std::string](#%E8%BD%AC%E5%8C%96%E4%B8%BAstdstring)
    * [转化为bool](#%E8%BD%AC%E5%8C%96%E4%B8%BAbool)
    * [转化为null](#%E8%BD%AC%E5%8C%96%E4%B8%BAnull)
    * [转化为std::vector&lt;Json&gt;](#%E8%BD%AC%E5%8C%96%E4%B8%BAstdvectorjson)
    * [转化为std::map&lt;std::string,Json&gt;](#%E8%BD%AC%E5%8C%96%E4%B8%BAstdmapstdstringjson)
  * [sujson中的注释](#sujson%E4%B8%AD%E7%9A%84%E6%B3%A8%E9%87%8A)
  * [Json的子节点获取](#json%E7%9A%84%E5%AD%90%E8%8A%82%E7%82%B9%E8%8E%B7%E5%8F%96)
  * [更多细节](#%E6%9B%B4%E5%A4%9A%E7%BB%86%E8%8A%82)

# sujson使用说明(v1.0.0)

## 怎样读取一个原始的json字符串

###  使用`<<`

```cpp
#include"sujson.h"
#include<string>
using namespace std;
using namespace SU;
int main()
{
	string i;
	Json J;
	string str = R"(
	{
		"成绩":
				{
					"姓名":"AlexCui",
					"语文":33.6,
					"数学":123,
					"理综":[50,60,70]    
				}
	})";
	J  << str;  //使用 << 是一种简洁优雅的方式
}
```

### 使用`JsonRead` 成员函数

1. ```cpp
   #include"sujson.h"
   #include<string>
   using namespace std;
   using namespace SU;
   int main()
   {
   	string i;
   	Json J;
   	string str = R"(
   	{
   		"成绩":
   				{
   					"姓名":"AlexCui",
   					"语文":33.6,
   					"数学":123, 
   					"理综":[50,60,70]    
   				}
   	})";
   	J.JsonRead(str); //这与使用 <<  的方式无任何区别
   }
   ```

## 怎样获取一个Json对象的类型

```cpp
#include"sujson.h"
#include<string>
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	string str,jsonType;
	Json J;
	string str = R"(
	{
		"成绩":
				{
					"姓名":"AlexCui",
					"语文":33.6,
					"数学":123,
					"理综":[50,60,70]    
				}
	})";
	J.JsonRead(str); 
    jsonType = J.type();//在这里，jsonType为"object"。
    				  //type()成员函数有七种返回类型，分别为：
    				  //"object","array","string","null","true","false","number"
    				  //对应 Json 的七种类型
	cout << jsonType;  //打印:object
}
```

## 打印一个json对象

```cpp
#include"sujson.h"
#include<iostream>
#include<string>
using namespace std;
using namespace SU;
int main()
{
	string i;
	Json J;
	string str = R"(
	{
		"成绩":
				{
					"姓名":"AlexCui",
					"语文":33.6,
					"数学":123, //这是她的数学成绩
					"理综":[50,60,70]    
				}
	})";
	J.JsonRead(str);	
	cout << J;  //json对象可以直接使用cout来打印在控制台上，这于下面的语句等效：
	/*
		//这种方法不推荐，因为可能会与asString()产生歧义
		string out = J.toString();
		cout << out;  
	*/
	getchar();
}
```

## Json对象的构建

### 从`double`或`int`构建

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	double d = 3.25;
	Json J(d);  //从double类型构建Json对象
	cout << J;  //sujson底层采用std::to_string，这里输出：3.250000
}
```

### 从`std::string`构建

```cpp
#include"sujson.h"
#include<iostream>
#include<string>
using namespace std;
using namespace SU;
int main()
{
	string s = "Alexcui";
	Json J(s);  //从std::string类型构建Json对象
    /*
    	注意这里不能写为 Json J("Alexcui"); 因为"Alexcui"并不是std::string类型
    	应该写为 Json J(string("Alexcui"));
    */
	cout << J;  //这里输出："Alexcui"
}
```

### 从`bool`构建

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	bool b = true;
	Json J(b);  //从std::string类型构建Json对象
	cout << J;  //这里输出：true
}
```

### 从`void *` 构建

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	void * p = nullptr;  // 如果这里p不为nullptr,则行为未定义！！！注意！！
	Json J(p);  //从void *类型构建Json对象
	cout << J;	//这里输出：null
}
```

### 从`std::vector<Json>` 构建

```cpp
#include"sujson.h"
#include<iostream>
#include<vector>
using namespace std;
using namespace SU;
int main()
{
	vector<Json> vec{ Json(30),Json(string("40.4")),Json(50.5) };
	Json J(vec); 
	cout << J << endl; //输出：[30,"40.4",50.500000]
	return 0;
}
```

### 从`std::map<std::string,Json>`构建

```cpp
#include"sujson.h"
#include<iostream>
#include<map>
using namespace std;
using namespace SU;
int main()
{
	map<string, Json> mm{  {string("语文"),Json(30)},
							{string("数学"),Json(string("40.4"))}, 
							{string("外语"),Json(50.5)}
						 };
	Json J(mm); 
	cout << J << endl;  //输出：{"数学":"40.4","外语":50.500000,"语文":30}
	return 0;
}
```

除此之外，还可以从 `std::vector<std::string`>来构建任何类型的Json对象,但是这有些复杂，通常也用不到，所以在此不做详细说明。你可以通过阅读源码中了解这部分内容。

## 如何将Json对象转化为具体的C++中的类型

### 转化为`double`或者`int`

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	double d;
	Json J(3.25);  //从double类型构建Json对象
	d = J.asDouble();  //Json对象转化为double类型
    				  //相似的还有asInt()
	cout << d;  //这里输出：3.25
}
```

### 转化为`std::string`

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	string s;
	Json J(string("AlexCui"));  
	s = J.asString();  //Json对象转化为std::string类型
	cout << s;  		    // 这里输出：AlexCui
	cout << J;   		    //这里输出："AlexCui"
	cout << J.toString();  	//这里输出："AlexCui"
	//注意这三个cout的区别，通常情况下，我们需要的是第一个
}
```

### 转化为`bool`

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	bool b;
	Json J(false);  //从bool类型构建Json对象
	b = J.asBool();  //Json对象转化为bool类型
	cout << b;       		//这里输出0，如果是true，输出1
	cout << J;       		//这里输出：false
	cout << J.toString(); 	//这里输出：false
}
```

### 转化为`null`

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
	bool b;
	Json J(nullptr);  //从void*类型构建Json对象
	b = J.isNull();  //因为C++中并没有null类型，所以这个函数的作用是
    				//判断是否为空，返回的是bool型
	cout << b; 			//输出：1
	cout << J;			//输出：null
	cout << J.toString();//输出：null  
}
```

### 转化为`std::vector<Json>`

```cpp
#include"sujson.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;
using namespace SU;
int main()
{
	Json J;
	string str = R"(
		[50,"60",[80,44,66]]
	)";
	J.JsonRead(str);
	vector<Json> vec = J.asVec();  //Json对象转化为vector<Json>类型
	for (const Json & i : vec)
	{
		cout << i << " ";
	}
    //输出：50 "60" [80,44,66] 
}
```

### 转化为`std::map<std::string,Json>`

```cpp
#include"sujson.h"
#include<string>
#include<iostream>
#include<map>
using namespace std;
using namespace SU;
int main()
{
	Json J;
	string str = R"(
			{
				"姓名":"AlexCui",
				"语文":33.6,
				"数学":123,
				"理综":[50,60,70]    
			}
	)";
	J.JsonRead(str);
	map<string, Json> mm = J.asMap();
	for (const pair<string,Json> &i : mm)
	{
		cout << i.first << ":" << i.second << endl;
	}
    /*
    输出：理综:[50,60,70]
         数学:123
         姓名:"AlexCui"
         语文:33.6
         
    */
}
```

对于Json对象的转化，还有一种方式是使用 >> ,正如项目主页的README中的那样，但是那不作为推荐的方式,所以在此不做详细的介绍，如果你想这么做，可以自行阅读我的源代码。

## sujson中的注释

标准的Json文法并不支持注释，但是sujson支持单行注释，这是sujson的特色！！注释会在读入的时候被过滤掉。

```cpp
#include"sujson.h"
#include<string>
#include<iostream>
#include<map>
using namespace std;
using namespace SU;
int main()
{
	Json J;
	string str = R"(
			{
				"姓名":"AlexCui",
				"语文":33.6,
				"数学":123,  //我是注释！！！
				"理综":[50,60,70]    
			}
	)";
	J.JsonRead(str);
	map<string, Json> mm = J.asMap();
	for (const pair<string,Json> &i : mm)
	{
		cout << i.first << ":" << i.second << endl;
	}
	/*
    输出：理综:[50,60,70]
         数学:123
         姓名:"AlexCui"
         语文:33.6
         
    */
}
```



## Json的子节点获取

json对象的子节点也是Json对象，对于 object我们使用Json at(std::string)来获取，对于 array,我们使用Json at(size_t)来获取，下面我给出一个完整的例子：

```cpp
#include"sujson.h"
#include<iostream>
using namespace std;
using namespace SU;
int main()
{
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
	Json J; 
	J.JsonRead(str);
	cout << J.at("成绩").at("语文").asDouble() << endl;//这里输出：33.6
	cout << J.at("成绩").at("理综").at(1).asDouble() << endl;//这里输出：60
    //关于数组越界访问与访问不存在的key的说明：
    //数组越界，抛出与std::vector使用at访问相同的异常
    //key不存在，抛出与std::map使用at访问相同的异常
}
```

## 更多细节

* sujson通常不会对你的输入的正确性做检查，所以即使你错误输入，也不一定会抛出异常。
* Json对象一旦构建，基本可以认为是不变的，如果你想要修改，最好的办法是重新构建一个Json对象。
* Json对象的底层是一个`std::vector<std::string>` `data`，它保存了Json的经过词法分析后的原始数据，你可以通过直接修改它来构建任何你想要的Json对象,但是这不是通常的方法，你需要小心。
* sujson支持带单行注释`//`的非标准json,同样也能解析标准 json
