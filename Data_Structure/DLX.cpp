#define MAXN 4100
#define MAXM 1030
#define MAXND 16390
struct DLX{
	int n,m,sz,ansd;//高是n，寬是m的稀疏矩陣 
	int S[MAXM],H[MAXN];
	int row[MAXND],col[MAXND];//每個節點代表的列跟行 
	int L[MAXND],R[MAXND],U[MAXND],D[MAXND];
	vector<int> ans,anst;
	void init(int _n,int _m){
		n=_n,m=_m;
		for(int i=0;i<=m;++i){
			U[i]=D[i]=i,L[i]=i-1,R[i]=i+1;
			S[i]=0;
		}
		R[m]=0,L[0]=m;
		sz=m,ansd=INT_MAX;//ansd存最優解的個數 
		for(int i=1;i<=n;++i)H[i]=-1;
	}
	void add(int r,int c){ 
		++S[col[++sz]=c];
		row[sz]=r;
		D[sz]=D[c],U[D[c]]=sz,U[sz]=c,D[c]=sz;
		if(H[r]<0)H[r]=L[sz]=R[sz]=sz;
		else R[sz]=R[H[r]],L[R[H[r]]]=sz,L[sz]=H[r],R[H[r]]=sz;
	}
	#define DFOR(i,A,s) for(int i=A[s];i!=s;i=A[i])
	void remove(int c){//刪除第c行和所有當前覆蓋到第c行的列 
		L[R[c]]=L[c],R[L[c]]=R[c];//這裡刪除第c行，若有些行不需要處理可以在開始時呼叫他 
		DFOR(i,D,c)DFOR(j,R,i){U[D[j]]=U[j],D[U[j]]=D[j],--S[col[j]];}
	}
	void restore(int c){//恢復第c行和所有當前覆蓋到第c行的列，remove的逆操作 
		DFOR(i,U,c)DFOR(j,L,i){++S[col[j]],U[D[j]]=j,D[U[j]]=j;}
		L[R[c]]=c,R[L[c]]=c;
	}
	void remove2(int nd){//刪除nd所在的行當前所有點(包括虛擬節點)，只保留nd 
		DFOR(i,D,nd)L[R[i]]=L[i],R[L[i]]=R[i];
	}
	void restore2(int nd){//刪除nd所在的行當前所有點，為remove2的逆操作 
		DFOR(i,U,nd)L[R[i]]=R[L[i]]=i;
	}
	bool vis[MAXM];
	int h(){//估價函數 for IDA*
		int res=0;
		memset(vis,0,sizeof(vis));
		DFOR(i,R,0)if(!vis[i]){
			vis[i]=1;
			++res;
			DFOR(j,D,i)DFOR(k,R,j)vis[col[k]]=1;
		}
		return res;
	}
	bool dfs(int d){//for精確覆蓋問題 
		if(d+h()>=ansd)return 0;//找最佳解用，找任意解可以刪掉 
		if(!R[0]){ansd=d;return 1;}
		int c=R[0];
		DFOR(i,R,0)if(S[i]<S[c])c=i;
		remove(c);
		DFOR(i,D,c){
			ans.push_back(row[i]);
			DFOR(j,R,i)remove(col[j]);
			if(dfs(d+1))return 1;
			ans.pop_back();
			DFOR(j,L,i)restore(col[j]);
		}
		restore(c);
		return 0;
	}
	void dfs2(int d){//for最小重複覆蓋問題 
		if(d+h()>=ansd)return;
		if(!R[0]){ansd=d;ans=anst;return;}
		int c=R[0];
		DFOR(i,R,0)if(S[i]<S[c])c=i;
		DFOR(i,D,c){
			anst.push_back(row[i]);
			remove2(i);
			DFOR(j,R,i)remove2(j),--S[col[j]];
			dfs2(d+1);
			anst.pop_back();
			DFOR(j,L,i)restore2(j),++S[col[j]];
			restore2(i);
		}
	}
	bool exact_cover(){//解精確覆蓋問題 
		ans.clear();//答案存在ans裡 
		return dfs(0);
	}
	void min_cover(){//解最小重複覆蓋問題 
		anst.clear();//這只是暫存用，答案還是存在ans裡 
		dfs2(0);
	}
	#undef DFOR
};
