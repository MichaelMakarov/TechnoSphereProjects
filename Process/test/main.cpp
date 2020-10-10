#include <iostream>
#include "../include/Process.h"
#include <cstring>

int main()
{
    char str[100] = { 0 }, out[] = "here some string";
    size_t len = sizeof(str) / sizeof(char);
    Process p("TestProg");
    p.read(str, len);
    std::cout << str << std::endl;
    p.write(out, strlen(out) * sizeof(char));
    p.read(str, len);
    std::cout << str << std::endl;
    return 0;
}