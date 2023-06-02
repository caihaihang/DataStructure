#ifndef USEFULFUNCTION_H
#define USEFULFUNCTION_H

int simpleAtoi(const char *c);
float simpleAtof(const char *c);
char *simpleItoa(long in, int &length, int width = 8);
char *simpleFtoa(double in, int &length, int decimalWidth = 2, int width = 8);

/*printf格式控制符
 * %d：有符号十进制整数
%u：无符号十进制整数
%i：与%d相同
%o：无符号八进制整数（不输出前缀0）
%x：无符号十六进制整数（不输出前缀0）
%c：输出一个字符
%s：输出一个字符串
%f：浮点数，十进制小数形式，默认保留6位小数
%e：浮点数，e指数形式，小数点前有且仅有一位非零数，指数部分一般占4位
%g：根据值，自动选择%f或%e，不输出无意义的0
%p：输出指针（地址）
%%：输出一个 %
修饰符：
%m+...  ：控制输出数据的宽度，宽度大于m时，不起作用，小于m时，数据左侧补空格
%-m+... ：同上，但数据右侧补空格
%.n+... ：对%f，%e 实数格式，表示小数点右边数字的位数(第n+1位 四舍五入)
                对%s字符串格式，表示输出字符串的字符个数
%+ +... ：输出的数据前带有正负号
%0 +... ：输出数据右对齐时，在左侧不使用的空格位置自动填0
%# +... ：在八进制%o和十六进制%x数前，使输出数据带前缀 0 或 0x
%L +... ：在d、i、o、x、u 前，指定输出精度位long int 型
%h +... ：同上，指定输出short int 型
*/
#endif // USEFULFUNCTION_H
