/**
 *	author:	 fractal
 *	timus: 	 288481RF
 *	created: 03/26/21 17:28
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
 
const int N = 1e6 + 2;
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

struct node {
	node *l, *r;
	int sz;
	ll val, sum;
	ull y;
	node (ll _val) {
		l = r = nullptr;
		sz = 1;
		val = sum = _val;
		y = rofl();
	}
} *t;

typedef pair<node*, node*> pnn;

ll get_sum(node *v) {
	return (v ? v->sum : 0);
}

int get_sz(node *v) {
	return (v ? v->sz : 0);
}

void update(node *v) {
	if (!v)
		return;
	v->sum = v->val + get_sum(v->l) + get_sum(v->r);
	v->sz = 1 + get_sz(v->l) + get_sz(v->r);
}

node* merge(node *t1, node *t2) {
	if (!t1) return t2;
	if (!t2) return t1;
	if (t1->y > t2->y) {
		t1->r = merge(t1->r, t2);
		update(t1);
		return t1;		
	}
	else {
		t2->l = merge(t1, t2->l);
		update(t2);
		return t2;		
	}		
}

pnn split(node *t, int k) {
	if (!t) return {nullptr, nullptr};
	if (get_sz(t->l) + 1 <= k) {
		pnn cnt = split(t->r, k - get_sz(t->l) - 1);
		t->r = cnt.F;
		update(t);
		return {t, cnt.S};
	}
	else {
		pnn cnt = split(t->l, k);
		t->l = cnt.S;
		update(t);
		return {cnt.F, t};		
	}
}

int main() {
	
}
