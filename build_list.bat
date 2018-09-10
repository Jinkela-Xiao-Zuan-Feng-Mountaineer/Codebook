@echo off
if not exist "GenCodebookList.exe" (
    g++ -std=c++14 -O2 -o GenCodebookList.exe GenCodebookList.cpp
)
GenCodebookList.exe
