void dq(int l,int r){
	if(l==r)return;
	int mid=(l+r)/2;
	dq(l,mid);
	處理[l,mid]的操作對[mid+1,r]的影響 
	dq(mid+1,r);
}
