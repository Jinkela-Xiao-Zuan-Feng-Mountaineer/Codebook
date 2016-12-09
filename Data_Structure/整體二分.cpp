void BS(int l,int r,vector<Item> &vs){
	//答案該<l會有的已經做完了 
	if(l==r)整個vs的答案=l;//??????
	int mid=(l+r)/2;
	do_thing(l,mid);//做答案<=mid會做的事 
	vector<Item> left=vs裡滿足的; 
	vector<Item> right=vs-left;
	undo_thing(l,mid);
	BS(l,mid,left);
	do_thing(l,mid);
	BS(mid+1,r,right);//??????
}
