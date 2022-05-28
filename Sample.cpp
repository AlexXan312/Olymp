#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using big_int = __int128_t;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using vii = vector<int>;
using str = string;
using vll = vector<ll>;
using vpl = vector<pll>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using ld = double;

const ld eps = 1e-9;
const ld PI = acos(-1);

#define all(c) (c).begin(), (c).end()
#define rall(c) ((c).rbegin()), ((c).rend())
#define ff first
#define ss second
#define pb push_back
#define fast ios_base::sync_with_stdio(0); cin.tie(0)
#define forn(i, n) for (ll i = 0; i < n; ++i)
#define rforn(i, n) for (ll i = n - 1; i >= 0; --i)
#define sz(a) (ll)a.size()
#define endl '\n'
#define u_map unordered_map
#define mset multiset
/*
#define x first
#define y second
*/
#define debug(x) cerr << #x << ": " << x << endl;

str IO[2] = {"NO\n", "YES\n"};
str io[2] = {"no\n", "yes\n"};
str Io[2] = {"No\n", "Yes\n"};

inline pll euclide(ll a, ll b) {
    if (b == 0) {
        return {1, 0};
    }
    pll divide = euclide(b, a % b);
    return {divide.ss, divide.ff - a / b * divide.ss};
}

inline ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
//mt19937 rnd(1232423);

template<class T> inline bool inmax(T& x_, T y_) {
    if (y_ > x_) {
        x_ = y_;
        return 1;
    }
    return 0;
};

template<class T> inline bool inmin(T& x_, T y_) {
    if (y_ < x_) {
        x_ = y_;
        return 1;
    }
    return 0;
};

template<class T> inline void input(T& a_) {
    for (auto& x_ : a_) {
        cin >> x_;
    }
    return;
};

template<class T> inline void print(T& a_, ll SZ) {
    cout << SZ << endl;
    for (int i = 0; i < SZ; ++i) cout << a_[i] << ' ';
    cout << endl;
    return;
};

//const ll Mod = 1e4 + 7;
const ll Mod = 998244353;
//const ll Mod = 1e9 + 9;

//const ll Mod = 1234567891;
const ll INF = 1e12;

template<class T> inline void add(T& x_, T y_) {
    x_ = (x_ + y_) % Mod;
    return;
};

template<class T> inline void sub(T& x_, T y_) {
    x_ = (x_ + Mod - y_) % Mod;
    return;
};

template<class T> inline void mul(T& x_, T y_) {
    x_ = (x_ * y_) % Mod;
    return;
};

inline void solve() {

}

int main() {
    fast;
    cout << fixed << setprecision(10);
    ll t;
    t = 1;
   // cin >> t;
    forn (i, t) {
        solve();
    }
    return 0;
}
