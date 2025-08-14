// Copyright (c) 2025 David Ibehej
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace dp {
  struct Box {
   public:
    Box() {
      _width = 0;
      _length = 0;
      _heigth = 0;
    }

    Box(int width, int length, int heigth)
        : _width(width), _length(length), _heigth(heigth) {};

    int getWidth() const { return _width; }
    int getLength() const { return _length; }
    int getHeigth() const { return _heigth; }

   private:
    int _width;
    int _length;
    int _heigth;
  };
}  // namespace dp