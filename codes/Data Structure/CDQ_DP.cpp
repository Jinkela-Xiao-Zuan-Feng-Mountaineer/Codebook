#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
struct node{
	double a,b,r,k,x,y;
	int id;
} p[MAXN];
double DP[MAXN];
deque<int> q;
bool cmpK(const node &a,const node &b){
	return a.k>b.k;
}
bool cmpX(const node &a,const node &b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
double Slope(int a,int b){
	if(!b) return -1e20;
	if(p[a].x==p[b].x) return 1e20;
	return (p[a].y-p[b].y)/(p[a].x-p[b].x);
}
void CDQ(int l, int r){
	if(l==r){
		DP[l] = max(DP[l],DP[l-1]);
		p[l].y = DP[l]/(p[l].a*p[l].r+p[l].b);
		p[l].x = p[l].y*p[l].r;
		return;
	}
	int mid = (l+r)/2;
	stable_partition(p+l,p+r+1,[&](const node &d){return d.id<=mid;});
	CDQ(l, mid); q.clear();
	for(int i=l, j; i<=mid; ++i){
		while((j=q.size())>1&&Slope(q[j-2],q[j-1])<Slope(q[j-1],i)) q.pop_back();
		q.push_back(i);
	}q.push_back(0);
	for(int i=mid+1; i<=r; ++i){
		while(q.size()>1&&Slope(q[0],q[1])>p[i].k) q.pop_front();
		DP[p[i].id] = max(DP[p[i].id], p[i].a*p[q[0]].x+p[i].b*p[q[0]].y);
	}
	CDQ(mid+1,r);
	inplace_merge(p+l,p+mid+1,p+r+1,cmpX);
}
double solve(int n,double S){
	DP[0] = S;
	sort(p+1,p+1+n,cmpK);
	CDQ(1,n);
	return DP[n];
}
int main(){
	int n; double S;
	scanf("%d%lf",&n,&S);
	for(int i=1; i<=n; ++i){
		scanf("%lf%lf%lf",&p[i].a,&p[i].b,&p[i].r);
		p[i].id = i, p[i].k = -p[i].a/p[i].b;
	}
	printf("%.3lf\n",solve(n,S));
	return 0;
}