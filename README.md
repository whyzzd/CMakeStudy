## CMake学习笔记(第一部分，Linux平台下)

#### 编写最简单的CMake文件

1.在同一目录下创建CMakeLists.txt文件和所需的要编译的文件

2.CMake中的内容如下：

```
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (Demo1)
# 指定生成目标
add_executable(Demo main.cc)
```

3.在当前目录下执行cmake . ;之后再使用make文件进行编译，则可以得到可执行文件

4.可通过./执行文件；

#### **当多个文件时，可修改位以下形式**

```
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

#指定生成目标
add_executable(Demo ${DIR_SRCS})
```

#### **当有多个目录时，类似下面结构**

```
./Demo3
    |
    +--- main.cc
    |
    +--- math/
          |
          +--- MathFunctions.cc
          |
          +--- MathFunctions.h

```

1.此时需要写两个CMakeLists.txt文件

2.可将math中的文件编译成静态库进行，再有根目录下的main调用

根目录下的CMakeLists.txt文件代码

```
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo3)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加 math 子目录
add_subdirectory(math)

# 指定生成目标 
add_executable(Demo main.cc)

# 添加链接库
target_link_libraries(Demo MathFunctions)
```

子目录下的CMakeLists.txt文件代码

```
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (MathFunctions ${DIR_LIB_SRCS})
```

