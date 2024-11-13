#include "ONP.h"
#include <cassert>
#include <iostream>

int main() {
    std::vector<std::string> input1 = { "+2", "+3", "+", "+6", "*" };
    assert(rpn(input1) == 30);

    std::vector<std::string> input2 = { "+4", "-2", "-" };
    assert(rpn(input2) == 6);

    std::vector<std::string> input3 = { "-6", "+2", "/" };
    assert(rpn(input3) == -3);

    std::vector<std::string> input4 = { "+5", "+1", "+2", "+", "+4", "*", "+", "+3", "-" };
    assert(rpn(input4) == 14);

    std::vector<std::string> input5 = { "+10", "+3", "+2", "*", "+4", "+2", "/", "+", "-", "+3", "*" };
    assert(rpn(input5) == 6);

    std::vector<std::string> input6 = { "-63", "-3", "/" };
    assert(rpn(input6) == 21);

    std::cout << "Wszystkie wyniki sa poprawne" << std::endl;
    return 0;
}