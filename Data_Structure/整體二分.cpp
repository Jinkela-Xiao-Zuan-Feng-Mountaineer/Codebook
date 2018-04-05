void totBS(int L, int R, vector<Item> M){
	if(Q.empty()) return; //維護全域B陣列
	if(L==R) 整個M的答案=r, return;
	int mid = (L+R)/2;
	vector<Item> mL, mR;
	do_modify_B_with_divide(mid,M);
	//讓B陣列在遞迴的時候只會保留[L~mid]的資訊
	undo_modify_B(mid,M);
	totBS(L,mid,mL);
	totBS(mid+1,R,mR);
}
