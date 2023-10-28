#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"

namespace forestry {
class navigate_to_tree : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    return 0.5;
  }

  void execute(base_state &ws) override {
    std::cout << "Navigating to tree... ";
  }
};
} // namespace combat