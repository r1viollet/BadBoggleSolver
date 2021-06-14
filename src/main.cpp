#include "boggle.h"
#include "boggle_expander.h"
#include "boggle_gridmock.h"
#include "boggle_helper.h"
#include "time_helpers.h"
#include "worddict.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdio.h>  /* printf, fgets */
#include <stdlib.h> /* atoi */
#include <string>

//#define DEBUG

namespace tng {
constexpr int kDefaultComputationTimeInSecs = 30;

int main(int argc, char *argv[]) {
  int runDuration = kDefaultComputationTimeInSecs;

  if (argc >= 2) {
    runDuration = atoi(argv[1]); // don't actually use atoi ;-)
    std::cerr << "Override run duration to : " << runDuration << std::endl;
  }

  TimePoint t1 = GetTimePoint();
  unsigned counter = 0; // for a more random behaviour --> time(NULL)
  int nbWordsFound = 0;
  // Loop for 30 seconds to allow profiling
  while (GetTimeFrom<TimeInS>(t1).count() < runDuration) {
    /* Create dictionary */
    // Should this be in the loop or outside ? ;-)
    std::string pathWords = TNG_DATA_PATH;
    pathWords += "words_reduced.txt";
    std::ifstream fs(pathWords);
    tng::WordDict words(fs);

    /* Create grid : todo a better create function would make it more likely to
     * find words */
    tng::Boggle::GridChar grid = tng::Boggle::RandomFactory(counter);
#ifdef DEBUG
    tng::Boggle::operator<<(std::cerr, grid);
#endif
    /* Look for words */
    std::vector<std::string> validWords =
        tng::Boggle::FindAllWords(grid, words);
    nbWordsFound += validWords.size();

#ifdef DEBUG
    /* output */
    for (std::string w : validWords) {
      std::cerr << w << std::endl;
    }
#endif
    ++counter;
  }
  std::cerr << "nbComputations=" << counter << std::endl;
  std::cerr << "nbWords=" << nbWordsFound << std::endl;
  return 0;
}
} // namespace tng

int main(int argc, char *argv[]) { return tng::main(argc, argv); }
