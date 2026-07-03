#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/gcyy/digital_set_fragment.hpp"
#include "asking_star/gcyy/gcyy_result.hpp"
#include "asking_star/v56/sky/app_intent_record.hpp"
#include "asking_star/walker/walker_runtime.hpp"

#include <string>

namespace asking_star::v56::sky {

struct SkyIngressResult {
  AppIntentRecord intent;
  gcyy::DigitalSetFragment fragment;
  v5::DigitalSetRefRecord fragment_ref;

  [[nodiscard]] bool is_valid() const;
};

class SkyIngress {
 public:
  [[nodiscard]] gcyy::GcyyResult accept_command(
      const std::string& command,
      const std::string& trace_id,
      SkyIngressResult& out_result) const;

 private:
  walker::WalkerRuntime walker_;
};

}  // namespace asking_star::v56::sky

