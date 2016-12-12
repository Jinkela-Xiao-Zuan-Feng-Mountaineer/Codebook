@echo off
if not exist ".MergeCodeBook.exe" (
    g++ -std=c++14 -O2 -o .MergeCodeBook.exe .MergeCodeBook.cpp
)
.MergeCodeBook.exe s
xelatex Codebook.tex