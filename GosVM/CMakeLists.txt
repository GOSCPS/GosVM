# CMakeList.txt: GosVM 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("GosVM" VERSION 1.0.0 LANGUAGES C CXX)

# 编译GosVM
add_library(GosVM STATIC "GosVM.c" "Stack.c")

# 编译器
add_executable (GosVMCompiler "Gos.cpp" "GosVM.c" "Stack.c")

# 虚拟机
add_executable(Gos "VM.cpp"  "GosVM.c" "Stack.c")

# TODO: 如有需要，请添加测试并安装目标。
