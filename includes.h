#pragma once

#include <cstring>
#include <iostream>
#include <utility>
#include <tuple>
using namespace std;
#include "BigNum.h"
#include "BigInt.h"
#include "BigFloat.h"

const int LENGTH_OF_BITS = 128;
const int MAX_DEC_LENGTH = 39;
const int MAX_HEX_LENGTH = 32;
const int FULL_EXPONENT = (1 << 15) - 1;
