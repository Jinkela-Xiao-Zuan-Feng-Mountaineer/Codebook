void XORtransform(LL *P,int k=log,bool inv=0){
	for(int len=1;2*len<=(1<<k);len<<=1)
		for(int i=0;i<(1<<k);i+=2*len)
			for (int j=0;j<len;++j){
				LL u=P[i+j],v=P[i+len+j];
				P[i+j]=u+v,P[i+len+j]=u-v;
			}
	if(inv)for(int i=0;i<(1<<k);++i)P[i]/=(1<<k);
}
void ANDtransform(LL *P,int k=log,bool inv=0){
	for(int len=1;2*len<=(1<<k);len<<=1)
		for(int i=0;i<(1<<k);i+=2*len)
			for(int j=0;j<len;++j){
				LL u=P[i+j],v=P[i+len+j];
				if(!inverse){
					P[i+j]=v,P[i+len+j]=u+v;
					//P[i+j]=u,P[i+len+j]=u+v; OR version
				}else{
					P[i+j]=-u+v,P[i+len+j]=u;
					//P[i+j]=u,P[i+len+j]=v-u; OR version
				}
			}
}