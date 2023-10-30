#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"

namespace forestry {
class drop_logs : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    return -1.0;
  }

  void execute(base_state &ws) override {
    std::cout << "Dropping logs... ";
  }
};
} // namespace combat