// Copyright (c) 2025 David Ibehej
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <array>
#include <iostream>

#include "structs/Box.h"

namespace dp {

  using Boxes = std::vector<Box>;

  class DynamicProgramming {
   public:
    void setBoxes(const Boxes &boxes);

    void run();

   private:
    Boxes _boxes;
    std::vector<int> _values;
    std::vector<int> _parents;

    void sort_boxes();
    void init_heights();
    void search_order();
    int find_max_index() const;
    void extract_solution(std::vector<int> &result, int index) const;
    void print_result(const std::vector<int> &result) const;
  };

};  // namespace dp
