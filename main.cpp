#include "includes.h"
//#include "helper.h"

//void test() {
//	freopen("testcases/test.in", "r", stdin);
//	freopen("testcases/test.out", "w", stdout);
//	int T;
//	cin >> T;
//	for (int tc = 0; tc < T; ++tc) {
//		string sa, sb;
//		cin >> sa >> sb;
//		BigInt a = BigInt::from_dec_str(sa);
//		BigInt b = BigInt::from_dec_str(sb);
//		cout << a + b << " "
//			 << a - b << " "
//			 << a * b << " "
//			 << a / b << " "
//			 << a % b << endl;
//	}
//}

int main() {
	string t = "0.000000000001010101010111100001";
	BigFloat a = BigFloat::from_bin_str(t);
	cout << (a.to_bin_str() == t) << endl;
	return 0;
}
