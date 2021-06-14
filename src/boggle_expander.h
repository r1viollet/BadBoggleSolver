#pragma once

#include "boggle.h"
#include "boggle_helper.h"
#include "worddict.h"

#include <string>
#include <vector>

// #define DEBUG

namespace tng {
namespace Boggle {
typedef std::vector<std::string> ValidWords;

GridBool ConsiderPos(const GridBool &currentMoves, const Pos &pos) {
  GridBool nextTurnMoves = currentMoves;
  nextTurnMoves[pos[0]][pos[1]] = false; /* remove current pos */
  return nextTurnMoves;
}

void ExpandNode(Node &currentNode, const GridBool &validMoves,
                const WordDict &allWords, const GridChar &gridChar,
                const std::string &currentString, ValidWords &words) {
  const Pos &pos = currentNode.getPos();
  GridBool nextTurnMoves = ConsiderPos(validMoves, pos);
  std::string nextTurnString = currentString;
  nextTurnString.push_back(gridChar[pos[0]][pos[1]]);
  std::pair<bool, bool> wordCheck = allWords.contains(nextTurnString);
#ifdef DEBUG
  std::cerr << "considering " << nextTurnString << std::endl;
#endif
  if (wordCheck.first) {
    words.push_back(nextTurnString);
  }
  if (wordCheck.second) /* expand all children */
  {
    currentNode.createChildren(nextTurnMoves);
    for (Node &node : currentNode.getChildren()) {
      ExpandNode(node, nextTurnMoves, allWords, gridChar, nextTurnString,
                 words);
    }
  }
}

ValidWords FindAllWords(const GridChar &gridChar, const WordDict &allWords) {
  ValidWords validWords;
  GridBool validMoves;
  FillGrid(validMoves, true);
  std::string currentString;
  currentString.reserve(kL * kL);
  for (unsigned x = 0; x < kL; ++x) {
    for (unsigned y = 0; y < kL; ++y) {
      Pos curPos = {static_cast<int>(x), static_cast<int>(y)};
      Node root(curPos);
      ExpandNode(root, validMoves, allWords, gridChar, currentString,
                 validWords);
    }
  }
  return validWords;
}

} // namespace Boggle
} // namespace tng