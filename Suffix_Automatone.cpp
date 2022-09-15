 
//Суффиксный автомат
#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using pii = pair<int, int>;
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
#define forn(i, n) for (int i = 0; i < n; ++i)
#define sz(a) (int)a.size()

#ifdef LOCAL
#define debug(x) cerr << #x << ": " << x << endl;
#else
#define debug(x)
#endif

template<typename T> ostream& operator<<(ostream &other, const vector<T> &_v) {
    for (const T &x: _v) other << x << ' '; return other;
}
template<typename T> bool inmin(T& _x, T _y) {return _y < _x ? (_x = _y, true) : false;};
template<typename T> bool inmax(T& _x, T _y) {return _y > _x ? (_x = _y, true) : false;};


mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct state {
    ll len, link;
    map<char, ll> next;
};

const ll Maxn = 2e5 + 10;
state st[2 * Maxn];
ll sz, last;

void init() {
    sz = last = 0;
    st[0].len = 0, st[0].link = -1;
    ++sz;
}

void add(char c) {
    ll cur = sz++;
    st[cur].len = st[last].len + 1;
    ll par;
    for (par = last; par != -1 && !st[par].next.count(c); par = st[par].link)
        st[par].next[c] = cur;
    if (par == -1) st[cur].link = 0;
    else {
        ll q = st[par].next[c];
        if (st[par].len + 1 == st[q].len) st[cur].link = q;
        else {
            ll new_v = sz++;
            st[new_v].len = st[par].len + 1;
            st[new_v].next = st[q].next;
            st[new_v].link = st[q].link;
            for (; par != -1 && st[par].next[c] == q; par = st[par].link)
                st[par].next[c] = new_v;
            st[q].link = st[cur].link = new_v;
        }
    }
    last = cur;
}

inline void solve() {
    str s;
    cin >> s;
    init();
    for (char x : s) {
        add(x);
    }
    vc<ll> path;
    vc<bool> used(sz);
    function<void(ll)> dfs = [&](ll v) {
        used[v] = 1;
        for (auto [c, adj] : st[v].next) {
            if (!used[adj]) {
                dfs(adj);
            }
        }
        path.pb(v);
    };
    dfs(0);
    reverse(all(path));
    vc<ll> dp(sz);
    dp[path[0]] = 1;
    for (ll v : path) {
        for (auto [c, adj] : st[v].next) {
            dp[adj] += dp[v];
        }
    }
    ll ans = 0;
    for (ll i = 1; i < sz; ++i) {
        ans += dp[i];
    }
    cout << ans << '\n';
}


int main() {
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
