# CMakeList.txt: GosVM 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("GosVM" VERSION 0.1.0 LANGUAGES C)

# 编译GosVM
add_library(GosVM STATIC "GosVM.c" "Stack.c")


# 测试用例
add_executable (GosVMTest "Test.c" "GosVM.c" "Stack.c")

# TODO: 如有需要，请添加测试并安装目标。
