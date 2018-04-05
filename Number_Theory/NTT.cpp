2615053605667*(2^18)+1,3
15*(2^27)+1,31
479*(2^21)+1,3
7*17*(2^23)+1,3
3*3*211*(2^19)+1,5
25*(2^22)+1,3
template<typename T,typename VT=vector<T> >
struct NTT{
	const T P,G;
	NTT(T p=(1<<23)*7*17+1,T g=3):P(p),G(g){}
	unsigned bit_reverse(unsigned a,int len){
		//look FFT.cpp
	}
	T pow_mod(T n,T k,T m){
		T ans=1;
		for(n=(n>=m?n%m:n);k;k>>=1){
			if(k&1)ans=ans*n%m;
			n=n*n%m;
		}
		return ans;
	}
	void ntt(bool is_inv,VT &in,VT &out,int N){
		int bitlen=__lg(N);
		for(int i=0;i<N;++i)out[bit_reverse(i,bitlen)]=in[i];
		for(int step=2,id=1;step<=N;step<<=1,++id){
			T wn=pow_mod(G,(P-1)>>id,P),wi=1,u,t;
			const int mh=step>>1;
			for(int i=0;i<mh;++i){
				for(int j=i;j<N;j+=step){
					u=out[j],t=wi*out[j+mh]%P;
					out[j]=u+t;
					out[j+mh]=u-t;
					if(out[j]>=P)out[j]-=P;
					if(out[j+mh]<0)out[j+mh]+=P;
				}
				wi=wi*wn%P;
			}
		}
		if(is_inv){
			for(int i=1;i<N/2;++i)swap(out[i],out[N-i]);
			T invn=pow_mod(N,P-2,P);
			for(int i=0;i<N;++i)out[i]=out[i]*invn%P;
		}
	}
};
