#include "includes.h"
//#include "helper.h"

int main() {
//<<<<<<< HEAD
	//std::cout << 11321;
	BigInt a(10);//10
	a = a * BigInt(2);
	for (int i = 0; i < 128; i++)
		cout << a.get_bit(i);
	cout<<endl;
	return 0;
//=======
	/*BigInt a = 5;
	BigInt b = 4;
	tell(a);
	tell(b);
	tell(b-a);
	tell(0-b);
	tell(a+b);*/
//>>>>>>> ff8004af70c52afe12a4f81287a559e38440b394
}
