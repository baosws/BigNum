#include "includes.h"
#include "helper.h"

void test() {
	freopen("testcases/test.in", "r", stdin);
	freopen("testcases/test.out", "w", stdout);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; ++tc) {
		string sa, sb;
		cin >> sa >> sb;
		BigInt a = BigInt::from_dec_str(sa);
		BigInt b = BigInt::from_dec_str(sb);
		cout << a + b << " "
			 << a - b << " "
			 << a * b << " "
			 << a / b << " "
			 << a % b << endl;
	}
}

int main() {
// 	BigInt a = 7;
// 	BigInt b = -5;
// 	cout << a << endl;
// 	cout << b << endl;
// 	cout << a / b << endl;
	test();
}
