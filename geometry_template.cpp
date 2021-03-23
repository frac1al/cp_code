/**
 *	author:	 fractal
 *	timus: 	 288481RF
 *  created: 03/23/21 19:37
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
 
const int N = 1e5 + 2;
const int M = 1e5;
const int mod = 0;
const int inf = 2e9 + 3;
const ll INF = 1e18;
const ld pi2 = 2.0 * 3.14159265359;
const ld pi = 3.14159265359;

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

struct point {
	ld x, y;
	
	point (ld x = 0.0, ld y = 0.0) : x(x), y(y) {}
	
	point norm() {
		return point(-y, x);
	}
	
	ld l() {
		return sqrt(x * x + y * y);
	}	
	
	point unit() {
		return point(x / this->l(), y / this->l());
	}
	
	point rot(ld alph) {
		alph = alph * pi / 180.0;
		ld c = cos(alph);
		ld s = sin(alph);
		return point(x * c - y * s, x * s + y * c);
	}
	
	point operator+(const point a) {
		return point(x + a.x, y + a.y);
	}
	
	point operator-(const point a) {
		return point(x - a.x, y - a.y);
	}
	
	ll operator*(const point a) {
		return x * a.y - y * a.x;
	}
	
	ll operator%(const point a) {
		return x * a.x + y * a.y;
	}
	
	ld polar() {
		if (x >= 0 && y >= 0)
			return asin(y / this->l());
		if (x >= 0 && y < 0)
			return pi2 - asin(-y / this->l());
		if (x < 0 && y >= 0)
			return pi - asin(y / this->l());
		if (x < 0 && y < 0)
			return pi + asin(-y / this->l());
	}
};

ld dist(point a, point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct line {
	ld a, b, c;
	
	line (ld a = 0.0, ld b = 0.0, ld c = 0.0) : a(a), b(b), c(c) {}
	
	line (point A, point B) {
		B = B - A;
		a = B.y, b = -B.x, c = B.x * A.y - B.y * A.x;
	}
	
	void get(point &A, point &B) {
		if (b != 0.0) {
			A = {0.0, -c / b};
			B = {1.0, (-c - a) / b};
		}
		else {
			A = {-c / a, 0.0};
			B = {-c / a, 1.0};
		}
	}
};

ld get_dist(point a, point b, point c) {
	point d = c - b;
	if ((a - c) % d >= 0.0) {
		return dist(a, c);
	}
	else if ((a - b) % d <= 0.0) {
		return dist(a, b);
	}
	else {
		a = a - b;
		return abs(a * d) / d.l();
	}
}

bool inter(point a, point b, point c, point d) {
	point A = c - a, B = b - a, C = d - a;
	if (A * C == 0)
		return (A % C <= 0);
	ll v1 = abs(A * C), v2 = abs(A * B), v3 = abs(B * C), v4 = abs((c - b) * (d - b));
	if ((A * C > 0) == (A * B >= 0) && (A * C > 0) == (B * C >= 0))
		if (v1 == v2 + v3 + v4)
			return (v4 == 0);
		else
			return true;
	else
		return false;
}

bool inter(line a, line b, point &p) {
	a.c = -a.c; b.c = -b.c;
	ld det = (a.a * b.b - a.b * b.a);
	swap(a.a, b.b);
	swap(a.b, b.a);
	a.b = -a.b;	b.a = -b.a;
	swap(b.a, a.b);
	p.x = (a.c * a.a + b.c * a.b) / det;	
	p.y = (a.c * b.a + b.c * b.b) / det;	
	return true;
}

int main() {

}
