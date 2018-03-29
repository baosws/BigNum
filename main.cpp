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
<<<<<<< HEAD
	string t = "1100.001";
	BigFloat a = BigFloat::from_bin_str(t);
	BigFloat b = 1.0;
//	cout << a.to_bin_str().c_str() << endl;
	cout << a.to_hex_str().c_str() << endl;
=======
// 	string t = "-1.00101e-1111111111111";
	BigFloat a = 1.1;
	BigFloat b = 1.1;
// 	cout << a.to_bin_str() << endl;
// 	cout << b.to_bin_str() << endl;
// 	cout << (a * b).to_bin_str() << endl;
	cout << (a - b).to_bin_str() << endl;
	cout << BigFloat::ZERO.to_bin_str() << endl;
// 	cout << (a - b).to_bin_str() << endl;
>>>>>>> refs/remotes/origin/master
// 	cout << t << endl;
// 	cout << b.to_bin_str() << endl;
// 	cout << (a.to_bin_str() == t) << endl;
	return 0;
}
