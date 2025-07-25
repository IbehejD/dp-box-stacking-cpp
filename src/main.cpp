// Copyright (c) 2025 David Ibehej
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <vector>
#include <string>
#include "dynamic_programming.h"

int main()
{
    std::vector<std::array<int, 3>> boxes = {{{4, 5, 3},
                                              {1, 5, 4},
                                              {2, 3, 2},
                                              {2, 4, 1},
                                              {3, 6, 2},
                                              {1, 2, 2}}};
    DynamicProgramming::run(boxes);

    return 0;
}