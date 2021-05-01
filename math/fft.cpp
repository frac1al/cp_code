/**
 *	author:	 fractal
 *	timus: 	 288481RF
 *	created: _
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
#define make_unique(x) sort(all(x)), x.erase(unique(x), x.end())

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

struct cp {
	double x = 0.0, y = 0.0;
 
	cp(double x = 0, double y = 0) : x(x), y(y) {}
 
	cp operator*(cp const &a) {
		return cp(x * a.x - y * a.y, x * a.y + y * a.x);
	}
 
	cp operator+(cp const &a) {
		return cp(x + a.x, y + a.y);
	}
	
	cp operator-(cp const &a) {
		return cp(x - a.x, y - a.y);
	}

	void operator/=(double const &n) {
		x /= n;
		y /= n;
	}
};

cp conj(cp &a) {
	return cp(a.x, -a.y);
}

typedef vector<cp> poly;
const int PW = 22;
int dp[PW][1 << PW], pw[PW], lg[1 << PW];
cp w[30];

void calc() {
	pw[0] = 1;
	ld a = pi2;
	for (int i = 0; i < PW; ++i) {
		if (i) pw[i] = pw[i - 1] + pw[i - 1];
	 	w[i] = cp(cos(a / (pw[i] + 0.0)), sin(a / (pw[i] + 0.0)));
	}
	for (int i = 2; i < (1 << PW); ++i) {
		lg[i] = lg[i >> 1] + 1;
	}
	for (int i = 0; i < PW; ++i) {
		dp[i][0] = 0;
		for (int j = 1; j < (1 << i); ++j) {
			dp[i][j] = dp[i][j ^ pw[lg[j]]] ^ pw[i - lg[j] - 1];
		}
	}
}

void norm(poly &A) {
	for (auto &it : A) {
		if (it.x > 0.5)
			it = cp(1, 0);
		else	
			it = cp(0, 0);
	}
	while (sz(A) && A.back().x < 0.5)
		A.ppb();
}

void fft(poly &A, bool rev) {
	int n = sz(A);
	int l = lg[n];
	poly B(n);
	for (int i = 0; i < n; ++i)
		B[dp[l][i]] = A[i];
	for (int i = 1, l = 1; i < n; i <<= 1, ++l) {
		for (int j = 0; j < n; j += 2 * i) {
			cp pw = cp(1.0, 0.0);
			for (int k = j; k < j + i; ++k) {
				A[k + 0] = B[k] + B[k + i] * pw;
				A[k + i] = B[k] - B[k + i] * pw;
				pw = pw * (rev ? conj(w[l]) : w[l]);
			}
		}
		B.swap(A);
	}
	A.swap(B);
	if (!rev)
		return;
	for (auto &it : A)
		it /= (n + 0.0);	
}

void mult_poly(poly &A, poly &B) {
    int n = 1;
	while (n < sz(A) || n < sz(B))
		n <<= 1;
	n <<= 1;
	A.resize(n); B.resize(n);
	fft(A, 0); fft(B, 0);
	for (int i = 0; i < n; ++i)
		A[i] = A[i] * B[i];
	fft(A, 1); fft(B, 1);
	norm(B);
	norm(A);
}

void sqr(poly &A) {
	int n = 1;
	while (n < sz(A))
		n <<= 1;
	n <<= 1;
	A.resize(n);
	fft(A, 0);
	for (int i = 0; i < n; ++i)
		A[i] = A[i] * A[i];
	fft(A, 1);
	norm(A);
}

void binpow_poly(poly &a, int n) {
	poly ret = {1, 0};
	while (n) {
		if (n & 1) mult_poly(ret, a);
		sqr(a);
		n >>= 1;
	}
	a.swap(ret);
}

int main() {
	speed;
	calc();

}
