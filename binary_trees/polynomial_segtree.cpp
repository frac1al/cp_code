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
 
const int N = 2e5 + 2;
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
	return a + b;
	if (a + b < 0) return a + b + mod;
	if (a + b >= mod) return a + b - mod;
	return a + b;		
}

int mul(int a, int b) {
	return a * 1LL * b;
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

int n, m, q;
int a[N];

struct mat {
	int **a, sz;

	mat(int c = 0) {
		a = new int*[m];
		for (int i = 0; i < m; ++i)
			a[i] = new int[m];
		if (c == 3) {
			for (int i = 0; i < m; ++i) {
				a[i][i] = 1;
				if (i + 1 < m)
					a[i + 1][i] = add(0, -1);
			}
		}
		if (c == 2) {
			for (int i = 0; i < m; ++i)
				for (int j = 0; j <= i; ++j)
					a[i][j] = 1;
		}
		if (c == 1) {
			for (int i = 0; i < m; ++i)
				a[i][i] = 1;
		}
	}

	mat operator *(const mat b) {
		mat res(0);
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < m; ++j)
				for (int k = 0; k < m; ++k)
					res.a[i][j] = add(res.a[i][j], mul(a[i][k], b.a[k][j]));
		return res;
	}

	mat operator +(const mat b) {
		mat res(0);
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < m; ++j)
				res.a[i][j] = add(a[i][j], b.a[i][j]);
		return res;
	}
} zero, one, neg;

mat binpow(mat a, int n) {
	mat res(1);
	while (n) {
		if (n & 1) res = res * a;
		a = a * a;
		n >>= 1;
	}
	return res;
}

struct tree {
	mat t[N << 2], p[N << 2];

	void push(int v, int tl, int tr) {
		if (tl != tr) {
			p[v * 2] = p[v * 2] * p[v];
			p[v * 2 + 1] = p[v * 2 + 1] * p[v];
		}
		t[v] = t[v] * p[v];
		p[v] = mat(1);
	}

	void build(int v = 1, int tl = 1, int tr = n) {
		p[v] = mat(1);
		if (tl == tr) {
			if (a[tl] > 0)
				t[v] = zero * binpow(one, +a[tl]);
			else
				t[v] = zero * binpow(neg, -a[tl]);
			return;
		}
		int tm = tl + tr >> 1;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm + 1, tr);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}

	void upd(int l, int r, mat val, int v = 1, int tl = 1, int tr = n) {
		push(v, tl, tr);
		if (l <= tl && tr <= r) {
			p[v] = val;
			push(v, tl, tr);
			return;
		}
		if (r < tl || tr < l)
			return;
		int tm = tl + tr >> 1;
		upd(l, r, val, v * 2, tl, tm);
		upd(l, r, val, v * 2 + 1, tm + 1, tr);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}

	int get(int l, int r, int v = 1, int tl = 1, int tr = n) {
		push(v, tl, tr);
		if (l <= tl && tr <= r) {
			int ans = 0;
			for (int i = 0; i < m; ++i)
				ans = add(ans, t[v].a[i][0]);
			return ans;
		}
		if (r < tl || tr < l)
			return 0;
		int tm = tl + tr >> 1;
		return add(get(l, r, v * 2, tl, tm), get(l, r, v * 2 + 1, tm + 1, tr));
	}
} t;

int main() {
	cin >> n >> m >> q;
	m++;
	zero = mat(0), one = mat(2), neg = mat(3);
	for (int i = 0, x; i < m; ++i) {
		cin >> x;
		for (int j = 0; j < m; ++j) {
			a[j] = binpow(j, m - 1 - i) * ((m - 1 - i) & 1 ? -1 : 1);
			a[j] = add(0, a[j]);
		}
		for (int j = 0; j < m; ++j) {
			zero.a[i][j] = mul(x, a[0]);
			for (int k = 0; k < m - j - 1; ++k)
				a[k] = add(a[k], -a[k + 1]);
		}
	}
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	t.build();
	while (q--) {
		int tp, l, r, x;
		cin >> tp >> l >> r;
		if (tp == 1)
			cout << t.get(l, r) << '\n';
		else {
			cin >> x;
			if (x > 0)
				t.upd(l, r, binpow(one, +x));
			else
				t.upd(l, r, binpow(neg, -x));
		}
	}
}
