#include "includes.h"
//#include "helper.h"

void test() {
	freopen("testcases/test.in", "r", stdin);
	freopen("testcases/test.out", "w", stdout);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; ++tc) {
		string sa, sb;
		cin >> sa >> sb;
		BigInt a = BigInt::from_dec_str(sa);
		BigInt b = BigInt::from_dec_str(sb);
		cout << a + b << " "
			 << a - b << " "
			 << a * b << " "
			 << a / b << " "
			 << a % b << endl;
	}
}

int main() {
//<<<<<<< HEAD
//<<<<<<< HEAD
// 	BigInt a = 5;
// 	BigInt b = 4;
// 	tell(a);
// 	tell(b);
// 	tell(b-a);
// 	tell(0-b);
// 	tell(a+b);
// 	tell(a<<10);
// 	tell(a>>1);
	
	
//=======
//<<<<<<< HEAD
	//std::cout << 11321;
	//BigInt a(10);//10
// 	BigInt a(200);
// 	cout << a << endl;
// 	a = a / BigInt(2);
// 	cout<<a<<endl;
// 	return 0;
//=======
	/*BigInt a = 5;
	BigInt b = 4;
	tell(a);
	tell(b);
	tell(b-a);
	tell(0-b);
	tell(a+b);*/
//>>>>>>> ff8004af70c52afe12a4f81287a559e38440b394
//>>>>>>> ee3fd9b8ad070e117796d788b4c63631f16c3152
//=======
// 	BigInt a = 7;
// 	BigInt b = -5;
// 	cout << a << endl;
// 	cout << b << endl;
// 	cout << a / b << endl;
	test();
//>>>>>>> bd12e7a44220dc13fb0c52eabdbb0275adbba7c0
}
