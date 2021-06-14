#include "gtest/gtest.h"

#include "../src/tree.h"

TEST(TreeTest, simple) {
  Node someNode(12);
  someNode.insert(3);
  someNode.insert(20);
  someNode.printInOrder(std::cerr);
  ASSERT_TRUE(someNode.contains(3));
  ASSERT_FALSE(someNode.contains(0));

  const Node<int> *pRefToNode = someNode.find(3);
  ASSERT_EQ(pRefToNode->getData(),3);
}

