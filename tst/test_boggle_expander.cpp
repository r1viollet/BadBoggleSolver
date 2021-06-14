#include "gtest/gtest.h"

#include "../src/boggle_expander.h"
#include "../src/boggle_gridmock.h"

TEST(BoggleExpansion, simple) {
  std::vector<std::string> testWords = {"CAMELEON", "STUPID", "AS"};
  tng::WordDict words(testWords);

  /* Create grid */
  tng::Boggle::GridChar grid = tng::Boggle::Ex2Factory();

  /* Look for words */
  std::vector<std::string> validWords = tng::Boggle::FindAllWords(grid, words);

  /* output */
  for (std::string w : validWords) {
    std::cerr << w << std::endl;
  }

  EXPECT_EQ(validWords.size(), 5);
  EXPECT_EQ(validWords.size(), 5);
  EXPECT_TRUE(std::find(validWords.begin(), validWords.end(), "CAMELEON") !=
              validWords.end());
}