//Xor свертка
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using ld = long double;
using str = string;
const ld eps = 1e-7;

#define vc vector
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define ff first
#define ss second
#define pb push_back
#define forn(i, n) for (ll i = 0; i < n; ++i)
#define sz(a) (ll)a.size()

#ifdef ONLINE_JUDGE
#define debug(x);
#else
#define debug(x) cerr << #x << ": " << x << endl;
#endif

str IO[2] = {"NO\n", "YES\n"};
str Io[2] = {"No\n", "Yes\n"};

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
//mt19937 rnd(3144);

template<typename T> ostream& operator<<(ostream &other, const vector<T> &_v) {
    for (const T &x: _v) other << x << ' '; return other;
}
template<typename T> bool inmin(T& _x, T _y) {return _y < _x ? (_x = _y, true) : false;};
template<typename T> bool inmax(T& _x, T _y) {return _y > _x ? (_x = _y, true) : false;};

const ll MOD = 1e9 + 7;
template<class T> ll add(T x_, T y_) {return (x_ + y_) % MOD;};
template<class T> ll sub(T x_, T y_) {return (x_ + MOD - y_) % MOD;};
template<class T> ll mul(T x_, T y_) {return (x_ * y_) % MOD;};

ll binpow(ll base, ll p) {
    if (p == 0)
        return 1;
    if (p == 1)
        return base;
    ll res = binpow(base, p / 2);
    res = mul(res, res);
    if (p % 2)
        res = mul(res, base);
    return res;
}


ll k;
ll n;
ll inv;

void fwht(vc<ll> &a) {
    forn (i, k) {
        forn (j, n) {
            if ((j & (1ll << i)) == 0) {
                ll u = a[j], v = a[j + (1 << i)];
                a[j] = add(u, v);
                a[j + (1 << i)] = sub(u, v);
            }
        }
    }
}

void fwht_inv(vc<ll> &a) {
    forn (i, k) {
        forn (j, n) {
            if ((j & (1ll << i)) == 0) {
                ll u = a[j], v = a[j + (1 << i)];
                a[j] = add(u, v);
                a[j + (1 << i)] = sub(u, v);
            }
        }
    }
    for (ll &x : a) {
        x = mul(x, inv);
    }
}

inline void solve() {
    cin >> k;
    n = (1 << k);
    inv = binpow(n, MOD - 2);
    vc<ll> a(n);
    for (ll &x : a) cin >> x;
    vc<ll> b(n);
    for (ll &x : b) cin >> x;
    fwht(a);
    fwht(b);
    vc<ll> c(n);
    forn (i, n) {
        c[i] = mul(a[i], b[i]);
    }
    fwht_inv(c);
    for (ll &x : c) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    //freopen("knapsack.in", "r", stdin);
    //freopen("knapsack.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout << fixed << setprecision(10);
    ll tt;
    tt = 1;
    //cin >> tt;
    forn (_, tt) {
        solve();
    }
    return 0;
}
