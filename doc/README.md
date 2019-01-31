# sujson使用说明

[TOC]

## 怎样读取一个原始的json字符串

###  使用<<

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
					"数学":123, //这是她的数学成绩
					"理综":[50,60,70]    
				}
	})";
	J  << str;  //使用 << 是一种简洁优雅的方式
}
```

### 使用JsonRead 成员函数

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
   					"数学":123, //这是她的数学成绩
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
					"数学":123, //这是她的数学成绩
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

### 从double构建

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

### 从std::string构建

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
	cout << J;  //这里输出："Alexcui"
}
```

### 从bool构建

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

### 从void * 构建

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

除此之外，还可以从 std::map构建object或者从std::vector构建array,但是这有些复杂，通常也用不到（一般可以使用前面所述的JsonRead成员函数来构建），所以在此不做详细说明。你可以从后面的例子或者通过阅读源码中了解这部分内容。

## 如何将Json对象转化为具体的C++中的类型

### 转化为double或者int

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

### 转化为std::string

```
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

### 转化为bool

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

### 转化为null

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

对于Json对象的转化，还有一种方式是使用 >> ,正如项目主页的README中的那样，但是那不作为推荐的方式,所以在此不做详细的介绍，如果你想这么做，可以自行阅读我的源代码。

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

## 数组的遍历

文档待完成。。。