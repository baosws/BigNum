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
	string t = "1.1";
	BigFloat a = -313.0;
	BigFloat b = BigFloat::from_dec_str("1.3e1");
	cout << "a: " << a.to_bin_str() << endl;
	cout << "b: " << b.to_bin_str() << endl;
	cout << (a / b).to_bin_str() << endl;
// 	cout << (a * b).to_bin_str() << endl;
// 	cout << (a + b).to_bin_str() << endl;
// 	cout << BigFloat::ZERO.to_hex_str() << endl;
// 	cout << (a - b).to_bin_str() << endl;
// 	cout << t << endl;
// 	cout << b.to_bin_str() << endl;
// 	cout << (a.to_bin_str() == t) << endl;
	return 0;
}
