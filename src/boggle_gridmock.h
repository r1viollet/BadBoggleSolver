#pragma once

#include "boggle.h"
#include <array>

namespace tng {
namespace Boggle {
static constexpr std::array<std::array<char, 4>, 4> kEx1 = {
    {{'A', 'E', 'G', 'O'},
     {'U', 'P', 'A', 'Q'},
     {'U', 'V', 'L', 'Z'},
     {'W', 'S', 'F', 'I'}}};
inline GridChar Ex1Factory() { return kEx1; }

static constexpr std::array<std::array<char, 4>, 4> kEx2 = {
    {{'C', 'A', 'M', 'E'},
     {'N', 'O', 'E', 'L'},
     {'S', 'T', 'U', 'P'},
     {'S', 'A', 'D', 'I'}}};

inline GridChar Ex2Factory() { return kEx2; }

inline GridChar RandomFactory(unsigned seed) {
  GridChar gridRand;
  srand(seed); // initialize the random number generator
  for (auto &line : gridRand) {
    for (auto &el : line) {
      int r = rand() % 26;
      el = 'A' + r;
    }
  }
  return gridRand;
}
} // namespace Boggle
} // namespace tng
