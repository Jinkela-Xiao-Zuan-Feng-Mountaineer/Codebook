// an*x^n + ... + a1x + a0 = 0;
int sign(double x){
    return x < -eps ? -1 : x > eps;
}

double get(const vector<double>&coef, double x){
    double e = 1, s = 0;
    for(auto i : coef) s += i*e, e *= x;
    return s;
}

double find(const vector<double>&coef, int n, double lo, double hi){
    double sign_lo, sign_hi;
    if( !(sign_lo = sign(get(coef,lo))) ) return lo;
    if( !(sign_hi = sign(get(coef,hi))) ) return hi;
    if(sign_lo * sign_hi > 0) return INF;
    for(int stp = 0; stp < 100 && hi - lo > eps; ++stp){
        double m = (lo+hi)/2.0;
        int sign_mid = sign(get(coef,m));
        if(!sign_mid) return m;
        if(sign_lo*sign_mid < 0) hi = m;
        else lo = m;
    }
    return (lo+hi)/2.0;
}

vector<double> cal(vector<double>coef, int n){
    vector<double>res;
    if(n == 1){
        if(sign(coef[1])) res.pb(-coef[0]/coef[1]);
        return res;
    }
    vector<double>dcoef(n);
    for(int i = 0; i < n; ++i) dcoef[i] = coef[i+1]*(i+1);
    vector<double>droot = cal(dcoef, n-1);
    droot.insert(droot.begin(), -INF);
    droot.pb(INF);
    for(int i = 0; i+1 < droot.size(); ++i){
        double tmp = find(coef, n, droot[i], droot[i+1]);
        if(tmp < INF) res.pb(tmp);
    }
    return res;
}

int main () {
    vector<double>ve;
    vector<double>ans = cal(ve, n);
    // 視情況把答案 +eps，避免 -0
}
