// Copyright (c) 2025 David Ibehej
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include "dynamic_programming.h"

namespace DynamicProgramming
{
    void run(std::vector<std::array<int, 3>> &boxes)
    {
        // initializing vectors
        std::vector<int> values(boxes.size());     // vector of current height values
        std::vector<int> parent(boxes.size(), -1); // vector of indexes pointing to previous box
        std::vector<int> result;                   // vector for storing sequence of boxes

        // Sort the array by the first element
        std::sort(boxes.begin(), boxes.end(), [](const std::array<int, 3> &a, const std::array<int, 3> &b)
                  { return a[0] < b[0]; });

        // initialize values with height of each box
        for (size_t i = 0; i < boxes.size(); ++i)
        {
            values[i] = boxes[i][2];
        }

        // condition for valid placing
        auto is_base_smaller = [boxes](int i, int j)
        {
            // upper box has to have larger base then lower
            return j != i && boxes[i][0] > boxes[j][0] && boxes[i][1] > boxes[j][1];
        };

        // searching logic
        for (size_t i = 0; i < boxes.size(); ++i) // for each box we have compute value
        {
            int max = values[i];           // curret max value for box
            for (size_t j = 0; j < i; ++j) // for current box check if there is another box i can build on
            {

                if (is_base_smaller(i, j)) // checking if the base is smaller then base of previouse box
                {
                    int new_max = values[i] + values[j]; // computing potencial new_max
                    if (max < new_max)                   // improving box?
                    {
                        max = new_max; // setting current max
                        parent[i] = j; // seting previouse box
                    }
                }
            }
            values[i] = max; // setting the best value to box
        }

        // Find the index of the maximum value in values
        int index = std::distance(values.begin(), std::max_element(values.begin(), values.end())); // finding index of bigest value box

        // reverse box sequence searching
        while (index > 0) // while any other predecessor exists
        {
            result.push_back(index);
            index = parent[index];
        }

        // printing result
        for (const auto &idx : result)
        {
            std::cout << "{" << boxes[idx][0] << ", " << boxes[idx][1] << ", " << boxes[idx][2] << "} ";
        }
        std::cout << std::endl;
    }
}