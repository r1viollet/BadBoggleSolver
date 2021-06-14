#include <cassert>
#include <memory>
#include <ostream>

#pragma once

using std::endl;

template <typename T> class Node {
public:
  typedef T DataType;
  Node(DataType data) : _left(nullptr), _right(nullptr), _data(data) {}

  void insert(int value) {
    if (value <= _data) {
      if (_left == nullptr) {
        _left = std::unique_ptr<Node>(new Node(value));
      } else {
        _left->insert(value);
      }
    } else {
      if (_right == nullptr) {
        _right = std::unique_ptr<Node>(new Node(value));
      } else {
        _right->insert(value);
      }
    }
  }

  bool contains(DataType value) const {
    if (find(value)) {
      return true;
    }
    return false;
  }

  const Node *find(DataType value) const {
    if (value == _data) {
      return this;
    }
    if (value < _data) {
      return _left ? _left->find(value) : nullptr;
    } else {
      return _right ? _right->find(value) : nullptr;
    }
  }

  std::ostream &printInOrder(std::ostream &os) const {
    if (_left) {
      _left->printInOrder(os);
    }
    os << _data << endl;
    if (_right) {
      _right->printInOrder(os);
    }
    return os;
  }
  const DataType &getData() const { return _data; }

private:
  std::unique_ptr<Node> _left;
  std::unique_ptr<Node> _right;
  DataType _data; /* todo template */
};
