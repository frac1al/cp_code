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

struct node {
	int val, sz;
	ll sum;
	node *l, *r, *p;
	node (int val) : val(val) {
		sum = val;
		sz = 1;
		l = r = p = nullptr;
	}
} *t = nullptr;

int getsz(node *v) {
	return v ? v->sz : 0;
}

int getval(node *v) {
	return v ? v->val : 0;
}

ll getsum(node *v) {
	return v ? v->sum : 0;
}

void update(node *v) {
	if (!v) return;
	v->sz = 1 + getsz(v->l) + getsz(v->r);
	v->sum = v->val + getval(v->l) + getval(v->r);
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

void splay(node *v) {
	while (true) {
		node *p = v->p;
		if (!p) break;
		node *g = p->p;
		if (!g || (g->l && g->l->l == v) || (g->r && g->r->r == v)) {
			if (g) {
				if (g->r == p) rotl(p);
				else rotr(p);
			}
			if (p->r == v) rotl(v);
			else rotr(v);
		}
		else {
			if (p->r == v) {
				rotl(v);
				rotr(v);
			}
			else {
				rotr(v);
				rotl(v);
			}
		}
	}
}

node* merge(node *v, node *u) {
	if (!v) return u;
	if (!u) return v;
	while (v->r) v = v->r;
	splay(v);
	v->r = u;
	u->p = v;
	update(v);
	return v;	
}

node* find(node *v, int k) {
	if (!v || !k || k > getsz(v)) return nullptr;
	while (true) {
		if (k == getsz(v->l) + 1)  break;
		if (getsz(v->l) + 1 < k) {
			k -= getsz(v->l) + 1;
			v = v->r;
		}
		else {
			v = v->l;	
		}
	}
	return v;
}

typedef pair<node*, node*> pnn;

pnn split_by_node(node *v) {
	splay(v);
	node *u = v->r;
	v->r = nullptr;
	if (u)	u->p = nullptr;
	update(v);
	return {v, u};
}

pnn split_by_node_(node *v) {
	splay(v);
	node *u = v->l;
	v->l = nullptr;
	if (u)	u->p = nullptr;
	update(v);
	return {u, v};
}

pnn split(node *v, int k) {
	if (!v) return {nullptr, nullptr};
	if (k == 0) return {nullptr, v};
	if (k > getsz(v)) return {v, nullptr};
	v = find(v, k);
	return split_by_node(v);
}

int main() {
	speed;
	return 0;
}


