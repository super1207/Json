# sujson
[![badge](https://img.shields.io/badge/sujson%2F1.0.0-green.svg)](http://github.com/super1207/Json)

sujson是一个轻量级的C++JSON解析库，允许你通过简洁的步骤来解析Json，完全使用C++11标准库编写，无任何其它的依赖

##  文档

https://github.com/super1207/Json/tree/master/doc

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
    暂缺
 ## 你可以通过以下方法来使用这个简洁的json库
 ### 方法一：从源码引用
 * 将sujson.cpp添加到你的工程源码中
 * 将sujson.h添加到你的工程包含目录

### 方法二：构建静态链接库以使用sujson

* 首先，你需要确保你的环境中有CMake、Git、和一个支持C++11标准的编译器

* 然后，执行以下命令：

  ```shell
  git clone https://github.com/super1207/Json.git
  ```

* 之后，你可以使用CMake来构建VS工程或者mingw-Makefile

* 编译出静态链接库，得到sujson.lib(libjson.a)
* 在你的项目中链接上一步生成的静态链接库
* 在你的项目中包含include文件夹