/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */

int bitAnd(int x, int y) {
	/* 드모르간 법칙을 사용했습니다 */
	return ~(~x|~y);
}

int getByte(int x, int n) {
	/* 두번째 인수인 n바이트만큼 오른쪽으로 시프트해 가져오려는 비트를 lsb로 만든 뒤, 0xff(마지막 바이트가 모두 1)과 &하여 lsb만 return했습니다 */
	int shifted = x >> (n << 3);
	return shifted & 0xff;
}

int logicalShift(int x, int n) {
	 /* 산술 시프트로 msb쪽에 n개의 1이 추가되는 경우를 막기 위해, msb부터 n개의 비트가 0이고 나머지 비트는 1인 mask값과의 and연산을 수행했습니다. 왼쪽 시프트를 통해 1을 msb로 옮긴 뒤 산술 시프트하고 모든 비트를 반전시켜 mask를 구현했습니다 */
	int mask = ~(((1<<31) >> n) << 1);
	return (x >> n) & mask;
}

int bitCount(int x) {
	/* 마스크를 이용해 2비트씩, 4비트씩, ... 비트수를 늘려가며 1의 개수를 세어줬습니다. 0xFF보다 큰 수를 사용할 수 없어 시프트를 이용했습니다 */
	int tmp1 = 0x55 | (0x55 << 8); // 0x55 == 0101 0101
	int mask1 = tmp1 | (tmp1 << 16);  // 01010101 01010101 01010101 01010101

	int tmp2 = 0x33 | (0x33 << 8); // 0x33 == 0011 0011
	int mask2 = tmp2 | (tmp2 << 16);  // 00110011 00110011 00110011 00110011

	int tmp3 = 0x0f | (0x0f << 8); // 0x0F == 0000 1111
	int mask3 = tmp3 | (tmp3 << 16);  // 00001111 00001111 00001111 00001111

	int mask4 = 0xff | (0xff << 16);  // 00000000 11111111 00000000 11111111

	int mask5 = 0xff | (0xff << 8);  // 00000000 00000000 11111111 11111111

	x = (x & mask1) + ((x >> 1) & mask1);
	x = (x & mask2) + ((x >> 2) & mask2);
	x = (x & mask3) + ((x >> 4) & mask3);
	x = (x & mask4) + ((x >> 8) & mask4);
	x = (x & mask5) + ((x >> 16) & mask5);

	return x;
}

int bang(int x) {
	/* 주어진 x의 msb와 negation의 msb가 모두 0인 경우는 x = 0일 때 뿐입니다 */
	int negate = ~x + 1;
	return ((x | negate) >> 31) + 1;
}

int tmin(void) {
	/* tmin의 비트패턴은 msb가 1, 나머지 비트가 0입니다 */
	return 1<<31;
}

int fitsBits(int x, int n) {
	/* n비트의 표현 가능 범위는 2의 n-1승 -1(양수)부터 -(2의 n-1승)(음수)까지입니다 */
	int msb = x >> 31;
	int neg1 = ~1 + 1;
	int con1 = !msb & !(x >> (n + neg1));
	int con2 = msb & !((x >> (n + neg1)) + 1);
	return con1 | con2;
}

int divpwr2(int x, int n) {
	/* x가 음수인 경우 round towrad zero를 구현하기 위해 2의 n승 -1의 bias를 시프트 전에 더해줬습니다 */
	int neg1 = ~1 + 1;
	int bias = (x >> 31) & ((1 << n) + neg1);
	return (x + bias) >> n;
}

int negate(int x) {
	/* 비트반전 후 1을 더해주면 negation과 논리적으로 같습니다. tmin과 0은 negation의 영향을 받지 않습니다 */
	return ~x+1;
}

int isPositive(int x) {
	/* x가 0일 때 1이 아닌 0이 출력되게 하기 위해 !x와 or연산을 추가했습니다 */
	int msb = x >> 31;
	return !(msb | !x);
}

int isLessOrEqual(int x, int y) {
	/* x가 y보다 작거나 같을 조건을 두 값의 msb가 같을 때와 다를 때로 나누어 구현했습니다 */
	int diff = y + (~x + 1);
	int msbx = x >> 31;
	int msby = y >> 31;
	int con1  = msbx & ~msby & 1;
	int con2 = !(msbx ^ msby) & !((diff >> 31) & 1);

	return con1 | con2;
}

int ilog2(int x) {
	/* x가 양수이기 때문에 가장 왼쪽에 있는 1의 위치(2진값)에서 1을 빼주면 되므로, 나머지 비트를 모두 1로 채운 뒤 bitCount한 값에서 1을 빼 구현했습니다 */
	int tmp1 = 0x55 | (0x55 << 8); // 0x55 == 0101 0101
	int mask1 = tmp1 | (tmp1 << 16);  // 01010101 01010101 01010101 01010101

	int tmp2 = 0x33 | (0x33 << 8); // 0x33 == 0011 0011
	int mask2 = tmp2 | (tmp2 << 16);  // 00110011 00110011 00110011 00110011

	int tmp3 = 0x0f | (0x0f << 8); // 0x0F == 0000 1111
	int mask3 = tmp3 | (tmp3 << 16);  // 00001111 00001111 00001111 00001111

	int mask4 = 0xff | (0xff << 16);  // 00000000 11111111 00000000 11111111

	int mask5 = 0xff | (0xff << 8);  // 00000000 00000000 11111111 11111111

	x = x | x >> 1; // 가장 왼쪽에 있는 1 오른쪽 비트들을 1로 채우기
	x = x | x >> 2;
	x = x | x >> 4;
	x = x | x >> 8;
	x = x | x >> 16;

	x = (x & mask1) + ((x >> 1) & mask1); // bitCount...
	x = (x & mask2) + ((x >> 2) & mask2);
	x = (x & mask3) + ((x >> 4) & mask3);
	x = (x & mask4) + ((x >> 8) & mask4);
	x = (x & mask5) + ((x >> 16) & mask5);

	return x + (~1 + 1); // bitCount -1
}

// 0x0101~~ 는 hexadecimal == 16진수. 즉 한글자가 16진수, 4비트 차지!!! 8 == 1000, F == 1111
unsigned float_neg(unsigned uf) {
	unsigned exp = 0x7F800000; // 지수부가 모두 1
	unsigned frac = 0x007FFFFF; // fraction이 모두 1

	unsigned con1 = (uf & exp) == exp; // NaN이거나 무한대일때 true
	unsigned con2 = (uf & frac) != 0; // fraction이 모두 0일때 true

	if (con1 && con2) {
		return uf;
	}
	return uf ^ 0x80000000;
}

unsigned float_i2f(int x) {
   unsigned sign, exp, frac, bit, round;

   if (x == 0)
      return 0;
   if (x == 0x80000000)
      return 0xCF000000;

   sign = x & 0x80000000; // x가 음수면 sign = 1
   if (sign)
      x = -x;

   bit = 1;
   while ((x >> bit) != 0)
      bit++;        // x가 몇비트로 표현될 수 있는 수인지 확인 후 변수 bit에 저장
   bit--;           // 초기값으로 설정해둔 1 처리
   exp = bit + 127; // 8bit exp의 bias인 2^8 - 1 = 127

   x = x << (31 - bit);
   frac = (x & 0x7fffffff) >> 8; // sign비트를 제외한 뒤 fraction에 해당하는 23비트만 남겨줍니다

   if (bit > 23)
   { // fraction이 커버할 수 있는 23비트로 표현할 수 없는 수
      round = x & 0xFF;
      if ((round > 0x80) || ((round == 0x80) && (frac & 1)))
      {          // halfway보다 크거나(sticky가 있거나), halfway고 guard가 1이면
         frac++; // round up
         if (frac >> 23)
         { // round up 한 뒤 fraction 자릿수를 초과하는 경우
            exp++;
            frac = 0; // postnormalize
         }
      }
   }
   return sign | exp << 23 | frac;
}

unsigned float_twice(unsigned uf) {
	/* 인수가 NaN이면 NaN, 인수가 denormalized일 경우 fraction을 시프트(exp가 모두 0이므로 전체를 시프트), 인수가 normalized일 경우 exp+1 해 구현했습니다 */
	unsigned exp = uf & 0x7F800000; // 0111 1111 1
	unsigned sign = uf & 0x80000000; // 0100 0000 0

	if (exp == 0x7F800000) {
		return uf;
	}
	else if (exp == 0) {
		return sign | (uf << 1);
	}
	else {
		return uf + 0x00800000;
	}
}
