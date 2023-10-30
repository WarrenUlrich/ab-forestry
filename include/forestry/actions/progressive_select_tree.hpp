#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"
#include "../tree_type.hpp"

namespace forestry {
class progressive_select_tree
    : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    if (!Mainscreen::IsLoggedIn())
      return -1.0;

    if (ws.selected_tree_type.has_value())
      return -1.0;

    return 1.0;
  }

  void execute(base_state &ws) override {
    std::cout << "Selecting tree... ";
    const auto wc_level =
        Stats::GetRealLevel(Stats::WOODCUTTING);
    std::optional<tree_type> selected;
    for (const auto &tree_ref : tree_type::types) {
      const auto &tree = tree_ref.get();
      if (tree.required_level > wc_level)
        continue;

      if (!selected ||
          selected->required_level < tree.required_level)
        selected = tree;
    }

    if (selected.has_value()) {
      std::cout << "Selected: " << selected->name << '\n';
      ws.selected_tree_type = selected.value();
    }
  }
};
} // namespace forestry