#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")

#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ld = long double;
using str = string;
const ld eps = 1e-8;

//#define int long long
#define vc vector
#define mp make_pair
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define ff first
#define ss second
#define pb push_back
#define forn(i, n) for (int i = 0; i < n; ++i)
#define sz(a) (int)a.size()

#ifdef LOCAL
#define debug(x) cerr << #x << ": " << x << endl;
#else
#define debug(x)
#endif

template<typename T> istream& operator>>(istream &other, vector<T> &_v) {
    for (T &x : _v) other >> x; return other;
}
template<typename T> ostream& operator<<(ostream &other, const vector<T> &_v) {
    for (const T &x: _v) other << x << ' '; return other;
}
template<typename T, typename Y> istream& operator>>(istream &other, std::pair<T, Y> &_v) {
    other >> _v.first >> _v.second; return other;
}
template<typename T, typename Y> ostream& operator<<(ostream &other, std::pair<T, Y> &_v) {
    other << _v.first << ' ' <<  _v.second; return other;
}
template<typename T> bool inmin(T& _x, T _y) {return _y < _x ? (_x = _y, true) : false;};
template<typename T> bool inmax(T& _x, T _y) {return _y > _x ? (_x = _y, true) : false;};

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
inline void solve();

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("/Users/alexsus/Desktop/solve/read.txt", "r", stdin);
#else
#endif
    //cout << fixed << setprecision(10);
    ll tt;
    tt = 1;
    //cin >> tt;
    forn (i, tt) {
        solve();
    }
    return 0;
}

inline void solve() {
    return;
}
