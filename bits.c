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
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/*
     *本函数的作用为：实现三元运算符表达式x ? y : z
     *思路：
     *  1. 该运算符含义为当x不为0时，返回y的值，否则，返回z的值。
     *  2. 首先判断x是否为0。通过两次！取非运算，获得与x的布尔代数值temp，即x为0时，temp=0，否则temp=1。
     *  3. 构造检查操作数check，temp=0时，check=0x00000000，temp=1时，check=0xffffffff
     *  4. 将检查操作数分别于y，z进行与运算，再将结果取或，相当于根据x的值选择y或z的值输出。
           等价布尔算式为（x· y）+（x(非)· z）
     */
    int temp = !!(x);
    int check = (temp << 31) >> 31;
    
    return (check & y) | ((~check) & z);
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
	 /*
     *本函数的作用为：判断x是否为非负数
     *思路：
     *  1. 只需取出x的符号位，若为0，x为非负数，否则x为负数   
     *  2. 将x与0x80000000进行与运算，得到只保留x的符号位的数temp
     *  3. temp进行取非！运算，若temp为0，即x符号位为0，x为非负数，输出结果为1，否则，输出结果为0。
     */
    int test = 1 << 31;
    int temp = x & test;
    return !(temp);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
	/*
     *本函数的作用为：x > y返回1，否则返回0
     *思路：
     *  只需判断x-y的值，x-y>0，则代表x>y。但是要特别注意补码运算中的两种溢出情况，进行修正。
     *  补码运算的两种溢出:
     *      上溢出：x为正数，y为负数，x-y为负数
     *      下溢出：x为负数，y为正数，x-y为正数
     *  可以根据上面两种情况，判断x、y、x-y的符号来确定是否产生溢出   
     */
    int flag_x = x >> 31;	//x的符号,x>0为0x00000000，否则为0xffffffff，下同
    int flag_y = y >> 31;	//y的符号
    int result = x + (~y) + 1;	//equal代表x是否等于y
    int equal = !!(result);		//x-y对应的布尔值
    int flag_result = result >> 31;		//x-y的符号

    int overflow_up = ((~flag_x) & flag_y & flag_result);	//上溢出判断，产生溢出为0xffffffff，下同
    int overflow_down = (flag_x & (~flag_y) & ~(flag_result));	//下溢出判断

    int check = (flag_result & overflow_up) | ((~flag_result) & (~overflow_down));	//x-y大于0且未产生下溢出 或 x-y小于0但产生了上溢出,以上两种情况判定为x>y

    return check & 1 & equal;	//check判定正确，且x不等于y时，输出1。
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    /*
     *本函数的作用为：求x的绝对值
     *思路：
        1. 取符号位判断x的正负
        2. 若x为负，返回-x，否则返回x
     */
    int test = x >> 31;     //取x的符号位，x为负，test=0xffffffff，否则为0x00000000
    int inverse = (test & ((~x) + 1)) | ((~test) & x);      //根据text的值返回对应结果
    
    return inverse;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
    /*
     *本函数的作用为: 判断x是否恰为2^n，是则返回1，否则返回0
     *思路：
     *  1. 首先判断x正负，负数肯定不为2^n
     *  2. 判断x是否为0，若为0则返回0
     *  3. 若x为正数，则x恰为2^n等价于x二进制位只有一位为1。则x与x-1按位与的结果应恰为0。
     */
    int flag_check = ~(x >> 31);        //判断x正负，x为负结果为0x00000000，否则为0xffffffff
    int zero_check = ((!!(x)) << 31) >> 31;         //判断x是否为0，是则返回0x00000000，否则为0xffffffff

    int check = !((x + ~(1) + 1) & x);          //x & (x-1)
    return check & flag_check & zero_check;         //三种检查的共同结果
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    /*
     *本函数的作用为：求浮点数的相反数
     *思路：
     *  输入为浮点数的无符号整数形式，输出也为浮点数的无符号整数形式
     *  由浮点数的存储方式决定，浮点数的正负只与符号位有关，因此只需将输入的无符号整数最高位取反即可
     *  注：若输入为NaN，则返回原数   
     */
    if ((uf & 0x7fffffff) > 0x7f800000){    //浮点数NaN，exp位全为1，frac位不全为0。因此若uf为NaN，则uf的frac位一定有数
        return uf;                          //uf & 0x7fffffff的作用为将uf的符号位为改为0，便于比较
    }
    
    return uf ^ 0x80000000;     //最高位与1做异或，与1异或的结果相当于取相反数
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
   /*
     *本函数的作用为：返回(float)x的值对应的无符号整数值
     *思路：
     *  1. 单精度浮点数x = (-1)^s * M * 2^E，的存储分为3部分，最高位为符号位s，后8位为exp位，其余23位为小数位frac。
     *  2. 只需分别求出x对应的s、M、E的值并转化为s、exp、frac值，即可求出结果。
     */
    int flag = (x >> 31) & 1;       //取出x的符号位，并记下结果flag，即为s的值。
    int exp = 0;                    //exp值
    int frac = 0;                   //frac值
    int i = 30;                     //循环标记

    if (x == 0){                    //当x为0时，直接返回0
      return 0;
    }else if (x == 0x80000000){     //当x为0x80000000时，该值int值的溢出值，在浮点数表示为1*1.0*2^31
      exp = 158;                    //根据公式E = exp - bias，对于单精度浮点数bias=127，因此exp = 31 + 127 = 158
    }else{                          //其余情况，注意int值可以表示的范围只能是规格类数

      if (flag){                    //首先x若为负，将其变为正数
        x = -x;
      }

      while ((x >> i) == 0){        //求出x除符号位外，1的最高位i，则2^i即为E的值。
        i--;
      }

      exp = i + 127;                //exp = E + 127
      x = x << (31 - i);            //消除x的符号位及exp位，剩下的位数就是M左移了9位的数

      frac = (x >> 8) & 0x7fffff;   //获取frac小数位，本应右移9位空出符号位+exp位，但因为对于非规格化数M=1+frac，因此M的最高位也被舍弃，再和0x7fffff与运算后，一共舍弃了9位（M的后8位+最高1位）。
      x = x & 0xff;                 //获取被舍弃的后8位
 
      if (x > 128){                 //当后8位的值大于最大值的一半（128），小数位进位，否则舍弃
        frac += 1;
      }

      if (x == 128){                //当后8位的值等于最大值的一半，向偶数舍入。frac第0位为0为偶数，舍弃，为1为奇数，进位。
        if (frac & 1){
          frac += 1;
        }
      }

      if (frac >> 23){              //若上述舍入过程使frac产生了进位，则舍弃最高位，并exp位进位
        frac = frac & 0x7fffff;
        exp ++;
      }
    }
    
    return (flag<<31) | (exp << 23) | frac;     //拼接浮点数
}
