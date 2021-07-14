本项目推荐由VisualStudio2019打开

本项目采用C++11标准，无法在老版编译器上编译
编译时需要增加stack大小
测试环境
GNU GCC: g++.exe
g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
MSVC: cl.exe
用于 x86 的 Microsoft (R) C/C++ 优化编译器 19.29.30038.1 版

若使用g++进行编译，可以通过以下命令进行手动编译
Debug(不进行优化):
g++  -Wl,--stack,33554432 -o SortCompare_debug.exe MyRand.cpp MyRand.h score.cpp score.h SortCompare.cpp SortCompare.h Sorts.h SortString.cpp Test.cpp Test.h
Release(O2优化):
g++ -O2 -Wl,--stack,33554432 -o SortCompare_release.exe MyRand.cpp MyRand.h score.cpp score.h SortCompare.cpp SortCompare.h Sorts.h SortString.cpp Test.cpp Test.h