#include "gtest/gtest.h"

#include "../src/boggle.h"
#include "../src/boggle_gridmock.h"
#include "../src/boggle_helper.h"

using namespace tng;
using namespace Boggle;

TEST(BoggleTest, simple)
{
    GridChar a;
    a[0][0] = 'C';
    EXPECT_EQ(a[0][0], 'C');
    a[3][2] = 'A';
}

TEST(BoogleNode, simple)
{
    Pos pos = {0, 0};
    Node node(pos);
    GridBool validMoves;
    FillGrid(validMoves, true);
    std::cerr << validMoves;
    node.createChildren(validMoves);
    const Node::NodeVect &children = node.getChildren();
    for (const Node &node : children)
    {
        std::cerr << node.getPos() << std::endl;
    }
    EXPECT_EQ(children.size(), 3);
}