#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct _RefCounter{
	T data;
	int ref;
	_RefCounter(const T&d=0):data(d),ref(0){}
};
template<typename T>
struct reference_pointer{
	_RefCounter<T> *p;
	T *operator->(){return &(*p).data;}
	T &operator*(){return p->data;}
	operator int(){return(int)(long long)p;}
	reference_pointer&operator=(const reference_pointer &t){
		if(p&&--(*p).ref==0)delete p;
		p=t.p;
		p&&++(*p).ref;
		return*this;
	}
	reference_pointer(_RefCounter<T> *t=0):p(t){
		p&&++(*p).ref;
	}
	reference_pointer(const reference_pointer &t):p(t.p){
		p&&++(*p).ref;
	}
	~reference_pointer(){
		if(p&&--(*p).ref==0)delete p;
	}
};
template<typename T>
inline const reference_pointer<T> new_reference(const T&nd){
	return reference_pointer<T>(new _RefCounter<T>(nd));
}
struct P{
	int a,b;
	P(int A,int B):a(A),b(B){}
}p(2,3);
int main(){
	reference_pointer<int >b=new_reference(int(5));
	reference_pointer<int >a=new_reference(*b);
	reference_pointer<P >c=new_reference(p);
	return 0;
}

