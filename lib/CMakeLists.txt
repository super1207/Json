CMAKE_MINIMUM_REQUIRED(VERSION 2.8)  

#添加包含目录
include_directories(../include)

#添加源文件
SET(LIB_SRC ../src/sujson.cpp)  

#添加静态库  
ADD_LIBRARY(sujson_static STATIC ${LIB_SRC})  

#将静态库重新命名为sujson
SET_TARGET_PROPERTIES(sujson_static PROPERTIES OUTPUT_NAME sujson)