
#pragma once

#include "boggle.h"

#include <ostream>
#include <string>

namespace tng {
namespace Boggle {

template <typename T> void FillGrid(Grid<T> &grid, const T &val) {
  for (std::array<T, kL> &arr : grid) {
    arr.fill(val);
  }
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Grid<T> &grid) {
  for (const std::array<T, kL> &arr : grid) {
    for (const T &val : arr) {
      os << val << " ";
    }
    os << std::endl;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const Pos &pos);
} // namespace Boggle
} // namespace tng