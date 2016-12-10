template<typename T>
struct Matrix{
	using rt = std::vector<T>;
	using mt = std::vector<rt>;
	using matrix = Matrix<T>;
	int r,c;
	mt m;
	Matrix(int r,int c):r(r),c(c),m(r,rt(c)){}
	rt& operator[](int i){return m[i];}
	matrix operator+(const matrix &a){
		matrix rev(r,c);
		for(int i=0;i<r;++i)
			for(int j=0;j<c;++j)
				rev[i][j]=m[i][j]+a.m[i][j];
		return rev;
	}
	matrix operator-(const matrix &a){
		matrix rev(r,c);
		for(int i=0;i<r;++i)
			for(int j=0;j<c;++j)
				rev[i][j]=m[i][j]-a.m[i][j];
		return rev;
	}
	matrix operator*(const matrix &a){
		matrix rev(r,a.c);
		matrix tmp(a.c,a.r);
		for(int i=0;i<a.r;++i)
			for(int j=0;j<a.c;++j)
				tmp[j][i]=a.m[i][j];
		for(int i=0;i<r;++i)
			for(int j=0;j<a.c;++j)
				for(int k=0;k<c;++k)
					rev.m[i][j]+=m[i][k]*tmp[j][k];
		return rev;
	}
	bool inverse(){
		Matrix t(r,r+c);
		for(int y=0;y<r;y++){
			t.m[y][c+y] = 1;
			for(int x=0;x<c;++x)
				t.m[y][x]=m[y][x];
		}
		if( !t.gas() )
			return false;
		for(int y=0;y<r;y++)
			for(int x=0;x<c;++x)
				m[y][x]=t.m[y][c+x]/t.m[y][y];
		return true;
	}
	T gas(){
		vector<T> lazy(r,1);
		bool sign=false;
		for(int i=0;i<r;++i){
			if( m[i][i]==0 ){
				int j=i+1;
				while(j<r&&!m[j][i])j++;
				if(j==r)continue;
				m[i].swap(m[j]);
				sign=!sign;
			}
			for(int j=0;j<r;++j){
				if(i==j)continue;
				lazy[j]=lazy[j]*m[i][i];
				T mx=m[j][i];
				for(int k=0;k<c;++k)
					m[j][k]=m[j][k]*m[i][i]-m[i][k]*mx;
			}
		}
		T det=sign?-1:1;
		for(int i=0;i<r;++i){
			det = det*m[i][i];
			det = det/lazy[i];
			for(auto &j:m[i])j/=lazy[i];
		}
		return det;
	}
};
