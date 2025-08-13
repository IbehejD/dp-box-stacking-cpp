// Copyright (c) 2025 David Ibehej
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <array>
#include <iostream>

namespace DynamicProgramming {
  using Boxes = std::vector<std::array<int, 3>>;
  void run(Boxes &boxes);

};  // namespace DynamicProgramming
