#include <iostream>
#include "Process.h"
#include <cstring>

int main()
{
    char str[] = "Some output data\n", out[] = "here some string";
    size_t len = sizeof(str) / sizeof(char);
    Process p("TestProg");
    p.readExact(str, len);
    std::cout << str << std::endl;
    p.writeExact(out, strlen(out) * sizeof(char));
    p.read(str, len);
    std::cout << str << std::endl;
    return 0;
}