#include <iostream>
#include <vector>
#inlcude <cmath>

using ld = long double;
using ll = long long;

const ld PI = acos(-1);

struct pp {
    ld x, y;
    ll id;
    bool operator==(pp other) {
        return x == other.x && y == other.y;
    }
    pp operator-(pp other) {
        return {x - other.x, y - other.y};
    }
    pp operator+(pp other) {
        return {x + other.x, y + other.y};
    }
    ll operator*(pp other) {
        return x * other.x + y * other.y;
    }
    ll operator^(pp other) {
        return x * other.y - other.x * y;
    }
};

using vc = pp;

struct line {
    ll a, b, c;
    line (pp f, pp s) {
        a = s.y - f.y;
        b = f.x - s.x;
        c = f.y * s.x - f.x * s.y;
    }
    ll get(pp to) {
        return a * to.x + b * to.y + c;
    }
    bool operator== (line &other) {
        return other.a == a && other.b == b && other.c == c;
    }
};

ll dist(pp a, pp b) {
    ll dx = b.x - a.x;
    ll dy = b.y - a.y;
    return dx * dx + dy * dy;
}

ld sqrdist(pp a, pp b) {
    return sqrt(dist(a, b));
}

ld angle(pp a, pp b, pp p) {
    ld ax = a.x - p.x, ay = a.y - p.y, bx = b.x - p.x, by = b.y - p.y;
    return atan2l(ax * by - bx * ay, ax * bx + ay * by);
}

bool on_side(pp a, pp b, pp p) {
    return sqrdist(p, a) + sqrdist(p, b) == sqrdist(a, b);
}

struct figure {
    const ld INF = 1e12;
    vector<pp> f;
    vector<pp> res;
    ll n;
    figure(vector<pp> cur) {
        f = cur;
        n = f.size();
    }
    ll square = -1;
    ll get_square(ll id = 0) {
        if (id == 0) {
            if (square != -1) return square;
            f.push_back(f[0]);
            ll ans = 0;
            for (ll i = 0; i < n; ++i) {
                ans += f[i] ^ f[i + 1];
            }
            f.pop_back();
            ans = abs(ans);
            square = ans;
            return square;
        }
        res.push_back(res[0]);
        ll ans = 0;
        for (ll i = 0; i < res.size() - 1; ++i) {
            ans += res[i] ^ res[i + 1];
        }
        res.pop_back();
        ans = abs(ans);
        return ans;
    }

    bool is_convex() {
        if (f.size() <= 2) {
            return true;
        }
        f.push_back(f[0]);
        f.push_back(f[1]);
        ll need = 0;
        for (ll i = 0; i < n; ++i) {
            ll cur = (f[i] - f[i + 1]) ^ (f[i + 1] - f[i + 2]);
            ll ort;
            if (cur == 0) {
                ort = 0;
            } else if (cur > 0) {
                ort = 1;
            } else {
                ort = -1;
            }
            if (ort == 0) {
                continue;
            }
            if (need == 0) {
                need = ort;
            } else if (need != ort) {
                f.pop_back();
                f.pop_back();
                return false;
            }
        }
        f.pop_back();
        f.pop_back();
        return true;
    }

    void sort_figure(vector<pp> &to, bool need = 0) {
        to = f;
        for (ll i = 0; i < n; ++i) {
            if (to[i].y < to[0].y) {
                swap(to[0], to[i]);
            } else if (to[i].y == to[0].y && to[i].x < to[0].x) {
                swap(to[0], to[i]);
            }
        }
        pp min_p = to[0];
        auto cmp = [&](pp &a, pp &b)  {
            ll cur = (a - min_p) ^ (b - min_p);
            if (cur > 0) return true;
            if (cur == 0) {
                return dist(min_p, a) < dist(min_p, b);
            }
            return false;
        };
        sort(1 + to.begin(), to.end(), cmp);
        if (need) {
            ll it = to.size() - 1;
            vc fs = to.back() - to[0];
            while (it >= 0 && (fs ^ (to[it] - to[0])) == 0) {
                --it;
            }
            reverse(to.begin() + it + 1, to.end());
        }
    }

    void get_convex_hull(bool need = 0) {
        vector<pp> to;
        sort_figure(to, need);
        for (ll i = 0; i < n; ++i) {
            while (res.size() >= 2 && (((res.back() - res[res.size() - 2]) ^ (to[i] - res[res.size() - 2])) < 0 ||
                                    ((res.back() - res[res.size() - 2]) ^ (to[i] - res[res.size() - 2])) == !need)) {
                res.pop_back();
            }
            res.push_back(to[i]);
        }
        reverse(res.begin(), res.end());
        return;
    }

    bool checkIn_stupid(pp x) {
        f.push_back(f[0]);
        bool pos = false;
        ld summ = 0;
        for (ll i = 0; i < n; ++i) {
            if (on_side(f[i], f[i + 1], x)) {
                pos = true;
            }
            if (pos) break;
            summ += angle(f[i], f[i + 1], x);
        }
        if (summ >= PI || summ <= -PI) pos = true;
        f.pop_back();
        return pos;
    }

    bool checkIn_clever(pp x) {
        ll a1 = (f[1] - f[0]) ^ (x - f[0]);
        ll a2 = (x - f[0]) ^ (f[n - 1] - f[0]);
        if (a1 < 0 || a2 < 0) {
            return false;
        }
        ll lhs = 1;
        ll rhs = n;
        while (rhs - lhs > 1) {
            ll mid = (lhs + rhs) / 2;
            if (((f[mid] - f[0]) ^ (x - f[0])) >= 0) {
                lhs = mid;
            } else {
                rhs = mid;
            }
        }
        if (((f[lhs] - f[0]) ^  (x - f[0])) == 0) {
            return dist(f[0], x) <= dist(f[0], f[lhs]);
        }
        return ((f[rhs] - f[lhs]) ^ (x - f[lhs])) >= 0;
    }

    ld diam() {
        get_convex_hull(1);
        pp mnp = {INF, INF};
        pp mxp = {-INF, -INF};
        ll min_id, max_id;
        for (ll i = 0; i < res.size(); ++i) {
            if (res[i].y < mnp.y) {
                mnp = res[i];
                min_id = i;
            } else if (res[i].y == mnp.y && res[i].x < mnp.x) {
                mnp = res[i];
                min_id = i;
            }
            if (res[i].y > mxp.y) {
                mxp = res[i];
                max_id = i;
            } else if (res[i].y == mxp.y && res[i].x > mxp.x) {
                mxp = res[i];
                max_id = i;
            }
        }
        ll ans = -1;
        ll down = min_id, up = max_id;
        ll it = 0;
        while (it <= 2 * res.size()) {
            ans = max(ans, dist(res[down], res[up]));
            ll nxt_up = (up + 1) % res.size();
            ll nxt_down = (down + 1) % res.size();
            ll cur = ((res[nxt_down] - res[down]) ^ (res[up] - res[nxt_up]));
            if (cur < 0) {
                down = nxt_down;
            } else {
                up = nxt_up;
            }
            ++it;
        }
        return ans;
    }

    void print_f() {
        cout << n << endl;
        for (auto [cx, cy, id] : f) {
            cout << cx << ' ' << cy << endl;
        }
        return;
    }

    void print_convex() {
        cout << res.size() << endl;
        for (auto [cx, cy, id] : res) {
            cout << cx << ' ' << cy << endl;
        }
        return;
    }
};
