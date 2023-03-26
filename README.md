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

*以上对应demo1.*

#### **自定义编译选项**

1.修改根目录下的CMakeLists.txt文件

```c++
# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo4)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

# 是否使用自己的 MathFunctions 库
option (USE_MYMATH
       "Use provided math implementation" ON)

# 是否加入 MathFunctions 库
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/math")
  add_subdirectory (math)  
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
target_link_libraries (Demo  ${EXTRA_LIBS})
```

其中：

- 第7行的 `configure_file` 命令用于加入一个配置头文件 config.h(自动生成) ，这个文件由 CMake 从 config.h.in 生成，通过这样的机制，将可以通过预定义一些参数和变量来控制代码的生成。

- 第13行的 `option` 命令添加了一个 `USE_MYMATH` 选项，并且默认值为 `ON` (注意设置值时，清理以下文件夹，否则可能无效)。

- 第17行根据 `USE_MYMATH` 变量的值来决定是否使用我们自己编写的 MathFunctions 库。

2.生成makefile文件可以专门弄一个文件夹进行存放生成的的文件(需要注意源文件中头文件中包含路径)：可在根目录下创建build文件夹，进入build文件夹后输入`cmake ..`即可在此文件夹下生成make文件，然后执行`make`命令即可完成编译，`./Demo 参数1 参数2`完成调用。	

*以上对应demo2.*

#### **定制安装规则**

1.首先先在 math/CMakeLists.txt 文件里最后添加下面两行：

```
# 指定 MathFunctions 库的安装路径
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
```

指明 MathFunctions 库的安装路径。之后同样修改根目录的 CMakeLists 文件，在末尾添加下面几行：

```
# 指定安装路径
install (TARGETS Demo DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h"
         DESTINATION include)
```

2.在修改之后，执行`cmake ..`，然后执行`sudo make install`，即可将文件安装至`/usr/local/bin和/usr/local/include`(目录有可能略有不同)，此时不需要带目录就可以执行程序。

*以上对应demo3*

#### **为工程添加测试**

1.在CMakeLists中添加以下代码：

```
# 启用测试
enable_testing()

# 测试程序是否成功运行
add_test (test_run Demo 5 2)

# 测试帮助信息是否可以正常提示
add_test (test_usage Demo)
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "参数错误")

# 定义一个宏，用来简化测试工作
macro (do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} Demo ${arg1} ${arg2})
  set_tests_properties (test_${arg1}_${arg2}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
 
# 使用该宏进行一系列的数据测试
do_test (5 2 "=25")
do_test (10 5 "=100000")
do_test (2 10 "=1024")
```

2.在build文件夹中编译之后，使用`make test`可开始进行测试

*以上对应demo4*

#### **生成安装包**

1.首先在顶层的 CMakeLists.txt 文件尾部添加下面几行：

```
# 构建一个 CPack 安装包
include (InstallRequiredSystemLibraries)
# 这是可生成的安装的版本号信息                       
set(CPACK_PACKAGE_VERSION "1.0.0") 
include (CPack)
```

- 生成二进制安装包命令：

```
cpack -C CPackConfig.cmake
```

- 生成源码安装包

```
cpack -C CPackSourceConfig.cmake
```

2.若执行`cpack -C CPackConfig.cmake`则会在当前目录下生成3个不同格式的二进制包文件

```
xxx@xxx-virtual-machine:~/2023/month3/demo5/build$ ls Demo5-*
Demo5-1.0.0-Linux.sh  Demo5-1.0.0-Linux.tar.gz  Demo5-1.0.0-Linux.tar.Z
```

3.此时可以使用`sh Demo5-1.0.0-Linux.sh `安装到当前目录

4.安装完成可以执行以下命令查看结果

```
xxx@xxx-virtual-machine:~/2023/month3/demo5/build$ ./Demo5-1.0.0-Linux/bin/Demo  5 2
Now we use the standard library. 
5^2=25
```

*以上对应demo5*
