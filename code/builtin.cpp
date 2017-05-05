int __builtin_ffsll(lld x)
	//Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.

int __builtin_clzll(llu x)
	//Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.

int __builtin_ctzll(llu x)
	//Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.

int __builtin_clrsbll(lld x)
	//Returns the number of leading redundant sign bits in x, i.e. the number of bits following the most significant bit that are identical to it. There are no special cases for 0 or other values.

int __builtin_popcountll(llu x)
	//Returns the number of 1-bits in x.
