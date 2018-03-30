#include "includes.h"
//#include "helper.h"

<<<<<<< HEAD
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
	BigFloat a = 313.123;
	BigFloat b = BigFloat::from_dec_str("1.3231e4");
	cout << BigFloat::ZERO.to_dec_str()<<endl;
	cout << a.to_dec_str() << endl;
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

//
//void binary_operator_process(vector<string> args) {
//	if (is_float(args[1]) || is_float(arg[3])) {
//	}
//	else
//	{
//	}
//}
//void process(vector<string> args) {
//	if (args.size() == 4)
//		binary_operator_process(args);
//	else
//		if (args.size() == 3) {
//			if (arg[1] == '~') {
//				// sdfas
//			}
//			else
//				change_base(args);
//		}
//}
=======
bool is_float(const string& num) {
	return num.find_last_of(".e") != string::npos;
}
// 2 10101010 + 1010101
string int_operator(const string& opr1, const string& opr2, const string& opt, const string& src_base, const string& dest_base) {
	BigInt a, b, c;
	// parsing
	if (src_base == "2") {
		a = BigInt::from_bin_str(opr1);
		if (opr2 != "")
			b = BigInt::from_bin_str(opr2);
	}
	if (src_base == "10") {
		a = BigInt::from_dec_str(opr1);
		if (opr2 != "")
			b = BigInt::from_dec_str(opr2);
	}
	if (src_base == "16") {
		a = BigInt::from_hex_str(opr1);
		if (opr2 != "")
			b = BigInt::from_hex_str(opr2);
	}
	// computing
	if (opt == "+")
		c = a + b;
	else if (opt == "-")
		c = a - b;
	else if (opt == "*")
		c = a * b;
	else if (opt == "/")
		c = a / b;
	else if (opt == "&")
		c = a & b;
	else if (opt == "|")
		c = a | b;
	else if (opt == "^")
		c = a ^ b;
	else if (opt == "<<")
		c = a << (int)(long long)b;
	else if (opt == ">>")
		c = a >> (int)(long long)b;
	else if (opt == "~")
		c = ~a;
	else if (opt == "")
		c = a;
	// out
	if (dest_base == "2")
		return c.to_bin_str();
	if (dest_base == "10")
		return c.to_dec_str();
	if (dest_base == "16")
		return c.to_hex_str();
}

string float_operator(const string& opr1, const string& opr2, const string& opt, const string& src_base, const string& dest_base) {
	cout << opr1 << " " << opr2 << " " << opt << " " << src_base << " " << dest_base << endl;
	BigFloat a, b, c;
	// parsing
	if (src_base == "2") {
		a = BigFloat::from_bin_str(opr1);
		if (opr2 != "")
			b = BigFloat::from_bin_str(opr2);
	}
	if (src_base == "10") {
		a = BigFloat::from_dec_str(opr1);
		if (opr2 != "")
			b = BigFloat::from_dec_str(opr2);
	}
	if (src_base == "16") {
		a = BigFloat::from_hex_str(opr1);
		if (opr2 != "")
			b = BigFloat::from_hex_str(opr2);
	}
	// computing
	if (opt == "+")
		c = a + b;
	else if (opt == "-")
		c = a - b;
	else if (opt == "*")
		c = a * b;
	else if (opt == "/")
		c = a / b;
	else if (opt == "")
		c = a;
	// out
	if (dest_base == "2")
		return c.to_bin_str();
	if (dest_base == "10")
		return c.to_dec_str();
	if (dest_base == "16")
		return c.to_hex_str();
}
string binary_operator_process(const string& opr1, const string& opr2, const string& opt, const string& src_base, const string& dest_base) {
	if (is_float(opr1) || is_float(opr2))
		return float_operator(opr1, opr2, opt, src_base, dest_base);
	else
		return int_operator(opr1, opr2, opt, src_base, dest_base);
}
void process(const vector<string>& args) {
	if (args.size() == 4)
		cout << binary_operator_process(args[1], args[3], args[2], args[0], args[0]);
	else {
			if (args[1] == "~")
				cout << binary_operator_process(args[2], "", args[1], args[0], args[0]);
			else
				cout << binary_operator_process(args[2], "", "", args[0], args[1]);
		}
	cout << endl;
}
>>>>>>> refs/remotes/origin/master
int main() {
	test2();
	int n;
	scanf("%d\n", &n);
	while (n--) {
		string line;
		std::getline(cin, line);
		stringstream parser(line);
		string arg;
		vector<string> args;
		while (parser >> arg) {
// 			cout << arg << "\t";
			args.push_back(arg);
<<<<<<< HEAD
		//process(args);
=======
		}
		process(args);
>>>>>>> refs/remotes/origin/master
	}
}
