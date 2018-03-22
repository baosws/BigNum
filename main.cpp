#include "includes.h"
#include "helper.h"

int main() {
	string sa, sb;
// 	cin >> sa >> sb;
	BigInt a = 3457234; // BigInt::from_dec_str(sa.c_str());
	BigInt b = -935487363634564357ll; // BigInt::from_dec_str(sb.c_str());
	tell(a);
	tell(b);
	tell(a+b);
	tell(a-b);
	tell(a*b);
	tell(a/b);
	tell(a%b);
	(a % b).to_bits(cout << endl);
// 	(a%b).print_bits(cout);
}
