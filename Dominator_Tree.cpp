//Шаблон для дерева доминаторов
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

struct tree_dom {
private:
    const ll Lg = 20, INF = 1e18;
    vc<vc<ll>> gr, rg;
    vc<ll> p, val;
    vc<ll> dep;
    ll timer;
    vc<ll> tin, rtin;
    vc<vc<ll>> up;
    vc<vc<pll>> mn;
    vc<ll> dom, sdom;
    ll n, m;

    void dfs(ll v, ll par) {
        tin[v] = timer++;
        rtin[tin[v]] = v;
        dep[tin[v]] = dep[tin[par]] + 1;
        p[tin[v]] = up[0][tin[v]] = tin[par];
        //shuffle(all(gr[v]), rnd);
        for (ll adj : gr[v]) {
            if (tin[adj] == -1) {
                dfs(adj, v);
            }
        }
    }

    ll root(ll v, ll last) {
        if (p[v] <= last) return v;
        ll to = root(p[v], last);
        inmin(val[v], val[p[v]]);
        p[v] = to;
        return to;
    }

public:
    tree_dom(ll _n, ll _m, vc<vc<ll>> _gr) {
        n = _n, m = _m;
        dom.resize(n), sdom.resize(n);
        rg.resize(n);
        p.resize(n), val.resize(n);
        up.resize(Lg, vc<ll>(n));
        mn.resize(Lg, vc<pll>(n));
        tin.resize(n, -1), rtin.resize(n, -1), dep.resize(n);
        gr = _gr;
        timer = 0;
        dfs(0, 0);
        forn (v, timer) {
            ll now = rtin[v];
            for (ll adj : gr[now]) {
                rg[tin[adj]].pb(v);
            }
        }
        for (ll v = timer - 1; v >= 0; --v) {
            sdom[v] = v;
            for (ll adj : rg[v]) {
                if (adj < v) {
                    inmin(sdom[v], adj);
                } else {
                    root(adj, v);
                    inmin(sdom[v], val[adj]);
                }
            }
            val[v] = sdom[v];
            mn[0][v] = {sdom[v], v};
        }
        for (ll i = 1; i < Lg; ++i) {
            forn (v, timer) {
                up[i][v] = up[i - 1][up[i - 1][v]];
                mn[i][v] =  min(mn[i - 1][up[i - 1][v]], mn[i - 1][v]);
            }
        }
        auto get = [&](ll u, ll v) {
            pll ans = {INF, -1};
            ll dif = dep[u] - dep[v];
            for (ll i = Lg - 1; i >= 0; --i) {
                if ((1 << i) <= dif) {
                    inmin(ans, mn[i][u]);
                    u = up[i][u];
                    dif -= (1 << i);
                }
            }
            return ans;
        };
        forn (v, timer) {
            pll now = get(v, sdom[v]);
            if (now.ff >= sdom[v]) {
                dom[v] = sdom[v];
            } else {
                dom[v] = dom[now.ss];
            }
        }

    }

    ll get_dom(ll v) {
        if (tin[v] == -1) return -1;
        return rtin[dom[tin[v]]];
    }

    ll get_sdom(ll v) {
        if (tin[v] == -1) return -1;
        return rtin[sdom[tin[v]]];
    }
};

inline void solve() {
    ll n, m;
    cin >> n >> m;
    vc<vc<ll>> gr(n);
    forn (i, m) {
        ll u, v;
        cin >> u >> v;
        --u, --v;
        gr[u].pb(v);
    }
    tree_dom tt(n, m, gr);
    forn (i, n) {
        cout << tt.get_dom(i) + 1 << ' ';
    }
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
