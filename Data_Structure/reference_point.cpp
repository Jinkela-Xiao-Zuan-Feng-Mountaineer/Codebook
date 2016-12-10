#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct _RefCounter{
	T data;
	int ref;
	_RefCounter(const T&d=0):data(d),ref(0){}
};
template<typename T>
struct ref_pointer{
	_RefCounter<T> *p;
	T *operator->(){return &(*p).data;}
	T &operator*(){return p->data;}
	operator int(){return(int)(long long)p;}
	ref_pointer&operator=(const ref_pointer &t){
		if(p&&--(*p).ref==0)delete p;
		p=t.p;
		p&&++(*p).ref;
		return*this;
	}
	ref_pointer(_RefCounter<T> *t=0):p(t){
		p&&++(*p).ref;
	}
	ref_pointer(const ref_pointer &t):p(t.p){
		p&&++(*p).ref;
	}
	~ref_pointer(){
		if(p&&--(*p).ref==0)delete p;
	}
};
template<typename T>
inline const ref_pointer<T> new_ref(const T&nd){
	return ref_pointer<T>(new _RefCounter<T>(nd));
}
struct P{
	int a,b;
	P(int A,int B):a(A),b(B){}
}p(2,3);
int main(){
	ref_pointer<int>b=new_ref(int(5));
	ref_pointer<int>a=new_ref(*b);
	ref_pointer<P>c=new_ref(p);
	return 0;
}

