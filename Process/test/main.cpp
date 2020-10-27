#include <iostream>
#include "Process.h"
#include <cstring>

int main()
{
    char str[] = "Some ououou data", 
        out1[] = "here some stringgggg", 
        out2[30] = { 0 };
    size_t len = strlen(out1);
    Process p("./TestProg");
    p.readExact(str, strlen(str));
    std::cout << str << std::endl;
    p.writeExact(out1, strlen(out1));
    p.readExact(out2, len + 10);
    std::cout << out2 << std::endl;
    return 0;
}