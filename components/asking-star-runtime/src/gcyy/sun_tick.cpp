#include "asking_star/gcyy/sun_tick.hpp"

#include <sstream>

namespace asking_star::gcyy {

std::string SunTick::debug_dump() const {
  std::ostringstream out;
  out << "SunTick{id=" << tick_id << ", epoch=" << epoch
      << ", trace=" << trace_id << "}";
  return out.str();
}

}  // namespace asking_star::gcyy

