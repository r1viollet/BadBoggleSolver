#pragma once

#include <algorithm>
#include <string>

namespace tng {

inline bool InvalidChar(char c) { return !(c >= 'A' && c <= 'Z'); }
// trim from end (in place)
inline void Trim(std::string &s) {
  s.erase(std::remove_if(s.begin(), s.end(), InvalidChar), s.end());
}

inline void SanitizeWord(std::string &word) {
  std::transform(
      word.begin(), word.end(), word.begin(),
      [](unsigned char c) -> unsigned char { return std::toupper(c); });
  Trim(word);
}

} // namespace tng