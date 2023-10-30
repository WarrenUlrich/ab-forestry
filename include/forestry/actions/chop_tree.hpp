#pragma once

#include <Game/Core.hpp>

#include <util-ai/util-ai.hpp>

#include "../base_state.hpp"

namespace forestry {
class chop_tree : public util_ai::base_action<base_state> {
public:
  double utility(const base_state &ws) override {
    if (!Mainscreen::IsLoggedIn())
      return -1.0;

    if (!ws.current_axe.has_value())
      return -1.0;

    if (!(ws.current_axe->in_inventory() ||
          ws.current_axe->equipped()))
      return -1.0;

    if (!ws.selected_tree_type.has_value())
      return -1.0;

    if (!ws.tree_cluster.has_value())
      return -1.0;

    return 1.0;
  }

  void execute(base_state &ws) override {
    std::cout << "Chopping tree... ";
    
    std::cout << "Success.\n";
  }
};
} // namespace forestry