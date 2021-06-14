#include "gtest/gtest.h"

#include "../src/worddict.h"

#include <filesystem>
#include <fstream>

#define DEBUG

using namespace tng;

TEST(WordDictTest, simple) {
  std::vector<std::string> allWords = {"toto", "tata", "titi"};
  WordDict dict(allWords);
#ifdef DEBUG
  dict.print();
#endif
  EXPECT_FALSE(dict.contains("toto").first);
  EXPECT_TRUE(dict.contains("TOTO").first);
  EXPECT_FALSE(dict.contains("TOT").first);
  EXPECT_TRUE(dict.contains("TOT").second);
  EXPECT_TRUE(dict.containsAnyCase("toto").first);
  EXPECT_FALSE(dict.contains("BA").second);
}

namespace fs = std::filesystem;

TEST(WordDictdStreamTest, simple) {
  std::string pathWords = TNG_DATA_PATH;
  pathWords += "words_reduced.txt";

  std::ifstream _fs(pathWords);
  std::cerr << pathWords << "is open :" << _fs.is_open() << std::endl;
  WordDict dict(_fs);
#ifdef DEBUG
  dict.print();
#endif
  EXPECT_FALSE(dict.contains("zoogloeic").first);
  EXPECT_TRUE(dict.contains("ZED").first);
  EXPECT_TRUE(dict.contains("ZOOGLOEIC").first);
  EXPECT_FALSE(dict.contains("ZOOG").first);
  EXPECT_TRUE(dict.contains("ZOOG").second);
}
