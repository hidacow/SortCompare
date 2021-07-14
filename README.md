# SortCompare

 Project Repository for the Summer "Programming Training" Course

## **Introduction**

This program is a testing framework of different sorting algorithms.

## **Quick Start**

### **Open with Visual Studio(Recommended)**

This repository contains the VS2019 project file.

The easiest way to open this project is to install Visual Studio 2019 and open `SortCompare.sln`

### **Build**

If you wish to build this project with g++, you may

1. Clone/Download this repository
2. Open a shell/command line
3. Change directory to the project folder
4. Run the following line

Debug

```bash
g++ -Wl,--stack,33554432 -o SortCompare_debug.exe *.cpp *.h
```

Release (with O2 optimization)

```bash
g++ -O2 -Wl,--stack,33554432 -o SortCompare_release.exe *.cpp *.h
```

### **Notice**

- You must increase the program stack size in order to run this program properly.
- We tested building this program with MSVC(19.29.30038.1) and g++(8.1.0)
- The code(comments, output) contains Chinese
- Source files are encoded with GB2312
- You may not copy any part of this project and use it in your **SHU course project**

## **Group Members**

- 20122971
- 20123030
- 20123032
- 20123033
- 20123034
