#include "testfunction.h"
#include "usefulfunction.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <cstdarg>
using namespace std;

void print_args(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int arg = va_arg(args, int);
        std::cout << "arg" << i << ": " << arg << std::endl;
    }
    va_end(args);
}

int main()
{
    print_args(4, 1, 2.5, "Hello World", 0xff);
    //testSimpleArray();
    //testSimpleStack();
    //testSimpleQueue();
}
