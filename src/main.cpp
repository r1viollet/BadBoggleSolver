#include "boggle.h"
#include "boggle_expander.h"
#include "boggle_gridmock.h"
#include "boggle_helper.h"
#include "time_helpers.h"
#include "worddict.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdio.h>  /* printf, fgets */
#include <stdlib.h> /* atoi */
#include <string>
#include <signal.h>


#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif
//#define DEBUG

namespace tng {
constexpr int kDefaultComputationTimeInSecs = 30;

struct InputValues {
  InputValues() : _runDuration(-1), _nbComputations(-1){};
  InputValues(int runDuration, int nbComputations, int crash = 3)
      : _runDuration(runDuration), _nbComputations(nbComputations), _crash_type(crash) {};
  int _runDuration;
  int _nbComputations;
  int _crash_type;
};

void PrintHelp(std::string exe) {
  std::cerr << "This is a toy app to generate work. It expects a data folder "
               "in ../data"
            << std::endl;
  std::cerr << std::endl;
  std::cerr << "Example of usage:" << std::endl;
  std::cerr << "      " << exe << " time nb_seconds" << std::endl;
  std::cerr << "      " << exe << " work nb_seconds" << std::endl;
  std::cerr << "      " << exe << " crash crash_type_num" << std::endl;
  std::cerr << "      " << exe << " nb_seconds" << std::endl;
  std::cerr << "      ";
  std::cerr << "Types of crash";
  std::cerr << "    - 1 --> SIGSEGV";
  std::cerr << "    - 2 --> abort";
  std::cerr << "    - 3 --> exception";
  std::cerr << ""
            << "Defaults to a run of " << kDefaultComputationTimeInSecs
            << "seconds with no arguments" << std::endl
            << "Crash happens after 3 seconds of work" << std::endl;

}

void do_crash(int crash_type){
  if (crash_type == 1) {
    raise(SIGSEGV);
  }
  else if (crash_type == 2) {
    abort();
  }
  else if (crash_type == 3) {
    throw std::exception();
  }
}

InputValues GetInputValues(int argc, char *argv[]) {
  if (argc == 1) {
    return InputValues(kDefaultComputationTimeInSecs, -1);
  }

  if (argc == 2) {
    int argValue = atoi(argv[1]);
    if (argValue == 0) {
      PrintHelp(std::string(argv[0]));
      exit(1);
    }
    return InputValues(argValue, -1);
  }
  if (argc == 3) {
    int argValue = atoi(argv[2]);
    if (argValue == 0) {
      PrintHelp(std::string(argv[0]));
      exit(1);
    }
    if (std::string(argv[1]) == "time") {
      return InputValues(argValue, -1);
    } else if (std::string(argv[1]) == "work") {
      return InputValues(-1, argValue);
    } else if (std::string(argv[1]) == "crash") {
      return InputValues(3, -1, argValue);
    }
  }
  PrintHelp(std::string(argv[0]));
  exit(1);
  return InputValues();
}

bool TimeToStop(const InputValues &inputValues, const TimePoint &startTime,
                int nbComputations) {
  // always read time to ensure we see it in profiles (read it twice)
  TimePoint t2 = GetTimePoint();
  auto timeInSecs = GetTimeDiff<TimeInS>(startTime, t2);
  auto timeInMs = GetTimeDiff<TimeInMs>(startTime, t2);

  if (nbComputations % 1000 == 0) {
    std::cerr << timeInMs.count() << "ms - Work done = " << nbComputations
              << std::endl;
  }
  if (inputValues._nbComputations != -1 &&
      nbComputations >= inputValues._nbComputations) {
    std::cerr << "timeInMs=" << timeInMs.count() << std::endl;
    return true;
  }
  if (inputValues._runDuration != -1 &&
      timeInSecs.count() >= inputValues._runDuration) {
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  InputValues inputValues = GetInputValues(argc, argv);
  TimePoint t1 = GetTimePoint();
  unsigned counter = 0; // for a more random behaviour --> time(NULL)
  int nbWordsFound = 0;
  // Loop for 30 seconds to allow profiling
  while (!TimeToStop(inputValues, t1, counter)) {
    /* Create dictionary */
    // This is done to ensure we reload words at every cycle
    // File read is somewhat important for profiling
#ifdef __APPLE__
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0) {
      std::cerr << "Failure to write exe path" << std::endl;
      exit(1);
    }
    std::filesystem::path exe = std::filesystem::canonical(path);
#else
    std::filesystem::path exe = std::filesystem::canonical("/proc/self/exe");
#endif
    std::filesystem::path dataPath = exe.remove_filename();

    dataPath /= "../data";
    dataPath /= "words_reduced.txt";
    std::ifstream fs(dataPath);
    if (!fs.good()) {
      std::cerr << "Could not find data for words in " << dataPath << std::endl;
      std::cerr << "Check install / build config" << std::endl;
      exit(1);
    }
    tng::WordDict words(fs);

    /* Create grid : todo a better create function would make it more likely
     * to find words */
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

  do_crash(inputValues._crash_type);
  return 0;
}
} // namespace tng

int main(int argc, char *argv[]) { return tng::main(argc, argv); }
