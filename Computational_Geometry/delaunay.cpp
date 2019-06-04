template<class T>
class Delaunay{
	struct PT:public point<T>{
		int g[2];
		PT(const point<T> &p):
			point<T>(p){ g[0]=g[1]=-1; }
	};
	static bool cmp(const PT &a,const PT &b){
		return a.x<b.x||(a.x==b.x&&a.y<b.y);
	}
	struct edge{
		int v,g[2];
		edge(int v,int g0,int g1):
			v(v){g[0]=g0,g[1]=g1;}
	};
	vector<PT> S;
	vector<edge> E;
	bool convex(int &from,int to,T LR){
		for(int i=0;i<2;++i){
			int c = E[S[from].g[i]].v;
			auto A=S[from]-S[to], B=S[c]-S[to];
			T v = A.cross(B)*LR;
			if(v>0||(v==0&&B.abs2()<A.abs2()))
				return from = c, true;
		}
		return false;
	}
	void addEdge(int v,int g0,int g1){
		E.emplace_back(v,g0,g1);
		E[E.back().g[0]].g[1] = E.size()-1;
		E[E.back().g[1]].g[0] = E.size()-1;
	}
	void climb(int &p, int e, int n, int nl, int nr, int LR){
		for(int i=E[e].g[LR]; (S[nr]-S[nl]).cross(S[E[i].v]-S[n])>0;){
			if(inCircle(S[E[i].v],S[nl],S[nr],S[E[E[i].g[LR]].v])>=0)
				{ p = i; break; }
			for(int j=0;j<4;++j)
				E[E[i^j/2].g[j%2^1]].g[j%2] = E[i^j/2].g[j%2];
			int j=i; i=E[i].g[LR];
			E[j].g[0]=E[j].g[1]=E[j^1].g[0]=E[j^1].g[1]=-1;
		}
	}
	T det3(T a11,T a12,T a13,T a21,T a22,T a23,T a31,T a32,T a33){
		return a11*(a22*a33-a32*a23)-a12*(a21*a33-a31*a23)+a13*(a21*a32-a31*a22);
	}
	int inCircle(const PT &a, const PT &b, const PT &c, const PT &p){
T as = a.abs2(), bs = b.abs2(), cs = c.abs2(), ps = p.abs2();
T res = a.x * det3(b.y,bs,1,c.y,cs,1,p.y,ps,1)
-a.y * det3(b.x,bs,1,c.x,cs,1,p.x,ps,1)
+as * det3(b.x,b.y,1,c.x,c.y,1,p.x,p.y,1)
-det3(b.x,b.y,bs,c.x,c.y,cs,p.x,p.y,ps);
		return res<0 ? 1 : (res>0 ? -1 : 0);
	}
	void divide(int l, int r){
		if(l>=r)return;
		if(l+1==r){
			int A=S[l].g[0]=S[l].g[1]=E.size();
			E.emplace_back(r,A,A);
			int B=S[r].g[0]=S[r].g[1]=E.size();
			E.emplace_back(l,B,B);
			return;
		}
		int mid = (l+r)/2;
		divide(l,mid), divide(mid+1, r);
		int nl = mid, nr = mid+1;
		for(;;){
			if(convex(nl,nr,1)) continue;
			if(S[nr].g[0]!=-1&&convex(nr,nl,-1)) continue;
			break;
		}
		addEdge(nr,S[nl].g[0],S[nl].g[1]);
		S[nl].g[1] = E.size()-1;
		if(S[nr].g[0]==-1){
			addEdge(nl,E.size(),E.size());
			S[nr].g[1] = E.size()-1;
		}else addEdge(nl,S[nr].g[0],S[nr].g[1]);
		S[nr].g[0] = E.size()-1;
		int cl = nl, cr = nr;
		for(;;){
			int pl=-1, pr=-1, side;
			climb(pl,E.size()-2,nl,nl,nr,1);
			climb(pr,E.size()-1,nr,nl,nr,0);
			if(pl==-1&&pr==-1) break;
			if(pl==-1||pr==-1) side = pl==-1;
			else side=inCircle(S[E[pl].v],S[nl],S[nr],S[E[pr].v])<=0;
			if(side){
nr = E[pr].v;
addEdge(nr,E.size()-2,E[E.size()-2].g[1]);
addEdge(nl,E[pr^1].g[0],pr^1);
			}else{
nl = E[pl].v;
addEdge(nr,pl^1,E[pl^1].g[1]);
addEdge(nl,E[E.size()-2].g[0],E.size()-2);
			}
		}
		if(cl==nl&&cr==nr) return;//Collinearity
		S[nl].g[0] = E.size()-2;
		S[nr].g[1] = E.size()-1;
	}
public:
	void solve(const vector<point<T>> &P){
		S.clear(), E.clear();
		for(const auto &p:P) S.emplace_back(p);
		sort(S.begin(),S.end(),cmp);
		divide(0,int(S.size())-1);
	}
	vector<pair<int,int>> getEdge(){
		vector<pair<int,int>> res;
		for(size_t i=0;i<E.size();i+=2)
			if(E[i].g[0]!=-1)
				res.emplace_back(E[i].v,E[i^1].v);
		return res;
	}
};