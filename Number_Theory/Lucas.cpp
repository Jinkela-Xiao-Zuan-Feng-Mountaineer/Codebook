int mod_fact(int n,int &e){
    e=0;
    if(n==0)return 1;
    // (n/p)! % p
    int res=mod_fact(n/P,e);
    e += n/P; 
    if( (n/P) %2 == 0){// = 1
        return res*fact[n%P]%P;
    }
    // = -1
    return res*(P-fact[n%P])%P;
}
int extGCD(int a,int b,int &x,int &y){
    int d=a;
    if(b!=0){
        d=extGCD(b,a%b,y,x);
        y-= (a/b)*x;
    }else{
        x=1;y=0;
    }
    return d;
}
int modInverse(int n){
    int x,y;
    extGCD(n,P,x,y);
    return (P+x%P)%P;
}
int Cmod(int n,int m){
    int a1,a2,a3,e1,e2,e3;
    a1=mod_fact(n,e1);
    a2=mod_fact(m,e2);
    a3=mod_fact(n-m,e3);
    if(e1>e2+e3)return 0;
    return a1*modInverse(a2*a3%P)%P;
}
