// Copyright (c) 2025 David Ibehej
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#include "DynamicProgramming.h"

#include <algorithm>

#include "structs/Box.h"

namespace dp {

  void DynamicProgramming::setBoxes(const Boxes &boxes) {
    _boxes = boxes;
    _parents.reserve(boxes.size() - 1);
  }

  void DynamicProgramming::sort_boxes() {
    // Sort the array by the first element
    std::sort(_boxes.begin(), _boxes.end(), [](const Box &a, const Box &b) {
      return a.getWidth() < b.getWidth();
    });
  }

  void DynamicProgramming::init_heights() {
    for (size_t i = 0; i < _boxes.size(); ++i) {
      _values.push_back(_boxes[i].getHeigth());
    }
  }

  void DynamicProgramming::search_order(
      
  ) {
    // condition for valid placing
    auto is_base_smaller = [this](int i, int j) {
      // upper box has to have larger base then lower
      return j != i && _boxes[i].getWidth() > _boxes[j].getWidth() &&
             _boxes[i].getLength() > _boxes[j].getLength();
    };

    // searching logic
    for (size_t i = 0; i < _boxes.size();
         ++i)  // for each box we have compute value
    {
      int max = _values[i];  // curret max value for box
      for (size_t j = 0; j < i;
           ++j)  // for current box check if there is another box i can build on
      {
        if (is_base_smaller(
                i, j
            ))  // checking if the base is smaller then base of previouse box
        {
          int new_max = _values[i] + _values[j];  // computing potencial new_max
          if (max < new_max)                      // improving box?
          {
            max = new_max;    // setting current max
            _parents[i] = j;  // setting previous box
          }
        }
      }
      _values[i] = max;  // setting the best value to box
    }
  }

  int DynamicProgramming::find_max_index() const {
    return std::distance(
        _values.begin(), std::max_element(_values.begin(), _values.end())
    );  // finding index of bigest value box
  }

  void DynamicProgramming::extract_solution(
      std::vector<int> &result, int index
  ) const {
    // reverse box sequence searching
    while (index > 0)  // while any other predecessor exists
    {
      result.push_back(index);
      index = _parents[index];
    }
  }

  void DynamicProgramming::print_result(const std::vector<int> &result) const {
    for (const auto &idx : result) {
      std::cout << "{" << _boxes[idx].getWidth() << ", "
                << _boxes[idx].getLength() << ", " << _boxes[idx].getHeigth()
                << "} ";
    }
    std::cout << std::endl;
  }

  void DynamicProgramming::run() {
    std::vector<int> result;

    sort_boxes();    // vector for storing sequence of _boxes
    init_heights();  // initialize _values with height of each box
    search_order();  // search for solution
    int index =
        find_max_index();  // Find the index of the maximum value in _values
    extract_solution(result, index);  // extract solution from _values
    print_result(result);             // printing result
  }
}  // namespace dp