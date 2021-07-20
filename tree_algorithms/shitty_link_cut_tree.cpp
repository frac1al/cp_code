/**
 *	author:	 fractal
 *	timus: 	 288481RF
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
#define make_unique(x) sort(all(x)), x.erase(unique(all(x)), x.end())

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
 
const int N = 1e6 + 2;
const int M = 1e5;
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

// SPLAY

struct node {
	int v, sz;
	bool f = 0;
	node *l, *r, *p, *op;
	int val, add;
	node (int v) : v(v), val(0), add(0) {
		sz = 1;
		l = r = p = op = nullptr;
	}
};

int getsz(node *v) {
	return v ? v->sz : 0;
}

void update(node *v) {
	if (!v) return;
	v->sz = 1 + getsz(v->l) + getsz(v->r);
	if (v->r) v->r->p = v;
	if (v->l) v->l->p = v;
}

void rotl(node *v) {
	node *p = v->p;
	v->p = nullptr;
	if (p->p) {
		v->p = p->p;
		if (p->p->l == p) p->p->l = v;
		else p->p->r = v;
	}
	p->p = v;
	p->r = v->l;
	if (v->l) v->l->p = p;
	v->l = p;
	update(p);
	update(v);
}

void rotr(node *v) {
	node *p = v->p;
	v->p = nullptr;
	if (p->p) {
		v->p = p->p;
		if (p->p->l == p) p->p->l = v;
		else p->p->r = v;
	}
	p->p = v;
	p->l = v->r;
	if (v->r) v->r->p = p;
	v->r = p;
	update(p);
	update(v);
}

void rot(node *v) {
	if (v->p->r == v) rotl(v);
	else rotr(v);
}

void push(node *v) {
	if (v->f) swap(v->l, v->r);
	if (v->l) v->l->f ^= v->f, v->l->op = v->op;
	if (v->r) v->r->f ^= v->f, v->r->op = v->op;
	v->f = 0;
}

void apply(node *v) {
	if (v->p) apply(v->p);
	push(v);
}

void splay(node *v) {
	apply(v);
	while (true) {
		node *p = v->p;
		if (!p) break;
		node *g = p->p;
		if (!g || (g->l && g->l->l == v) || (g->r && g->r->r == v)) {
			if (g) rot(p);
			rot(v);
		}
		else {
			rot(v);
			rot(v);
		}
	}
}

void reverse(node *v) {
	v->f ^= 1;
}

void out(node *v) {
	if(!v) return;
	push(v);
	if (v->l) out(v->l);
	cout << (v->v) << ' ';
	if (v->r) out(v->r);
}

// LINK-CUT

node* p[N];

int expose(int v) {
	int u = 0;
	while (true) {
		splay(p[v]);
		if (p[v]->r) {
			int r = p[v]->r->v;
			p[r]->p = nullptr;
			p[v]->r = nullptr;
			splay(p[r]);
			p[r]->op = p[v];
		}
		if (u) {
			p[v]->r = p[u];
			p[u]->p = p[v];
		}
		update(p[v]);
		u = v;
		if (p[v]->op == nullptr) break;
		v = p[v]->op->v;
	}
	return v;
}

void makeroot(int v) {
	expose(v);
	splay(p[v]);
	p[v]->f ^= 1;
}

void link(int v, int u) {
	makeroot(v);
	p[v]->op = p[u];
}

void cut(int v, int u) {
	makeroot(v);
	expose(u);
	splay(p[v]);
	p[u]->p = nullptr;
	p[v]->r = nullptr;
}

int lca(int v, int u) {
	expose(u);
	int ans = expose(v);
	if (expose(u) == ans)
		return ans;
	return -1;
}

int main() {
//	speed;
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		p[i] = new node(i);
	}
	while (m--) {
		string s;
		int v, u;
		cin >> s >> v;
		if (s == "link") {
			cin >> u;
			link(v, u);
		}
		if (s == "cut") {
			cin >> u;
			cut(v, u);
		}
		if (s == "lca") {
			cin >> u;
			cout << lca(v, u) << '\n';
		}
		if (s == "root") {
			makeroot(v);
		}
	}
	return 0;
}


