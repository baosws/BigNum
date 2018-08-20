#include <bits/stdc++.h>
#include "../include/bigint.h"
using namespace std;
using namespace bpp;

int main() {
    bigint<2> a;
    bigint<4> b(a + a);
    cout << sizeof(b);
}
