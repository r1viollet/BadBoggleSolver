#pragma once

#include "boggle_string_helper.h"

#include <algorithm>
#include <iostream>
#include <locale>
#include <stdlib.h>
#include <string>

//#define DEBUG

namespace tng {
class WordDict {
public:
  WordDict(std::vector<std::string> &allWords) {
    _wordVect = allWords;
    std::for_each(_wordVect.begin(), _wordVect.end(), SanitizeWord);
    std::sort(_wordVect.begin(), _wordVect.end());
  }

  WordDict(std::istream &is, unsigned maxSize = 16) {
    unsigned i = 0;
    while (is.good()) {
      std::string line;
      getline(is, line);
      if (line.length() > maxSize) {
        continue;
      }
      SanitizeWord(line);
      _wordVect.emplace_back(std::move(line));
    }
    std::sort(_wordVect.begin(), _wordVect.end());
  }

  void print() const { operator<<(std::cerr); }

  std::ostream &operator<<(std::ostream &os) const {
    static const int kMaxPrint = 10;
    os << "Dict contains " << _wordVect.size() << " Words" << std::endl;
    int cpt = 0;
    for (const std::string &word : _wordVect) {
      os << word << std::endl;
      ++cpt;
      if (cpt >= kMaxPrint) {
        break;
      }
    }
    return os;
  }

  // first -> word is in dict
  // second -> other words start like this
  std::pair<bool, bool> contains(const std::string &w) const {
    bool isWord = false;
    bool rCont = false;
    auto lb = std::lower_bound(_wordVect.begin(), _wordVect.end(), w);
#ifdef DEBUG
    if (lb != _wordVect.end())
      std::cerr << "Word found : " << *lb << std::endl;
#endif
    if (_wordVect.end() != lb && StartsWithSubStr(*lb, w)) {
      rCont = true; /* possible optim to check next word */
      if (lb->compare(w) == 0) {
        isWord = true;
      }
    }
    return std::make_pair(isWord, rCont);
  }

  std::pair<bool, bool> containsAnyCase(const std::string &w) const {
    std::string wSani = w;
    SanitizeWord(wSani);
    return contains(wSani);
  }

private:
  static bool StartsWithSubStr(const std::string &str, const std::string &sub) {
    for (unsigned i = 0; i < sub.length(); ++i) {
      if (sub[i] != str[i]) {
        return false;
      }
    }
    return true;
  }
  std::vector<std::string> _wordVect;
};
} // namespace tng