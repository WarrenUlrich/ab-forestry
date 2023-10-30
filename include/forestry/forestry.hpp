#pragma once

#include <memory>

#include <util-ai/util-ai.hpp>

#include "base_state.hpp"

#include "axe.hpp"
#include "tree_location.hpp"
#include "tree_type.hpp"

#include "actions/login.hpp"
#include "actions/chop_tree.hpp"
#include "actions/drop_logs.hpp"
#include "actions/find_axe_bank.hpp"
#include "actions/locate_tree.hpp"
#include "actions/idle.hpp"
#include "actions/login.hpp"
#include "actions/progressive_select_tree.hpp"
#include "actions/burn_logs.hpp"

namespace forestry {
template <State WorldState = base_state, 
          typename Login = login,
          typename ChopTree = chop_tree,
          typename SelectTree = progressive_select_tree,
          typename LocateTree = locate_tree,
          typename ManageInventory = drop_logs,
          typename GrabEquipment = find_axe_bank>
class agent
    : public util_ai::agent<
          WorldState, util_ai::base_action<WorldState>> {
public:
  agent() {
    this->add_action(std::make_unique<idle>());
    this->add_action(std::make_unique<Login>());
    this->add_action(std::make_unique<ChopTree>());
    this->add_action(std::make_unique<SelectTree>());
    this->add_action(std::make_unique<LocateTree>());
    this->add_action(std::make_unique<ManageInventory>());
    this->add_action(std::make_unique<GrabEquipment>());
  }
};

} // namespace forestry