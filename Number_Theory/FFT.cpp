template<typename T,typename VT=std::vector<std::complex<T> > >
struct FFT{
	const T pi;
	FFT(const T pi=acos((T)-1)):pi(pi){}
	unsigned int bit_reverse(unsigned int a,int len){
		a=((a&0x55555555U)<<1)|((a&0xAAAAAAAAU)>>1);
		a=((a&0x33333333U)<<2)|((a&0xCCCCCCCCU)>>2);
		a=((a&0x0F0F0F0FU)<<4)|((a&0xF0F0F0F0U)>>4);
		a=((a&0x00FF00FFU)<<8)|((a&0xFF00FF00U)>>8);
		a=((a&0x0000FFFFU)<<16)|((a&0xFFFF0000U)>>16);
		return a>>(32-len);
	}
	void fft(bool is_inv,VT &in,VT &out,int N){
		int bitlen=std::__lg(N),num=is_inv?-1:1;
		for(int i=0;i<N;++i)out[bit_reverse(i,bitlen)]=in[i];
		for(int step=2;step<=N;step<<=1){
			const int mh=step>>1;
			for(int i=0;i<mh;++i){
				std::complex<T> wi=exp(std::complex<T>(0,i*num*pi/mh));
				for(int j=i;j<N;j+=step){
					int k=j+mh;
					std::complex<T> u=out[j],t=wi*out[k];
					out[j]=u+t;
					out[k]=u-t;
				}
			}
		}
		if(is_inv)for(int i=0;i<N;++i)out[i]/=N;
	}
};
