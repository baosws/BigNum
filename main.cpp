#include "includes.h"

int main() {
	//std::cout << 11321;
	BigInt a(10);//10
	a = a << 1;
	for (int i = 0; i < 128; i++)
		cout << a.get_bit(i);
	cout<<endl;
	return 0;
}
