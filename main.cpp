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

int test2() {
	string t = "1.1";
	BigFloat a = 313.0;
	BigFloat b = BigFloat::from_dec_str("1.3231e4");
// 	cout << "a: " << a.to_bin_str() << endl;
// 	cout << "b: " << b.to_bin_str() << endl;
// 	cout << (a / b).to_bin_str() << endl;
// 	cout << (a * b).to_bin_str() << endl;
// 	cout << (a + b).to_bin_str() << endl;
// 	cout << BigFloat::ZERO.to_hex_str() << endl;
// 	cout << ((b / a).operator BigInt()).to_dec_str() << endl;
// =======
// 	string st = "012345679";
// 	st.erase(st.begin()+3);
// 	cout << st.c_str() << endl;
// 	cout << st.find_first_of("1") << endl;


//<<<<<<< HEAD
//	string t = "1100.001";
//	BigFloat a = BigFloat::from_bin_str(t);
//	BigFloat b = 1.0;
//	cout << a.to_bin_str().c_str() << endl;
//	cout << a.to_hex_str().c_str() << endl;
//=======
// 	string t = "-1.00101e-1111111111111";
	return 0;
}
void binary_operator_process(vector<string> args) {
	if (is_float(args[1]) || is_float(arg[3])) {
	}
	else
	{
	}
}
void process(vector<string> args) {
	if (args.size() == 4)
		binary_operator_process(args);
	else
		if (args.size() == 3) {
			if (arg[1] == '~') {
				// sdfas
			}
			else
				change_base(args);
		}
}
int main() {
	int n;
	cin >> n;
	while (n--) {
		string line;
		std::getline(cin, line);
		stringstream parser(line);
		string arg;
		vector<string> args;
		while (parser >> arg)
			args.push_back(arg);
		process(args);
	}
}
