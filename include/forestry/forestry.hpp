#pragma once

#include <util-ai/util-ai.hpp>

#include "base_state.hpp"

#include "axe.hpp"
#include "tree_instance.hpp"
#include "tree_type.hpp"

#include "actions/chop_tree.hpp"
#include "actions/drop_logs.hpp"
#include "actions/find_axe_bank.hpp"
#include "actions/locate_tree.hpp"
#include "actions/idle.hpp"
#include "actions/login.hpp"
#include "actions/navigate_to_tree.hpp"
#include "actions/progressive_select_tree.hpp"

namespace forestry {
template <State WorldState, typename ChopTree = chop_tree,
          typename SelectTree = progressive_select_tree,
          typename LocateTree = locate_tree,
          typename ManageInventory = drop_logs,
          typename FindAxe = find_axe_bank,
          typename Navigate = navigate_to_tree>
class agent
    : public util_ai::agent<
          WorldState, util_ai::base_action<WorldState>> {
public:
  agent() {
    add_action(std::make_unique<ChopTree>());
    add_action(std::make_unique<SelectTree>());
    add_action(std::make_unique<LocateTree>());
    add_action(std::make_unique<ManageInventory>());
    add_action(std::make_unique<FindAxe>());
    add_action(std::make_unique<Navigate>());
  }
};
} // namespace forestry