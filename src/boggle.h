#pragma once

#include <array>
#include <vector>

namespace tng {
namespace Boggle {
static const unsigned kL = 4;
static const unsigned kDim = 2;
typedef std::array<int, kDim> Pos;

Pos operator+(const Pos &lhs, const Pos &rhs);

template <typename T> using Grid = std::array<std::array<T, kL>, kL>;

typedef Grid<char> GridChar;
typedef Grid<bool> GridBool;

template <typename T> T GetVal(const Grid<T> &grid, const Pos &coord) {
  return grid[coord[0]][coord[1]];
}

static const unsigned kNbMoves = 8;
static constexpr std::array<Pos, kNbMoves> kMoves = {
    {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}};

typedef unsigned NodeIdx_t;
static const NodeIdx_t kNodeIdxNull = std::numeric_limits<unsigned>::max();

class Node {
public:
  typedef std::vector<Node> NodeVect;
  Node(const Pos &position, Node *pParent = nullptr)
      : _pParent(pParent), _position(position) {}
  void createChildren(const GridBool &availablePositions);
  const NodeVect &getChildren() const { return _children; }
  NodeVect &getChildren() { return _children; }
  const Pos &getPos() const { return _position; }

private:
  static bool IsValidPostion(const Pos &pos);

  Node *_pParent;
  NodeVect _children;
  Pos _position;
};
} // namespace Boggle
} // namespace tng
