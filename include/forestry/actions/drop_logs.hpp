#pragma once

#include <regex>

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"
#include "../constants.hpp"

namespace forestry {
class drop_logs : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    if (!Mainscreen::IsLoggedIn())
      return -1.0;

    if (!Inventory::IsFull())
      return -1.0;

    if (!Inventory::ContainsAny(log_names))
      return -1.0;

    return 1.0;
  }

  void execute(base_state &ws) override {
    std::cout << "Dropping logs... ";

    const auto logs = Inventory::GetItems(log_names);
    if (logs.empty())
      return;

    for (const auto &log : logs) {
      Inventory::Drop(log);
    }

    std::cout << "Done.\n";
  }
};
} // namespace forestry