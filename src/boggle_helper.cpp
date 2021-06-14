#include "boggle_helper.h"

namespace tng {
namespace Boggle {
std::ostream &operator<<(std::ostream &os, const Pos &pos) {
  os << pos[0] << " " << pos[1] << std::endl;
  return os;
}
} // namespace Boggle
} // namespace tng
