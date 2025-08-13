// Copyright (c) 2025 David Ibehej
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "dynamic_programming.h"

#include "structs/Box.h"

namespace DynamicProgramming {

  void sort_boxes(Boxes &boxes) {
    // Sort the array by the first element
    std::sort(
        boxes.begin(), boxes.end(),
        [](const std::array<int, 3> &a, const std::array<int, 3> &b) {
          return a[0] < b[0];
        }
    );
  }

  void init_heights(Boxes &boxes, std::vector<int> &values) {
    for (size_t i = 0; i < boxes.size(); ++i) {
      values[i] = boxes[i][2];
    }
  }

  void search_order(
      Boxes &boxes, std::vector<int> &values, std::vector<int> &parent
  ) {
    // condition for valid placing
    auto is_base_smaller = [boxes](int i, int j) {
      // upper box has to have larger base then lower
      return j != i && boxes[i][0] > boxes[j][0] && boxes[i][1] > boxes[j][1];
    };

    // searching logic
    for (size_t i = 0; i < boxes.size();
         ++i)  // for each box we have compute value
    {
      int max = values[i];  // curret max value for box
      for (size_t j = 0; j < i;
           ++j)  // for current box check if there is another box i can build on
      {
        if (is_base_smaller(
                i, j
            ))  // checking if the base is smaller then base of previouse box
        {
          int new_max = values[i] + values[j];  // computing potencial new_max
          if (max < new_max)                    // improving box?
          {
            max = new_max;  // setting current max
            parent[i] = j;  // seting previouse box
          }
        }
      }
      values[i] = max;  // setting the best value to box
    }
  }

  int find_max_index(std::vector<int> &values) {
    return std::distance(
        values.begin(), std::max_element(values.begin(), values.end())
    );  // finding index of bigest value box
  }

  void extract_solution(
      std::vector<int> &result, std::vector<int> &parent, int index
  ) {
    // reverse box sequence searching
    while (index > 0)  // while any other predecessor exists
    {
      result.push_back(index);
      index = parent[index];
    }
  }

  void print_result(std::vector<int> &result, Boxes &boxes) {
    for (const auto &idx : result) {
      std::cout << "{" << boxes[idx][0] << ", " << boxes[idx][1] << ", "
                << boxes[idx][2] << "} ";
    }
    std::cout << std::endl;
  }

  void run(Boxes &boxes) {
    // initializing vectors
    std::vector<int> values(boxes.size());  // vector of current height values
    std::vector<int> parent(
        boxes.size(), -1
    );  // vector of indexes pointing to previous box
    std::vector<int> result;

    sort_boxes(boxes);            // vector for storing sequence of boxes
    init_heights(boxes, values);  // initialize values with height of each box
    search_order(boxes, values, parent);  // search for solution
    int index = find_max_index(
        values
    );  // Find the index of the maximum value in values
    extract_solution(result, parent, index);  // extract solution from values
    print_result(result, boxes);              // printing result
  }
}  // namespace DynamicProgramming