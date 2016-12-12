inline int read(){
    int x=0; bool f=0; char c=getchar();
    while(ch<'0'||'9'<ch)f|=ch=='-',ch=getchar();
    while('0'<=ch&&ch<='9')x=x*10-'0'+ch,ch=getchar();
    return f?-x:x;
}
//  !/bin/bash
//  g++ -std=c++11 -O2 -Wall -Wextra -Wno-unused-variable -DDEBUG $1 && ./a.out
