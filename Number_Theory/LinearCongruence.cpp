pair<LL,LL> LinearCongruence(LL a[],LL b[],LL m[],int n) {
    // a[i]*x = b[i] ( mod m[i] )
    for(int i=0;i<n;++i) {
        LL x, y, d = extgcd(a[i],m[i],x,y);
        if(b[i]%d!=0) return make_pair(-1LL,0LL);
        m[i] /= d;
        b[i] = LLmul(b[i]/d,x,m[i]);
    }
    LL lastb = b[0], lastm = m[0];
    for(int i=1;i<n;++i) {
        LL x, y, d = extgcd(m[i],lastm,x,y);
        if((lastb-b[i])%d!=0) return make_pair(-1LL,0LL);
        lastb = LLmul((lastb-b[i])/d,x,(lastm/d))*m[i];
        lastm = (lastm/d)*m[i];
        lastb = (lastb+b[i])%lastm;
    }
    return make_pair(lastb<0?lastb+lastm:lastb,lastm);
}
