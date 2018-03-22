#include "includes.h"
#include "helper.h"

int main() {
	BigInt a;
	BigInt b;
	cin >> a >> b;
	tell(a);
	tell(b);
	tell(a+b);
	tell(a-b);
	tell(a*b);
	tell(a/b);
	tell(a%b);
}
