template<typename T,long long mod>
struct mod_t{//mod只能是質數 
	T data;
	mod_t(){}
	mod_t(const T &d):data((d%mod+mod)%mod){}
	mod_t pow(T b)const{
		mod_t ans(1);
		for(mod_t now=*this;b;now=now*now,b/=2)
			if(b%2)ans=ans*now;
		return ans;
	}
	mod_t operator-(int)const{
		return mod_t(mod-data);
	}
	mod_t operator+(const mod_t &b)const{
		return mod_t((data+b.data)%mod);
	}
	mod_t operator-(const mod_t &b)const{
		return mod_t((data-b.data+mod)%mod);
	}
	mod_t operator*(const mod_t &b)const{
		return mod_t((data*b.data)%mod);
	}
	mod_t operator/(const mod_t &b)const{
		return *this*b.pow(mod-2);//*this * Inverse(b) 
	}
	operator T()const{return data;}
	friend istream &operator>>(istream &i,mod_t &b){
		T d;
		i>>d;
		b=mod_t(d);
		return i;
	}
};
