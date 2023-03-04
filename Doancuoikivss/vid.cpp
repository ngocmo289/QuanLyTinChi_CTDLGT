#include<iostream>
#include<algorithm>
#include <math.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	int a[100001];
	int max = 100000;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	bool check[100001];
	for (int i = 2; i <= max; ++i) {
		check[i] = i;
		check[i] = true;
	}
	for (int i = 2; i <= max; ++i) {
		if (check[i] == true) {
			for (int j = 2 * i; j <= max; j += i) {
				check[j] = false;
			}
		}
	}
	int dem = 0, hi = 0;
	for (int i = 2; i <= max; ++i) {
		if (check[i] == true) {
			for (int j = 0; j < n; ++j) {
				if (a[j] % i == 0) dem++;
			}
			if (dem > hi) hi = dem;
			dem = 0;
		}
	}
	cout << hi;
	return 0;
}