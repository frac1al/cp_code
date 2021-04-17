/**
 *	author:	 fractal
 *	timus: 	 288481RF
 *  created: 04/16/21 00:24
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
 
const int N = 5e3 + 20;
const int M = 1e5 + 20;
const int mod = 0;
const int inf = 2e9 + 3;
const ll INF = 1e18;
const ld pi2 = 2.0 * 3.141592;
const ld pi = 3.141592;
const ld eps = 1e-12;

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

struct edge{
	int u, c, f;
} e[M];

int sz = -1, d[N];
int s, t, pt[N], n;	

vi g[N];
queue <int> q;

void make(int a) {
	for (int i = 1; i <= n; ++i)
		g[i].clear(), pt[i] = 0;
	sz = -1;
	n = a;
	s = 1, t = a;
}	

void addedge(int v, int u, int c) {
	g[v].pb(++sz);
	e[sz] = {u, 0, c};
	g[u].pb(++sz);
	e[sz] = {v, 0, c};
}

bool bfs() {
	q.push(s);
	memset(d, -1, sizeof d);
	d[s] = 0;
	q.push(s);
	while (sz(q)) {
		int v = q.front();
		q.pop();
		for (auto it : g[v]) {
			if (e[it].c == e[it].f)
				continue;
			int to = e[it].u;
			if (d[to] == -1) {
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}
	return d[t] != -1;
}

int dfs(int v, int cost = inf) {
	if (v == t)
		return cost;
	for (int &it = pt[v]; it < sz(g[v]); ++it) {
		int i = g[v][it];
		int to = e[i].u;
		if (d[to] != d[v] + 1 || e[i].f == e[i].c)
			continue;
		int delta = dfs(to, min(cost, e[i].f - e[i].c));
		if (delta) {				
			e[i ^ 0].c += delta;
			e[i ^ 1].c -= delta;
			return delta;
		}
	}
	return 0;
}

ll maxflow() {
	ll F = 0, delta = 0;
	while (bfs()) {
		memset(pt, 0, sizeof pt);
		while (true) {
			delta = dfs(s);
			F += delta;
			if (!delta) break;
		}
	}
	return F;
}

int main() {
	speed;
	int n, m, p;
	cin >> n >> m;
	make(n);
	while (m--) {
		int a, b, c;
		cin >> a >> b >> c;
		addedge(a, b, c);
	}
	cout << maxflow() << '\n';
}
