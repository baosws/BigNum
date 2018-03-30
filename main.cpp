#include "includes.h"

bool is_float(const string& num) {
	return num.find_last_of(".e") != string::npos;
}
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

// result of a query line with fixed argument format
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
int main(int nargs, char* args[]) {
	int count = 1;
	freopen(args[1], "r", stdin);
//	freopen(args[2], "w", stdout);
	string line;
	for (int i = 0; std::getline(cin, line); ++i) {
		stringstream parser(line);
		string arg;
		vector<string> args;
		while (parser >> arg) {
			args.push_back(arg);
		}
		cout << "*Resul test " << count++ <<": "<< endl;
		process(args);
		cout <<  endl;
	}
}
