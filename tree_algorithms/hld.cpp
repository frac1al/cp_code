/**
 *	author:	 fractal
 *	timus: 	 288481RF
 *	created: 03/26/21 15:46
**/

#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second 
#define mp make_pair
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define speed ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define sz(x) (int)x.size()
#define len(x) (int)strlen(x)
#define all(x) x.begin(), x.end()
#define debug cerr << "OK\n";
#define ub upper_bound
#define lb lower_bound 
#define nl printf("\n");
#define clbuff fflush(stdin);

mt19937 bruh(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rofl(chrono::steady_clock::now().time_since_epoch().count());
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef set<int> si;
typedef set<ll> sll;
typedef set<pii> spii;
typedef set<pll> spll;
typedef multiset <int> msi;
typedef multiset <ll> msll;
typedef map <int, int> mi;
typedef map <ll, ll> mll;
 
const int N = 1e5 + 200;
const int M = 1e5;
const int mod = 0;
const int inf = 2e9 + 3;
const ll INF = 1e18;
const ld pi2 = 2.0 * 3.141592;
const ld pi = 3.141592;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

void files(string s = "main") {
	#ifndef PC
		freopen((s + ".in").c_str(), "r", stdin);
		freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

int add(int a, int b) {
	if (a + b < 0) return a + b + mod;
	if (a + b >= mod) return a + b - mod;
	return a + b;		
}

int mul(int a, int b) {
	return a * 1LL * b % mod;
}

int binpow(int a, int n) {
	int ret = 1;
	while (n) {
		if (n & 1) ret = mul(ret, a);
		a = mul(a, a);
		n >>= 1;
	}
	return ret;
}

//Sum on the path from v to u
//Update value in vertex

int n, sz[N], val[N], anc[N], d[N], pos[N], h[N];
vi g[N];

struct tree {
	int t[N << 2], sz;
	void upd(int pos, int val, int v = 1, int tl = 1, int tr = n) {
		if (tl == tr)
			return (void)(t[v] = val);
		int tm = tl +tr >> 1;
		if (pos <= tm)
			upd(pos, val, v * 2, tl, tm);
		else
			upd(pos, val, v * 2 + 1, tm + 1, tr);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
	int get(int l, int r, int v = 1, int tl = 1, int tr = n) {
		if (l <= tl && tr <= r)
			return t[v];
		if (r < tl || tr < l)
			return 0;
		int tm = tl + tr >> 1;
		return get(l, r, v * 2, tl, tm) + get(l, r, v * 2 + 1, tm + 1, tr);
	}
} t;

void prec(int v = 1, int p = 0) {
	sz[v] = 1;
	for (auto &to : g[v]) {
		if (to == p)
			continue;
		prec(to, v);
		sz[v] += sz[to];
		if (sz[to] > sz[g[v].front()])
			swap(to, g[v].front());
	}
}

void dfs(int v = 1, int p = 0) {
	if (!h[v]) h[v] = v;
	pos[v] = ++t.sz;
	t.upd(pos[v], val[v]);
	anc[v] = p;
	d[v] = d[p] + 1;
	for (auto to : g[v]) {
		if (to == p)
			continue;
		if (to == g[v].front())
			h[to] = h[v];
		dfs(to, v);
	}
}

int get(int v, int u) {
	int ans = 0;
	while (true) {
		if (d[h[v]] < d[h[u]])
			swap(v, u);
		if (h[v] == h[u]) {
			if (pos[v] > pos[u]) swap(v, u);
			ans += t.get(pos[v], pos[u]);
			break;
		}
		else {
			ans += t.get(pos[h[v]], pos[v]);
			v = anc[h[v]];
		}
	}
	return ans;
}

int main() {
	speed;
	
}
