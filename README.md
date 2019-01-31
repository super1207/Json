# sujson
[![badge](https://img.shields.io/badge/sujson%2F1.0.0-green.svg)](http://github.com/super1207/Json)

sujson是一个轻量级的C++JSON解析库，允许你通过简洁的步骤来解析Json，完全使用C++11标准库编写，无任何其它的依赖

##  文档

https://github.com/super1207/Json/doc

## 一个最简单的例子
  ```cpp
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
  }
  ```
  ### 快速运行这个例程
    git clone https://github.com/super1207/Json
    cd Json
    make
    make run
 ## 你可以通过以下方法来使用这个简洁的json库
 ### 方法一：从源码引用
 * 将sujson.cpp添加到你的工程源码中
 * 将sujson.h添加到你的工程包含目录
 * 在需要使用的地方#include "sujson.h"
 * 在需要的地方using namespace SU;
