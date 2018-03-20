#include "includes.h"
#include "helper.h"

int main() {
// 	BigInt a = 5;
// 	BigInt b = 4;
// 	tell(a);
// 	tell(b);
// 	tell(b-a);
// 	tell(0-b);
// 	tell(a+b);
// 	tell(a<<10);
// 	tell(a>>1);
	BigInt a(10);
	cout << a << endl;
	for (int i = 0; i < 128; i++)
		cout << a.get_bit(i);
}
