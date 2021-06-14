#include "boggle.h"

namespace tng {

namespace Boggle {
Pos operator+(const Pos &lhs, const Pos &rhs) {
  Pos val = lhs;
  for (unsigned i = 0; i < val.size(); ++i) {
    val[i] += rhs[i];
  }
  return val;
}

/* NODE DEF */

void Node::createChildren(const GridBool &availablePositions) {
  for (const Pos &pos : kMoves) {
    Pos newPos = pos + _position;
    if (!IsValidPostion(newPos)) {
      continue;
    }
    if (availablePositions[newPos[0]][newPos[1]]) {
      _children.emplace_back(newPos, this);
    }
  }
}

bool Node::IsValidPostion(const Pos &pos) {
  for (int coord : pos) {
    if (coord >= static_cast<int>(kL) || coord < 0) {
      return false;
    }
  }
  return true;
}

} // namespace Boggle

} // namespace tng
