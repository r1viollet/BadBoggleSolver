#include "boggle.h"
#include "boggle_expander.h"
#include "boggle_gridmock.h"
#include "boggle_helper.h"
#include "time_helpers.h"
#include "worddict.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#define DEBUG

namespace tng {
int main(int argc, char *argv[]) {
  TimePoint t1 = GetTimePoint();
  unsigned seed = 0; // for a more random behaviour --> time(NULL)
  // Loop for 30 seconds to allow profiling
  while (GetTimeFrom<TimeInS>(t1).count() < 30) {
    /* Create dictionary */
    // This is a voluntary mistake : we want people to notice that we are
    // recreating the dictionary in a loop
    std::string pathWords = TNG_DATA_PATH;
    pathWords += "words_reduced.txt";
    std::ifstream fs(pathWords);
    tng::WordDict words(fs);

    /* Create grid */
    tng::Boggle::GridChar grid = tng::Boggle::RandomFactory(seed);
    tng::Boggle::operator<<(std::cerr, grid);
    /* Look for words */
    std::vector<std::string> validWords =
        tng::Boggle::FindAllWords(grid, words);

    /* output */
    for (std::string w : validWords) {
      std::cerr << w << std::endl;
    }
    ++seed;
  }
  return 0;
}
} // namespace tng

int main(int argc, char *argv[]) { return tng::main(argc, argv); }
