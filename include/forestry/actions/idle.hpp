#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"

namespace forestry {
class idle : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    return 0.25;
  }

  void execute(base_state &ws) override {
    std::cout << "Idling...\n";
    if (Internal::GetFocused())
      Antiban::MouseOffClient(true);
  }
};
} // namespace combat