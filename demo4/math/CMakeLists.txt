# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (MathFunction ${DIR_LIB_SRCS})

# 指定 MathFunction 库的安装路径
install (TARGETS MathFunction DESTINATION bin)
install (FILES MathFunction.h DESTINATION include)

