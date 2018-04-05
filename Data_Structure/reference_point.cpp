template<typename T>
struct _RefC{
	T data;
	int ref;
	_RefC(const T&d=0):data(d),ref(0){}
};
template<typename T>
struct _rp{
	_RefC<T> *p;
	T *operator->(){return &p->data;}
	T &operator*(){return p->data;}
	operator _RefC<T>*(){return p;}
	_rp &operator=(const _rp &t){
		if(p&&!--p->ref)delete p;
		p=t.p,p&&++p->ref;
		return *this;
	}
	_rp(_RefC<T> *t=0):p(t){p&&++p->ref;}
	_rp(const _rp &t):p(t.p){p&&++p->ref;}
	~_rp(){if(p&&!--p->ref)delete p;}
};
template<typename T>
inline _rp<T> new_rp(const T&nd){
	return _rp<T>(new _RefC<T>(nd));
}